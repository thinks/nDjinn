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
inline GLuint createShader(GLenum const type)
{
  GLuint const shader = glCreateShader(type);
  checkError("glCreateShader");
  return shader; 
}

//! glDeleteShader wrapper. May throw. 
inline void deleteShader(GLuint const shader)
{
  glDeleteShader(shader); 
  checkError("glDeleteShader");
}

//! glIsShader wrapper. May throw.
inline GLboolean isShader(GLuint const shader)
{
  GLboolean const isShader = glIsShader(shader);
  checkError("glIsShader");
  return isShader; 
}

//! glShaderSource wrapper. May throw.
inline void shaderSource(GLuint const shader, GLsizei const count,
                         GLchar const** string, GLint const* length)
{
  glShaderSource(shader, count, string, length); 
  checkError("glShaderSource");
}

//! glCompileShader wrapper. May throw. 
inline void compileShader(GLuint const shader)
{
  glCompileShader(shader); 
  checkError("glCompileShader");
}

//! glGetShaderiv wrapper. May throw.
inline void getShaderiv(GLuint const shader,
                        GLenum const pname,
                        GLint *params)
{
  glGetShaderiv(shader, pname, params);
  checkError("glGetShaderiv");
}

//! glGetShaderInfoLog wrapper. May throw.
inline void getShaderInfoLog(GLuint const shader,
                             GLsizei const bufSize,
                             GLsizei* length,
                             GLchar* infoLog)
{
  glGetShaderInfoLog(shader, bufSize, length, infoLog); 
  checkError("glGetShaderInfoLog");
}

//! glGetShaderSource wrapper. May throw.
inline void getShaderSource(GLuint const shader,
                            GLsizei const bufSize,
                            GLsizei* length,
                            GLchar* source)
{
  glGetShaderSource(shader, bufSize, length, source);
  checkError("glGetShaderSource"); 
}

inline std::string shaderTypeToString(GLenum const type)
{
  switch (type) {
  case GL_VERTEX_SHADER:    return std::string("GL_VERTEX_SHADER");
  case GL_GEOMETRY_SHADER:  return std::string("GL_GEOMETRY_SHADER");
  case GL_FRAGMENT_SHADER:  return std::string("GL_FRAGMENT_SHADER");
  }
  NDJINN_THROW("unrecognized shader type: " << type);
}

} // Namespace: detail.

//! DOCS
template<GLenum Type>
class Shader
{
public:
  static GLenum const TYPE = Type;

  //! CTOR
  Shader(std::string const& source)
    : _handle(detail::createShader(Type))
  {
    throwIfInvalidHandle();
    GLint shader_type = 0;
    detail::getShaderiv(_handle, GL_SHADER_TYPE, &shader_type);
    if (TYPE != static_cast<GLenum>(shader_type)) {
        NDJINN_THROW("invalid shader type: " << shader_type <<
                     " (should be " << TYPE << ")");
    }

    GLchar const* src = static_cast<const GLchar*>(source.c_str());
    GLint const length = static_cast<GLint>(source.size());
    detail::shaderSource(_handle, 1, &src, &length);

    compile();
  }

  //! DTOR
  ~Shader()
  {
    detail::deleteShader(_handle);
  }

  GLuint handle() const
  {
    return _handle;
  }

  bool isCompiled() const
  {
    GLint compileStatus = GL_FALSE;
    detail::getShaderiv(_handle, GL_COMPILE_STATUS, &compileStatus);
    return compileStatus == GL_TRUE;
  }

  std::string source() const
  {
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

  std::string infoLog() const
  {
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

  void throwIfInvalidHandle()
  {
    if (detail::isShader(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid shader handle: " << _handle);
    }
  }

  void compile()
  {
    detail::compileShader(_handle);
    if (!isCompiled()) {
      NDJINN_THROW("shader compile error: " << _handle << ": " << infoLog());
    }
  }

  GLuint const _handle; //!< Resource handle.
};

// Convenient types.
typedef Shader<GL_VERTEX_SHADER> VertexShader;
typedef Shader<GL_GEOMETRY_SHADER> GeometryShader;
typedef Shader<GL_FRAGMENT_SHADER> FragmentShader;

//! Read shader source from file.
inline std::string readShaderFile(const std::string& filename)
{
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

NDJINN_END_NAMESPACE

namespace std {

template<GLenum Type> inline
ostream& operator<<(ostream& os, ndj::Shader<Type> const& sh)
{
  os << "Shader<"
     << ndj::detail::shaderTypeToString(ndj::Shader<Type>::TYPE) << ">" << endl
     << "  Handle: " << sh.handle() << endl
     << "  Filename: '" << sh.filename() << "'" << endl
     << "  Compiled: " << sh.isCompiled() << endl;

  return os;
}

} // namespace std

#endif // NDJINN_SHADER_HPP_INCLUDED
