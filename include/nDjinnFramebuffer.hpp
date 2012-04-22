//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_FRAMEBUFFER_HPP_INCLUDED
#define NDJINN_FRAMEBUFFER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnState.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>
#include <string>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

//! DOCS
class Framebuffer
{
public:

    static GLuint
    binding();

    static void
    disable(GLenum target = GL_FRAMEBUFFER);

public:

    Framebuffer(GLenum target = GL_FRAMEBUFFER);

    ~Framebuffer();

public:

    void
    bind();

    void
    release();

    bool
    bound();

    bool
    checkStatus(std::string &msg);

    void
    attachTexture(GLenum attachment, GLuint texture, GLint level);

    void
    attachTexture3D(GLenum attachment, 
                    GLuint texture, 
                    GLint  layer,
                    GLenum textarget = GL_TEXTURE_3D,
                    GLint  level     = 0);

    void
    attachTexture2D(GLenum attachment, 
                    GLuint texture, 
                    GLenum textarget = GL_TEXTURE_2D,
                    GLint  level     = 0);

    void
    attachTexture1D(GLenum attachment, 
                    GLuint texture, 
                    GLenum textarget = GL_TEXTURE_1D,
                    GLint  level     = 0);

    void
    attachRenderBuffer(GLenum attachment,  
                       GLuint renderbuffer,
                       GLenum renderbufferTarget = GL_RENDERBUFFER);

    void
    detachTexture(GLenum textarget, GLenum attachment);

    void
    detachRenderbuffer();

    void
    detachAll();

private:    // Binding and Managing.

    static void
    _bindFramebuffer(GLenum target, GLuint framebuffer);

    static void
    _deleteFramebuffers(GLsizei n, const GLuint *framebuffers);

    static void
    _genFramebuffers(GLsizei n, GLuint *ids);

private:    // Attaching Renderbuffer Images.

    static void
    _framebufferRenderbuffer(GLenum target, GLenum attachment, 
                             GLenum renderbufferTarget, GLuint renderbuffer);

private:    // Attaching Texture Images.

    static void
    _framebufferTexture(GLenum target, GLenum attachment, 
                        GLuint texture, GLint level);

    static void
    _framebufferTexture3D(GLenum target, GLenum attachment, 
                          GLenum textarget, GLuint texture, 
                          GLint level, GLint layer);

    static void
    _framebufferTexture2D(GLenum target, GLenum attachment, 
                          GLenum textarget, GLuint texture, 
                          GLint level);

    static void
    _framebufferTexture1D(GLenum target, GLenum attachment, 
                          GLenum textarget, GLuint texture, 
                          GLint level);

    static void
    _framebufferTextureLayer(GLenum target, GLenum attachment,
                             GLuint texture, GLint level, GLint  layer);

private:    // Framebuffer Completeness.

    static GLenum
    _checkFramebufferStatus(GLenum target);

    static void
    _statusMessage(GLenum status, std::string &msg);

private:    // Framebuffer Object Queries.

    static GLboolean
    _isFramebuffer(GLuint framebuffer);

    static void
    _getFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, 
                                         GLenum pname, GLint *params);

private:

    //! DOCS
    class _Bindor
    {
    public:

        //! CTOR.
        explicit
        _Bindor(Framebuffer *fbo) 
            : _fbo(fbo) 
        { _fbo->bind(); }   

        //! DTOR.
        ~_Bindor() 
        { 
            try { _fbo->release(); } 
            catch (...) {} 
        } 

    private:    // Member variables.

        Framebuffer *_fbo;
    };

    Framebuffer(const Framebuffer&);            //!< Disabled copy.
    Framebuffer& operator=(const Framebuffer&); //!< Disabled assign.

private:    // Member variables.

    const GLenum _target;
    GLuint       _handle;     //!< Resource handle.
    GLuint       _savedHandle;
};

// -----------------------------------------------------------------------------

//! Returns currently bound framebuffer. May throw. [static]
inline GLuint
Framebuffer::binding()
{
    GLint params = 0;
    State::getIntegerv(GL_FRAMEBUFFER_BINDING, &params); // May throw.
    return static_cast<GLuint>(params);
}


