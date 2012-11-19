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

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glCreateProgram wrapper. May throw.
inline GLuint
createProgram() { 
  const GLuint program = glCreateProgram();
  checkError("glCreateProgram");
  return program; 
}

//! glDeleteProgram wrapper. May throw.
inline void
deleteProgram(const GLuint program) { 
  glDeleteProgram(program); 
  checkError("glDeleteProgram"); 
}

//! glUseProgram wrapper. May throw.
inline void
useProgram(const GLuint program) { 
  glUseProgram(program); 
  checkError("glUseProgram");
}

//! glAttachShader wrapper. May throw.
inline void
attachShader(const GLuint program, const GLuint shader) { 
  glAttachShader(program, shader); 
  checkError("glAttachShader");
}

//! glDetachShader wrapper. May throw.
inline void
detachShader(const GLuint program, const GLuint shader) { 
  glDetachShader(program, shader); 
  checkError("glDetachShader");
}

//! glLinkProgram wrapper. May throw.
inline void
linkProgram(const GLuint program) { 
  glLinkProgram(program); 
  checkError("glLinkProgram"); 
}

//! glValidateProgram wrapper. May throw.
inline void
validateProgram(const GLuint program) { 
  glValidateProgram(program); 
  checkError("glValidateProgram"); 
}

//! glIsProgram wrapper. May throw.
inline GLboolean
isProgram(const GLuint program) {
  const GLboolean isProgram = glIsProgram(program);
  checkError("glIsProgram"); 
  return isProgram;
}

//! glGetActiveAttrib wrapper. May throw.
inline void
getActiveAttrib(const GLuint program, 
                const GLuint index,
                const GLsizei bufSize, 
                GLsizei *length, 
                GLint *size,
                GLenum *type, 
                GLchar *name) { 
  glGetActiveAttrib(program, index, bufSize, length, size, type, name); 
  checkError("glGetActiveAttrib");
}

//! glGetAttriLocation wrapper. May throw.
inline GLint
getAttribLocation(const GLuint program, const GLchar *name) { 
  GLint loc = glGetAttribLocation(program, name); 
  checkError("glGetAttribLocation");
  return loc;
}

//! glGetActiveUniform wrapper. May throw.
inline void
getActiveUniform(const GLuint program, 
                 const GLuint index,
                 const GLsizei bufSize, 
                 GLsizei *length, 
                 GLint *size,
                 GLenum *type, 
                 GLchar *name) { 
  glGetActiveUniform(program, index, bufSize, length, size, type, name); 
  checkError("glGetActiveUniform"); 
}

//! glGetUniformLocation wrapper. May throw.
inline GLint
getUniformLocation(const GLuint program, const GLchar *name) {
  GLint loc = glGetUniformLocation(program, name);
  checkError("glGetUniformLocation"); 
  return loc; 
}

//! glGetProgramiv wrapper. May throw.
inline void
getProgramiv(const GLuint program, 
             const GLenum pname, 
             GLint *params) { 
  glGetProgramiv(program, pname, params); 
  checkError("glGetProgramiv");
}

//! glUniform1i wrapper. May throw. 
inline void
uniform1i(const GLint location, const GLint v0) {
  glUniform1i(location, v0);
  checkError("glUniform1i");
}

//! glUniform1f wrapper. May throw.
inline void
uniform1f(const GLint location, const GLfloat v0) {
  glUniform1f(location, v0);
  checkError("glUniform1f");
}

//! glUniform2i wrapper. May throw.
inline void
uniform2i(const GLint location, const GLint v0, const GLint v1) {
  glUniform2i(location, v0, v1);
  checkError("glUniform2i");
}

//! glUniform2f wrapper. May throw.
inline void
uniform2f(const GLint location, const GLfloat v0, const GLfloat v1) {
  glUniform2f(location, v0, v1);
  checkError("glUniform2f");
}

//! glUniform3i wrapper. May throw.
inline void
uniform3i(const GLint location, 
          const GLint v0, 
          const GLint v1, 
          const GLint v2) {
  glUniform3i(location, v0, v1, v2);
  checkError("glUniform3i");
}

//! glUniform3f wrapper. May throw.
inline void
uniform3f(const GLint location, 
          const GLfloat v0, 
          const GLfloat v1, 
          const GLfloat v2) {
  glUniform3f(location, v0, v1, v2);
  checkError("glUniform3f");
}

