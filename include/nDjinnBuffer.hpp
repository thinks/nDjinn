// -----------------------------------------------------------------------------
//
// Copyright (C) Tommy Hinks              
// tommy[dot]hinks[at]gmail[dot]com                       
//
// Contributors: 
//             1) Tommy Hinks
//
// -----------------------------------------------------------------------------

#ifndef NDJINN_BUFFER_HPP_INCLUDED
#define NDJINN_BUFFER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! Generate n buffer handles. May throw.
inline void 
genBuffers(GLsizei const n, GLuint *buffers) { 
  glGenBuffers(n, buffers); 
  checkError("glGenBuffers"); 
}

//! Free handle resources. May throw.
inline void
deleteBuffers(GLsizei const n, GLuint const* buffers) { 
  glDeleteBuffers(n, buffers); 
  checkError("glDeleteBuffers");
}

//! Make buffer the currently bound buffer. May throw.
inline void
bindBuffer(GLenum const target, GLuint const buffer) { 
  glBindBuffer(target, buffer); 
  checkError("glBindBuffer"); 
}

//! glBindBufferBase wrapper. May throw.
inline void
bindBufferBase(GLenum const target, GLuint const index, GLuint const buffer) {
  glBindBufferBase(target, index, buffer);
  checkError("glBindBufferBase");
}

inline void 
bindBufferRange(GLenum const target, 
                GLuint const index, 
                GLuint const buffer, 
                GLintptr const offset, 
                GLsizeiptr const size) {
  glBindBufferRange(target, index, buffer, offset, size);
  checkError("glBindBufferRange");
}

//! Reserve 'size' bytes in buffer. If 'data' is non-null also copy 
//! data into buffer. May throw.
inline void
bufferData(GLenum const target, 
           GLsizeiptr const size,
           GLvoid const* data, 
           GLenum const usage) { 
  glBufferData(target, size, data, usage); 
  checkError("glBufferData"); 
}

//! Copy data to buffer. May throw.
inline void
bufferSubData(GLenum const target, 
              GLintptr const offset, 
              GLsizeiptr const size, 
              GLvoid const* data) {
  glBufferSubData(target, offset, size, data);
  checkError("glBufferSubData"); 
}

//! Read data from buffer. May throw.
inline void
getBufferSubData(GLenum const target, 
                 GLintptr const offset, 
                 GLsizeiptr const size, 
                 GLvoid *data) {
  glGetBufferSubData(target, offset, size, data);
  checkError("glGetBufferSubData"); 
}

//! Retrieve (currently bound) buffer parameters from OpenGL. May throw.
inline void
getBufferParameteriv(GLenum const target, GLenum const pname, GLint *data) { 
  glGetBufferParameteriv(target, pname, data); 
  checkError("glGetBufferParameteriv"); 
}

//! glIsBuffer wrapper. May throw.
inline GLboolean
isBuffer(GLuint const buffer) {
  GLboolean const isBuffer = glIsBuffer(buffer);
  checkError("glIsBuffer"); 
  return isBuffer;
}

template<GLenum T>
struct BufferBinding;

template<>
struct BufferBinding<GL_ARRAY_BUFFER> {
  static GLenum const value = GL_ARRAY_BUFFER_BINDING;
};

template<>
struct BufferBinding<GL_ELEMENT_ARRAY_BUFFER> {
  static GLenum const value = GL_ELEMENT_ARRAY_BUFFER_BINDING;
};

template<>
struct BufferBinding<GL_UNIFORM_BUFFER> {
  static GLenum const value = GL_UNIFORM_BUFFER_BINDING;
};

template<GLenum T> inline
GLuint
bufferBinding() {
  GLint binding = 0;
  getIntegerv(BufferBinding<T>::value, &binding);
  return binding;
}

//! Convenience, generate a single buffer handle and return it. May throw.
inline GLuint
genBuffer() {
  GLuint handle = 0;
  genBuffers(1, &handle);
  return handle;
}

//! Convenience.
inline void 
deleteBuffer(GLuint const& handle) {
  deleteBuffers(1, &handle);
}


// Named version of buffer operations. These version avoid 
// having to bind/release a certain buffer every time it is used.

void 
namedBufferData(GLuint const buffer, 
                GLsizeiptr const size,
                GLvoid const* data, 
                GLenum const usage) {
  glNamedBufferDataEXT(buffer, size, data, usage);
  checkError("glNamedBufferDataEXT"); 
}