//! Disable all framebuffer objects and return to "traditional" 
//! rendering. May throw. [static]
inline void
Framebuffer::disable(const GLenum target)
{ 
    _bindFramebuffer(target, 0); // May throw.
} 

// -----------------------------------------------------------------------------

//! CTOR.
inline
Framebuffer::Framebuffer(const GLenum target)
    : _target(target)
    , _handle(0)
    , _savedHandle(0)
{
    try {
        _genFramebuffers(1, &_handle);
        _Bindor bind(this); // Make sure framebuffer object gets created now.
    }
    catch (...) {
        _deleteFramebuffers(1, &_handle);  // Clean up.
        throw;                             // Rethrow.
    }    
}


//! DTOR.
inline
Framebuffer::~Framebuffer()
{
    // TODO: release(); ?
    try { _deleteFramebuffers(1, &_handle); }
    catch (...) {}    
}

// -----------------------------------------------------------------------------

//! Store current FBO and bind this FBO. May throw.
//! TODO: Not thread-safe!
inline void
Framebuffer::bind()
{ 
    std::cerr << "BIND: handle:" << _handle << " | binding:" << binding() << "\n";
    _savedHandle = binding();             // May throw.
    if (_savedHandle != _handle) {
        _bindFramebuffer(_target, _handle); // May throw.
    }
} 


//! Return to stored FBO, if it is different from this one. May throw.
//! TODO: Not thread-safe!
inline void
Framebuffer::release()
{ 
    std::cerr << "RELEASE: saved handle:" << _savedHandle << " | handle:" << _handle << "\n";
    if (_savedHandle != _handle) {
        _bindFramebuffer(_target, _savedHandle); // May throw.
    }
} 


//! Returns true if this framebuffer is currently bound. May throw.
inline bool
Framebuffer::bound() 
{ 
    return (_handle == binding()); // May throw.
} 


//! Returns true if status is OK. May throw.
inline bool
Framebuffer::checkStatus(std::string &msg)
{
    msg.clear();
    _Bindor bind(this);
    const GLenum status = _checkFramebufferStatus(_target); // May throw.
    _statusMessage(status, msg);
    return (GL_FRAMEBUFFER_COMPLETE == status);
}


//! DOCS
inline void
Framebuffer::attachTexture(const GLenum attachment, 
                           const GLuint texture, 
                           const GLint level)
{
    _Bindor bind(this);
    _framebufferTexture(_target, attachment, texture, level); // May throw.
}


//! DOCS
inline void
Framebuffer::attachTexture3D(const GLenum attachment, 
                             const GLuint texture,
                             const GLint  layer,
                             const GLenum textarget,
                             const GLint  level)
{
    _Bindor bind(this);
    _framebufferTexture3D(_target, attachment, textarget, texture, level,layer);
}


//! DOCS
inline void
Framebuffer::attachTexture2D(const GLenum attachment, 
                             const GLuint texture, 
                             const GLenum textarget,
                             const GLint  level)
{
    _Bindor bind(this);
    _framebufferTexture2D(_target, attachment, textarget, texture, level); 
}


//! DOCS
inline void
Framebuffer::attachTexture1D(const GLenum attachment, 
                             const GLuint texture, 
                             const GLenum textarget,
                             const GLint  level)
{
    _Bindor bind(this);
    _framebufferTexture1D(_target, attachment, textarget, texture, level);
}


//! DOCS
inline void
Framebuffer::attachRenderBuffer(const GLenum attachment, 
                                const GLuint renderbuffer,
                                const GLenum renderbufferTarget)
{
    _Bindor bind(this);
    _framebufferRenderbuffer(_target, attachment, 
                             renderbufferTarget, renderbuffer);
}

// -----------------------------------------------------------------------------

//! glBindFramebuffer wrapper. May throw. [static]
inline void
Framebuffer::_bindFramebuffer(const GLenum target, const GLuint framebuffer)
{
    glBindFramebuffer(target, framebuffer);
    Error::check("glBindFramebuffer"); // May throw.
}


//! glDeleteFramebuffers wrapper. May throw. [static]
inline void
Framebuffer::_deleteFramebuffers(const GLsizei n, const GLuint *framebuffers)
{
    glDeleteFramebuffers(n, framebuffers);
    Error::check("glDeleteFramebuffers"); // May throw.
}


