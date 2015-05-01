//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_SHADER_PROGRAM_HPP_INCLUDED
#define NDJINN_SHADER_PROGRAM_HPP_INCLUDED

#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>

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

//! glIsProgram wrapper. May throw.
inline GLboolean isProgram(GLuint const program) {
  const GLboolean isProgram = glIsProgram(program);
  checkError("glIsProgram");
  return isProgram;
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

//! glGetProgramInfoLog wrapper. May throw.
inline void getProgramInfoLog(GLuint const program,
                              GLsizei const bufSize,
                              GLsizei* length,
                              GLchar* infoLog) {
  glGetProgramInfoLog(program, bufSize, length, infoLog);
  checkError("glGetProgramInfoLog");
}

//! glUseProgram wrapper. May throw.
inline void useProgram(GLuint const program) {
  glUseProgram(program);
  checkError("glUseProgram");
}

//! glGetProgramiv wrapper. May throw.
inline void getProgramiv(GLuint const program,
                         GLenum const pname,
                         GLint* params) {
  glGetProgramiv(program, pname, params);
  checkError("glGetProgramiv");
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

//! glGetActiveUniformsiv wrapper. May throw.
inline void getActiveUniformsiv(GLuint const program,
                                GLsizei const ucount,
                                GLuint const* uIndices,
                                GLenum const pname,
                                GLint* params) {
  glGetActiveUniformsiv(program, ucount, uIndices, pname, params);
  checkError("glGetActiveUniformsiv");
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

//! glGetUniformBlockIndex wrapper. May throw.
inline GLuint getUniformBlockIndex(GLuint const program,
                                         GLchar const* name) {
  GLuint const index = glGetUniformBlockIndex(program, name);
  checkError("glGetActiveUniformBlockIndex");
  return index;
}

//! glUniformBlockBinding wrapper. May throw.
inline void uniformBlockBinding(GLuint const program,
                                GLuint const uniformBlockIndex,
                                GLuint const uniformBlockBinding) {
  glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
  checkError("glUniformBlockBinding");
}

//! Generic.
template <class T>
void getUniformv(GLuint program, GLint location, T* params);

//! glGetUniformfv wrapper. May throw.
template <> inline
void getUniformv<GLfloat>(GLuint const program,
                          GLint const location,
                          GLfloat* params) {
  glGetUniformfv(program, location, params);
  checkError("glGetUniformfv");
}

//! glGetUniformiv wrapper. May throw.
template <> inline
void getUniformv<GLint>(GLuint const program,
                        GLint const location,
                        GLint* params) {
  glGetUniformiv(program, location, params);
  checkError("glGetUniformiv");
}

//! glGetUniformuiv wrapper. May throw.
template <> inline
void getUniformv<GLuint>(GLuint const program,
                         GLint const location,
                         GLuint* params) {
  glGetUniformuiv(program, location, params);
  checkError("glGetUniformuiv");
}

//! glGetUniformdv wrapper. May throw.
template <> inline
void getUniformv<GLdouble>(GLuint const program,
                           GLint const location,
                           GLdouble* params) {
  glGetUniformdv(program, location, params);
  checkError("glGetUniformdv");
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
  glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
  checkError("glProgramUniformMatrix4x3fv");
}

//! Convenience.
inline std::string uniformTypeToString(GLenum const type) {
  using std::string;

  switch (type) {
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
  }
  NDJINN_THROW("unrecognized uniform type: " << type);
}

//! Convenience.
inline std::string attribTypeToString(GLenum const type) {
  using std::string;

  switch (type) {
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
  }
  NDJINN_THROW("unrecognized attrib type: " << type);
}

//! Convenience.
inline GLint elementCount(GLenum const type) {
  // TODO: Add more types if needed!
  switch (type) {
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
  case GL_FLOAT_MAT2:
    return 4;
  case GL_FLOAT_MAT3x2:
  case GL_FLOAT_MAT2x3:
    return 6;
  case GL_FLOAT_MAT2x4:
  case GL_FLOAT_MAT4x2:
    return 8;
  case GL_FLOAT_MAT3:
    return 9;
  case GL_FLOAT_MAT3x4:
  case GL_FLOAT_MAT4x3:
    return 12;
  case GL_FLOAT_MAT4:
    return 16;
  }
  NDJINN_THROW("unrecognized type: " << type);
}

} // Namespace: detail.

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

//! DOCS
class UniformBlock {
public:
  //! Represents an active uniform within a block.
  struct Field {
    std::string name;
    GLint offset;
    GLuint blockIndex;
    GLint size;
    GLenum type;
  };

  typedef std::vector<Field> FieldContainer;
  typedef FieldContainer::const_iterator FieldIterator;

  //! CTOR
  UniformBlock(GLuint const index, GLuint const program)
    : _index(index)
    , _program(program)
  {
    // Get the number of active uniforms, i.e. fields, in this block.
    GLint fieldCount = -1;
    detail::getActiveUniformBlockiv(
      _program,
      _index,
      GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,
      &fieldCount);

    // Get the indices of the active uniforms in this block.
    std::vector<GLint> fieldIndices(fieldCount, -1);
    detail::getActiveUniformBlockiv(
      _program,
      _index,
      GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
      &fieldIndices[0]);

    // Get the offsets of the active uniforms in this block.
    std::vector<GLint> fieldOffsets(fieldIndices.size(), -1);
    detail::getActiveUniformsiv(
      _program,
      static_cast<GLsizei>(fieldIndices.size()),
      reinterpret_cast<GLuint*>(&fieldIndices[0]),
      GL_UNIFORM_OFFSET,
      &fieldOffsets[0]);

    // Get the maximum length of a uniform for the whole program.
    GLint activeUniformMaxLength = -1;
    ndj::detail::getProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH,
                              &activeUniformMaxLength);

    for (std::size_t i = 0; i < fieldIndices.size(); ++i) {
      Field field;
      field.name.resize(activeUniformMaxLength);
      field.blockIndex = fieldIndices[i];
      field.offset = fieldOffsets[i];
      GLsizei length = 0;
      detail::getActiveUniform(
          program,
          static_cast<GLuint>(fieldIndices[i]),
          activeUniformMaxLength,
          &length, // Exluding null-termination!
          &field.size,
          &field.type,
          &field.name[0]);
      field.name.resize(length);
      _fields.push_back(field);
    }

    // Sort in increasing offset order.
    std::sort(_fields.begin(), _fields.end(),
              [](Field const& lhs, Field const& rhs) {
                return lhs.offset < rhs.offset;
              });
  }

  GLuint program() const {
    return _program;
  }

  GLuint index() const {
    return _index;
  }

  void bind(GLuint const uniformBlockBinding) const {
    detail::uniformBlockBinding(_program, _index, uniformBlockBinding);
  }

  //! Returns size of block in bytes.
  GLint size() const {
    GLint size = -1;
    detail::getActiveUniformBlockiv(
      _program,
      _index,
      GL_UNIFORM_BLOCK_DATA_SIZE,
      &size);
    return size;
  }

  GLuint binding() const {
    GLint binding = -1;
    detail::getActiveUniformBlockiv(
      _program,
      _index,
      GL_UNIFORM_BLOCK_BINDING,
      &binding);
    return static_cast<GLuint>(binding);
  }

  FieldIterator fieldsBegin() const {
    return _fields.begin();
  }

  FieldIterator fieldsEnd() const {
    return _fields.end();
  }

private:
  GLuint _index;
  GLuint _program;
  FieldContainer _fields;
};


//! DOCS
class ShaderProgram {
public:
  typedef std::map<std::string, Attrib> AttribContainer;
  typedef std::map<std::string, Uniform> UniformContainer;
  typedef std::map<std::string, UniformBlock> UniformBlockContainer;
  typedef AttribContainer::const_iterator AttribIterator;
  typedef UniformContainer::const_iterator UniformIterator;
  typedef UniformBlockContainer::const_iterator UniformBlockIterator;

  //! CTOR.
  ShaderProgram(VertexShader const& vs, FragmentShader const& fs)
    : _handle(detail::createProgram())
  {
    throwIfInvalidHandle();
    attachShader(vs);
    attachShader(fs);
    link();
    detachShader(vs);
    detachShader(fs);
  }

  //! CTOR.
  ShaderProgram(VertexShader const& vs,
                GeometryShader const& gs,
                FragmentShader const& fs)
    : _handle(detail::createProgram())
  {
    throwIfInvalidHandle();
    attachShader(vs);
    attachShader(gs);
    attachShader(fs);
    link();
    detachShader(vs);
    detachShader(gs);
    detachShader(fs);
  }

  //! DTOR.
  ~ShaderProgram() {
    detail::deleteProgram(_handle);
  }

  GLuint handle() const {
    return _handle;
  }

  //! Enable shader program.
  void bind() const {
    detail::useProgram(_handle);
  }

  //! Disabled shader program.
  void release() const {
    detail::useProgram(0);
  }

  bool isLinked() const {
    GLint linkStatus = GL_FALSE;
    detail::getProgramiv(_handle, GL_LINK_STATUS, &linkStatus);
    return linkStatus == GL_TRUE;
  }

  std::string infoLog() const {
    std::string str;
    GLint maxLength = 0;
    detail::getProgramiv(_handle, GL_INFO_LOG_LENGTH, &maxLength);
    if (maxLength > 0) { // Info exists.
      str.resize(maxLength);
      GLsizei logLength = 0;
      detail::getProgramInfoLog(_handle,
                                static_cast<GLsizei>(maxLength),
                                &logLength, // Excluding null-termination!
                                &str[0]); // Null-terminated.
      str.resize(logLength + 1); // Trim.
    }
    return str;
  }

  // Active uniforms.

  UniformIterator activeUniformsBegin() const {
    return _uniforms.begin();
  }

  UniformIterator activeUniformsEnd() const {
    return _uniforms.end();
  }

  Uniform const* queryActiveUniform(std::string const& name) const {
    UniformIterator const iter = _uniforms.find(name);
    return (iter != _uniforms.end()) ? &iter->second : nullptr;
  }

  Uniform const& activeUniform(std::string const& name) const {
    UniformIterator const iter = _uniforms.find(name);
    if (iter == _uniforms.end()) {
      NDJINN_THROW("unknown uniform: '" << name << "'");
    }
    return iter->second;
  }

  // Active uniform blocks.

  UniformBlockIterator activeUniformBlocksBegin() const {
    return _uniformBlocks.begin();
  }

  UniformBlockIterator activeUniformBlocksEnd() const {
    return _uniformBlocks.end();
  }

  UniformBlock const* queryActiveUniformBlock(std::string const& name) const {
    UniformBlockIterator const iter = _uniformBlocks.find(name);
    return (iter != _uniformBlocks.end()) ? &iter->second : nullptr;
  }

  UniformBlock const& activeUniformBlock(std::string const& name) const {
    UniformBlockIterator const iter = _uniformBlocks.find(name);
    if (iter == _uniformBlocks.end()) {
      NDJINN_THROW("unknown uniform block: '" << name << "'");
    }
    return iter->second;
  }

  // Active attribs.

  AttribIterator activeAttribsBegin() const {
    return _attribs.begin();
  }

  AttribIterator activeAttribsEnd() const {
    return _attribs.end();
  }

  Attrib const* queryActiveAttrib(std::string const& name) const {
    AttribIterator const iter = _attribs.find(name);
    return (iter != _attribs.end()) ? &iter->second : nullptr;
  }

  Attrib const& activeAttrib(std::string const& name) const {
    AttribIterator const iter = _attribs.find(name);
    if (iter == _attribs.end()) {
      NDJINN_THROW("unknown attrib: '" << name << "'");
    }
    return iter->second;
  }

  // Uniforms.

  template <class T>
  void uniformValue(Uniform const& uni, T* params) const {
    detail::getUniformv(_handle, uni.location, params);
  }

  template<class T>
  void setUniform1(Uniform const& uni, T const v0) {
    detail::programUniform1<T>(_handle, uni.location, v0);
  }

  template<class T>
  void setUniform2(Uniform const& uni, T const v0, T const v1) {
    detail::programUniform2<T>(_handle, uni.location, v0, v1);
  }

  template<class T>
  void setUniform3(Uniform const& uni, T const v0, T const v1, T const v2) {
    detail::programUniform3<T>(_handle, uni.location, v0, v1, v2);
  }

  template<class T>
  void setUniform4(Uniform const& uni,
                T const v0, T const v1, T const v2, T const v3) {
    detail::programUniform4<T>(_handle, uni.location, v0, v1, v2, v3);
  }

  template<int D, class T>
  void setUniformv(Uniform const& uni, T const* v) {
    detail::programUniformv<D,T>(_handle, uni.location, uni.size, v);
  }

  template<int R, int C>
  void setUniformMatrixfv(Uniform const& uni,
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

  void throwIfInvalidHandle() {
    if (detail::isProgram(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid shader program handle: " << _handle);
    }
  }

  //! Attach a shader to this shader program.
  template<GLenum Type>
  void attachShader(Shader<Type> const& sh) {
    detail::attachShader(_handle, sh.handle());
  }

  //! Detach a shader from this shader program.
  template<GLenum Type>
  void detachShader(Shader<Type> const& sh) {
    detail::detachShader(_handle, sh.handle());
  }

  void link() {
    detail::linkProgram(_handle);
    if (!isLinked()) {
      NDJINN_THROW("shader program link error: "
                   << _handle << ": " << infoLog());
    }

    detail::validateProgram(_handle);
    GLint validateStatus = GL_FALSE;
    detail::getProgramiv(_handle, GL_VALIDATE_STATUS, &validateStatus);
    if (validateStatus == GL_FALSE) {
      NDJINN_THROW("shader program validation error: "
                   << _handle << ": " << infoLog());
    }

    // Successful link and validation. Now get some info about the shader.
    updateActiveUniforms();
    updateActiveUniformBlocks();
    updateActiveAttribs();
  }

  void updateActiveUniforms() {
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

      // Don't store uniform that are part of a block.
      if (uni.location != -1) {
        _uniforms.insert(UniformContainer::value_type(name, uni));
      }
    }
  }

  void updateActiveUniformBlocks() {
    _uniformBlocks.clear();
    GLint activeUniformBlocks = 0;
    detail::getProgramiv(_handle, GL_ACTIVE_UNIFORM_BLOCKS,
                         &activeUniformBlocks);
    std::string uniformBlockName;
    for (GLint i = 0; i < activeUniformBlocks; ++i) {
      // Get the name if the i'th uniform block.
      GLint uniformBlockNameLength = -1;
      detail::getActiveUniformBlockiv(
        _handle,
        static_cast<GLuint>(i),
        GL_UNIFORM_BLOCK_NAME_LENGTH,
        &uniformBlockNameLength);

      uniformBlockName.resize(uniformBlockNameLength);
      GLsizei length = -1;
      detail::getActiveUniformBlockName(
        _handle,
        static_cast<GLuint>(i),
        static_cast<GLsizei>(uniformBlockName.size()),
        &length,
        &uniformBlockName[0]);
      uniformBlockName.resize(length);

      // Get the index of the i'th uniform block.
      GLuint uniformBlockIndex =
        detail::getUniformBlockIndex(_handle, &uniformBlockName[0]);

      _uniformBlocks.insert(
        UniformBlockContainer::value_type(
          uniformBlockName, UniformBlock(uniformBlockIndex, _handle)));
    }
  }

  void updateActiveAttribs() {
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
      _attribs.insert(AttribContainer::value_type(name, attr));
    }
  }

  GLuint _handle; //!< Resource handle.
  AttribContainer _attribs;
  UniformContainer _uniforms;
  UniformBlockContainer _uniformBlocks;
};

NDJINN_END_NAMESPACE

namespace std {

ostream& operator<<(ostream& os, ndj::ShaderProgram const& sp)
{
  using namespace ndj;

  os << "ShaderProgram" << endl
     << "  Handle: " << sp.handle() << endl
     << "  Linked: " << sp.isLinked() << endl;

  os << "  Uniforms: " << endl;
  if (sp.activeUniformsBegin() != sp.activeUniformsEnd()) {
      for (auto iter = sp.activeUniformsBegin();
           iter != sp.activeUniformsEnd(); ++iter) {
        Uniform const& uni = iter->second;
        os << "  Location: " << uni.location
           << ", Name: '" << iter->first
           << "', Type: " << detail::uniformTypeToString(uni.type)
             << "[" << uni.size << "]" << endl;
      }
  }
  else {
    os << "    <empty>" << endl;
  }

  os << "  Uniform blocks: " << endl;
  for (auto iter = sp.activeUniformBlocksBegin();
       iter != sp.activeUniformBlocksEnd(); ++iter) {
    UniformBlock const& ub = iter->second;
    os << "    Block: "
       << "Index: " << ub.index()
       << ", Name: '" << iter->first << "'"
       << ", Binding: " << ub.binding()
       << ", Size: " << ub.size() << " [bytes]" << endl;

    for (auto iter = ub.fieldsBegin();
         iter != ub.fieldsEnd(); ++iter) {
      UniformBlock::Field const& field = *iter;
      os << "      Field: "
         << "Offset: " << field.offset
         << ", Type: " << detail::uniformTypeToString(field.type)
           << "[" << field.size << "]"
         << ", Index: " << field.blockIndex
         << ", Name: '" << field.name << "'" << endl;
    }
  }

  os << "Attributes: " << endl;
  for (auto iter = sp.activeAttribsBegin();
       iter != sp.activeAttribsEnd(); ++iter) {
    Attrib const& attrib = iter->second;
    os << "  Attribute: "
       << "Location: " << attrib.location
       << ", Name: '" << iter->first
       << "', Type: " << detail::attribTypeToString(attrib.type)
         << "[" << attrib.size << "]" << endl;
  }

  return os;
}

} // namespace std

#endif // NDJINN_SHADER_PROGRAM_HPP_INCLUDED
