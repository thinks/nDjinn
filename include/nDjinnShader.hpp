//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_SHADER_HPP_INCLUDED
#define NDJINN_SHADER_HPP_INCLUDED

#include <string>
#include <iostream>

#include "nDjinnError.hpp"
#include "nDjinnException.hpp"
#include "nDjinnGL.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glCreateShader wrapper. May throw. 
inline GLuint createShader(GLenum const type) {
  GLuint const shader = glCreateShader(type);
  checkError("glCreateShader");
  return shader; 
}

//! glDeleteShader wrapper. May throw. 
inline void deleteShader(GLuint const shader) {
  glDeleteShader(shader); 
  checkError("glDeleteShader");
}

//! glIsShader wrapper. May throw.
inline GLboolean isShader(GLuint const shader) {
  GLboolean const isShader = glIsShader(shader);
  checkError("glIsShader");
  return isShader; 
}

//! glShaderSource wrapper. May throw.
inline void shaderSource(GLuint const shader,
                         GLsizei const count,
                         GLchar const** string,
                         GLint const* length) {
  glShaderSource(shader, count, string, length); 
  checkError("glShaderSource");
}

//! glCompileShader wrapper. May throw. 
inline void compileShader(GLuint const shader) {
  glCompileShader(shader); 
  checkError("glCompileShader");
}

//! glGetShaderiv wrapper. May throw.
inline void getShaderiv(GLuint const shader,
                        GLenum const pname,
                        GLint *params) {
  glGetShaderiv(shader, pname, params);
  checkError("glGetShaderiv");
}

//! glGetShaderInfoLog wrapper. May throw.
inline void getShaderInfoLog(GLuint const shader,
                             GLsizei const bufSize,
                             GLsizei* length,
                             GLchar* infoLog) {
  glGetShaderInfoLog(shader, bufSize, length, infoLog); 
  checkError("glGetShaderInfoLog");
}

//! glGetShaderSource wrapper. May throw.
inline void getShaderSource(GLuint const shader,
                            GLsizei const bufSize,
                            GLsizei* length,
                            GLchar* source) {
  glGetShaderSource(shader, bufSize, length, source);
  checkError("glGetShaderSource"); 
}

inline std::string shaderTypeToString(GLenum const type) {
  using namespace std;

  switch (type) {
  case GL_VERTEX_SHADER:    return string("GL_VERTEX_SHADER");
  case GL_GEOMETRY_SHADER:  return string("GL_GEOMETRY_SHADER");
  case GL_FRAGMENT_SHADER:  return string("GL_FRAGMENT_SHADER");
  }
  NDJINN_THROW("unrecognized shader type: " << type);
}

//! Read shader source from file.
inline std::string readShaderFile(const std::string& filename) {
  using namespace std;

  string src;
  FILE *file = fopen(filename.c_str(), "rb");
  if (file == nullptr) {
    NDJINN_THROW("cannot open file: " << filename);
  }

  fseek(file, 0, SEEK_END);
  long const size = ftell(file); // [bytes].
  src.resize(size + 1);
  fseek(file, 0, SEEK_SET);
  fread(&src[0], size, 1, file);
  fclose(file);
  src[size] = '\0'; // Null-termination
  return src;
}

} // Namespace: detail.

//! DOCS
class Shader {
public:
/*  explicit Shader(GLenum const type)
    : _handle(detail::createShader(type))
  {
    throwIfInvalidHandle();
  }*/

  //! CTOR
  Shader(GLenum const type, std::string const& filename)
    : _handle(detail::createShader(type))
    , _filename(filename)
  {
    throwIfInvalidHandle();
    setSourceFromFile(filename);
    compile();
  }

  //! DTOR
  ~Shader() {
    detail::deleteShader(_handle);
  }

  GLuint handle() const {
    return _handle;
  }

  std::string filename() const {
    return _filename;
  }

  GLenum type() const {
    GLint params = 0;
    detail::getShaderiv(_handle, GL_SHADER_TYPE, &params);
    return static_cast<GLenum>(params); // TODO: Ugly static_cast to enum...
  }

  void compile() {
    detail::compileShader(_handle);
    if (!isCompiled()) {
      NDJINN_THROW("shader compile error: " << _handle << ", '" << _filename
                   << "': " << infoLog());
    }
  }

  bool isCompiled() const {
    GLint compileStatus = GL_FALSE;
    detail::getShaderiv(_handle, GL_COMPILE_STATUS, &compileStatus);
    return compileStatus == GL_TRUE;
  }

  std::string source() const {
    std::string str;
    GLint maxLength = 0;
    detail::getShaderiv(_handle, GL_SHADER_SOURCE_LENGTH, &maxLength);
    if (maxLength > 0) {
      str.resize(maxLength);
      GLsizei srcLength = 0;
      detail::getShaderSource(_handle,
                              static_cast<GLsizei>(maxLength),
                              &srcLength, // Excluding null-termination.
                              &str[0]); // Null-terminated.
      str.resize(srcLength + 1); // Trim.
    }
    return str;
  }

  std::string infoLog() const {
    std::string str;
    GLint maxLength = 0;
    detail::getShaderiv(_handle, GL_INFO_LOG_LENGTH, &maxLength);
    if (maxLength > 0) { // Info exists.
      str.resize(maxLength);
      GLsizei logLength = 0;
      detail::getShaderInfoLog(_handle,
                               static_cast<GLsizei>(maxLength),
                               &logLength, // Excluding null-termination.
                               &str[0]); // Null-terminated.
      str.resize(logLength + 1); // Trim.
    }
    return str;
  }

private:
  Shader(Shader const&); //!< Disable copy CTOR.
  Shader& operator=(Shader const&); //!< Disable assign.

  void throwIfInvalidHandle() {
    if (detail::isShader(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid shader handle: "
                   << _handle << ", '" << _filename << "'");
    }
  }

  void setSourceFromFile(std::string const& filename) {
    std::string const src = detail::readShaderFile(filename);
    setSourceFromString(src);
    _filename = filename;
  }

  void setSourceFromString(std::string const& source) {
    GLchar const* src = static_cast<const GLchar*>(source.c_str());
    GLint const length = static_cast<GLint>(source.size());
    detail::shaderSource(_handle, 1, &src, &length);
  }

  void setSource(GLsizei count, GLchar const **string, GLint const* length) {
    detail::shaderSource(_handle, count, string, length);
  }

  GLuint const _handle; //!< Resource handle.
  std::string _filename;
};

NDJINN_END_NAMESPACE

namespace std {

inline
ostream& operator<<(ostream& os, ndj::Shader const& sh)
{
  os << "Shader" << endl
     << "  Handle: " << sh.handle() << endl
     << "  Filename: '" << sh.filename() << "'" << endl
     << "  Type: " << ndj::detail::shaderTypeToString(sh.type()) << endl
     << "  Compiled: " << sh.isCompiled() << endl;

  return os;
}

} // namespace std

#endif // NDJINN_SHADER_HPP_INCLUDED
