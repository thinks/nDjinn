//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_SHADER_HPP_INCLUDED
#define NDJ_SHADER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

class Shader
{
public:

    //! CTOR.
    explicit
    Shader(const GLenum type)
        : _handle(0)
    {
        try {
            _handle = _createShader(type); // May throw.
            if (_handle == 0) {
                NDJINN_THROW("Invalid Shader handle");
            }
        }
        catch (...) {
            _deleteShader(_handle);        // TODO: May throw!?
            throw;                          // Re-throw.
        }
    }

    //! DTOR. Free handle resource.
    ~Shader()
    { 
        try {
            _deleteShader(_handle);    // May throw.
        }
        catch (...) {
        }
    }

    GLuint 
    handle() const 
    { return _handle; }

    void
    source(const GLsizei   count, 
           const GLchar  **string,
           const GLint    *length)
    { _shaderSource(_handle, count, string, length); } // May throw.

    void
    compile()
    {
        _compileShader(_handle); // May throw.
        _fetchInfoLog(_handle, _infoLog); // May throw.
        GLint compileStatus = GL_FALSE;
        _getShaderiv(_handle, GL_COMPILE_STATUS, &compileStatus); // May throw.
        if (compileStatus == GL_FALSE) {                          
            NDJINN_THROW("Shader compile error: " << _handle << ": " << _infoLog);
        }
    }

    GLenum
    type() const
    { 
        GLint params;
        _getShaderiv(_handle, GL_SHADER_TYPE, &params);
        return static_cast<GLenum>(params);
    }

    const std::string&
    infoLog() const
    { return _infoLog; }

private:

    static void
    _getInfoLog(const GLuint shader, std::string &infoLog)
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
            info_log.resize(logLength + 1);
        }
    }

private:    // OpenGL wrappers.

    //! glCreateShader wrapper. May throw.
    static GLuint
    _createShader(const GLenum type)
    {
        const GLuint shader = glCreateShader(type);
        Error::check("glCreateShader"); // May throw;
        return shader; 
    }

    //! glDeleteShader wrapper. May throw.
    static void
    _deleteShader(const GLuint shader)
    { 
        glDeleteShader(shader); 
        Error::check("glDeleteShader"); // May throw;
    }

    //! glIsShader wrapper. May throw.
    static GLboolean
    _isShader(const GLuint shader)
    {
        const GLboolean isShader = glIsShader(shader);
        Error::check("glIsShader");    // May throw;
        return isShader; 
    }

    //! glShaderSource wrapper. May throw.
    static void
    _shaderSource(const GLuint    shader,
                  const GLsizei   count, 
                  const GLchar  **string, 
                  const GLint    *length)
    { 
        glShaderSource(shader, count, string, length); 
        Error::check("glShaderSource"); // May throw;
    }

    //! glCompileShader wrapper. May throw.
    static void
    _compileShader(const GLuint shader)
    { 
        glCompileShader(shader); 
        Error::check("glCompileShader"); // May throw;
    }

    //! glGetShaderInfoLog wrapper. May throw.
    static void 
    _getShaderInfoLog(const GLuint   shader,
                      const GLsizei  bufSize, 
                      GLsizei       *length, 
                      GLchar        *infoLog)
    { 
        glGetShaderInfoLog(shader, bufSize, length, infoLog); 
        Error::check("glGetShaderInfoLog"); // May throw;
    }

    //! glGetShaderiv wrapper. May throw.
    static void
    _getShaderiv(const GLuint shader, const GLenum pname, GLint *params)
    { 
        glGetShaderiv(shader, pname, params); 
        Error::check("glGetShaderiv"); // May throw;
    }

private:

    Shader(const Shader&);            //!< Disable copy CTOR.
    Shader& operator=(const Shader&); //!< Disable assign.

private:    // Member variables.

    GLuint      _handle;    //!< Resource handle.
    std::string _info_log;
};

// -----------------------------------------------------------------------------

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif // NDJ_SHADER_HPP_INCLUDED
