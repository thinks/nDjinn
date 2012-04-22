//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_SHADER_PROGRAM_HPP_INCLUDED
#define NDJINN_SHADER_PROGRAM_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include "nDjinnShader.hpp"
#include <gl/glew.h>
#include <string>
#include <map>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

//! DOCS
class ShaderProgram
{
public:

    //! POD
    struct Attrib
    {
        GLenum type;
        GLint  size;
        GLint  location;
    };

    //! POD
    struct Uniform
    {
        GLenum type;
        GLint  size;
        GLint  location;
    };

    typedef std::map<std::string, Attrib>  AttribMap;
    typedef std::map<std::string, Uniform> UniformMap;

public:

    explicit
    ShaderProgram();

    ~ShaderProgram();

public:

    void
    bind() const;

    void
    release() const;

    void
    attachShader(const Shader &sh);
    
    void
    detachShader(const Shader &sh);

    void
    link();

    const std::string&
    infoLog() const;

public:

    const Uniform*
    queryActiveUniform(const std::string &name) const;

    const Attrib*
    queryActiveAttrib(const std::string &name) const;

private:

    static void
    _getActiveUniforms(GLuint program, UniformMap &uniforms);

    static void
    _getActiveAttribs(GLuint program, AttribMap &attribs);

    static void
    _getInfoLog(GLuint program, std::string &infoLog);

private:    // OpenGL wrappers.

    static GLuint
    _createProgram();

    static void
    _deleteProgram(GLuint program);

    static void
    _useProgram(GLuint program);

    static void
    _attachShader(GLuint program, GLuint shader);

    static void
    _detachShader(GLuint program, GLuint shader);

    static void
    _linkProgram(GLuint program);

    static void
    _validateProgram(GLuint program);

    static GLboolean
    _isProgram(GLuint program);

    static void
    _getActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, 
                     GLsizei *length, GLint *size, GLenum *type, GLchar *name);

    static GLint
    _getAttribLocation(GLuint program, const GLchar *name);

    static void
    _getActiveUniform(GLuint program, GLuint index, GLsizei bufSize, 
                      GLsizei *length, GLint *size, GLenum *type, 
                      GLchar *name);

    static GLint
    _getUniformLocation(GLuint program, const GLchar *name);

    static void
    _getProgramiv(GLuint program, GLenum pname, GLint *params);

    static void
    _getProgramInfoLog(GLuint program, GLsizei bufSize,
                       GLsizei *length, GLchar *infoLog);

private:        // Member variables.

    GLuint      _handle;      //!< Resource handle.
    std::string _infoLog;
    AttribMap   _attribs;
    UniformMap  _uniforms;    
};

// -----------------------------------------------------------------------------

//! CTOR.
inline
ShaderProgram::ShaderProgram()
    : _handle(0)
{
    try {
        _handle = _createProgram();    // May throw.
        if (_handle == 0) {
            NDJINN_THROW("Invalid shader program handle");
        }
    }
    catch (...) {
        _deleteProgram(_handle);       // TODO: May throw!?
        throw;                         // Re-throw.
    }
}


//! DTOR.
inline
ShaderProgram::~ShaderProgram()
{ 
    try { _deleteProgram(_handle); }
    catch (...) {}
}

// -----------------------------------------------------------------------------

//! Enable shader program.
inline void
ShaderProgram::bind() const
{ 
    _useProgram(_handle); // May throw. 
} 


//! Disabled shader program.
inline void
ShaderProgram::release() const
{ 
    _useProgram(0); // May throw. 
} 


//! Attach a shader to this shader program.
inline void
ShaderProgram::attachShader(const Shader &sh) 
{ 
    _attachShader(_handle, sh.handle()); // May throw.
} 
    

//! Detach a shader from this shader program.
inline void
ShaderProgram::detachShader(const Shader &sh)
{ 
    _detachShader(_handle, sh.handle()); // May throw.
} 


