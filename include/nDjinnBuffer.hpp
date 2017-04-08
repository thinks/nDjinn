//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_BUFFER_HPP_INCLUDED
#define NDJINN_BUFFER_HPP_INCLUDED

#include <iostream>
#include <string>

#include "nDjinnError.hpp"
#include "nDjinnException.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! Generate @a n buffer handles. May throw.
inline void genBuffers(GLsizei const n, GLuint *buffers) { 
  glGenBuffers(n, buffers); 
  checkError("glGenBuffers"); 
}

//! Free handle resources. May throw.
inline void deleteBuffers(GLsizei const n, GLuint const* buffers) {
  glDeleteBuffers(n, buffers); 
  checkError("glDeleteBuffers");
}

//! Make buffer the currently bound buffer. May throw.
inline void bindBuffer(GLenum const target, GLuint const buffer) {
  glBindBuffer(target, buffer); 
  checkError("glBindBuffer"); 
}

//! glBindBufferBase wrapper. May throw.
inline void bindBufferBase(GLenum const target,
                           GLuint const index,
                           GLuint const buffer) {
  glBindBufferBase(target, index, buffer);
  checkError("glBindBufferBase");
}

//! glBindBufferRange wrapper. May throw.
inline void bindBufferRange(GLenum const target, 
                            GLuint const index,
                            GLuint const buffer,
                            GLintptr const offset,
                            GLsizeiptr const size) {
  glBindBufferRange(target, index, buffer, offset, size);
  checkError("glBindBufferRange");
}

//! glIsBuffer wrapper. May throw.
inline GLboolean isBuffer(GLuint const buffer) {
  GLboolean const isBuffer = glIsBuffer(buffer);
  checkError("glIsBuffer"); 
  return isBuffer;
}

// Named version of buffer operations. These version avoid
// having to bind/release a certain buffer every time it is used.

//! glNamedBufferData wrapper. May throw.
inline void namedBufferData(GLuint const buffer,
                            GLsizeiptr const size,
                            GLvoid const* data,
                            GLenum const usage) {
  glNamedBufferDataEXT(buffer, size, data, usage);
  checkError("glNamedBufferDataEXT");
}

//! glNamedBufferSubData wrapper. May throw.
inline void namedBufferSubData(GLuint const buffer,
                               GLintptr const offset,
                               GLsizeiptr const size,
                               GLvoid const* data) {
  glNamedBufferSubDataEXT(buffer, offset, size, data);
  checkError("glNamedBufferSubDataEXT");
}

//! glGetNamedBuffersSubData wrapper. May throw.
inline void getNamedBufferSubData(GLuint const buffer,
                                  GLintptr const offset,
                                  GLsizeiptr const size,
                                  GLvoid* data) {
  glGetNamedBufferSubDataEXT(buffer, offset, size, data);
  checkError("glGetNamedBufferSubDataEXT");
}

//! glMapNamedBuffer wrapper. May throw.
inline GLvoid* mapNamedBuffer(GLuint const buffer,
                              GLenum const access) {
  GLvoid* ptr = glMapNamedBufferEXT(buffer, access);
  checkError("glMapNamedBufferEXT");
  return ptr;
}

//! glUnmapNamedBuffer wrapper. May throw.
inline GLboolean unmapNamedBuffer(GLuint const buffer) {
  GLboolean const mapped = glUnmapNamedBufferEXT(buffer);
  checkError("glUnmapNamedBufferEXT");
  return mapped;
}

//! glGetNamedBufferParameteriv wrapper. May throw.
inline void getNamedBufferParameteriv(GLuint const buffer,
                                      GLenum const pname,
                                      GLint* params) {
  glGetNamedBufferParameterivEXT(buffer, pname, params);
  checkError("glGetNamedBufferParameterivEXT");
}

//! glGetNamedBufferPointerv wrapper. May throw.
inline void getNamedBufferPointerv(GLuint const buffer,
                                   GLenum const pname,
                                   GLvoid** params) {
  glGetNamedBufferPointervEXT(buffer, pname, params);
  checkError("glGetNamedBufferPointervEXT");
}

