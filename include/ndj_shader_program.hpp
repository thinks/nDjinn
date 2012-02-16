//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_SHADER_PROGRAM_HPP_INCLUDED
#define NDJ_SHADER_PROGRAM_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>
#include <string>
#include <map>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

// shader_program
// --------------
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

    typedef std::map<std::string, attrib>  AttribMap;
    typedef std::map<std::string, uniform> UniformMap;

public:     // Interface

    //! CTOR.
    explicit
    ShaderProgram()
        : _handle(0)
    {
        try {
            _handle = _createProgram();    // May throw.
            if (_handle == 0) {
                NDJINN_THROW("Invalid Shader program handle");
            }
        }
        catch (...) {
            _deleteProgram(_handle);       // TODO: May throw!?
            throw;                          // Re-throw.
        }
    }

    //! DTOR.
    ~shader_program()
    { 
        try {
            _deleteProgram(_handle);   // May throw.
        }
        catch (...) {
        }
    }

public:

    void
    bind() const
    { _useProgram(_handle); } // May throw.

    void
    release() const
    { _useProgram(0); } // May throw.

    void
    attachShader(const shader &sh) 
    { _attachShader(_handle, sh.handle()); } // May throw.
    
    void
    detachShader(const shader &sh)
    { _detachShader(_handle, sh.handle()); } // May throw.

    void
    link()
    { 
        _linkProgram(_handle);             // May throw.
        _getInfoLog(_handle, _infoLog);    // May throw.
        GLint linkStatus = GL_FALSE;
        _getProgramiv(_handle, GL_LINK_STATUS, &linkStatus); // May throw.
        if (linkStatus == GL_FALSE) {
            NDJINN_THROW("Shader program link error: " 
                         << _handle << ": " << _infoLog);
        }

        _validate_program(_handle);
        GLint validateStatus = GL_FALSE;
        _getProgramiv(_handle, GL_VALIDATE_STATUS, &validateStatus); 
        if (validate_status == GL_FALSE) {
            NDJINN_THROW("Shader program validation error: " 
                            << _handle << ": " << _info_log);
        }

        _getActiveUniforms(_handle, _uniforms);
        _getActiveAttribs(_handle, _attribs);
    }

    const std::string&
    infoLog() const
    { return _info_log; }

public:

    const uniform*
    queryActiveUniform(const std::string &name) const 
    {
        const uniform *uni = 0;
        const UniformMap::const_iterator iter =
            _uniforms.find(name);
        if (iter != _uniforms.end()) {
            uni = &iter->second;
        }
        return uni;
    }

    const attrib*
    query_active_attrib(const std::string &name) const 
    {
        const attrib *attr = 0;
        const _attrib_map_type::const_iterator iter =
            _attribs.find(name);
        if (iter != _attribs.end()) {
            attr = &iter->second;
        }
        return attr;
    }

private:

    //! Grab info about active uniforms from OpenGL.
    static void
    _getActiveUniforms(const GLuint program, UniformMap &uniforms)
    {
        uniforms.clear();
        GLint activeUniforms = 0;
        _getProgramiv(program, GL_ACTIVE_UNIFORMS, &active_uniforms);
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

    //! Grab info about active attribs from OpenGL.
    static void
    _getActiveAttribs(const GLuint program, AttribMap &attribs)
    {
        attribs.clear();
        GLint activeAttributes = 0;
        _get_program_iv(program, GL_ACTIVE_ATTRIBUTES, &active_attributes);
        GLint activeAttributeMaxLength = 0; 
        _get_program_iv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, 
                        &active_attribute_max_length );
        for (GLint i = 0; i < activeAttributes; ++i) {
            std::string name;
            name.resize(activeAttributeMaxLength);
            GLsizei length = 0;
            attrib attr;
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

    //! Grab info log from OpenGL.
    static void
    _getInfoLog(const GLuint program, std::string &infoLog)
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
            info_log.resize(log_length + 1);
        }
    }

