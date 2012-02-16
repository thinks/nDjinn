// -----------------------------------------------------------------------------
//
// Copyright (C) Tommy Hinks						  
// tommy[dot]hinks[at]gmail[dot]com  											
//
// Contributors: 
//             1) Tommy Hinks
//
// -----------------------------------------------------------------------------

#ifndef NDJ_VERTEX_BUFFER_HPP_INCLUDED
#define NDJ_VERTEX_BUFFER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

class VertexBuffer
{
public:     // Buffer queries.

    // The following functions retrieve buffer parameters from the driver.
    // There may be a performance penalty involved, so use with caution.
    // Note that these functions operate on the currently "bound" buffer.

    //! Return currently bound buffer size in bytes. May throw.
    static GLint 
    size(const GLenum target = GL_ARRAY_BUFFER)
    { 
        GLint size = 0; // Default/initial value.
        _getBufferParameteriv(target, GL_BUFFER_SIZE, &size); // May throw.
        return size;
    } 

    //! Return currently bound buffer access mode. May throw.
    static GLint 
    access(const GLenum target = GL_ARRAY_BUFFER)
    {
        GLint access = GL_READ_WRITE; // Default/initial value.
        _getBufferParameteriv(target, GL_BUFFER_ACCESS, &access); // May throw.
        return access;
    }

    //! Return GL_TRUE if currently bound buffer is currently mapped, otherwise
    //! GL_FALSE. May throw.
    static GLint  
    mapped(const GLenum target = GL_ARRAY_BUFFER)
    {
        GLint mapped = GL_FALSE; // Default/initial value.
        _getBufferParameteriv(target, GL_BUFFER_MAPPED, &mapped); // May throw.
        return mapped;
    }

    //! Return currently bound buffer usage mode. May throw.
    static GLint 
    usage(const GLenum target = GL_ARRAY_BUFFER)
    {
        GLint usage = GL_STATIC_DRAW; // Default/initial value.
        _getBufferParameteriv(target, GL_BUFFER_USAGE, &usage); // May throw.
        return usage;
    }

public:

    //! CTOR. Construct an empty VBO, no resources (except the handle)
    //! are allocated.
    explicit
    VertexBuffer(const GLenum target = GL_ARRAY_BUFFER)
        : _target(target)
        , _handle(0)       
    {
        try {
            _genBuffers(1, &_handle); // May throw.
            if (_handle == 0) {
                NDJINN_THROW("Invalid vertex buffer handle: " << _handle);
            }
        }
        catch (...) {
            _deleteBuffers(1, &_handle);       // Clean up.
            throw;                             // Rethrow.
        }
    }

    //! CTOR. Construct a VBO from a single chunk of memory. Note that
    //! if data is null the buffer will be allocated but nothing copied.
    explicit
    VertexBuffer(const GLsizeiptr  size,         // [bytes]
                 const GLvoid     *data,
                 const GLenum      usage  = GL_STATIC_DRAW,
                 const GLenum      target = GL_ARRAY_BUFFER)
        : _target(target)
        , _handle(0)       
    {
        try {
            _genBuffers(1, &_handle); // May throw.
            if (_handle == 0) {
                NDJINN_THROW("Invalid vertex buffer handle: " << _handle);
            }
            bind();                                  // Make current, may throw.
            _bufferData(_target, size, data, usage); // May throw.
            release();                               // May throw.
        }
        catch (...) {
            _deleteBuffers(1, &_handle);       // Clean up.
            throw;                             // Rethrow.
        }
    }

    //! DTOR. Free handle resource.
    ~VertexBuffer()
    { 
        try {
            _deleteBuffers(1, &_handle);   // May throw.
        }
        catch (...) {
            // TODO: log error!
        }
    }

public:

    //! Return buffer target, usually GL_ARRAY_BUFFER.
    GLenum     
    target() const
    { return _target; }

