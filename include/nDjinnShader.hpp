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

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glCreateShader wrapper. May throw. 
inline GLuint
createShader(const GLenum type) {
  const GLuint shader = glCreateShader(type);
  checkError("glCreateShader");
  return shader; 
}

//! glDeleteShader wrapper. May throw. 
inline void
deleteShader(const GLuint shader) { 
  glDeleteShader(shader); 
  checkError("glDeleteShader");
}

//! glIsShader wrapper. May throw.
inline GLboolean
isShader(const GLuint shader) {
  const GLboolean isShader = glIsShader(shader);
  checkError("glIsShader");
  return isShader; 
}

//! glShaderSource wrapper. May throw.
inline void
shaderSource(const GLuint shader,
             const GLsizei count, 
             const GLchar **string, 
             const GLint *length) { 
  glShaderSource(shader, count, string, length); 
  checkError("glShaderSource");
}

//! glCompileShader wrapper. May throw. 
inline void
compileShader(const GLuint shader) { 
  glCompileShader(shader); 
  checkError("glCompileShader");
}

//! glGetShaderInfoLog wrapper. May throw.
inline void 
getShaderInfoLog(const GLuint shader,
                 const GLsizei bufSize, 
                 GLsizei *length, 
                 GLchar  *infoLog) { 
  glGetShaderInfoLog(shader, bufSize, length, infoLog); 
  checkError("glGetShaderInfoLog");
}

//! glGetShaderiv wrapper. May throw.
inline void
getShaderiv(const GLuint shader, const GLenum pname, GLint *params) { 
  glGetShaderiv(shader, pname, params); 
  checkError("glGetShaderiv"); 
}

//! Retrieve info log. May throw.
inline void
getShaderInfoLog(const GLuint shader, std::string &infoLog) {
  GLint maxLength = 0;
  getShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength); 
  if (maxLength > 0) { // Info exists. 
    infoLog.clear();
    infoLog.resize(maxLength);
    GLsizei logLength = 0;
    getShaderInfoLog(shader, 
                     static_cast<GLsizei>(maxLength),
                     &logLength,   // Excluding null-termination.
                     &infoLog[0]); // Null-terminated.
    infoLog.resize(logLength + 1); // Trim.
  }
}

} // Namespace: detail.

//------------------------------------------------------------------------------

//! DOCS
class Shader
{
public:

    explicit Shader(GLenum type);
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
  Shader(const Shader&);            //!< Disable copy CTOR.
  Shader& operator=(const Shader&); //!< Disable assign.

private: // Member variables.
  GLuint _handle; //!< Resource handle.
  std::string _infoLog;
};

// -----------------------------------------------------------------------------

//! CTOR. May throw.
inline
Shader::Shader(const GLenum type)
  : _handle(0)
{
  _handle = detail::createShader(type);
  if (_handle == 0) {
    NDJINN_THROW("Invalid shader handle");
  }
}

//! DTOR. Free handle resource.
inline 
Shader::~Shader() { 
  try {
    detail::deleteShader(_handle);
  }
  catch (...) {
  }
}

// -----------------------------------------------------------------------------

//! DOCS
inline GLuint 
Shader::handle() const { 
  return _handle; 
}

//! DOCS. May throw.
inline void
Shader::source(const GLsizei count, 
               const GLchar **string, 
               const GLint *length) { 
  detail::shaderSource(_handle, count, string, length);
} 

//! Compile shader from previously set source. May throw.
inline void
Shader::compile() {
  detail::compileShader(_handle); 
  detail::getShaderInfoLog(_handle, _infoLog); 
  GLint compileStatus = GL_FALSE;
  detail::getShaderiv(_handle, GL_COMPILE_STATUS, &compileStatus);
  if (compileStatus != GL_TRUE) {                          
    NDJINN_THROW("Shader compile error: " << _handle << ": " << _infoLog);
  }
}

//! Shader type.
inline GLenum
Shader::type() const { 
  GLint params;
  detail::getShaderiv(_handle, GL_SHADER_TYPE, &params);
  return static_cast<GLenum>(params);
}

//! Return info log. May be empty.
inline const std::string&
Shader::infoLog() const { 
  return _infoLog; 
}

NDJINN_END_NAMESPACE

#endif // NDJINN_SHADER_HPP_INCLUDED
