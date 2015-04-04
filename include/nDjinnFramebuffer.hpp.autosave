//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_FRAMEBUFFER_HPP_INCLUDED
#define NDJINN_FRAMEBUFFER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include "nDjinnFunctions.hpp"
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

//! Convenience.
inline GLuint
genFramebuffer() {
  GLuint handle = 0;
  genFramebuffers(1, &handle);
  return handle;
}

//! Convenience.
inline void 
deleteFramebuffer(GLuint const handle) {
  deleteFramebuffers(1, &handle);
}


// Named version of framebuffer operations. These version avoid 
// having to bind/release a certain framebuffer every time it is used.

inline GLenum 
checkNamedFramebufferStatus(GLuint const framebuffer, GLenum const target) {
  GLenum const status = glCheckNamedFramebufferStatusEXT(framebuffer, target);
  checkError("glCheckNamedFramebufferStatusEXT");
  return status;
}

inline void 
namedFramebufferTexture(GLuint const framebuffer,
                        GLenum const attachment,
                        GLuint const texture,
                        GLint const level) {
  glNamedFramebufferTextureEXT(
    framebuffer, attachment, texture, level);
  checkError("glNamedFramebufferTextureEXT");
}

inline void 
namedFramebufferTexture1D(GLuint const framebuffer,
                          GLenum const attachment,
                          GLenum const textarget, 
                          GLuint const texture,
                          GLint const level) {
  glNamedFramebufferTexture1DEXT(
    framebuffer, attachment, textarget, texture, level);
  checkError("glNamedFramebufferTexture1DEXT");
}

inline void 
namedFramebufferTexture2D(GLuint const framebuffer,
                          GLenum const attachment,
                          GLenum const textarget, 
                          GLuint const texture,
                          GLint const level) {
  glNamedFramebufferTexture2DEXT(
    framebuffer, attachment, textarget, texture, level);
  checkError("glNamedFramebufferTexture2DEXT");
}


inline void 
namedFramebufferTexture3D(GLuint const framebuffer,
                          GLenum const attachment,
                          GLenum const textarget, 
                          GLuint const texture,
                          GLint const level, 
                          GLint const zoffset) {
  glNamedFramebufferTexture3DEXT(
    framebuffer, attachment, textarget, texture, level, zoffset);
  checkError("glNamedFramebufferTexture3DEXT");
}

inline void 
namedFramebufferRenderbuffer(GLuint const framebuffer,
                             GLenum const attachment,
                             GLenum const renderbuffertarget,
                             GLuint const renderbuffer) {
  glNamedFramebufferRenderbufferEXT(
    framebuffer, attachment, renderbuffertarget, renderbuffer);
  checkError("glNamedFramebufferRenderbufferEXT");
}

inline void 
getNamedFramebufferAttachmentParameteriv(GLuint const framebuffer,
                                         GLenum const attachment,
                                         GLenum const pname,
                                         GLint* params) {
  glGetNamedFramebufferAttachmentParameterivEXT(
    framebuffer, attachment, pname, params);
  checkError("glGetNamedFramebufferAttachmentParameterivEXT");
}

} // Namespace: detail.

//------------------------------------------------------------------------------

//! DOCS
class Framebuffer {
public:
  static GLuint
  binding();

  static void
  disable(GLenum target = GL_FRAMEBUFFER);

public:
  explicit Framebuffer(GLenum target = GL_FRAMEBUFFER);
  ~Framebuffer();

  void bind() const;
  void release() const;

  bool
  bound();

  bool
  checkStatus(std::string &msg);

  void
  attachTexture(GLenum attachment, GLuint texture, GLint level);

  void
  attachTexture3D(GLenum attachment, 
                  GLuint texture, 
                  GLint zoffset,
                  GLenum textarget = GL_TEXTURE_3D,
                  GLint level = 0);

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
  attachRenderbuffer(GLenum attachment,  
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
  class _Bindor {
  public:
    //! CTOR.
    explicit _Bindor(Framebuffer *fbo) 
      : _fbo(fbo) { 
      _fbo->bind(); 
    }   

    //! DTOR.
    ~_Bindor() { 
      _fbo->release(); 
    } 

  private:  // Member variables.
    Framebuffer *_fbo;
  };

  Framebuffer(const Framebuffer&);            //!< Disabled copy.
  Framebuffer& operator=(const Framebuffer&); //!< Disabled assign.

private:  // Member variables.
  const GLenum _target;
  GLuint _handle;     //!< Resource handle.
  mutable GLuint _savedHandle;
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
  , _handle(detail::genFramebuffer())
  , _savedHandle(0) 
{
  bind(); // Make sure buffer gets created.
  if (detail::isFramebuffer(_handle) == GL_FALSE) {
    NDJINN_THROW("invalid framebuffer");
  }
  release();
}

//! DTOR.
inline
Framebuffer::~Framebuffer() {
  detail::deleteFramebuffer(_handle); 
}

// -----------------------------------------------------------------------------

//! Store current FBO and bind this FBO. May throw.
//! NOTE: Not thread-safe!
inline void
Framebuffer::bind() const { 
  _savedHandle = binding();
  if (_savedHandle != _handle) {
    detail::bindFramebuffer(_target, _handle);
  }
} 

//! Return to stored FBO, if it is different from this one. May throw.
//! TODO: Not thread-safe!
inline void
Framebuffer::release() const { 
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
  const GLenum status = detail::checkNamedFramebufferStatus(_handle, _target);
  detail::statusMessage(status, msg);
  return (GL_FRAMEBUFFER_COMPLETE == status);
}

//! DOCS. May throw.
inline void
Framebuffer::attachTexture(const GLenum attachment, 
                           const GLuint texture, 
                           const GLint level) {
  detail::namedFramebufferTexture(_handle, attachment, texture, level);
}

//! DOCS. May throw.
inline void
Framebuffer::attachTexture3D(const GLenum attachment, 
                             const GLuint texture,
                             const GLint zoffset,
                             const GLenum textarget,
                             const GLint level) {
  detail::namedFramebufferTexture3D(
    _handle, attachment, textarget, texture, level, zoffset);
}

//! DOCS. May throw.
inline void
Framebuffer::attachTexture2D(const GLenum attachment, 
                             const GLuint texture, 
                             const GLenum textarget,
                             const GLint level) {
  detail::namedFramebufferTexture2D(
    _handle, attachment, textarget, texture, level); 
}

//! DOCS. May throw.
inline void
Framebuffer::attachTexture1D(const GLenum attachment, 
                             const GLuint texture, 
                             const GLenum textarget,
                             const GLint level) {
  detail::namedFramebufferTexture1D(
    _handle, attachment, textarget, texture, level);
}

//! DOCS. May throw.
inline void
Framebuffer::attachRenderbuffer(const GLenum attachment, 
                                const GLuint renderbuffer,
                                const GLenum renderbufferTarget) {
  detail::namedFramebufferRenderbuffer(
    _handle, attachment, renderbufferTarget, renderbuffer);
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_FRAMEBUFFER_HPP_INCLUDED