//! Link shader program.
inline void
ShaderProgram::link()
{ 
    _linkProgram(_handle);             // May throw.
    _getInfoLog(_handle, _infoLog);    // May throw.
    GLint linkStatus = GL_FALSE;
    _getProgramiv(_handle, GL_LINK_STATUS, &linkStatus); // May throw.
    if (linkStatus == GL_FALSE) {
        NDJINN_THROW("Shader program link error: " 
                     << _handle << ": " << _infoLog);
    }

    _validateProgram(_handle);
    GLint validateStatus = GL_FALSE;
    _getProgramiv(_handle, GL_VALIDATE_STATUS, &validateStatus); 
    if (validateStatus == GL_FALSE) {
        NDJINN_THROW("Shader program validation error: " 
                     << _handle << ": " << _infoLog);
    }

    // Successful link and validation. Now get some info about the shader.

    _getActiveUniforms(_handle, _uniforms);
    _getActiveAttribs(_handle, _attribs);
}


//! Returns info log.
inline const std::string&
ShaderProgram::infoLog() const
{ 
    return _infoLog; 
}

// -----------------------------------------------------------------------------

//! May return null.
inline const ShaderProgram::Uniform*
ShaderProgram::queryActiveUniform(const std::string &name) const 
{
    const Uniform *uni = 0;
    const UniformMap::const_iterator iter = _uniforms.find(name);
    if (iter != _uniforms.end()) {
        uni = &iter->second;
    }
    return uni;
}


//! May return null.
inline const ShaderProgram::Attrib*
ShaderProgram::queryActiveAttrib(const std::string &name) const 
{
    const Attrib *attr = 0;
    const AttribMap::const_iterator iter = _attribs.find(name);
    if (iter != _attribs.end()) {
        attr = &iter->second;
    }
    return attr;
}

// -----------------------------------------------------------------------------

//! Grab info about active uniforms from OpenGL. [static]
inline void
ShaderProgram::_getActiveUniforms(const GLuint program, UniformMap &uniforms)
{
    uniforms.clear();
    GLint activeUniforms = 0;
    _getProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms);
    GLint activeUniformMaxLength = 0; 
    _getProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, 
                    &activeUniformMaxLength);
    for (GLint i = 0; i < activeUniforms; ++i) {
        std::string name;            
        name.resize(activeUniformMaxLength);
        GLsizei length = 0;
        Uniform uni;
        _getActiveUniform(
            program,
            static_cast<GLuint>(i),
            activeUniformMaxLength,
            &length,                // Exluding null-termination!
            &uni.size,
            &uni.type,
            &name[0]);              // May throw.
        name.resize(length);
        uni.location = 
            _getUniformLocation(program, name.c_str()); // May throw.
        uniforms.insert(UniformMap::value_type(name, uni));
    }
}


//! Grab info about active attribs from OpenGL. [static]
inline void
ShaderProgram::_getActiveAttribs(const GLuint program, AttribMap &attribs)
{
    attribs.clear();
    GLint activeAttributes = 0;
    _getProgramiv(program, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
    GLint activeAttributeMaxLength = 0; 
    _getProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, 
                    &activeAttributeMaxLength );
    for (GLint i = 0; i < activeAttributes; ++i) {
        std::string name;
        name.resize(activeAttributeMaxLength);
        GLsizei length = 0;
        Attrib attr;
        _getActiveAttrib(
            program, 
            static_cast<GLuint>(i), 
            activeAttributeMaxLength,
            &length,             // Excluding null-termination!
            &attr.size,
            &attr.type,
            &name[0]);
        name.resize(length);
        attr.location = 
            _getAttribLocation(program, name.c_str()); // May throw.
        attribs.insert(AttribMap::value_type(name, attr));
    }
}


//! Grab info log from OpenGL. [static]
inline void
ShaderProgram::_getInfoLog(const GLuint program, std::string &infoLog)
{
    GLint maxLength = 0;
    _getProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    if (maxLength > 0) {
        // Info exists. The returned string is null-terminated.

        infoLog.clear();
        infoLog.resize(maxLength);
        GLsizei logLength = 0; 
        _getProgramInfoLog(program, 
                            static_cast<GLsizei>(maxLength),
                            &logLength, // Excluding null-termination!
                            &infoLog[0]); // Null-terminated.
        infoLog.resize(logLength + 1);
    }
}

// -----------------------------------------------------------------------------