//! glUniform4i wrapper. May throw. 
inline void
uniform4i(const GLint location, 
          const GLint v0, 
          const GLint v1, 
          const GLint v2, 
          const GLint v3) {
  glUniform4i(location, v0, v1, v2, v3);
  checkError("glUniform4i");
}

//! glUniform4f wrapper. May throw.
inline void
uniform4f(const GLint   location, 
          const GLfloat v0, 
          const GLfloat v1, 
          const GLfloat v2, 
          const GLfloat v3) {
  glUniform4f(location, v0, v1, v2, v3);
  checkError("glUniform4f"); 
}

//! glUniform1fv wrapper. May throw. 
inline void
uniform1fv(const GLint location, 
           const GLsizei count, 
           const GLfloat *value) {
  glUniform1fv(location, count, value);
  checkError("glUniform1fv");
}

//! glUniform2fv wrapper. May throw.
inline void
uniform2fv(const GLint location, 
           const GLsizei count,
           const GLfloat *value) {
  glUniform2fv(location, count, value);
  checkError("glUniform2fv");
}

//! glUniform3fv wrapper. May throw.
inline void
uniform3fv(const GLint location, 
           const GLsizei count,
           const GLfloat *value) {
  glUniform3fv(location, count, value);
  checkError("glUniform3fv"); 
}

//! glUniform4fv wrapper. May throw.
inline void
uniform4fv(const GLint location, 
           const GLsizei count, 
           const GLfloat *value) {
  glUniform4fv(location, count, value);
  checkError("glUniform4fv");
}

//! glUniform1iv wrapper. May throw.
inline void
uniform1iv(const GLint location, 
           const GLsizei count, 
           const GLint *value) {
  glUniform1iv(location, count, value);
  checkError("glUniform1iv"); 
}

//! glUniform2iv wrapper. May throw.
inline void
uniform2iv(const GLint location, 
           const GLsizei count, 
           const GLint *value) {
  glUniform2iv(location, count, value);
  checkError("glUniform2iv");
}

//! glUniform3iv wrapper. May throw.
inline void
uniform3iv(const GLint location, 
           const GLsizei count, 
           const GLint *value) {
  glUniform3iv(location, count, value);
  checkError("glUniform3iv");
}

//! glUniform4iv wrapper. May throw.
inline void
uniform4iv(const GLint location, 
           const GLsizei count, 
           const GLint *value) {
  glUniform4iv(location, count, value);
  checkError("glUniform4iv");
}

//! glUniformMatrix2fv wrapper. May throw.
inline void
uniformMatrix2fv(const GLint location,
                 const GLsizei count,
                 const GLboolean transpose,
                 const GLfloat *value) {
  glUniformMatrix2fv(location, count, transpose, value);
  checkError("glUniformMatrix2fv");
}

//! glUniformMatrix3fv wrapper. May throw. 
inline void
uniformMatrix3fv(const GLint location,
                 const GLsizei count,
                 const GLboolean transpose,
                 const GLfloat *value) {
  glUniformMatrix3fv(location, count, transpose, value);
  checkError("glUniformMatrix3fv"); 
}

//! glUniformMatrix4fv wrapper. May throw.
inline void
uniformMatrix4fv(const GLint location,
                 const GLsizei count,
                 const GLboolean transpose,
                 const GLfloat *value) {
  glUniformMatrix4fv(location, count, transpose, value);
  checkError("glUniformMatrix4fv");
}

//! glUniformMatrix2x3fv wrapper. May throw.
inline void
uniformMatrix2x3fv(const GLint location,
                   const GLsizei count,
                   const GLboolean transpose,
                   const GLfloat *value) {
  glUniformMatrix2x3fv(location, count, transpose, value);
  checkError("glUniformMatrix2x3fv"); 
}

//! glUniformMatrix3x2fv wrapper. May throw.
inline void
uniformMatrix3x2fv(const GLint location,
                   const GLsizei count,
                   const GLboolean transpose,
                   const GLfloat *value) {
  glUniformMatrix3x2fv(location, count, transpose, value);
  checkError("glUniformMatrix3x2fv"); 
}

