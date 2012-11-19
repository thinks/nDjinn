//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_RENDERBUFFER_HPP_INCLUDED
#define NDJINN_RENDERBUFFER_HPP_INCLUDED

#include "nDjinnException.hpp"
#include "nDjinnError.hpp"

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

}

//------------------------------------------------------------------------------

class framebuffer
{
public:

    static const GLenum target = GL_RENDERBUFFER;

public:

    //! CTOR.
    renderbuffer()
        : _handle(0)
    {
        try {
            _gen_renderbuffers(1, &_handle);
        }
        catch (...) {
            _delete_renderbuffers(1, &_handle);  // Clean up.
            throw;                               // Rethrow.
        }    
    }

    //! DTOR.
    ~renderbuffer()
    {
        try {
            // TODO: release(); ?
            _delete_framebuffers(1, &_handle);  // May throw.
        }
        catch (...) {
        }    
    }

private:    // Renderbuffer Objects.

    //! glBindRenderBuffer wrapper. May throw.
    static void
    _bind_renderbuffer(const GLenum target, const GLuint renderbuffer)
    {
        glBindRenderbuffer(target, renderbuffer);
        error::check("glBindRenderbuffer"); // May throw.
    }

    //! glDeleteRenderBuffers wrapper. May throw.
    static void
    _delete_renderbuffers(const GLsizei n, const GLuint *renderbuffers)
    {
        glDeleteRenderbuffers(n, renderbuffers);
        error::check("glDeleteRenderbuffers"); // May throw.
    }

    //! glGenRenderBuffers wrapper. May throw.
    static void
    _gen_renderbuffers(const GLsizei n, GLuint *renderbuffers)
    {
        glGenRenderBuffers(n, renderbuffers);
        error::check("glGenRenderbuffers"); // May throw.
    }

    //! glRenderbufferStorageMultisample wrapper. May throw.
    static void 
    _renderbuffer_storage_multisample(
        const GLenum target, const GLsizei samples,
        const GLenum internalformat, const GLsizei width, const GLsizei height)
    {
        glRenderbufferStorageMultisample(
            target, samples, internalformat, width, height);
        error::check("glRenderbufferStorageMultisample"); // May throw.
    }

    //! glRenderbufferStorageMultisample wrapper. May throw.
    static void 
    _renderbuffer_storage(const GLenum target, const GLenum internalformat, 
                          const GLsizei width, const GLsizei height)
    {
        glRenderbufferStorage(
            target, internalformat, width, height);
        error::check("glRenderbufferStorage"); // May throw.
    }

private:    // Renderbuffer Object Queries.

    //! glIsRenderbuffer wrapper. May throw.
    static GLboolean
    _is_renderbuffer(const GLuint renderbuffer)
    {
        const GLboolean result = glIsRenderbuffer(renderbuffer);
        error::check("glIsRenderbuffer"); // May throw.
        return result;
    }

    //! glGetRenderbufferAttachmentParameteriv wrapper. May throw.
    static void
    _get_renderbuffer_attachment_parameter_iv(const GLenum  target, 
                                              const GLenum  pname, 
                                              GLint        *params)
    {
        glGetRenderbufferAttachmentParameteriv(target, pname, params);
        error::check("glGetRenderbufferAttachmentParameteriv"); // May throw.
    }

private:

    renderbuffer(const renderbuffer&);            //!< Disabled copy.
    renderbuffer& operator=(const renderbuffer&); //!< Disabled assign.

private:    // Member variables.

    GLuint _handle;     //!< Resource handle.
};

// -----------------------------------------------------------------------------

}   // Namespace: ndj.

// -----------------------------------------------------------------------------

#endif  // NDJ_RENDERBUFFER_HPP_INCLUDED