//! glCreateProgram wrapper. May throw. [static]
inline GLuint
ShaderProgram::_createProgram()
{ 
    const GLuint program = glCreateProgram();
    Error::check("glCreateProgram"); // May throw;
    return program; 
}


//! glDeleteProgram wrapper. May throw. [static]
inline void
ShaderProgram::_deleteProgram(const GLuint program)
{ 
    glDeleteProgram(program); 
    Error::check("glDeleteProgram"); // May throw;
}


//! glUseProgram wrapper. May throw. [static]
inline void
ShaderProgram::_useProgram(const GLuint program)
{ 
    glUseProgram(program); 
    Error::check("glUseProgram"); // May throw;
}


//! glAttachShader wrapper. May throw. [static]
inline void
ShaderProgram::_attachShader(const GLuint program, const GLuint shader)
{ 
    glAttachShader(program, shader); 
    Error::check("glAttachShader"); // May throw;
}


//! glDetachShader wrapper. May throw. [static]
inline void
ShaderProgram::_detachShader(const GLuint program, const GLuint shader)
{ 
    glDetachShader(program, shader); 
    Error::check("glDetachShader"); // May throw;
}


//! glLinkProgram wrapper. May throw. [static]
inline void
ShaderProgram::_linkProgram(const GLuint program)
{ 
    glLinkProgram(program); 
    Error::check("glLinkProgram"); // May throw;
}


//! glValidateProgram wrapper. May throw. [static]
inline void
ShaderProgram::_validateProgram(const GLuint program)
{ 
    glValidateProgram(program); 
    Error::check("glValidateProgram"); // May throw;
}


//! glIsProgram wrapper. May throw. [static]
inline GLboolean
ShaderProgram::_isProgram(const GLuint program)
{
    const GLboolean isProgram = glIsProgram(program);
    Error::check("glIsProgram"); // May throw;
    return isProgram;
}


//! glGetActiveAttrib wrapper. May throw. [static]
inline void
ShaderProgram::_getActiveAttrib(const GLuint   program, 
                                const GLuint   index,
                                const GLsizei  bufSize, 
                                GLsizei       *length, 
                                GLint         *size,
                                GLenum        *type, 
                                GLchar        *name)
{ 
    glGetActiveAttrib(program, index, bufSize, length, size, type, name); 
    Error::check("glGetActiveAttrib"); // May throw;
}


//! glGetAttriLocation wrapper. May throw. [static]
inline GLint
ShaderProgram::_getAttribLocation(const GLuint program, const GLchar *name)
{ 
    GLint loc = glGetAttribLocation(program, name); 
    Error::check("glGetAttribLocation"); // May throw;
    return loc;
}


//! glGetActiveUniform wrapper. May throw. [static]
inline void
ShaderProgram::_getActiveUniform(const GLuint   program, 
                                 const GLuint   index,
                                 const GLsizei  bufSize, 
                                 GLsizei       *length, 
                                 GLint         *size,
                                 GLenum        *type, 
                                 GLchar        *name)
{ 
    glGetActiveUniform(program, index, bufSize, length, size, type, name); 
    Error::check("glGetActiveUniform"); // May throw;    
}


//! glGetUniformLocation wrapper. May throw. [static]
inline GLint
ShaderProgram::_getUniformLocation(const GLuint program, const GLchar *name)
{
    GLint loc = glGetUniformLocation(program, name);
    Error::check("glGetUniformLocation"); // May throw;
    return loc; 
}


//! glGetProgramiv wrapper. May throw. [static]
inline void
ShaderProgram::_getProgramiv(const GLuint  program, 
                             const GLenum  pname, 
                             GLint		  *params)
{ 
    glGetProgramiv(program, pname, params); 
    Error::check("glGetProgramiv"); // May throw;
}


//! glGetProgramInfoLog wrapper. May throw. [static]
inline void
ShaderProgram::_getProgramInfoLog(const GLuint   program, 
                                  const GLsizei  bufSize,
                                  GLsizei	    *length, 
                                  GLchar	    *infoLog)
{ 
    glGetProgramInfoLog(program, bufSize, length, infoLog); 
    Error::check("glGetProgramInfoLog"); // May throw;
}

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif // NDJINN_SHADER_PROGRAM_HPP_INCLUDED