//! glUniformMatrix2x4fv wrapper. May throw.
inline void
uniformMatrix2x4fv(const GLint location,
                   const GLsizei count,
                   const GLboolean transpose,
                   const GLfloat *value) {
  glUniformMatrix2x4fv(location, count, transpose, value);
  checkError("glUniformMatrix2x4fv");
}

//! glUniformMatrix4x2fv wrapper. May throw.
inline void
uniformMatrix4x2fv(const GLint location,
                   const GLsizei count,
                   const GLboolean transpose,
                   const GLfloat *value) {
  glUniformMatrix4x2fv(location, count, transpose, value);
  checkError("glUniformMatrix4x2fv");
}

//! glUniformMatrix3x4fv wrapper. May throw. 
inline void
uniformMatrixfv3x4fv(const GLint location,
                     const GLsizei count,
                     const GLboolean transpose,
                     const GLfloat *value) {
  glUniformMatrix3x4fv(location, count, transpose, value);
  checkError("glUniformMatrix3x4fv"); 
}

//! glUniformMatrix4x3fv wrapper. May throw.
inline void
UniformMatrix4x3fv(const GLint location,
                   const GLsizei count,
                   const GLboolean transpose,
                   const GLfloat *value) {
  glUniformMatrix4x3fv(location, count, transpose, value);
  checkError("glUniformMatrix4x3fv"); 
}

//! glGetProgramInfoLog wrapper. May throw.
inline void
getProgramInfoLog(const GLuint program, 
                  const GLsizei bufSize,
                  GLsizei *length, 
                  GLchar *infoLog) { 
  glGetProgramInfoLog(program, bufSize, length, infoLog); 
  checkError("glGetProgramInfoLog");
}

//! Grab info log from OpenGL. 
inline void
getProgramInfoLog(const GLuint program, std::string &infoLog) {
  GLint maxLength = 0;
  getProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
  if (maxLength > 0) {
    // Info exists. The returned string is null-terminated.

    infoLog.clear();
    infoLog.resize(maxLength);
    GLsizei logLength = 0; 
    getProgramInfoLog(program, 
                      static_cast<GLsizei>(maxLength),
                      &logLength, // Excluding null-termination!
                      &infoLog[0]); // Null-terminated.
    infoLog.resize(logLength + 1);
  }
}

} // Namespace: detail.

//------------------------------------------------------------------------------

//! DOCS
class ShaderProgram
{
public:

  //! POD
  struct Attrib
  {
    GLenum type;
    GLint size;
    GLint location;
  };

  //! POD
  struct Uniform
  {
    GLenum type;
    GLint size;
    GLint location;
  };

  typedef std::map<std::string, Attrib>  AttribMap;
  typedef std::map<std::string, Uniform> UniformMap;

public:

  explicit ShaderProgram();
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

  const Uniform&
  activeUniform(const std::string &name) const;

  const Attrib&
  activeAttrib(const std::string &name) const;

private:

  void
  _updateActiveUniforms();

  void
  _updateActiveAttribs();

private:  // Member variables.
  GLuint _handle; //!< Resource handle.
  std::string _infoLog;
  AttribMap _attribs;
  UniformMap _uniforms;    
};

// -----------------------------------------------------------------------------

//! CTOR. May throw.
inline
ShaderProgram::ShaderProgram()
    : _handle(0)
{
  _handle = detail::createProgram(); 
  if (_handle == 0) {
    NDJINN_THROW("Invalid shader program handle");
  }
}

//! DTOR.
inline
ShaderProgram::~ShaderProgram() { 
  try { 
    detail::deleteProgram(_handle); 
  }
  catch (...) {
  }
}

// -----------------------------------------------------------------------------

//! Enable shader program. May throw. 
inline void
ShaderProgram::bind() const { 
  detail::useProgram(_handle); 
} 

//! Disabled shader program.
inline void
ShaderProgram::release() const { 
  detail::useProgram(0); // May throw. 
} 

//! Attach a shader to this shader program. May throw.
inline void
ShaderProgram::attachShader(const Shader &sh) { 
  detail::attachShader(_handle, sh.handle());
} 

//! Detach a shader from this shader program. May throw.
inline void
ShaderProgram::detachShader(const Shader &sh) { 
  detail::detachShader(_handle, sh.handle());
} 

