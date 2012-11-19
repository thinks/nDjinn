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

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glBindFramebuffer wrapper. May throw.
inline void
bindFramebuffer(const GLenum target, const GLuint framebuffer) {
  glBindFramebuffer(target, framebuffer);
  checkError("glBindFramebuffer"); 
}

//! glDeleteFramebuffers wrapper. May throw.
inline void
deleteFramebuffers(const GLsizei n, const GLuint *framebuffers) {
  glDeleteFramebuffers(n, framebuffers);
  checkError("glDeleteFramebuffers");
}

//! glGenFramebuffers wrapper. May throw.
inline void
genFramebuffers(const GLsizei n, GLuint *ids) {
  glGenFramebuffers(n, ids);
  checkError("glGenFramebuffers");
}

//! glFramebufferRenderbuffer wrapper. May throw. 
inline void
framebufferRenderbuffer(const GLenum target, 
                        const GLenum attachment, 
                        const GLenum renderbufferTarget, 
                        const GLuint renderbuffer) {
  glFramebufferRenderbuffer(target, attachment, 
                            renderbufferTarget, renderbuffer);
  checkError("glFramebufferRenderbuffer");
}

//! glFramebufferTexture wrapper. May throw. 
inline void
framebufferTexture(const GLenum target, 
                   const GLenum attachment, 
                   const GLuint texture, 
                   const GLint  level) {
  glFramebufferTexture(target, attachment, texture, level);
  checkError("glFramebufferTexture"); 
}

//! glFramebufferTexture3D wrapper. May throw.
inline void
framebufferTexture3D(const GLenum target, 
                     const GLenum attachment, 
                     const GLenum textarget, 
                     const GLuint texture, 
                     const GLint level, 
                     const GLint layer) {
  glFramebufferTexture3D(target, attachment, 
                         textarget, texture, level, layer);
  checkError("glFramebufferTexture3D");
}

//! glFramebufferTexture2D wrapper. May throw. 
inline void
framebufferTexture2D(const GLenum target, 
                     const GLenum attachment, 
                     const GLenum textarget, 
                     const GLuint texture, 
                     const GLint level) {
  glFramebufferTexture2D(target, attachment, textarget, texture, level);
  checkError("glFramebufferTexture2D"); 
}

//! glFramebufferTexture1D wrapper. May throw. 
inline void
framebufferTexture1D(const GLenum target, 
                     const GLenum attachment, 
                     const GLenum textarget, 
                     const GLuint texture, 
                     const GLint level) {
  glFramebufferTexture1D(target, attachment, textarget, texture, level);
  checkError("glFramebufferTexture1D"); // May throw.
}

//! glFramebufferTextureLayer wrapper. May throw. 
inline void
framebufferTextureLayer(const GLenum target, 
                        const GLenum attachment,
                        const GLuint texture, 
                        const GLint level, 
                        const GLint layer) {
  glFramebufferTextureLayer(target, attachment, texture, level, layer);
  checkError("glFramebufferTextureLayer"); // May throw.
}

//! glCheckFramebufferStatus wrapper. May throw.
inline GLenum
checkFramebufferStatus(const GLenum target) {
  const GLenum status = glCheckFramebufferStatus(target);
  checkError("glCheckFramebufferStatus");
  return status;
}

//! Convert status enum to a string. TODO: add more enums! 
inline void
statusMessage(const GLenum status, std::string &msg) {
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

//! glIsFramebuffer wrapper. May throw.
inline GLboolean
isFramebuffer(const GLuint framebuffer) {
  const GLboolean result = glIsFramebuffer(framebuffer);
  checkError("glIsFramebuffer"); 
  return result;
}

//! glGetFramebufferAttachmentParameteriv wrapper. May throw.
inline void
getFramebufferAttachmentParameteriv(const GLenum target, 
                                    const GLenum attachment, 
                                    const GLenum pname, 
                                    GLint *params) {
  glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
  checkError("glGetFramebufferAttachmentParameteriv");
}

} // Namespace: detail.

//------------------------------------------------------------------------------

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
                  GLint  level = 0);

  void
  attachTexture2D(GLenum attachment, 
                  GLuint texture, 
                  GLenum textarget = GL_TEXTURE_2D,
                  GLint  level = 0);

  void
  attachTexture1D(GLenum attachment, 
                  GLuint texture, 
                  GLenum textarget = GL_TEXTURE_1D,
                  GLint  level = 0);

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

