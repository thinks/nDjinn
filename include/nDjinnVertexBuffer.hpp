// -----------------------------------------------------------------------------
//
// Copyright (C) Tommy Hinks						  
// tommy[dot]hinks[at]gmail[dot]com  											
//
// Contributors: 
//             1) Tommy Hinks
//
// -----------------------------------------------------------------------------

#ifndef NDJINN_VERTEX_BUFFER_HPP_INCLUDED
#define NDJINN_VERTEX_BUFFER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! Generate n buffer handles. May throw.
inline void 
genBuffers(const GLsizei n, GLuint *buffers) { 
  glGenBuffers(n, buffers); 
  checkError("glGenBuffers"); 
}

//! Free handle resources. May throw.
inline void
deleteBuffers(const GLsizei n, const GLuint *buffers) { 
  glDeleteBuffers(n, buffers); 
  checkError("glDeleteBuffers");
}

//! Make buffer the currently bound buffer. May throw.
inline void
bindBuffer(const GLenum target, const GLuint buffer) { 
  glBindBuffer(target, buffer); 
  checkError("glBindBuffer"); 
}

//! glBindBufferBase wrapper. May throw.
inline void
bindBufferBase(const GLenum target, const GLuint index, const GLuint buffer) {
  glBindBufferBase(target, index, buffer);
  checkError("glBindBufferBase");
}

inline void 
bindBufferRange(const GLenum target, 
                const GLuint index, 
                const GLuint buffer, 
                const GLintptr offset, 
                const GLsizeiptr size) {
  glBindBufferRange(target, index, buffer, offset, size);
  checkError("glBindBufferRange");
}

//! Reserve 'size' bytes in buffer. If 'data' is non-null also copy 
//! data into buffer. May throw.
inline void
bufferData(const GLenum target, 
           const GLsizeiptr size,
           const void *data, 
           const GLenum usage) { 
  glBufferData(target, size, data, usage); 
  checkError("glBufferData"); 
}

//! Copy data to buffer. May throw.
inline void
bufferSubData(const GLenum target, 
              const GLintptr offset, 
              const GLsizeiptr size, 
              const GLvoid *data) {
  glBufferSubData(target, offset, size, data);
  checkError("glBufferSubData"); 
}

//! Read data from buffer. May throw.
inline void
getBufferSubData(const GLenum target, 
                 const GLintptr offset, 
                 const GLsizeiptr size, 
                 GLvoid *data) {
  glGetBufferSubData(target, offset, size, data);
  checkError("glGetBufferSubData"); 
}

//! Retrieve (currently bound) buffer parameters from OpenGL. May throw.
inline void
getBufferParameteriv(const GLenum target, const GLenum pname, GLint *data) { 
  glGetBufferParameteriv(target, pname, data); 
  checkError("glGetBufferParameteriv"); 
}

} // Namespace: detail.

//------------------------------------------------------------------------------

class VertexBuffer
{
public:

  explicit
  VertexBuffer(GLenum target = GL_ARRAY_BUFFER);

  explicit
  VertexBuffer(GLsizeiptr size,   
               const GLvoid *data,
               GLenum usage  = GL_STATIC_DRAW,
               GLenum target = GL_ARRAY_BUFFER);

  ~VertexBuffer();

public:

  GLenum     
  target() const;

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
  bufferData(GLsizeiptr size, 
             const GLvoid *data  = 0, 
             GLenum usage = GL_STATIC_DRAW);

  void 
  bufferSubData(GLintptr offset, GLsizeiptr size, const GLvoid *data);

  void 
  getBufferSubData(GLintptr offset, GLsizeiptr size, GLvoid *data) const;

  // TODO: map
  // TODO: unmap

public:

  // The following functions retrieve buffer parameters from the driver.
  // There may be a performance penalty involved, so use with caution.
  // Note that these functions operate on the currently "bound" buffer.

  GLint 
  size() const;

  GLint 
  access() const;

  GLint  
  mapped() const;

  GLint 
  usage() const;

private:

  //! DOCS
  //! TODO: _Bindor should probably restore the previous binding on destruction
  //!       rather than set it to zero.
  class _Bindor
  {
  public:

    //! CTOR.
    explicit _Bindor(const VertexBuffer *vbo)
      : _vbo(vbo) { 
      vbo->bind(); 
    }

    //! DTOR.
    ~_Bindor() { 
      try { 
        _vbo->release(); 
      } 
      catch (...) {
      } 
    }

  private: // Member variables.
    const VertexBuffer *_vbo;
  };

  VertexBuffer(const VertexBuffer&);              //!< Disabled copy.
  VertexBuffer& operator=(const VertexBuffer&);   //!< Disabled assign.

private: // Member variables.
  GLenum _target;
  GLuint _handle; //!< OpenGL handle.
};