//! Convenience, generate a single buffer handle and return it. May throw.
inline GLuint genBuffer() {
  GLuint handle = 0;
  genBuffers(1, &handle);
  return handle;
}

//! Convenience.
inline void deleteBuffer(GLuint const handle) {
  deleteBuffers(1, &handle);
}

#if 0 // Where to put this stuff?
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
GLuint bufferBinding() {
  GLint binding = 0;
  getIntegerv(BufferBinding<T>::value, &binding);
  return binding;
}
#endif

//! DOCS
inline std::string bufferTargetToString(GLenum const target) {
  using std::string;

  switch (target) {
  case GL_ARRAY_BUFFER:               return string("GL_ARRAY_BUFFER");
  case GL_ATOMIC_COUNTER_BUFFER:      return string("GL_ATOMIC_COUNTER_BUFFER");
  case GL_COPY_READ_BUFFER:           return string("GL_COPY_READ_BUFFER");
  case GL_COPY_WRITE_BUFFER:          return string("GL_COPY_WRITE_BUFFER");
  //case GL_DISPATCH_INDIRECT_BUFFER:   return string("GL_DISPATCH_INDIRECT_BUFFER");
  case GL_DRAW_INDIRECT_BUFFER:       return string("GL_DRAW_INDIRECT_BUFFER");
  case GL_ELEMENT_ARRAY_BUFFER:       return string("GL_ELEMENT_ARRAY_BUFFER");
  case GL_PIXEL_PACK_BUFFER:          return string("GL_PIXEL_PACK_BUFFER");
  case GL_PIXEL_UNPACK_BUFFER:        return string("GL_PIXEL_UNPACK_BUFFER");
  //case GL_QUERY_BUFFER:               return string("GL_QUERY_BUFFER");
  //case GL_SHADER_STORAGE_BUFFER:      return string("GL_SHADER_STORAGE_BUFFER");
  case GL_TEXTURE_BUFFER:             return string("GL_TEXTURE_BUFFER");
  case GL_TRANSFORM_FEEDBACK_BUFFER:  return string("GL_TRANSFORM_FEEDBACK_BUFFER");
  case GL_UNIFORM_BUFFER:             return string("GL_UNIFORM_BUFFER");
  }
  NDJINN_THROW("unrecognized buffer target: " << target);
}

//! DOCS
inline std::string bufferUsageToString(GLenum const usage) {
  using std::string;

  switch (usage) {
  case GL_STREAM_DRAW:  return string("GL_STREAM_DRAW");
  case GL_STREAM_READ:  return string("GL_STREAM_READ");
  case GL_STREAM_COPY:  return string("GL_STREAM_COPY");
  case GL_STATIC_DRAW:  return string("GL_STATIC_DRAW");
  case GL_STATIC_READ:  return string("GL_STATIC_READ");
  case GL_STATIC_COPY:  return string("GL_STATIC_COPY");
  case GL_DYNAMIC_DRAW: return string("GL_DYNAMIC_DRAW");
  case GL_DYNAMIC_READ: return string("GL_DYNAMIC_READ");
  case GL_DYNAMIC_COPY: return string("GL_DYNAMIC_COPY");
  }
  NDJINN_THROW("unrecognized buffer usage: " << usage);
}

} // Namespace: detail.

//! DOCS
template<GLenum TargetT>
class Buffer {
public:
  static GLenum const TARGET = TargetT;

  //! CTOR. Construct an empty buffer, no resources (except the handle)
  //! are allocated.
  Buffer()
    : _handle(detail::genBuffer())
  {
    throwIfInvalidHandle();
  }

  //! CTOR. Construct a VBO from a single chunk of memory. Note that
  //! if data is null the buffer will be allocated but nothing copied.
  Buffer(GLsizeiptr const size,
         GLvoid const* ptr,
         GLenum const usage = GL_STATIC_DRAW)
    : _handle(detail::genBuffer())
  {
    //throwIfInvalidHandle();
    setData(size, ptr, usage);
  }

  //! DTOR
  ~Buffer() {
    detail::deleteBuffer(_handle);
  }

  //! Expose resource handle.
  GLuint handle() const {
    return _handle;
  }

  //! Bind buffer.
  void bind() const {
    detail::bindBuffer(TARGET, _handle);
  }

