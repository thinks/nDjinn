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

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

class VertexBuffer
{
public:

    explicit
    VertexBuffer(GLenum target = GL_ARRAY_BUFFER);

    explicit
    VertexBuffer(GLsizeiptr    size,   
                 const GLvoid *data,
                 GLenum        usage  = GL_STATIC_DRAW,
                 GLenum        target = GL_ARRAY_BUFFER);

    ~VertexBuffer();

public:

    GLenum     
    target() const;

    GLuint
    handle() const;

    void 
    bind() const;

    void 
    release() const;

    void 
    bufferData(GLsizeiptr    size,
               const GLvoid *data  = 0,
               GLenum        usage = GL_STATIC_DRAW);

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

private:    // OpenGL wrappers.

    static void 
    _genBuffers(GLsizei n, GLuint *buffers);

    static void
    _deleteBuffers(GLsizei n, const GLuint *buffers);

    static void
    _bindBuffer(GLenum target, GLuint buffer);

    static void
    _bufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

    static void
    _bufferSubData(GLenum target, GLintptr offset, 
                   GLsizeiptr size, const GLvoid *data);

    static void
    _getBufferSubData(GLenum target, GLintptr offset, 
                      GLsizeiptr size, GLvoid *data);

    static void
    _getBufferParameteriv(GLenum target, GLenum pname, GLint *data);

private:

    //! DOCS
    class _Bindor
    {
    public:

        //! CTOR.
        explicit
        _Bindor(const VertexBuffer *vbo)
            : _vbo(vbo)
        { vbo->bind(); }

        //! DTOR.
        ~_Bindor()
        { try { _vbo->release(); } catch (...) {} }

    private:    // Member variables.

        const VertexBuffer *_vbo;
    };

    VertexBuffer(const VertexBuffer&);              //!< Disabled copy.
    VertexBuffer& operator=(const VertexBuffer&);   //!< Disabled assign.

private:        // Member variables.

    GLenum     _target;
    GLuint     _handle;     //!< OpenGL handle.
};

// -----------------------------------------------------------------------------

//! CTOR. Construct an empty VBO, no resources (except the handle)
//! are allocated.
inline
VertexBuffer::VertexBuffer(const GLenum target)
    : _target(target)
    , _handle(0)       
{
    try {
        _genBuffers(1, &_handle); // May throw.
        if (_handle == 0) {
            NDJINN_THROW("Null vertex buffer handle");
        }
    }
    catch (...) {
        _deleteBuffers(1, &_handle);       // Clean up.
        throw;                             // Rethrow.
    }
}


//! CTOR. Construct a VBO from a single chunk of memory. Note that
//! if data is null the buffer will be allocated but nothing copied.
inline
VertexBuffer::VertexBuffer(const GLsizeiptr  size, // [bytes]
                           const GLvoid     *data,
                           const GLenum      usage,
                           const GLenum      target)
    : _target(target)
    , _handle(0)       
{
    try {
        _genBuffers(1, &_handle); // May throw.
        if (_handle == 0) {
            NDJINN_THROW("Null vertex buffer handle");
        }
        bufferData(size, data, usage);
    }
    catch (...) {
        _deleteBuffers(1, &_handle);       // Clean up.
        throw;                             // Rethrow.
    }
}


//! DTOR. Free handle resource.
inline
VertexBuffer::~VertexBuffer()
{ 
    try { _deleteBuffers(1, &_handle); }
    catch (...) {} // TODO: log error!
}

// -----------------------------------------------------------------------------

//! Return buffer target, usually GL_ARRAY_BUFFER.
inline GLenum     
VertexBuffer::target() const
{ 
    return _target; 
}


//! Expose resource handle.
inline GLuint
VertexBuffer::handle() const 
{ 
    return _handle; 
}


//! Bind buffer.
inline void 
VertexBuffer::bind() const 
{ 
    _bindBuffer(_target, _handle); // May throw.
}


//! Release buffer.
inline void 
VertexBuffer::release() const
{ 
    _bindBuffer(_target, 0); // May throw.
}


//! Upload data to GPU memory. If data is null, memory gets allocated but
//! nothing gets transferred. This is useful for populating a VBO from
//! several sub-buffers.
inline void 
VertexBuffer::bufferData(const GLsizeiptr  size, // [bytes]
                         const GLvoid     *data,
                         const GLenum      usage)
{
    _Bindor b(this);
    _bufferData(_target, size, data, usage); // May throw.
}


