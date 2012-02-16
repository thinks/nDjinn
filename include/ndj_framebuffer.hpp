//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_FRAMEBUFFER_HPP_INCLUDED
#define NDJ_FRAMEBUFFER_HPP_INCLUDED

#include "ndj_state.hpp"
#include "ndj_exception.hpp"
#include "ndj_error.hpp"
#include <gl/glew.h>
#include <string>

// -----------------------------------------------------------------------------

namespace ndj {

// -----------------------------------------------------------------------------

//! DOCS
template<GLenum T = GL_FRAMEBUFFER>
class framebuffer
{
public:

    static const GLenum target = T;

    static GLuint
    binding()
    {
        GLint params = 0;
        state::get_integer(GL_FRAMEBUFFER_BINDING, &params); // May throw.
        return static_cast<GLuint>(params);
    }

    //! Disable any FBO and return to "traditional" rendering. May throw.
    static void
    disable()
    { 
        _bind_framebuffer(target, 0); // May throw.
        _stored_handle = 0;
    } 

public:

    //! CTOR.
    framebuffer()
        : _handle(0)
    {
        try {
            _gen_framebuffers(1, &_handle);
        }
        catch (...) {
            _delete_framebuffers(1, &_handle);  // Clean up.
            throw;                              // Rethrow.
        }    
    }

    //! DTOR.
    ~framebuffer()
    {
        try {
            // TODO: release(); ?
            _delete_framebuffers(1, &_handle);  // May throw.
        }
        catch (...) {
        }    
    }

    //! Store current FBO and bind this FBO. May throw.
    //! TODO: Not thread-safe!
    void
    bind()
    { 
        _stored_handle = binding();             // May throw.
        if (_stored_handle != _handle) {
            _bind_framebuffer(target, _handle); // May throw.
        }
    } 

    //! Return to stored FBO, if it is different from this one. May throw.
    //! TODO: Not thread-safe!
    void
    release()
    { 
        if (_stored_handle != _handle) {
            _bind_framebuffer(target, _stored_handle); // May throw.
        }
    } 

    //! Returns true if this framebuffer is currently bound. May throw.
    bool
    is_bound() 
    { return (binding() == _handle); } // May throw.

    //! Returns true if status is OK. May throw.
    bool
    check_status(std::string &msg)
    {
        msg.clear();
        bind(); // May throw.
        const GLenum status = _check_framebuffer_status(target); // May throw.
        _status_message(status, msg);
        release();  // May throw.
        return (GL_FRAMEBUFFER_COMPLETE == status);
    }

    void
    attach_texture(const GLenum attachment, const GLuint texture, 
                   const GLint level)
    {
        bind(); // May throw.
        _framebuffer_texture(target, attachment, texture, level); // May throw.
        release(); // May throw.
    }

    void
    attach_texture3(const GLenum attachment, 
                    const GLuint texture,
                    const GLint  layer,
                    const GLint  level     = 0, 
                    const GLenum textarget = GL_TEXTURE_3D)
    {
        bind(); // May throw.
        _framebuffer_texture_3d(target, attachment, textarget, 
                               texture, level, layer); // May throw.  
        release(); // May throw.
    }

    void
    attach_texture2(const GLenum attachment, 
                    const GLenum textarget,
                    const GLuint texture, 
                    const GLint  level = 0)
    {
        bind(); // May throw.
        _framebuffer_texture_2d(target, attachment, textarget, 
                                texture, level); // May throw.
        release(); // May throw.
    }

    void
    attach_texture1(const GLenum attachment, 
                    const GLuint texture, 
                    const GLint  level     = 0,
                    const GLenum textarget = GL_TEXTURE_1D)
    {
        bind(); // May throw.
        _framebuffer_texture_1d(target, attachment, textarget, 
                                texture, level); // May throw.
        release(); // May throw.
    }

private:    // Binding and Managing.

    //! glBindFramebuffer wrapper. May throw.
    static void
    _bind_framebuffer(const GLenum target, const GLuint framebuffer)
    {
        glBindFramebuffer(target, framebuffer);
        error::check("glBindFramebuffer"); // May throw.
    }

    //! glDeleteFramebuffers wrapper. May throw.
    static void
    _delete_framebuffers(const GLsizei n, const GLuint *framebuffers)
    {
        glDeleteFramebuffers(n, framebuffers);
        error::check("glDeleteFramebuffers"); // May throw.
    }

    //! glGenFramebuffers wrapper. May throw.
    static void
    _gen_framebuffers(const GLsizei n, GLuint *ids)
    {
        glGenFramebuffers(n, ids);
        error::check("glGenFramebuffers"); // May throw.
    }

private:    // Attaching Renderbuffer Images.