// -----------------------------------------------------------------------------

//! CTOR. Construct an empty VBO, no resources (except the handle)
//! are allocated.
inline
VertexBuffer::VertexBuffer(const GLenum target)
  : _target(target)
  , _handle(0) 
{
  detail::genBuffers(1, &_handle); // May throw.
  if (_handle == 0) {
      NDJINN_THROW("Null vertex buffer handle");
  }
}

//! CTOR. Construct a VBO from a single chunk of memory. Note that
//! if data is null the buffer will be allocated but nothing copied.
inline
VertexBuffer::VertexBuffer(const GLsizeiptr size, // [bytes]
                           const GLvoid *data,
                           const GLenum usage,
                           const GLenum target)
  : _target(target)
  , _handle(0) 
{
  try {
    detail::genBuffers(1, &_handle); // May throw.
    if (_handle == 0) {
      NDJINN_THROW("Null vertex buffer handle");
    }
    bufferData(size, data, usage);
  }
  catch (...) {
    detail::deleteBuffers(1, &_handle);       // Clean up.
    throw;                             // Rethrow.
  }
}

//! DTOR. Free handle resource.
inline
VertexBuffer::~VertexBuffer() { 
  try { 
    detail::deleteBuffers(1, &_handle); 
  }
  catch (...) {
  }
}

// -----------------------------------------------------------------------------

//! Return buffer target, usually GL_ARRAY_BUFFER.
inline GLenum     
VertexBuffer::target() const { 
  return _target; 
}

//! Expose resource handle.
inline GLuint
VertexBuffer::handle() const { 
  return _handle; 
}

//! Bind buffer. May throw.
inline void 
VertexBuffer::bind() const { 
  detail::bindBuffer(_target, _handle);
}

//! DOCS
inline void
VertexBuffer::bindBase(const GLuint index) const {
  detail::bindBufferBase(_target, index, _handle);
}

//! DOCS
inline void
VertexBuffer::bindRange(const GLuint index, 
                        const GLintptr offset, 
                        const GLsizeiptr size) const {
  detail::bindBufferRange(_target, index, _handle, offset, size);
}

//! Release buffer. May throw.
inline void 
VertexBuffer::release() const { 
  detail::bindBuffer(_target, 0);
}

//! Upload data to GPU memory. If data is null, memory gets allocated but
//! nothing gets transferred. This is useful for populating a VBO from
//! several sub-buffers. May throw.
inline void 
VertexBuffer::bufferData(const GLsizeiptr size, // [bytes]
                         const GLvoid *data,
                         const GLenum usage) {
  _Bindor bind(this);
  detail::bufferData(_target, size, data, usage);
}

//! Upload data to GPU memory. Size of buffer remains constant. May throw.
inline void 
VertexBuffer::bufferSubData(const GLintptr offset,
                            const GLsizeiptr size, // [bytes]
                            const GLvoid *data) {
  _Bindor bind(this);
  detail::bufferSubData(_target, offset, size, data); 
}

//! Copy data from the buffer in the provided memory. May throw.
inline void 
VertexBuffer::getBufferSubData(const GLintptr offset,
                               const GLsizeiptr size, // [bytes]
                               GLvoid *data) const {
  _Bindor bind(this);
  detail::getBufferSubData(_target, offset, size, data); 
}

// -----------------------------------------------------------------------------

//! Return currently bound buffer size in bytes. May throw.
inline GLint 
VertexBuffer::size() const { 
  _Bindor bind(this);
  GLint size = 0; // Default/initial value.
  detail::getBufferParameteriv(_target, GL_BUFFER_SIZE, &size); 
  return size;
} 

//! Return currently bound buffer access mode. May throw.
inline GLint 
VertexBuffer::access() const {
  _Bindor bind(this);
  GLint access = GL_READ_WRITE; // Default/initial value.
  detail::getBufferParameteriv(_target, GL_BUFFER_ACCESS, &access); 
  return access;
}

//! Return GL_TRUE if currently bound buffer is currently mapped, otherwise
//! GL_FALSE. May throw.
inline GLint  
VertexBuffer::mapped() const {
  _Bindor bind(this);
  GLint mapped = GL_FALSE; // Default/initial value.
  detail::getBufferParameteriv(_target, GL_BUFFER_MAPPED, &mapped); 
  return mapped;
}

//! Return currently bound buffer usage mode. May throw.
inline GLint 
VertexBuffer::usage() const {
  _Bindor bind(this);
  GLint usage = GL_STATIC_DRAW; // Default/initial value.
  detail::getBufferParameteriv(_target, GL_BUFFER_USAGE, &usage);
  return usage;
}

NDJINN_END_NAMESPACE

#endif // NDJINN_VERTEX_BUFFER_HPP_INCLUDED