private:

  //! DOCS
  class _Bindor
  {
  public:

    //! CTOR.
    explicit _Bindor(Framebuffer *fbo) 
      : _fbo(fbo) 
    { 
      _fbo->bind(); 
    }   

    //! DTOR.
    ~_Bindor() { 
      try { 
        _fbo->release(); 
      } 
      catch (...) {
      } 
    } 

  private:  // Member variables.
    Framebuffer *_fbo;
  };

  Framebuffer(const Framebuffer&);            //!< Disabled copy.
  Framebuffer& operator=(const Framebuffer&); //!< Disabled assign.

private:  // Member variables.
  const GLenum _target;
  GLuint _handle;     //!< Resource handle.
  GLuint _savedHandle;
};

// -----------------------------------------------------------------------------

//! Returns currently bound framebuffer. May throw. [static]
inline GLuint
Framebuffer::binding() {
  GLint params = 0;
  getIntegerv(GL_FRAMEBUFFER_BINDING, &params); 
  return static_cast<GLuint>(params);
}

//! Disable all framebuffer objects and return to "traditional" 
//! rendering. May throw. [static]
inline void
Framebuffer::disable(const GLenum target) { 
  detail::bindFramebuffer(target, 0);
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
    detail::genFramebuffers(1, &_handle);
    _Bindor bind(this); // Make sure framebuffer object gets created now.
  }
  catch (...) {
    detail::deleteFramebuffers(1, &_handle); // Clean up.
    throw; // Rethrow.
  }    
}

//! DTOR.
inline
Framebuffer::~Framebuffer() {
  try { 
    detail::deleteFramebuffers(1, &_handle); 
  }
  catch (...) {
  }    
}

// -----------------------------------------------------------------------------

//! Store current FBO and bind this FBO. May throw.
//! TODO: Not thread-safe!
inline void
Framebuffer::bind() { 
  _savedHandle = binding();
  if (_savedHandle != _handle) {
    detail::bindFramebuffer(_target, _handle);
  }
} 

//! Return to stored FBO, if it is different from this one. May throw.
//! TODO: Not thread-safe!
inline void
Framebuffer::release() { 
  if (_savedHandle != _handle) {
    detail::bindFramebuffer(_target, _savedHandle); // May throw.
  }
} 

//! Returns true if this framebuffer is currently bound. May throw.
inline bool
Framebuffer::bound() { 
  return _handle == binding();
} 

//! Returns true if status is OK. May throw.
inline bool
Framebuffer::checkStatus(std::string &msg) {
  msg.clear();
  _Bindor bind(this);
  const GLenum status = detail::checkFramebufferStatus(_target);
  detail::statusMessage(status, msg);
  return (GL_FRAMEBUFFER_COMPLETE == status);
}

//! DOCS. May throw.
inline void
Framebuffer::attachTexture(const GLenum attachment, 
                           const GLuint texture, 
                           const GLint level) {
  _Bindor bind(this);
  detail::framebufferTexture(_target, attachment, texture, level);
}

//! DOCS. May throw.
inline void
Framebuffer::attachTexture3D(const GLenum attachment, 
                             const GLuint texture,
                             const GLint layer,
                             const GLenum textarget,
                             const GLint level) {
  _Bindor bind(this);
  detail::framebufferTexture3D(_target, attachment, textarget, 
                               texture, level,layer);
}

//! DOCS. May throw.
inline void
Framebuffer::attachTexture2D(const GLenum attachment, 
                             const GLuint texture, 
                             const GLenum textarget,
                             const GLint level) {
  _Bindor bind(this);
  detail::framebufferTexture2D(_target, attachment, textarget, texture, level); 
}

//! DOCS. May throw.
inline void
Framebuffer::attachTexture1D(const GLenum attachment, 
                             const GLuint texture, 
                             const GLenum textarget,
                             const GLint level) {
  _Bindor bind(this);
  detail::framebufferTexture1D(_target, attachment, textarget, texture, level);
}

//! DOCS. May throw.
inline void
Framebuffer::attachRenderBuffer(const GLenum attachment, 
                                const GLuint renderbuffer,
                                const GLenum renderbufferTarget) {
  _Bindor bind(this);
  detail::framebufferRenderbuffer(_target, attachment, 
                                  renderbufferTarget, renderbuffer);
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_FRAMEBUFFER_HPP_INCLUDED
