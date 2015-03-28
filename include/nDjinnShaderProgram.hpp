//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_SHADER_PROGRAM_HPP_INCLUDED
#define NDJINN_SHADER_PROGRAM_HPP_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "nDjinnError.hpp"
#include "nDjinnException.hpp"
#include "nDjinnGL.hpp"
#include "nDjinnNamespace.hpp"
#include "nDjinnShader.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glCreateProgram wrapper. May throw.
inline GLuint createProgram() {
  GLuint const program = glCreateProgram();
  checkError("glCreateProgram");
  return program; 
}

//! glDeleteProgram wrapper. May throw.
inline void deleteProgram(GLuint const program) {
  glDeleteProgram(program); 
  checkError("glDeleteProgram"); 
}

//! glUseProgram wrapper. May throw.
inline void useProgram(GLuint const program) {
  glUseProgram(program); 
  checkError("glUseProgram");
}

//! glAttachShader wrapper. May throw.
inline void attachShader(GLuint const program, GLuint const shader) {
  glAttachShader(program, shader); 
  checkError("glAttachShader");
}

//! glDetachShader wrapper. May throw.
inline void detachShader(GLuint const program, GLuint const shader) {
  glDetachShader(program, shader); 
  checkError("glDetachShader");
}

//! glLinkProgram wrapper. May throw.
inline void linkProgram(GLuint const program) {
  glLinkProgram(program); 
  checkError("glLinkProgram"); 
}

//! glValidateProgram wrapper. May throw.
inline void validateProgram(GLuint const program) {
  glValidateProgram(program); 
  checkError("glValidateProgram"); 
}

//! glIsProgram wrapper. May throw.
inline GLboolean isProgram(GLuint const program) {
  const GLboolean isProgram = glIsProgram(program);
  checkError("glIsProgram"); 
  return isProgram;
}

//! glGetActiveAttrib wrapper. May throw.
inline void getActiveAttrib(GLuint const program,
                            GLuint const index,
                            GLsizei const bufSize,
                            GLsizei* length,
                            GLint* size,
                            GLenum* type,
                            GLchar* name) {
  glGetActiveAttrib(program, index, bufSize, length, size, type, name); 
  checkError("glGetActiveAttrib");
}

//! glGetAttribLocation wrapper. May throw.
inline GLint getAttribLocation(GLuint const program, GLchar const* name) {
  GLint loc = glGetAttribLocation(program, name); 
  checkError("glGetAttribLocation");
  return loc;
}

//! glGetActiveUniform wrapper. May throw.
inline void getActiveUniform(GLuint const program,
                             GLuint const index,
                             GLsizei const bufSize,
                             GLsizei* length,
                             GLint* size,
                             GLenum* type,
                             GLchar* name) {
  glGetActiveUniform(program, index, bufSize, length, size, type, name); 
  checkError("glGetActiveUniform"); 
}

//! glGetUniformLocation wrapper. May throw.
inline GLint getUniformLocation(GLuint const program, GLchar const* name) {
  GLint const loc = glGetUniformLocation(program, name);
  checkError("glGetUniformLocation"); 
  return loc; 
}

//! glGetProgramiv wrapper. May throw.
inline void getProgramiv(GLuint const program,
                         GLenum const pname,
                         GLint* params) {
  glGetProgramiv(program, pname, params); 
  checkError("glGetProgramiv");
}

//! glGetActiveUniformBlockiv wrapper. May throw.
inline void getActiveUniformBlockiv(GLuint const program,
                                    GLuint const uniformBlockIndex,
                                    GLenum const pname,
                                    GLint* params) {
  glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
  checkError("glGetActiveUniformBlockiv");
}

//! glGetActiveUniformBlockName wrapper. May throw.
inline void getActiveUniformBlockName(GLuint const program,
                                      GLuint const uniformBlockIndex,
                                      GLsizei const bufSize,
                                      GLsizei* length,
                                      GLchar* uniformBlockName) {
  glGetActiveUniformBlockName(program, 
                              uniformBlockIndex, 
                              bufSize, 
                              length, 
                              uniformBlockName);
  checkError("glGetActiveUniformBlockName");
}

//! glUniformBlockBinding wrapper. May throw.
inline void uniformBlockBinding(GLuint const program,
                                GLuint const uniformBlockIndex,
                                GLuint const uniformBlockBinding) {
  glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
  checkError("glUniformBlockBinding");
}

// Program Uniform