//! Link shader program. May throw.
inline void
ShaderProgram::link() { 
  detail::linkProgram(_handle);
  detail::getProgramInfoLog(_handle, _infoLog);
  GLint linkStatus = GL_FALSE;
  detail::getProgramiv(_handle, GL_LINK_STATUS, &linkStatus);
  if (linkStatus == GL_FALSE) {
    NDJINN_THROW("Shader program link error: " << _handle << ": " << _infoLog);
  }

  detail::validateProgram(_handle);
  GLint validateStatus = GL_FALSE;
  detail::getProgramiv(_handle, GL_VALIDATE_STATUS, &validateStatus); 
  if (validateStatus == GL_FALSE) {
    NDJINN_THROW("Shader program validation error: " 
                 << _handle << ": " << _infoLog);
  }

  // Successful link and validation. Now get some info about the shader.
  _updateActiveUniforms();
  _updateActiveAttribs();
}

//! Returns info log.
inline const std::string&
ShaderProgram::infoLog() const { 
  return _infoLog; 
}

// -----------------------------------------------------------------------------

//! May return null.
inline const ShaderProgram::Uniform*
ShaderProgram::queryActiveUniform(const std::string &name) const {
  const Uniform *uni = 0;
  const UniformMap::const_iterator iter = _uniforms.find(name);
  if (iter != _uniforms.end()) {
    uni = &iter->second;
  }
  return uni;
}

//! May return null.
inline const ShaderProgram::Attrib*
ShaderProgram::queryActiveAttrib(const std::string &name) const {
  const Attrib *attr = 0;
  const AttribMap::const_iterator iter = _attribs.find(name);
  if (iter != _attribs.end()) {
    attr = &iter->second;
  }
  return attr;
}

//! May throw.
inline const ShaderProgram::Uniform&
ShaderProgram::activeUniform(const std::string &name) const {
  const UniformMap::const_iterator iter = _uniforms.find(name);
  if (iter != _uniforms.end()) {
    return iter->second;
  }
  NDJINN_THROW("invalid uniform: '" << name << "'");
}

//! May throw.
inline const ShaderProgram::Attrib&
ShaderProgram::activeAttrib(const std::string &name) const {
  const AttribMap::const_iterator iter = _attribs.find(name);
  if (iter != _attribs.end()) {
    return iter->second;
  }
  NDJINN_THROW("invalid attrib: '" << name << "'");
}

// -----------------------------------------------------------------------------

//! Grab info about active uniforms from OpenGL.
inline void
ShaderProgram::_updateActiveUniforms() {
  _uniforms.clear();
  GLint activeUniforms = 0;
  detail::getProgramiv(_handle, GL_ACTIVE_UNIFORMS, &activeUniforms);
  GLint activeUniformMaxLength = 0; 
  detail::getProgramiv(_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, 
                       &activeUniformMaxLength);
  for (GLint i = 0; i < activeUniforms; ++i) {
    std::string name;            
    name.resize(activeUniformMaxLength);
    GLsizei length = 0;
    Uniform uni;
    detail::getActiveUniform(
        _handle,
        static_cast<GLuint>(i),
        activeUniformMaxLength,
        &length, // Exluding null-termination!
        &uni.size,
        &uni.type,
        &name[0]);
    name.resize(length);
    uni.location = detail::getUniformLocation(_handle, name.c_str());
    _uniforms.insert(UniformMap::value_type(name, uni));
  }
}

//! Grab info about active attribs from OpenGL.
inline void
ShaderProgram::_updateActiveAttribs() {
  _attribs.clear();
  GLint activeAttributes = 0;
  detail::getProgramiv(_handle, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
  GLint activeAttributeMaxLength = 0; 
  detail::getProgramiv(_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, 
                       &activeAttributeMaxLength );
  for (GLint i = 0; i < activeAttributes; ++i) {
    std::string name;
    name.resize(activeAttributeMaxLength);
    GLsizei length = 0;
    Attrib attr;
    detail::getActiveAttrib(
        _handle, 
        static_cast<GLuint>(i), 
        activeAttributeMaxLength,
        &length, // Excluding null-termination!
        &attr.size,
        &attr.type,
        &name[0]);
    name.resize(length);
    attr.location = detail::getAttribLocation(_handle, name.c_str());
    _attribs.insert(AttribMap::value_type(name, attr));
  }
}

NDJINN_END_NAMESPACE

#endif // NDJINN_SHADER_PROGRAM_HPP_INCLUDED