//! Upload data to GPU memory. Size of buffer remains constant.
inline void 
VertexBuffer::bufferSubData(const GLintptr    offset,
                            const GLsizeiptr  size, // [bytes]
                            const GLvoid     *data)
{
    _Bindor b(this);
    _bufferSubData(_target, offset, size, data); // May throw.
}


//! Copy data from the buffer in the provided memory.
inline void 
VertexBuffer::getBufferSubData(const GLintptr    offset,
                               const GLsizeiptr  size, // [bytes]
                               GLvoid           *data) const
{
    _Bindor b(this);
    _getBufferSubData(_target, offset, size, data); // May throw.
}

// -----------------------------------------------------------------------------

//! Return currently bound buffer size in bytes. May throw.
inline GLint 
VertexBuffer::size() const
{ 
    _Bindor b(this);
    GLint size = 0; // Default/initial value.
    _getBufferParameteriv(_target, GL_BUFFER_SIZE, &size); // May throw.
    return size;
} 


//! Return currently bound buffer access mode. May throw.
inline GLint 
VertexBuffer::access() const
{
    _Bindor b(this);
    GLint access = GL_READ_WRITE; // Default/initial value.
    _getBufferParameteriv(_target, GL_BUFFER_ACCESS, &access); // May throw.
    return access;
}


//! Return GL_TRUE if currently bound buffer is currently mapped, otherwise
//! GL_FALSE. May throw.
inline GLint  
VertexBuffer::mapped() const 
{
    _Bindor b(this);
    GLint mapped = GL_FALSE; // Default/initial value.
    _getBufferParameteriv(_target, GL_BUFFER_MAPPED, &mapped); // May throw.
    return mapped;
}


//! Return currently bound buffer usage mode. May throw.
inline GLint 
VertexBuffer::usage() const
{
    _Bindor b(this);
    GLint usage = GL_STATIC_DRAW; // Default/initial value.
    _getBufferParameteriv(_target, GL_BUFFER_USAGE, &usage); // May throw.
    return usage;
}

// -----------------------------------------------------------------------------

//! Generate n buffer handles. [static]
inline void 
VertexBuffer::_genBuffers(const GLsizei n, GLuint *buffers)
{ 
    glGenBuffers(n, buffers); 
    Error::check("glGenBuffers"); // May throw;
}


//! Free handle resources. [static]
inline void
VertexBuffer::_deleteBuffers(const GLsizei n, const GLuint *buffers)
{ 
    glDeleteBuffers(n, buffers); 
    Error::check("glDeleteBuffers"); // May throw;
}


//! Make buffer the currently bound buffer. [static]
inline void
VertexBuffer::_bindBuffer(const GLenum target, const GLuint buffer)
{ 
    glBindBuffer(target, buffer); 
    Error::check("glBindBuffer"); // May throw;
}


//! Reserve 'size' bytes in buffer. If 'data' is non-null also copy 
//! data into buffer. [static]
inline void
VertexBuffer::_bufferData(const GLenum      target, 
                          const GLsizeiptr  size,
                          const void       *data, 
                          const GLenum      usage)
{ 
    glBufferData(target, size, data, usage); 
    Error::check("glBufferData"); // May throw;
}


//! Copy data to buffer. [static]
inline void
VertexBuffer::_bufferSubData(const GLenum      target, 
                             const GLintptr    offset, 
                             const GLsizeiptr  size, 
                             const GLvoid     *data)
{
    glBufferSubData(target, offset, size, data);
    Error::check("glBufferSubData"); // May throw;
}


//! Read data from buffer. [static]
inline void
VertexBuffer::_getBufferSubData(const GLenum      target, 
                                const GLintptr    offset, 
                                const GLsizeiptr  size, 
                                GLvoid           *data)
{
    glGetBufferSubData(target, offset, size, data);
    Error::check("glGetBufferSubData"); // May throw;
}


//! Retrieve (currently bound) buffer parameters from OpenGL. [static]
inline void
VertexBuffer::_getBufferParameteriv(const GLenum  target, 
                                    const GLenum  pname, 
                                    GLint        *data)
{ 
    glGetBufferParameteriv(target, pname, data); 
    Error::check("glGetBufferParameteriv"); // May throw;
}

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif // NDJINN_VERTEX_BUFFER_HPP_INCLUDED