private:    // OpenGL wrappers.

    //! glCreateProgram wrapper. May throw.
    static GLuint
    _createProgram()
    { 
        const GLuint program = glCreateProgram();
        Error::check("glCreateProgram"); // May throw;
        return program; 
    }

    //! glDeleteProgram wrapper. May throw.
    static void
    _deleteProgram(const GLuint program)
    { 
        glDeleteProgram(program); 
        Error::check("glDeleteProgram"); // May throw;
    }

    //! glUseProgram wrapper. May throw.
    static void
    _useProgram(const GLuint program)
    { 
        glUseProgram(program); 
        Error::check("glUseProgram"); // May throw;
    }

    //! glAttachShader wrapper. May throw.
    static void
    _attachShader(const GLuint program, const GLuint shader)
    { 
        glAttachShader(program, shader); 
        Error::check("glAttachShader"); // May throw;
    }

    //! glDetachShader wrapper. May throw.
    static void
    _detachShader(const GLuint program, const GLuint shader)
    { 
        glDetachShader(program, shader); 
        Error::check("glDetachShader"); // May throw;
    }

    //! glLinkProgram wrapper. May throw.
    static void
    _linkProgram(const GLuint program)
    { 
        glLinkProgram(program); 
        Error::check("glLinkProgram"); // May throw;
    }

    //! glValidateProgram wrapper. May throw.
    static void
    _validateProgram(const GLuint program)
    { 
        glValidateProgram(program); 
        Error::check("glValidateProgram"); // May throw;
    }

    //! glIsProgram wrapper. May throw.
    static GLboolean
    _isProgram(const GLuint program)
    {
        const GLboolean isProgram = glIsProgram(program);
        Error::check("glIsProgram"); // May throw;
        return isProgram;
    }

    //! glGetActiveAttrib wrapper. May throw.
    static void
    _getActiveAttrib(const GLuint program, const GLuint index,
                     const GLsizei bufSize, GLsizei *length, GLint *size,
                     GLenum *type, GLchar *name)
    { 
        glGetActiveAttrib(program, index, bufSize, length, size, type, name); 
        Error::check("glGetActiveAttrib"); // May throw;
    }

    //! glGetAttriLocation wrapper. May throw.
    static GLint
    _get_attrib_location(const GLuint program, const GLchar *name)
    { 
        GLint loc = glGetAttribLocation(program, name); 
        Error::check("glGetAttribLocation"); // May throw;
        return loc;
    }

    //! glGetActiveUniform wrapper. May throw.
    static void
    _getActiveUniform(const GLuint program, const GLuint index,
                      const GLsizei bufSize, GLsizei *length, GLint *size,
                      GLenum *type, GLchar *name)
    { 
        glGetActiveUniform(program, index, bufSize, length, size, type, name); 
        Error::check("glGetActiveUniform"); // May throw;    
    }

    //! glGetUniformLocation wrapper. May throw.
    static GLint
    _getUniformLocation(const GLuint program, const GLchar *name)
    {
        GLint loc = glGetUniformLocation(program, name);
        Error::check("glGetUniformLocation"); // May throw;
        return loc; 
    }

    //! glGetProgramiv wrapper. May throw.
    static void
    _getProgramiv(const GLuint program, const GLenum pname, GLint *params)
    { 
        glGetProgramiv(program, pname, params); 
        Error::check("glGetProgramiv"); // May throw;
    }

    //! glGetProgramInfoLog wrapper. May throw.
    static void
    _getProgramInfoLog(const GLuint program, const GLsizei bufSize,
                       GLsizei *length, GLchar *infoLog)
    { 
        glGetProgramInfoLog(program, bufSize, length, infoLog); 
        Error::check("glGetProgramInfoLog"); // May throw;
    }

private:        // Member variables.

    GLuint      _handle;      //!< Resource handle.
    std::string _info_log;
    AttribMap   _attribs;
    UniformMap  _uniforms;    
};

// -----------------------------------------------------------------------------

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif // NDJ_SHADER_PROGRAM_HPP_INCLUDED