    //! glFramebufferRenderbuffer wrapper. May throw.
    static void
    _framebuffer_renderbuffer(const GLenum target, const GLenum internalformat, 
                              const GLsizei width, const GLsizei height)
    {
        glFramebufferRenderbuffer(target, internalformat, width, height);
        error::check("glFramebufferRenderbuffer"); // May throw.
    }

private:    // Attaching Texture Images.

    //! glFramebufferTexture wrapper. May throw.
    static void
    _framebuffer_texture(const GLenum target, const GLenum attachment, 
                         const GLuint texture, const GLint level)
    {
        glFramebufferTexture(target, attachment, texture, level);
        error::check("glFramebufferTexture"); // May throw.
    }

    //! glFramebufferTexture3D wrapper. May throw.
    static void
    _framebuffer_texture_3d(const GLenum target, const GLenum attachment, 
                            const GLenum textarget, const GLuint texture, 
                            const GLint level, const GLint layer)
    {
        glFramebufferTexture3D(target, attachment, 
                               textarget, texture, level, layer);
        error::check("glFramebufferTexture3D"); // May throw.
    }

    //! glFramebufferTexture2D wrapper. May throw.
    static void
    _framebuffer_texture_2d(const GLenum target, const GLenum attachment, 
                            const GLenum textarget, const GLuint texture, 
                            const GLint level)
    {
        glFramebufferTexture2D(target, attachment, textarget, texture, level);
        error::check("glFramebufferTexture2D"); // May throw.
    }

    //! glFramebufferTexture1D wrapper. May throw.
    static void
    _framebuffer_texture_1d(const GLenum target, const GLenum attachment, 
                            const GLenum textarget, const GLuint texture, 
                            const GLint level)
    {
        glFramebufferTexture1D(target, attachment, textarget, texture, level);
        error::check("glFramebufferTexture1D"); // May throw.
    }

    //! glFramebufferTextureLayer wrapper. May throw.
    static void
    _framebuffer_texture_layer(const GLenum target, const GLenum attachment,
                               const GLuint texture, const GLint level, 
                               const GLint layer)
    {
        glFramebufferTextureLayer(target, attachment, texture, level, layer);
        error::check("glFramebufferTextureLayer"); // May throw.
    }

private:    // Framebuffer Completeness.

    //! glCheckFramebufferStatus wrapper. May throw.
    static GLenum
    _check_framebuffer_status(const GLenum target)
    {
        glCheckFramebufferStatus(target);
        error::check("glCheckFramebufferStatus"); // May throw.
    }

    //! Convert status enum to a string. TODO: add more enums!
    static void
    _status_message(const GLenum status, std::string &msg)
    {
        switch(status) {                                          
        case GL_FRAMEBUFFER_COMPLETE:
            msg = std::string("GL_FRAMEBUFFER_COMPLETE");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            msg = std::string("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            msg = std::string("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
            break;
        //case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
        //    msg = std::string("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS");
        //    break;
        //case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
        //    msg = std::string("GL_FRAMEBUFFER_INCOMPLETE_FORMATS");
        //    break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            msg = std::string("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            msg = std::string("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            msg = std::string("GL_FRAMEBUFFER_UNSUPPORTED");
            break;
        case 0: // Zero is always error.
        default:
            msg = std::string("Unknown framebuffer status error");
            break;
        }
    }

private:    // Framebuffer Object Queries.

    //! glIsFramebuffer wrapper. May throw.
    static GLboolean
    _is_framebuffer(const GLuint framebuffer)
    {
        const GLboolean result = glIsFramebuffer(framebuffer);
        error::check("glIsFramebuffer"); // May throw.
        return result;
    }

    //! glGetFramebufferAttachmentParameteriv wrapper. May throw.
    static void
    _get_framebuffer_attachment_parameter_iv(const GLenum  target, 
                                             const GLenum  attachment, 
                                             const GLenum  pname, 
                                             GLint        *params)
    {
        glGetFramebufferAttachmentParameteriv(target,attachment,pname,params);
        error::check("glGetFramebufferAttachmentParameteriv"); // May throw.
    }

private:

    static GLuint _stored_handle;

private:

    framebuffer(const framebuffer<T>&);                 //!< Disabled copy.
    framebuffer<T>& operator=(const framebuffer<T>&);   //!< Disabled assign.

private:    // Member variables.

    GLuint _handle;     //!< Resource handle.
};


//! Store the currently bound FBO when binding this object. Restore
//! on release. Initially set to zero, i.e. default FBO.
//! TODO: Not thread-safe!
template<GLenum T>
GLuint framebuffer<T>::_stored_handle = 0;

// -----------------------------------------------------------------------------

}   // Namespace: ndj.

// -----------------------------------------------------------------------------

#endif  // NDJ_FRAMEBUFFER_HPP_INCLUDED