//! Generic.
template<class T>
void programUniform1(GLuint program, GLint location, T v0);

//! glProgramUniform1i wrapper. May throw.
template<> inline
void programUniform1<GLint>(GLuint const program,
                            GLint const location,
                            GLint const v0) {
  glProgramUniform1i(program, location, v0);
  checkError("glProgramUniform1i");
}

//! glProgramUniform1f wrapper. May throw.
template<> inline
void programUniform1<GLfloat>(GLuint const program,
                              GLint const location,
                              GLfloat const v0) {
  glProgramUniform1f(program, location, v0);
  checkError("glProgramUniform1f");
}

//! Generic.
template<class T>
void programUniform2(GLuint program, GLint location, T v0, T v1);

//! glProgramUniform2i wrapper. May throw.
template<> inline
void programUniform2<GLint>(GLuint const program,
                            GLint const location,
                            GLint const v0,
                            GLint const v1) {
  glProgramUniform2i(program, location, v0, v1);
  checkError("glProgramUniform2i");
}

//! glProgramUniform2f wrapper. May throw.
template<> inline
void programUniform2<GLfloat>(GLuint const program,
                              GLint const location,
                              GLfloat const v0,
                              GLfloat const v1) {
  glProgramUniform2f(program, location, v0, v1);
  checkError("glProgramUniform2f");
}

//! Generic.
template<class T>
void programUniform3(GLuint program, GLint location, T v0, T v1, T v2);

//! glProgramUniform3i wrapper. May throw.
template<> inline
void programUniform3<GLint>(GLuint const program,
                            GLint const location,
                            GLint const v0,
                            GLint const v1,
                            GLint const v2) {
  glProgramUniform3i(program, location, v0, v1, v2);
  checkError("glProgramUniform3i");
}

//! glProgramUniform3f wrapper. May throw.
template<> inline
void programUniform3<GLfloat>(GLuint const program,
                              GLint const location,
                              GLfloat const v0,
                              GLfloat const v1,
                              GLfloat const v2) {
  glProgramUniform3f(program, location, v0, v1, v2);
  checkError("glProgramUniform3f");
}

//! Generic.
template<class T>
void programUniform4(GLuint program, GLint location, T v0, T v1, T v2, T v3);

//! glProgramUniform4i wrapper. May throw.
template<> inline
void programUniform4<GLint>(GLuint const program,
                            GLint const location,
                            GLint const v0,
                            GLint const v1,
                            GLint const v2,
                            GLint const v3) {
  glProgramUniform4i(program, location, v0, v1, v2, v3);
  checkError("glProgramUniform4i");
}

//! glProgramUniform4f wrapper. May throw.
template<> inline
void programUniform4<GLfloat>(GLuint const program,
                              GLint const location,
                              GLfloat const v0,
                              GLfloat const v1,
                              GLfloat const v2,
                              GLfloat const v3) {
  glProgramUniform4f(program, location, v0, v1, v2, v3);
  checkError("glProgramUniform4f");
}

//! Generic.
template<int D, class T>
void programUniformv(GLuint program,
                     GLint location,
                     GLsizei count,
                     T const* value);

//! glProgramUniform1fv wrapper. May throw.
template<> inline
void programUniformv<1,GLfloat>(GLuint const program,
                                GLint const location,
                                GLsizei const count,
                                GLfloat const* value) {
  glProgramUniform1fv(program, location, count, value);
  checkError("glProgramUniform1fv");
}

//! glProgramUniform2fv wrapper. May throw.
template<> inline
void programUniformv<2,GLfloat>(GLuint const program,
                                GLint const location,
                                GLsizei const count,
                                GLfloat const* value) {
  glProgramUniform2fv(program, location, count, value);
  checkError("glProgramUniform2fv");
}

//! glProgramUniform3fv wrapper. May throw.
template<> inline
void programUniformv<3,GLfloat>(GLuint const program,
                                GLint const location,
                                GLsizei const count,
                                GLfloat const* value) {
  glProgramUniform3fv(program, location, count, value);
  checkError("glProgramUniform3fv");
}

//! glProgramUniform4fv wrapper. May throw.
template<> inline
void programUniformv<4,GLfloat>(GLuint const program,
                                GLint const location,
                                GLsizei const count,
                                GLfloat const* value) {
  glProgramUniform4fv(program, location, count, value);
  checkError("glProgramUniform4fv");
}