  //! DOCS
  void bindBase(GLuint const index) const {
    detail::bindBufferBase(TARGET, index, _handle);
  }

  //! DOCS
  void bindRange(GLuint const index,
                 GLintptr const offset,
                 GLsizeiptr const size) const {
    detail::bindBufferRange(TARGET, index, _handle, offset, size);
  }

  //! Release buffer.
  void release() const {
    detail::bindBuffer(TARGET, 0);
  }

  //! Copy data from the buffer in the provided memory.
  template <typename E>
  void getSubData(GLintptr const offsetInBytes,
                  GLsizeiptr const sizeInBytes,
                  E* ptr) const {
    detail::getNamedBufferSubData(_handle,
                                  offsetInBytes,
                                  sizeInBytes,
                                  reinterpret_cast<GLvoid*>(ptr));
  }

  //! Upload data to GPU memory. If data is null, memory gets allocated but
  //! nothing gets transferred. This is useful for populating a VBO from
  //! several sub-buffers.
  void setData(GLsizeiptr const sizeInBytes,
               GLvoid const* ptr = 0,
               GLenum const usage = GL_STATIC_DRAW) {
    detail::namedBufferData(_handle, sizeInBytes, ptr, usage);
  }

  //! Upload data to GPU memory. Size of buffer remains constant.
  void setSubData(GLintptr const offset,
                  GLsizeiptr const size,
                  GLvoid const* ptr) {
    detail::namedBufferSubData(_handle, offset, size, ptr);
  }

  //! DOCS
  template <typename E>
  E* map(GLenum const access) {
    return reinterpret_cast<E*>(detail::mapNamedBuffer(_handle, access));
  }

  //! DOCS
  bool unmap() {
    return detail::unmapNamedBuffer() == GL_TRUE;
  }

  // The following functions retrieve buffer parameters from the driver.
  // There may be a performance penalty involved, so use with caution.

  //! Return buffer size in bytes. May throw.
  GLint sizeInBytes() const {
    GLint size = -1;
    detail::getNamedBufferParameteriv(_handle, GL_BUFFER_SIZE, &size);
    return size;
  }

  //! Return buffer usage mode.
  GLint usage() const {
    GLint usage = -1;
    detail::getNamedBufferParameteriv(TARGET, GL_BUFFER_USAGE, &usage);
    return usage;
  }

  //! Return true if this buffer is currently mapped, otherwise false.
  bool mapped() const {
    GLint mapped = -1;
    detail::getNamedBufferParameteriv(TARGET, GL_BUFFER_MAPPED, &mapped);
    return mapped == GL_TRUE;
  }

private:
  Buffer(Buffer<TargetT> const&); //!< Disabled copy.
  Buffer& operator=(Buffer<TargetT> const&); //!< Disabled assign.

  void throwIfInvalidHandle() {
    if (detail::isBuffer(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid buffer handle: " << _handle);
    }
  }

  GLuint const _handle; //!< Resource handle.
};

typedef Buffer<GL_ARRAY_BUFFER> ArrayBuffer;
typedef Buffer<GL_ELEMENT_ARRAY_BUFFER> ElementArrayBuffer;
typedef Buffer<GL_UNIFORM_BUFFER> UniformBuffer;

template<typename E, typename Size, GLenum Target> inline
Size elementCount(Buffer<Target> const& buffer) {
  return static_cast<Size>(buffer.size() / sizeof(E));
}

NDJINN_END_NAMESPACE

namespace std {

template<GLenum TargetT> inline
ostream& operator<<(ostream& os, ndj::Buffer<TargetT> const& buf)
{
  os << "Buffer<"
       << ndj::detail::bufferTargetToString(ndj::Buffer<TargetT>::TARGET)
       << ">" << endl
     << "  Handle: " << buf.handle() << endl
     << "  Size: " << buf.sizeInBytes() << " [bytes]" << endl
     << "  Usage: " << ndj::detail::bufferUsageToString(buf.usage()) << endl
     << "  Mapped: " << buf.mapped() << endl
     << "  " << endl;
  return os;
}

} // namespace std

#endif // NDJINN_BUFFER_HPP_INCLUDED
