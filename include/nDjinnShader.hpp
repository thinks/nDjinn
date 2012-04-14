//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_SHADER_HPP_INCLUDED
#define NDJINN_SHADER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>
#include <string>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

//! DOCS
class Shader
{
public:

    explicit
    Shader(GLenum type);

    ~Shader();

public:

    GLuint 
    handle() const;

    void
    source(GLsizei count, const GLchar **string, const GLint *length);

    void
    compile();

    GLenum
    type() const;

    const std::string&
    infoLog() const;

private:

    static void
    _getInfoLog(const GLuint shader, std::string &infoLog);

private:    // OpenGL wrappers.

    static GLuint
    _createShader(GLenum type);

    static void
    _deleteShader(GLuint shader);

    static GLboolean
    _isShader(GLuint shader);

    static void
    _shaderSource(GLuint shader, GLsizei count, 
                  const GLchar **string, const GLint *length);

    static void
    _compileShader(GLuint shader);

    static void 
    _getShaderInfoLog(GLuint shader, GLsizei bufSize, 
                      GLsizei *length, GLchar *infoLog);

    static void
    _getShaderiv(GLuint shader, GLenum pname, GLint *params);

private:

    Shader(const Shader&);            //!< Disable copy CTOR.
    Shader& operator=(const Shader&); //!< Disable assign.

private:    // Member variables.

    GLuint      _handle;    //!< Resource handle.
    std::string _info_log;
};

// -----------------------------------------------------------------------------

//! CTOR.
inline
Shader::Shader(const GLenum type)
    : _handle(0)
{
    try {
        _handle = _createShader(type); // May throw.
        if (_handle == 0) {
            NDJINN_THROW("Invalid shader handle");
        }
    }
    catch (...) {
        _deleteShader(_handle);        // TODO: May throw!?
        throw;                          // Re-throw.
    }
}


//! DTOR. Free handle resource.
inline 
Shader::~Shader()
{ 
    try {
        _deleteShader(_handle);    // May throw.
    }
    catch (...) {
    }
}

// -----------------------------------------------------------------------------

//! DOCS
inline GLuint 
Shader::handle() const 
{ 
    return _handle; 
}


//! DOCS
inline void
Shader::source(const GLsizei count, const GLchar **string, const GLint *length)
{ 
    _shaderSource(_handle, count, string, length); // May throw.
} 


//! Compile shader from previously set source.
inline void
Shader::compile()
{
    _compileShader(_handle); // May throw.
    _getInfoLog(_handle, _infoLog); // May throw.
    GLint compileStatus = GL_FALSE;
    _getShaderiv(_handle, GL_COMPILE_STATUS, &compileStatus); // May throw.
    if (compileStatus != GL_TRUE) {                          
        NDJINN_THROW("Shader compile error: " << 
                        _handle << ": " << _infoLog);
    }
}


//! Shader type.
inline GLenum
Shader::type() const
{ 
    GLint params;
    _getShaderiv(_handle, GL_SHADER_TYPE, &params);
    return static_cast<GLenum>(params);
}


//! Return info log. May be empty.
inline const std::string&
Shader::infoLog() const
{ 
    return _infoLog; 
}

// -----------------------------------------------------------------------------

//! Retrieve info log.
inline void
Shader::_getInfoLog(const GLuint shader, std::string &infoLog)
{
    GLint maxLength = 0;
    _getShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength); // May throw.
    if (max_length > 0) { // Info exists. 
        info_log.clear();
        info_log.resize(maxLength);
        GLsizei logLength = 0;
        _getShaderInfoLog(shader, 
                            static_cast<GLsizei>(maxLength),
                            &logLength,   // Excluding null-termination.
                            &infoLog[0]); // Null-terminated.
        info_log.resize(logLength + 1); // Trim.
    }
}

// -----------------------------------------------------------------------------

//! glCreateShader wrapper. May throw. [static]
inline GLuint
Shader::_createShader(const GLenum type)
{
    const GLuint shader = glCreateShader(type);
    Error::check("glCreateShader"); // May throw;
    return shader; 
}


//! glDeleteShader wrapper. May throw. [static]
inline void
Shader::_deleteShader(const GLuint shader)
{ 
    glDeleteShader(shader); 
    Error::check("glDeleteShader"); // May throw;
}


//! glIsShader wrapper. May throw. [static]
inline GLboolean
Shader::_isShader(const GLuint shader)
{
    const GLboolean isShader = glIsShader(shader);
    Error::check("glIsShader");    // May throw;
    return isShader; 
}


//! glShaderSource wrapper. May throw. [static]
inline void
Shader::_shaderSource(const GLuint    shader,
                      const GLsizei   count, 
                      const GLchar  **string, 
                      const GLint    *length)
{ 
    glShaderSource(shader, count, string, length); 
    Error::check("glShaderSource"); // May throw;
}


//! glCompileShader wrapper. May throw. [static]
inline void
Shader::_compileShader(const GLuint shader)
{ 
    glCompileShader(shader); 
    Error::check("glCompileShader"); // May throw;
}


//! glGetShaderInfoLog wrapper. May throw. [static]
inline void 
Shader::_getShaderInfoLog(const GLuint   shader,
                          const GLsizei  bufSize, 
                          GLsizei       *length, 
                          GLchar        *infoLog)
{ 
    glGetShaderInfoLog(shader, bufSize, length, infoLog); 
    Error::check("glGetShaderInfoLog"); // May throw;
}


//! glGetShaderiv wrapper. May throw. [static]
inline void
Shader::_getShaderiv(const GLuint shader, const GLenum pname, GLint *params)
{ 
    glGetShaderiv(shader, pname, params); 
    Error::check("glGetShaderiv"); // May throw;
}

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif // NDJINN_SHADER_HPP_INCLUDED