//! glProgramUniform1iv wrapper. May throw.
template<> inline
void programUniformv<1,GLint>(GLuint const program,
                              GLint const location,
                              GLsizei const count,
                              GLint const* value) {
  glProgramUniform1iv(program, location, count, value);
  checkError("glProgramUniform1iv");
}

//! glProgramUniform2iv wrapper. May throw.
template<> inline
void programUniformv<2,GLint>(GLuint const program,
                              GLint const location,
                              GLsizei const count,
                              GLint const* value) {
  glProgramUniform2iv(program, location, count, value);
  checkError("glProgramUniform2iv");
}

//! glProgramUniform3iv wrapper. May throw.
template<> inline
void programUniformv<3,GLint>(GLuint const program,
                              GLint const location,
                              GLsizei const count,
                              GLint const* value) {
  glProgramUniform3iv(program, location, count, value);
  checkError("glProgramUniform3iv");
}

//! glProgramUniform4iv wrapper. May throw.
template<> inline
void programUniformv<4,GLint>(GLuint const program,
                              GLint const location,
                              GLsizei const count,
                              GLint const* value) {
  glProgramUniform4iv(program, location, count, value);
  checkError("glProgramUniform4iv");
}

//! Generic.
template<int R, int C>
void programUniformMatrixfv(GLuint program,
                            GLint location,
                            GLsizei count,
                            GLboolean transpose,
                            GLfloat const* value);

//! glProgramUniformMatrix2fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<2,2>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix2fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix2fv");
}

//! glProgramUniformMatrix3fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<3,3>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix3fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix3fv");
}

//! glProgramUniformMatrix4fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<4,4>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix4fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix4fv");
}

//! glProgramUniformMatrix2x3fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<2,3>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix2x3fv");
}

//! glProgramUniformMatrix3x2fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<3,2>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix3x2fv");
}

//! glProgramUniformMatrix2x4fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<2,4>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix2x4fv");
}

//! glProgramUniformMatrix4x2fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<4,2>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix4x2fv");
}

//! glProgramUniformMatrix3x4fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<3,4>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix3x4fv");
}

//! glProgramUniformMatrix4x3fv wrapper. May throw.
template<> inline
void programUniformMatrixfv<4,3>(GLuint const program,
                                 GLint const location,
                                 GLsizei const count,
                                 GLboolean const transpose,
                                 GLfloat const* value) {
  glProgramUniformMatrix4x3fv(location, count, transpose, value);
  checkError("glProgramUniformMatrix4x3fv");
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

} // Namespace: detail.

//! DOCS
class ShaderProgram {
public:
  //! POD
  struct Attrib {
    GLenum type;
    GLint size;
    GLint location;
  };

  //! POD
  struct Uniform {
    GLenum type;
    GLint size;
    GLint location;
  };

  class UniformBlock {
  public:
    explicit UniformBlock(const GLuint index, 
                          const GLuint program)
      : _index(index)
      , _program(program) {
    }

    GLuint program() const {
      return _program;
    }

    GLuint index() const {
      return _index;
    }

    GLint dataSize() const {
      GLint dataSize;
      detail::getActiveUniformBlockiv(
        _program, 
        _index, 
        GL_UNIFORM_BLOCK_DATA_SIZE,
        &dataSize);
      return dataSize;
    }

    //! Returns number of active uniforms in block.
    GLint activeUniforms() const {
      GLint activeUniforms;
      detail::getActiveUniformBlockiv(
        _program, 
        _index, 
        GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,
        &activeUniforms);
      return activeUniforms;
    }

    void bind(const GLuint uniformBlockBinding) const {
      detail::uniformBlockBinding(_program, _index, uniformBlockBinding);
    }

    GLint binding() const {
      GLint binding;
      detail::getActiveUniformBlockiv(
        _program, 
        _index, 
        GL_UNIFORM_BLOCK_BINDING,
        &binding);
      return binding;
    }

  private:
    const GLuint _index;
    const GLuint _program;
  };

  typedef std::map<std::string, Attrib> AttribMap;
  typedef std::map<std::string, Uniform> UniformMap;
  typedef std::map<std::string, UniformBlock> UniformBlockMap;

  static std::string
  typeName(const Attrib& attrib);

  static std::string
  typeName(const Uniform& uniform);

  static GLint
  componentCount(const Attrib& attrib);