    //! Expose resource handle.
    GLuint
    handle() const 
    { return _handle; }

    //! Bind buffer.
    void 
    bind() const 
    { _bindBuffer(_target, _handle); }

    //! Release buffer.
    void 
    release() const
    { _bindBuffer(_target, 0); }

    //! Upload data to GPU memory. If data is null, memory gets allocated but
    //! nothing gets transferred. This is useful for populating a VBO from
    //! several sub-buffers.
    void 
    bufferData(const GLsizeiptr  size, // [bytes]
               const GLvoid     *data  = 0,
               const GLenum      usage = GL_STATIC_DRAW)
    {
        bind();                                  // Make current, may throw.
        _bufferData(_target, size, data, usage); // May throw.
        release();                               // May throw.
    }

    //! Upload data to GPU memory. Size of buffer remains constant.
    void 
    bufferSubData(const GLintptr    offset,
                  const GLsizeiptr  size,        // [bytes]
                  const GLvoid     *data)
    {
        bind();                                      // Make current, may throw.
        _bufferSubData(_target, offset, size, data); // May throw.
        release();                                   // May throw.
    }

    //! Copy data from the buffer in the provided memory.
    void 
    getBufferSubData(const GLintptr    offset,
                     const GLsizeiptr  size,            // [bytes]
                     GLvoid           *data) const
    {
        bind();                                     // Make current, may throw.
        _getBufferSubData(_target, offset, size, data); // May throw.
        release();                                      // May throw.
    }

    // TODO: map
    // TODO: unmap

private:    // OpenGL wrappers.

    //! Generate n buffer handles.
    static void 
    _genBuffers(const GLsizei n, GLuint *buffers)
    { 
        glGenBuffers(n, buffers); 
        error::check(std::string("glGenBuffers")); // May throw;
    }

    //! Free handle resources.
    static void
    _deleteBuffers(const GLsizei n, const GLuint *buffers)
    { 
        glDeleteBuffers(n, buffers); 
        error::check(std::string("glDeleteBuffers")); // May throw;
    }

    //! Make buffer the currently bound buffer.
    static void
    _bindBuffer(const GLenum target, const GLuint buffer)
    { 
        glBindBuffer(target, buffer); 
        error::check(std::string("glBindBuffer")); // May throw;
    }

    //! Reserve 'size' bytes in buffer. If 'data' is non-null also copy 
    //! data into buffer.
    static void
    _bufferData(const GLenum target, const GLsizeiptr size,
                const void *data, const GLenum usage)
    { 
        glBufferData(target, size, data, usage); 
        error::check(std::string("glBufferData")); // May throw;
    }

    //! Copy data to buffer.
    static void
    _bufferSubData(const GLenum target, const GLintptr offset, 
                   const GLsizeiptr size, const GLvoid *data)
    {
        glBufferSubData(target, offset, size, data);
        error::check(std::string("glBufferSubData")); // May throw;
    }

    //! Read data from buffer.
    static void
    _getBufferSubData(const GLenum target, const GLintptr offset, 
                      const GLsizeiptr size, GLvoid *data)
    {
        glGetBufferSubData(target, offset, size, data);
        error::check(std::string("glGetBufferSubData")); // May throw;
    }

    //! Retrieve (currently bound) buffer parameters from OpenGL.
    static void
    _getBufferParameteriv(const GLenum target, const GLenum pname, GLint *data)
    { 
        glGetBufferParameteriv(target, pname, data); 
        error::check(std::string("glGetBufferParameteriv")); // May throw;
    }

private:

    VertexBuffer(const VertexBuffer&);              //!< Disabled copy.
    VertexBuffer& operator=(const VertexBuffer&);   //!< Disabled assign.

private:        // Member variables.

    GLenum     _target;
    GLuint     _handle;     //!< OpenGL handle.
};

// -----------------------------------------------------------------------------

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif // NDJ_VERTEX_BUFFER_HPP_INCLUDED
