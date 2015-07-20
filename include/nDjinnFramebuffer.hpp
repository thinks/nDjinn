//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_FRAMEBUFFER_HPP_INCLUDED
#define NDJINN_FRAMEBUFFER_HPP_INCLUDED

#include <array>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "nDjinnError.hpp"
#include "nDjinnException.hpp"
#include "nDjinnFunctions.hpp"
#include "nDjinnGL.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glGenFramebuffers wrapper. May throw.
inline void genFramebuffers(GLsizei const n, GLuint* ids) {
  glGenFramebuffers(n, ids);
  checkError("glGenFramebuffers");
}

//! glDeleteFramebuffers wrapper. May throw.
inline void deleteFramebuffers(GLsizei const n, GLuint const* framebuffers) {
  glDeleteFramebuffers(n, framebuffers);
  checkError("glDeleteFramebuffers");
}

//! glIsFramebuffer wrapper. May throw.
inline GLboolean isFramebuffer(GLuint const framebuffer) {
  GLboolean const result = glIsFramebuffer(framebuffer);
  checkError("glIsFramebuffer");
  return result;
}

//! glBindFramebuffer wrapper. May throw.
inline void bindFramebuffer(GLenum const target, GLuint const framebuffer)
{
  glBindFramebuffer(target, framebuffer);
  checkError("glBindFramebuffer"); 
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



// Named version of framebuffer operations. These version avoid 
// having to bind/release a framebuffer every time it is used.

//! glCheckNamedFramebufferStatusEXT wrapper. May throw.
inline GLenum checkNamedFramebufferStatus(GLuint const framebuffer,
                                          GLenum const target) {
  GLenum const status = glCheckNamedFramebufferStatusEXT(framebuffer, target);
  checkError("glCheckNamedFramebufferStatusEXT");
  return status;
}

//! glNamedFramebufferTexture2DEXT wrapper. May throw.
inline void namedFramebufferTexture(GLuint const framebuffer,
                                    GLenum const attachment,
                                    GLuint const texture, GLint const level)
{
  glNamedFramebufferTextureEXT(framebuffer, attachment, texture, level);
  checkError("glNamedFramebufferTextureEXT");
}

//! glNamedFramebufferTexture2DEXT wrapper. May throw.
inline void namedFramebufferTexture1D(GLuint const framebuffer,
                                      GLenum const attachment,
                                      GLenum const textarget,
                                      GLuint const texture, GLint const level)
{
  glNamedFramebufferTexture1DEXT(framebuffer, attachment, textarget, texture,
                                 level);
  checkError("glNamedFramebufferTexture1DEXT");
}

//! glNamedFramebufferTexture2DEXT wrapper. May throw.
inline void namedFramebufferTexture2D(GLuint const framebuffer,
                                      GLenum const attachment,
                                      GLenum const textarget,
                                      GLuint const texture, GLint const level)
{
  glNamedFramebufferTexture2DEXT(framebuffer, attachment, textarget, texture,
                                 level);
  checkError("glNamedFramebufferTexture2DEXT");
}

//! glNamedFramebufferTexture3DEXT wrapper. May throw.
inline void namedFramebufferTexture3D(GLuint const framebuffer,
                                      GLenum const attachment,
                                      GLenum const textarget,
                                      GLuint const texture, GLint const level,
                                      GLint const zoffset)
{
  glNamedFramebufferTexture3DEXT(framebuffer, attachment, textarget, texture,
                                 level, zoffset);
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

//! glGetNamedFramebufferAttachmentParameterivEXT wrapper. May throw.
inline void getNamedFramebufferAttachmentParameteriv(GLuint const framebuffer,
                                                     GLenum const attachment,
                                                     GLenum const pname,
                                                     GLint* params) {
  glGetNamedFramebufferAttachmentParameterivEXT(
    framebuffer, attachment, pname, params);
  checkError("glGetNamedFramebufferAttachmentParameterivEXT");
}

//! Convenience.
inline GLuint genFramebuffer() {
  GLuint handle = 0;
  genFramebuffers(1, &handle);
  return handle;
}

//! Convenience.
inline void deleteFramebuffer(GLuint const handle) {
  deleteFramebuffers(1, &handle);
}

//! Convenience.
inline GLint getNamedFramebufferAttachmentParameteri(GLuint const framebuffer,
                                                     GLenum const attachment,
                                                     GLenum const pname)
{
  GLint param = 0;
  getNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname,
                                           &param);
  return param;
}

//! Returns framebuffer status as a string.
inline std::string statusToString(GLenum const status)
{
  using std::string;
  string str;
  switch(status) {
  case GL_FRAMEBUFFER_COMPLETE:
    str = string("GL_FRAMEBUFFER_COMPLETE");
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    str = string("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    str = string("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
    break;
  //case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
  //    str = string("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS");
  //    break;
  //case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
  //    str = string("GL_FRAMEBUFFER_INCOMPLETE_FORMATS");
  //    break;
  case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
    str = string("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
    break;
  case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
    str = string("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
    break;
  case GL_FRAMEBUFFER_UNSUPPORTED:
    str = string("GL_FRAMEBUFFER_UNSUPPORTED");
    break;
  case 0: // Zero is always error.
  default:
    str = string("Unknown framebuffer status error");
    break;
  }
  return str;
}

//! Returns attachment object type as a string.
inline std::string objectTypeToString(GLint const object_type)
{
  using std::string;
  string str;
  switch (object_type)
  {
  case GL_TEXTURE:
    str = string("GL_TEXTURE");
    break;
  case GL_RENDERBUFFER:
    str = string("GL_RENDERBUFFER");
    break;
  case GL_NONE:
    str = string("GL_NONE");
    break;
  default:
    str = string("Unknown object type");
  }
  return str;
}

//! Returns attachment object type as a string.
inline std::string componentTypeToString(GLint const component_type)
{
  using std::string;
  string str;
  switch (component_type)
  {
  case GL_FLOAT:
    str = string("GL_FLOAT");
    break;
  case GL_INT:
    str = string("GL_INT");
    break;
  case GL_UNSIGNED_INT:
    str = string("GL_UNSIGNED_INT");
    break;
  case GL_SIGNED_NORMALIZED:
    str = string("GL_NORMALIZED");
    break;
  case GL_UNSIGNED_NORMALIZED:
    str = string("GL_UNSIGNED_NORMALIZED");
    break;
  case GL_NONE:
    str = string("GL_NONE");
    break;
  default:
    str = string("Unknown component type");
  }
  return str;
}

} // Namespace: detail.

//! DOCS
class Framebuffer
{
public:
  //! CTOR.
  Framebuffer()
    : _handle(detail::genFramebuffer())
  {}

  //! DTOR.
  ~Framebuffer()
  {
    detail::deleteFramebuffer(_handle);
  }

  GLuint handle() const
  {
    return _handle;
  }

  void bind(GLenum const target) const
  {
    detail::bindFramebuffer(target, _handle);
    throwIfInvalidStatus(target);
  }

  //! Disable all framebuffer objects and return to rendering to back buffer.
  void release(GLenum const target) const
  {
    detail::bindFramebuffer(target, 0);
  }

  GLenum status(GLenum const target) const
  {
    return detail::checkNamedFramebufferStatus(_handle, target);
  }

#if 0
  void attachTexture(GLenum const attachment, GLuint const texture,
                     GLint const level = 0)
  {
    detail::namedFramebufferTexture(_handle, attachment, texture, level);
  }
#endif

  void attachTexture1D(GLenum const attachment, GLuint const texture,
                       GLint const level = 0)
  {
    detail::namedFramebufferTexture1D(_handle, attachment, GL_TEXTURE_1D,
                                      texture, level);
  }

  void attachTexture2D(GLenum const attachment, GLuint const texture,
                       GLenum const textarget = GL_TEXTURE_2D,
                       GLint const level = 0)
  {
    detail::namedFramebufferTexture2D(_handle, attachment, textarget, texture,
                                      level);
  }

  void attachTexture3D(GLenum const attachment, GLuint const texture,
                       GLint const zoffset,
                       GLint level = 0)
  {
    detail::namedFramebufferTexture3D(_handle, attachment, GL_TEXTURE_3D,
                                      texture, level, zoffset);
  }

  void attachRenderbuffer(GLenum const attachment, GLuint const renderbuffer)
  {
    detail::namedFramebufferRenderbuffer(
      _handle, attachment, GL_RENDERBUFFER, renderbuffer);
  }

private:
  Framebuffer(const Framebuffer&); //!< Disabled copy.
  Framebuffer& operator=(const Framebuffer&); //!< Disabled assign.

#if 0
  // NOTE: Too awkward having to bind to check, could cause very nasty bugs!
  void throwIfInvalidHandle()
  {
    GLenum const kTarget = GL_FRAMEBUFFER;
    detail::bindFramebuffer(kTarget, _handle); // Make sure buffer gets created.
    if (detail::isFramebuffer(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid framebuffer handle: " << _handle);
    }
    release(kTarget);
  }
#endif

  void throwIfInvalidStatus(GLenum const target) const
  {
    GLenum const status = detail::checkNamedFramebufferStatus(_handle, target);
    if (GL_FRAMEBUFFER_COMPLETE != status)
    {
      NDJINN_THROW("invalid framebuffer status, handle: " << _handle
                   << ", status: " << detail::statusToString(status));
    }
  }

  GLuint const _handle; //!< Resource handle.
};

NDJINN_END_NAMESPACE

namespace std {

inline ostream& operator<<(ostream& os, ndj::Framebuffer const& fb)
{
  os << "Framebuffer" << endl
     << "  Handle: " << fb.handle() << endl;
  array<pair<GLenum, string>, 3> kTargets = {
    make_pair(GL_FRAMEBUFFER, string("GL_FRAMEBUFFER")),
    make_pair(GL_READ_FRAMEBUFFER, string("GL_READ_FRAMEBUFFER")),
    make_pair(GL_DRAW_FRAMEBUFFER, string("GL_DRAW_FRAMEBUFFER"))
  };

  os << "  Status:" << endl;
  for (auto target = begin(kTargets); target != end(kTargets); ++target)
  {
    GLenum const status = fb.status(target->first);
    string const status_msg = ndj::detail::statusToString(status);
    os << "    " << target->second << ": " << status_msg << endl;
  }

  vector<pair<GLenum, string>> attachments;
  GLint max_color_attachments = 0;
  ndj::getIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max_color_attachments);
  for (GLint i = 0; i < max_color_attachments; ++i)
  {
    GLenum color_attachment = GL_COLOR_ATTACHMENT0 + i;
    stringstream ss;
    ss << "GL_COLOR_ATTACHMENT" << i;
    attachments.push_back(make_pair(color_attachment, ss.str()));
  }
  attachments.push_back(make_pair(GL_DEPTH_ATTACHMENT, "GL_DEPTH_ATTACHMENT"));
  attachments.push_back(make_pair(GL_STENCIL_ATTACHMENT, "GL_STENCIL_ATTACHMENT"));
  //attachments.push_back(make_pair(GL_DEPTH_STENCIL_ATTACHMENT, "GL_DEPTH_STENCIL_ATTACHMENT"));
  os << "  Attachments:" << endl;
  for (auto attachment = begin(attachments); attachment != end(attachments);
       ++attachment)
  {
    GLint const object_type =
      ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
        attachment->first, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
    if (object_type != GL_NONE)
    {
      string const object_type_str = ndj::detail::objectTypeToString(object_type);
      GLint const object_name =
        ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
          attachment->first, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
      GLint const red_bits =
        ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
          attachment->first, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE);
      GLint const green_bits =
        ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
          attachment->first, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE);
      GLint const blue_bits =
        ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
          attachment->first, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE);
      GLint const alpha_bits =
        ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
          attachment->first, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE);
      GLint const depth_bits =
        ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
          attachment->first, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE);
      GLint const stencil_bits =
        ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
          attachment->first, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE);
      GLint const component_type =
        ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
          attachment->first, GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE);
      string const component_type_str =
        ndj::detail::componentTypeToString(component_type);

      os << "    " << attachment->second << ":" << endl
         << "      Type: " << object_type_str << endl
         << "      Name: " << object_name << endl
         << "      Red:     " << red_bits << " [bits]" << endl
         << "      Green:   " << green_bits << " [bits]" << endl
         << "      Blue:    " << blue_bits << " [bits]" << endl
         << "      Alpha:   " << alpha_bits << " [bits]" << endl
         << "      Depth:   " << depth_bits << " [bits]" << endl
         << "      Stencil: " << stencil_bits << " [bits]" << endl
         << "      Component type: " << component_type_str << endl;
      if (object_type == GL_TEXTURE)
      {
        GLint const texture_level =
          ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
            attachment->first, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
        GLint const texture_cube_map_face =
          ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
            attachment->first, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);
        GLint const layered =
          ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
            attachment->first, GL_FRAMEBUFFER_ATTACHMENT_LAYERED);
        GLint const texture_layer =
          ndj::detail::getNamedFramebufferAttachmentParameteri(fb.handle(),
            attachment->first, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER);

        os << "      Texture level: " << texture_level << endl
           << "      Texture cube map face: " << texture_cube_map_face << endl
           << "      Layered: " << layered << endl
           << "      Texture layer: " << texture_layer << endl;
       }
    }
  }
  return os;
}

} // namespace std

#endif  // NDJINN_FRAMEBUFFER_HPP_INCLUDED