  static GLenum
  dataType(const Attrib& attrib);

public:
  //! CTOR.
  ShaderProgram()
    : _handle(detail::createProgram())
  {
    if (detail::isProgram(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid shader program handle: " << _handle);
    }
  }

  //! DTOR.
  ~ShaderProgram() {
    detail::deleteProgram(_handle);
  }

  //! Enable shader program.
  void bind() const {
    detail::useProgram(_handle);
  }

  //! Disabled shader program.
  void release() const {
    detail::useProgram(0);
  }

  //! Attach a shader to this shader program.
  void attachShader(Shader const& sh) {
    detail::attachShader(_handle, sh.handle());
  }

  //! Detach a shader from this shader program.
  void detachShader(Shader const& sh) {
    detail::detachShader(_handle, sh.handle());
  }

  void link();

  std::string infoLog() const {
    std::string str;
    GLint maxLength = 0;
    detail::getProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    if (maxLength > 0) { // Info exists.
      str.resize(maxLength);
      GLsizei logLength = 0;
      detail::getProgramInfoLog(program,
                                static_cast<GLsizei>(maxLength),
                                &logLength, // Excluding null-termination!
                                &str[0]); // Null-terminated.
      infoLog.resize(logLength + 1); // Trim.
    }
    return str;
  }


  const Uniform* queryActiveUniform(std::string const& name) const;
  const UniformBlock* queryActiveUniformBlock(std::string const& name) const;
  const Attrib* queryActiveAttrib(std::string const& name) const;

  const Uniform&
  activeUniform(const std::string &name) const;

  const UniformBlock&
  activeUniformBlock(const std::string &name) const;

  const Attrib&
  activeAttrib(const std::string &name) const;

  template<class T>
  void uniform1(Uniform const& uni, T const v0) {
    detail::programUniform1<T>(_handle, uni.location, v0);
  }

  template<class T>
  void uniform2(Uniform const& uni, T const v0, T const v1) {
    detail::programUniform2<T>(_handle, uni.location, v0, v1);
  }

  template<class T>
  void uniform3(Uniform const& uni, T const v0, T const v1, T const v2) {
    detail::programUniform3<T>(_handle, uni.location, v0, v1, v2);
  }

  template<class T>
  void uniform4(Uniform const& uni,
                T const v0, T const v1, T const v2, T const v3) {
    detail::programUniform4<T>(_handle, uni.location, v0, v1, v2, v3);
  }

  template<int D, class T>
  void uniformv(Uniform const& uni, T const* v) {
    detail::programUniformv<D,T>(_handle, uni.location, uni.size, v);
  }

  template<int R, int C>
  void uniformMatrixfv(Uniform const& uni,
                       GLboolean const transpose,
                       GLfloat const* v) {
    detail::programUniformMatrixfv<R,C>(
      _handle,
      uni.location,
      uni.size,
      transpose,
      v);
  }

private:
  ShaderProgram(ShaderProgram const&); //!< Disable copy CTOR.
  ShaderProgram& operator=(ShaderProgram const&); //!< Disable assign.

  void _updateActiveUniforms();
  void _updateActiveUniformBlocks();
  void _updateActiveAttribs();

  GLuint _handle; //!< Resource handle.
  AttribMap _attribs;
  UniformMap _uniforms;    
  UniformBlockMap _uniformBlocks;
};

// -----------------------------------------------------------------------------

//! DOCS [static]
inline std::string
ShaderProgram::typeName(const ShaderProgram::Attrib& attrib) {
  using std::string;

  switch (attrib.type) {
  case GL_FLOAT:              return string("GL_FLOAT");
  case GL_FLOAT_VEC2:         return string("GL_FLOAT_VEC2");
  case GL_FLOAT_VEC3:         return string("GL_FLOAT_VEC3");
  case GL_FLOAT_VEC4:         return string("GL_FLOAT_VEC4");
  case GL_FLOAT_MAT2:         return string("GL_FLOAT_MAT2");
  case GL_FLOAT_MAT3:         return string("GL_FLOAT_MAT3");
  case GL_FLOAT_MAT4:         return string("GL_FLOAT_MAT4");
  case GL_FLOAT_MAT2x3:       return string("GL_FLOAT_MAT2x3");
  case GL_FLOAT_MAT2x4:       return string("GL_FLOAT_MAT2x4"); 
  case GL_FLOAT_MAT3x2:       return string("GL_FLOAT_MAT3x2");
  case GL_FLOAT_MAT3x4:       return string("GL_FLOAT_MAT3x4");
  case GL_FLOAT_MAT4x2:       return string("GL_FLOAT_MAT4x2");
  case GL_FLOAT_MAT4x3:       return string("GL_FLOAT_MAT4x3");
  case GL_INT:                return string("GL_INT");
  case GL_INT_VEC2:           return string("GL_INT_VEC2");
  case GL_INT_VEC3:           return string("GL_INT_VEC3");
  case GL_INT_VEC4:           return string("GL_INT_VEC4");
  case GL_UNSIGNED_INT:       return string("GL_UNSIGNED_INT");
  case GL_UNSIGNED_INT_VEC2:  return string("GL_UNSIGNED_INT_VEC2");
  case GL_UNSIGNED_INT_VEC3:  return string("GL_UNSIGNED_INT_VEC3");
  case GL_UNSIGNED_INT_VEC4:  return string("GL_UNSIGNED_INT_VEC4");
  default: NDJINN_THROW("Unrecognized attrib type: " << attrib.type);
  }
}

//! DOCS [static]
inline std::string
ShaderProgram::typeName(const ShaderProgram::Uniform& uniform) {
  using std::string; 
  
  switch (uniform.type) {
  case GL_FLOAT:              return string("GL_FLOAT");
  case GL_FLOAT_VEC2:         return string("GL_FLOAT_VEC2");
  case GL_FLOAT_VEC3:         return string("GL_FLOAT_VEC3");
  case GL_FLOAT_VEC4:         return string("GL_FLOAT_VEC4");
  case GL_INT:                return string("GL_INT");
  case GL_INT_VEC2:           return string("GL_INT_VEC2");
  case GL_INT_VEC3:           return string("GL_INT_VEC3");
  case GL_INT_VEC4:           return string("GL_INT_VEC4");
  case GL_BOOL:               return string("GL_BOOL");
  case GL_BOOL_VEC2:          return string("GL_BOOL_VEC2");
  case GL_BOOL_VEC3:          return string("GL_BOOL_VEC3");
  case GL_BOOL_VEC4:          return string("GL_BOOL_VEC4");
  case GL_FLOAT_MAT2:         return string("GL_FLOAT_MAT2");
  case GL_FLOAT_MAT3:         return string("GL_FLOAT_MAT3");
  case GL_FLOAT_MAT4:         return string("GL_FLOAT_MAT4");
  case GL_FLOAT_MAT2x3:       return string("GL_FLOAT_MAT2x3");
  case GL_FLOAT_MAT2x4:       return string("GL_FLOAT_MAT2x4"); 
  case GL_FLOAT_MAT3x2:       return string("GL_FLOAT_MAT3x2");
  case GL_FLOAT_MAT3x4:       return string("GL_FLOAT_MAT3x4");
  case GL_FLOAT_MAT4x2:       return string("GL_FLOAT_MAT4x2");
  case GL_FLOAT_MAT4x3:       return string("GL_FLOAT_MAT4x3");
  case GL_SAMPLER_1D:         return string("GL_SAMPLER_1D");
  case GL_SAMPLER_2D:         return string("GL_SAMPLER_2D");
  case GL_SAMPLER_3D:         return string("GL_SAMPLER_3D");
  case GL_SAMPLER_CUBE:       return string("GL_SAMPLER_CUBE");
  case GL_SAMPLER_1D_SHADOW:  return string("GL_SAMPLER_1D_SHADOW");
  case GL_SAMPLER_2D_SHADOW:  return string("GL_SAMPLER_2D_SHADOW");
  default: NDJINN_THROW("Unrecognized uniform type: " << uniform.type);
  }
}

//! DOCS [static]
inline GLint
ShaderProgram::componentCount(const ShaderProgram::Attrib& attrib) {
  switch (attrib.type) {
  case GL_FLOAT:
  case GL_INT:  
  case GL_UNSIGNED_INT:
    return 1;
  case GL_FLOAT_VEC2:       
  case GL_INT_VEC2:         
  case GL_UNSIGNED_INT_VEC2:
    return 2;
  case GL_FLOAT_VEC3:         
  case GL_INT_VEC3:           
  case GL_UNSIGNED_INT_VEC3:  
    return 3;
  case GL_FLOAT_VEC4:
  case GL_INT_VEC4:  
  case GL_UNSIGNED_INT_VEC4:
    return 4;
  default: NDJINN_THROW("Unrecognized attrib type: " << attrib.type);

  // TODO: Not sure about these...
  //case GL_FLOAT_MAT2:         return std::string("GL_FLOAT_MAT2");
  //case GL_FLOAT_MAT3:         return std::string("GL_FLOAT_MAT3");
  //case GL_FLOAT_MAT4:         return std::string("GL_FLOAT_MAT4");
  //case GL_FLOAT_MAT2x3:       return std::string("GL_FLOAT_MAT2x3");
  //case GL_FLOAT_MAT2x4:       return std::string("GL_FLOAT_MAT2x4"); 
  //case GL_FLOAT_MAT3x2:       return std::string("GL_FLOAT_MAT3x2");
  //case GL_FLOAT_MAT3x4:       return std::string("GL_FLOAT_MAT3x4");
  //case GL_FLOAT_MAT4x2:       return std::string("GL_FLOAT_MAT4x2");
  //case GL_FLOAT_MAT4x3:       return std::string("GL_FLOAT_MAT4x3");
  }
}

//! DOCS [static]
inline GLenum
ShaderProgram::dataType(const ShaderProgram::Attrib& attrib) {
  switch (attrib.type) {
  case GL_FLOAT:
  case GL_FLOAT_VEC2:       
  case GL_FLOAT_VEC3:         
  case GL_FLOAT_VEC4:
    return GL_FLOAT;
  case GL_INT:  
  case GL_INT_VEC2:         
  case GL_INT_VEC3:           
  case GL_INT_VEC4:  
    return GL_INT;
  case GL_UNSIGNED_INT:
  case GL_UNSIGNED_INT_VEC2:
  case GL_UNSIGNED_INT_VEC3:  
  case GL_UNSIGNED_INT_VEC4:
    return GL_UNSIGNED_INT;
  default: NDJINN_THROW("Unrecognized attrib type: " << attrib.type);
  }
}



//! Link shader program. May throw.
inline void
ShaderProgram::link() { 
  detail::linkProgram(_handle);
  detail::getProgramInfoLog(_handle, _infoLog);
  GLint linkStatus = GL_FALSE;
  detail::getProgramiv(_handle, GL_LINK_STATUS, &linkStatus);
  if (linkStatus == GL_FALSE) {
    NDJINN_THROW("Shader program link error: " 
                 << _handle << ": " << _infoLog);
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
  _updateActiveUniformBlocks();
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
inline const ShaderProgram::UniformBlock*
ShaderProgram::queryActiveUniformBlock(const std::string &name) const {
  const UniformBlock *uniBlock = 0;
  const UniformBlockMap::const_iterator iter = _uniformBlocks.find(name);
  if (iter != _uniformBlocks.end()) {
    uniBlock = &iter->second;
  }
  return uniBlock;
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
inline const ShaderProgram::UniformBlock&
ShaderProgram::activeUniformBlock(const std::string &name) const {
  const UniformBlockMap::const_iterator iter = _uniformBlocks.find(name);
  if (iter != _uniformBlocks.end()) {
    return iter->second;
  }
  NDJINN_THROW("invalid uniform block: '" << name << "'");
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

//! Grab info about active uniforms from OpenGL.
inline void
ShaderProgram::_updateActiveUniformBlocks() {
  _uniformBlocks.clear();
  GLint activeUniformBlocks = 0;
  detail::getProgramiv(_handle, GL_ACTIVE_UNIFORM_BLOCKS, &activeUniformBlocks);
  std::string uniformBlockName;
  for (GLint i = 0; i < activeUniformBlocks; ++i) {
    const GLuint uniformBlockIndex = static_cast<GLuint>(i);
    GLint uniformBlockNameLength = -1;
    detail::getActiveUniformBlockiv(
      _handle, 
      uniformBlockIndex,
      GL_UNIFORM_BLOCK_NAME_LENGTH,
      &uniformBlockNameLength);
    uniformBlockName.resize(uniformBlockNameLength);
    GLsizei length = -1;
    detail::getActiveUniformBlockName(
      _handle, 
      uniformBlockIndex, 
      static_cast<GLsizei>(uniformBlockName.size()), 
      &length, 
      &uniformBlockName[0]);
      uniformBlockName.resize(length);
    _uniformBlocks.insert(
      UniformBlockMap::value_type(
        uniformBlockName, UniformBlock(uniformBlockIndex, _handle)));
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

namespace std {

ostream& operator<<(ostream& os, ndj::ShaderProgram const& sp)
{
  //os << "ShaderProgram[" << sp.handle() << "]"
  //      <<

  return os;
}

} // namespace std

#endif // NDJINN_SHADER_PROGRAM_HPP_INCLUDED
