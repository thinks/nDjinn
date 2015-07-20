//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_RENDERBUFFER_HPP_INCLUDED
#define NDJINN_RENDERBUFFER_HPP_INCLUDED

#include <iostream>

#include "nDjinnError.hpp"
#include "nDjinnException.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glGenRenderbuffers wrapper. May throw.
inline void genRenderbuffers(GLsizei const n, GLuint* renderbuffers)
{
  glGenRenderbuffers(n, renderbuffers);
  checkError("glGenRenderbuffers");
}

//! glDeleteRenderbuffers wrapper. May throw.
inline void deleteRenderbuffers(GLsizei const n, GLuint const* renderbuffers)
{
  glDeleteRenderbuffers(n, renderbuffers);
  checkError("glDeleteRenderbuffers");
}

//! glIsRenderbuffer wrapper. May throw.
inline GLboolean isRenderbuffer(GLuint const renderbuffer)
{
  GLboolean const result = glIsRenderbuffer(renderbuffer);
  checkError("glIsRenderbuffer");
  return result;
}

//! glBindRenderbuffer wrapper. May throw.
inline GLboolean bindRenderbuffer(GLenum const target,
                                  GLuint const renderbuffer)
{
  glBindRenderbuffer(target, renderbuffer);
  checkError("glBindRenderbuffer");
}

//! glNamedRenderbufferStorageMultisampleEXT wrapper. May throw.
inline void namedRenderbufferStorageMultisample(GLuint const renderbuffer,
                                                GLsizei const samples,
                                                GLenum const internalformat,
                                                GLsizei const width,
                                                GLsizei const height)
{
  glNamedRenderbufferStorageMultisampleEXT(renderbuffer, samples,
                                           internalformat, width, height);
  checkError("glNamedRenderbufferStorageMultisampleEXT");
}

//! glGetNamedRenderbufferParameterivEXT wrapper. May throw.
inline void getNamedRenderbufferParameteriv(GLuint const renderbuffer,
                                            GLenum const pname, GLint* params)
{
  glGetNamedRenderbufferParameterivEXT(renderbuffer, pname, params);
  checkError("glGetNamedRenderbufferParameterivEXT");
}

//! Convenience.
inline GLuint genRenderbuffer() {
  GLuint handle = 0;
  genFramebuffers(1, &handle);
  return handle;
}

//! Convenience.
inline void deleteRenderbuffer(GLuint const handle) {
  deleteFramebuffers(1, &handle);
}

//! Convenience.
inline GLint getNamedRenderbufferParameteri(GLuint const renderbuffer,
                                            GLenum const pname)
{
  GLint params = 0;
  getNamedRenderbufferParameteriv(renderbuffer, pname, &params);
  return params;
}

} // namespace detail

//! DOCS
class Renderbuffer
{
public:
  Renderbuffer(GLenum const internal_format, GLsizei const width,
               GLsizei const height, GLsizei const samples = 0)
    : _handle(detail::genRenderbuffer())
  {
    //throwIfInvalidHandle();
    detail::namedRenderbufferStorageMultisample(_handle, samples,
                                                internal_format, width, height);
  }

  ~Renderbuffer()
  {
    detail::deleteRenderbuffer(_handle);
  }

  GLuint handle() const
  {
    return _handle;
  }

  void bind() const
  {
    detail::bindRenderbuffer(GL_RENDERBUFFER, _handle);
  }

  void release() const
  {
    detail::bindRenderbuffer(GL_RENDERBUFFER, 0);
  }

private:
  Renderbuffer(const Renderbuffer&); //!< Disabled copy.
  Renderbuffer& operator=(const Renderbuffer&); //!< Disabled assign.

  void throwIfInvalidHandle()
  {
    if (detail::isRenderbuffer(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid renderbuffer handle: " << _handle);
    }
  }

  GLuint const _handle;
};

NDJINN_END_NAMESPACE

namespace std {

ostream& operator<<(ostream& os, ndj::Renderbuffer const& rb)
{
  GLint const width =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_WIDTH);
  GLint const height =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_HEIGHT);
  GLint const internal_format =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_INTERNAL_FORMAT);
  GLint const samples =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_SAMPLES);
  GLint const red_size =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_RED_SIZE);
  GLint const green_size =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_GREEN_SIZE);
  GLint const blue_size =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_BLUE_SIZE);
  GLint const alpha_size =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_ALPHA_SIZE);
  GLint const depth_size =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_DEPTH_SIZE);
  GLint const stencil_size =
    ndj::detail::getNamedRenderbufferParameteri(rb.handle(),
      GL_RENDERBUFFER_STENCIL_SIZE);

  // TODO: internal_format as string!
  os << "Renderbuffer" << endl
     << "  Handle: " << rb.handle() << endl
     << "  Internal format: " << internal_format << endl
     << "  Samples: " << samples << endl
     << "  Height: " << height << endl
     << "  Width:  " << width << endl
     << "  Red: " << red_size << " [bits]" << endl
     << "  Green: " << green_size << " [bits]" << endl
     << "  Blue: " << blue_size << " [bits]" << endl
     << "  Alpha: " << alpha_size << " [bits]" << endl
     << "  Depth: " << depth_size << " [bits]" << endl
     << "  Stencil: " << stencil_size << " [bits]" << endl;
  return os;
}

} // namespace std

#endif  // NDJINN_RENDERBUFFER_HPP_INCLUDED