//! glGenFramebuffers wrapper. May throw. [static]
inline void
Framebuffer::_genFramebuffers(const GLsizei n, GLuint *ids)
{
    glGenFramebuffers(n, ids);
    Error::check("glGenFramebuffers"); // May throw.
}

// -----------------------------------------------------------------------------

//! glFramebufferRenderbuffer wrapper. May throw. [static]
inline void
Framebuffer::_framebufferRenderbuffer(const GLenum target, 
                                      const GLenum attachment, 
                                      const GLenum renderbufferTarget, 
                                      const GLuint renderbuffer)
{
    glFramebufferRenderbuffer(target, attachment, 
                              renderbufferTarget, renderbuffer);
    Error::check("glFramebufferRenderbuffer"); // May throw.
}

// -----------------------------------------------------------------------------

//! glFramebufferTexture wrapper. May throw. [static]
inline void
Framebuffer::_framebufferTexture(const GLenum target, 
                                 const GLenum attachment, 
                                 const GLuint texture, 
                                 const GLint  level)
{
    glFramebufferTexture(target, attachment, texture, level);
    Error::check("glFramebufferTexture"); // May throw.
}


//! glFramebufferTexture3D wrapper. May throw. [static]
inline void
Framebuffer::_framebufferTexture3D(const GLenum target, 
                                   const GLenum attachment, 
                                   const GLenum textarget, 
                                   const GLuint texture, 
                                   const GLint  level, 
                                   const GLint  layer)
{
    glFramebufferTexture3D(target, attachment, 
                           textarget, texture, level, layer);
    Error::check("glFramebufferTexture3D"); // May throw.
}


//! glFramebufferTexture2D wrapper. May throw. [static]
inline void
Framebuffer::_framebufferTexture2D(const GLenum target, 
                                   const GLenum attachment, 
                                   const GLenum textarget, 
                                   const GLuint texture, 
                                   const GLint  level)
{
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    Error::check("glFramebufferTexture2D"); // May throw.
}


//! glFramebufferTexture1D wrapper. May throw. [static]
inline void
Framebuffer::_framebufferTexture1D(const GLenum target, 
                                   const GLenum attachment, 
                                   const GLenum textarget, 
                                   const GLuint texture, 
                                   const GLint  level)
{
    glFramebufferTexture1D(target, attachment, textarget, texture, level);
    Error::check("glFramebufferTexture1D"); // May throw.
}


//! glFramebufferTextureLayer wrapper. May throw. [static]
inline void
Framebuffer::_framebufferTextureLayer(const GLenum target, 
                                      const GLenum attachment,
                                      const GLuint texture, 
                                      const GLint  level, 
                                      const GLint  layer)
{
    glFramebufferTextureLayer(target, attachment, texture, level, layer);
    Error::check("glFramebufferTextureLayer"); // May throw.
}

// -----------------------------------------------------------------------------

//! glCheckFramebufferStatus wrapper. May throw. [static]
inline GLenum
Framebuffer::_checkFramebufferStatus(const GLenum target)
{
    const GLenum status = glCheckFramebufferStatus(target);
    Error::check("glCheckFramebufferStatus"); // May throw.
    return status;
}


//! Convert status enum to a string. TODO: add more enums! [static]
inline void
Framebuffer::_statusMessage(const GLenum status, std::string &msg)
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

// -----------------------------------------------------------------------------

//! glIsFramebuffer wrapper. May throw. [static]
inline GLboolean
Framebuffer::_isFramebuffer(const GLuint framebuffer)
{
    const GLboolean result = glIsFramebuffer(framebuffer);
    Error::check("glIsFramebuffer"); // May throw.
    return result;
}


//! glGetFramebufferAttachmentParameteriv wrapper. May throw. [static]
inline void
Framebuffer::_getFramebufferAttachmentParameteriv(const GLenum  target, 
                                                  const GLenum  attachment, 
                                                  const GLenum  pname, 
                                                  GLint        *params)
{
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
    Error::check("glGetFramebufferAttachmentParameteriv"); // May throw.
}

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif  // NDJINN_FRAMEBUFFER_HPP_INCLUDED