void 
namedBufferSubData(GLuint const buffer, 
                   GLintptr const offset,
                   GLsizeiptr const size, 
                   GLvoid const* data) {
  glNamedBufferSubDataEXT(buffer, offset, size, data);
  checkError("glNamedBufferSubDataEXT"); 
}

GLvoid* 
mapNamedBuffer(GLuint const buffer, 
               GLenum const access) {
  GLvoid* ptr = glMapNamedBufferEXT(buffer, access);
  checkError("glMapNamedBufferEXT"); 
  return ptr;
}

GLboolean 
unmapNamedBuffer(GLuint const buffer) {
  GLboolean const mapped = glUnmapNamedBufferEXT(buffer);
  checkError("glUnmapNamedBufferEXT"); 
  return mapped;
}

void 
getNamedBufferParameteriv(GLuint const buffer,
                          GLenum const pname, 
                          GLint *params) {
  glGetNamedBufferParameterivEXT(buffer, pname, params);
  checkError("glGetNamedBufferParameterivEXT"); 
}

void 
getNamedBufferPointerv(GLuint const buffer,
                       GLenum const pname, 
                       GLvoid** params) {
  glGetNamedBufferPointervEXT(buffer, pname, params);
  checkError("glGetNamedBufferPointervEXT"); 
}

void 
getNamedBufferSubData(GLuint const buffer,
                      GLintptr const offset, 
                      GLsizeiptr const size, 
                      GLvoid *data) {
  glGetNamedBufferSubDataEXT(buffer, offset, size, data);
  checkError("glGetNamedBufferSubDataEXT"); 
}

} // Namespace: detail.

//------------------------------------------------------------------------------

//! DOCS
template<GLenum TargetT>
class Buffer {
public:
  static GLenum const TARGET = TargetT;

  explicit
  Buffer();

  explicit
  Buffer(GLsizeiptr size,   
         GLvoid const* ptr,
         GLenum usage = GL_STATIC_DRAW);

  ~Buffer();

public:
  //! Expose resource handle.
  GLuint
  handle() const;

  void 
  bind() const;

  void
  bindBase(GLuint index) const;

  void
  bindRange(GLuint index, GLintptr offset, GLsizeiptr size) const;

  void 
  release() const;

  void 
  data(GLsizeiptr size, 
       GLvoid const* ptr = 0, 
       GLenum usage = GL_STATIC_DRAW);

  void 
  subData(GLintptr offset, GLsizeiptr size, GLvoid const* ptr);

  void 
  getSubData(GLintptr offset, GLsizeiptr size, GLvoid* ptr) const;

  // TODO: map
  // TODO: unmap

public:

  // The following functions retrieve buffer parameters from the driver.
  // There may be a performance penalty involved, so use with caution.

  GLint 
  size() const;

  GLint 
  access() const;

  GLint  
  mapped() const;

  GLint 
  usage() const;

private:
  Buffer(Buffer<TARGET> const&);            //!< Disabled copy.
  Buffer& operator=(Buffer<TARGET> const&); //!< Disabled assign.

private: // Member variables.
  GLuint const _handle; //!< Resource handle.
  mutable GLuint _savedHandle;
};

typedef Buffer<GL_ARRAY_BUFFER> ArrayBuffer;
typedef Buffer<GL_ELEMENT_ARRAY_BUFFER> ElementArrayBuffer;
typedef Buffer<GL_UNIFORM_BUFFER> UniformBuffer;

// -----------------------------------------------------------------------------

//! CTOR. Construct an empty buffer, no resources (except the handle)
//! are allocated.
template<GLenum Target> inline
Buffer<Target>::Buffer()
  : _handle(detail::genBuffer()) // May throw. 
{
  bind(); // Make sure buffer gets created.
  if (detail::isBuffer(_handle) == GL_FALSE) {
    NDJINN_THROW("invalid buffer");
  }
  release();
}

//! CTOR. Construct a VBO from a single chunk of memory. Note that
//! if data is null the buffer will be allocated but nothing copied.
template<GLenum Target> inline
Buffer<Target>::Buffer(GLsizeiptr const size, // [bytes]
                       GLvoid const* ptr,
                       GLenum const usage)
  : _handle(detail::genBuffer()) // May throw.
{
  bind(); // Make sure buffer gets created.
  if (detail::isBuffer(_handle) == GL_FALSE) {
    NDJINN_THROW("invalid buffer");
  }
  data(size, ptr, usage);
  release();
}

//! DTOR. Free handle resource.
template<GLenum Target> inline
Buffer<Target>::~Buffer() { 
  detail::deleteBuffer(_handle); 
}

// -----------------------------------------------------------------------------

//! DOCS
template<GLenum Target> inline 
GLuint
Buffer<Target>::handle() const { 
  return _handle; 
}

//! Bind buffer. May throw.
template<GLenum Target> inline 
void 
Buffer<Target>::bind() const { 
  _savedHandle = detail::bufferBinding<TARGET>();
  if (_savedHandle != _handle) {
    detail::bindBuffer(TARGET, _handle);
  }  
}

//! DOCS
template<GLenum Target> inline 
void
Buffer<Target>::bindBase(GLuint const index) const {
  detail::bindBufferBase(TARGET, index, _handle);
}

//! DOCS
template<GLenum Target> inline 
void
Buffer<Target>::bindRange(GLuint const index, 
                          GLintptr const offset, 
                          GLsizeiptr const size) const {
  detail::bindBufferRange(TARGET, index, _handle, offset, size);
}

//! Release buffer. May throw.
template<GLenum Target> inline 
void 
Buffer<Target>::release() const { 
  if (_savedHandle != _handle) {
    detail::bindBuffer(TARGET, _savedHandle); // May throw.
  }  
}

//! Upload data to GPU memory. If data is null, memory gets allocated but
//! nothing gets transferred. This is useful for populating a VBO from
//! several sub-buffers. May throw.
template<GLenum Target> inline 
void 
Buffer<Target>::data(GLsizeiptr const size, // [bytes]
                     GLvoid const* ptr,
                     GLenum const usage) {
  detail::namedBufferData(_handle, size, ptr, usage);
}

//! Upload data to GPU memory. Size of buffer remains constant. May throw.
template<GLenum Target> inline 
void 
Buffer<Target>::subData(GLintptr const offset, // [bytes]
                        GLsizeiptr const size, // [bytes]
                        GLvoid const* ptr) {
  detail::namedBufferSubData(_handle, offset, size, ptr); 
}

//! Copy data from the buffer in the provided memory. May throw.
template<GLenum Target> inline 
void 
Buffer<Target>::getSubData(GLintptr const offset, // [bytes]
                           GLsizeiptr const size, // [bytes]
                           GLvoid* ptr) const {
  detail::getNamedBufferSubData(_handle, offset, size, ptr); 
}

// -----------------------------------------------------------------------------

//! Return buffer size in bytes. May throw.
template<GLenum Target> inline 
GLint 
Buffer<Target>::size() const { 
  GLint size = 0; // Initial value.
  detail::getNamedBufferParameteriv(_handle, GL_BUFFER_SIZE, &size); 
  return size;
} 

//! Return buffer access mode. May throw.
template<GLenum Target> inline 
GLint 
Buffer<Target>::access() const {
  GLint access = GL_READ_WRITE; // Initial value.
  detail::getNamedBufferParameteriv(_handle, GL_BUFFER_ACCESS, &access); 
  return access;
}

//! Return GL_TRUE if this buffer is currently mapped, otherwise
//! GL_FALSE. May throw.
template<GLenum Target> inline 
GLint  
Buffer<Target>::mapped() const {
  GLint mapped = GL_FALSE; // Initial value.
  detail::getNamedBufferParameteriv(TARGET, GL_BUFFER_MAPPED, &mapped); 
  return mapped;
}

//! Return buffer usage mode. May throw.
template<GLenum Target> inline 
GLint 
Buffer<Target>::usage() const {
  GLint usage = GL_STATIC_DRAW; // Initial value.
  detail::getNamedBufferParameteriv(TARGET, GL_BUFFER_USAGE, &usage);
  return usage;
}

// -----------------------------------------------------------------------------

template<typename E, typename Size, GLenum Target> inline
Size 
elementCount(Buffer<Target> const& buffer) {
  return static_cast<Size>(buffer.size()/sizeof(E));
}

// -----------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif // NDJINN_BUFFER_HPP_INCLUDED
