//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_TEXTURE2D_HPP_INCLUDED
#define NDJINN_TEXTURE2D_HPP_INCLUDED

#include <iostream>

#include "nDjinnError.hpp"
#include "nDjinnException.hpp"
#include "nDjinnGL.hpp"
#include "nDjinnNamespace.hpp"
#include "nDjinnTexture.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glTextureImage2D wrapper. May throw.
inline void textureImage2D(GLuint const texture, GLenum const target,
                           GLint const level, GLint const internal_format,
                           GLsizei const width, GLsizei const height,
                           GLint const border, GLenum const format,
                           GLenum const type, GLvoid const* data)
{
  glTextureImage2DEXT(texture, target, level, internal_format, width, height,
                      border, format, type, data);
  checkError("glTextureImage2DEXT");
}

//! glTextureSubImage2D wrapper. May throw.
inline void textureSubImage2D(GLuint const texture, GLenum const target,
                              GLint const level, GLint const x, GLint const y,
                              GLsizei const width, GLsizei const height,
                              GLenum const format, GLenum const type,
                              GLvoid const* data)
{
  glTextureSubImage2DEXT(texture, target, level, x, y, width, height, format,
                         type, data);
  checkError("glTextureSubImage2DEXT"); // May throw;
}

//! glCopyTextureImage2D wrapper. May throw.
inline void copyTextureImage2D(GLuint const texture, GLenum const target,
                               GLint const level, GLenum const internal_format,
                               GLint const x, GLint const y,
                               GLsizei const width, GLsizei const height,
                               GLint const border)
{
  glCopyTextureImage2DEXT(texture, target, level, internal_format, x, y, width,
                          height, border);
  checkError("glCopyTextureImage2DEXT");
}

//! glCopyTextureSubImage2D wrapper. May throw.
inline void copyTextureSubImage2D(GLuint const texture, GLenum const target,
                                  GLint const level, GLint const x_offset,
                                  GLint const y_offset, GLint const x,
                                  GLint const y, GLsizei const width,
                                  GLsizei const height)
{
  glCopyTextureSubImage2DEXT(texture, target, level, x_offset, y_offset, x, y,
                             width, height);
  checkError("glCopyTextureSubImage2DEXT");
}

//! glCompressedTextureImage2D wrapper. May throw.
inline void compressedTextureImage2D(GLuint const texture, const GLenum target,
                                     GLint const level,
                                     GLenum const internal_format,
                                     GLsizei const width, GLsizei const height,
                                     GLint const border, GLsizei const size,
                                     GLvoid const* data)
{
  glCompressedTextureImage2DEXT(texture, target, level, internal_format, width,
                                height, border, size, data);
  checkError("glCompressedTextureImage2DEXT");
}

//! glCompressedTextureSubImage2D wrapper. May throw.
inline void compressedTextureSubImage2D(GLuint const texture,
                                        GLenum const target, GLint const level,
                                        GLint const x,
                                        GLint const y,
                                        GLsizei const width,
                                        GLsizei const height,
                                        GLenum const format,
                                        GLsizei const size, GLvoid const* data)
{
  glCompressedTextureSubImage2DEXT(texture, target, level, x, y,
                                   width, height, format, size, data);
  checkError("glCompressedTextureSubImage2DEXT");
}

} // Namespace: detail.

//! 2D texture class.
class Texture2D
{
public:
  Texture2D()
    : _handle(detail::genTexture())
  {}

  Texture2D(GLenum const target, GLsizei const width, GLsizei const height,
            GLint const level = 0, GLint const internal_format = GL_RGBA8,
            GLint const border = 0, GLenum const format = GL_RGBA,
            GLenum const type = GL_UNSIGNED_BYTE, GLvoid const* data = nullptr)
    : _handle(detail::genTexture())
  {
    setImage(target, level, internal_format, width, height, border, format,
             type, data);
  }

  ~Texture2D()
  {
    detail::deleteTexture(_handle);
  }

  GLuint handle() const
  {
    return _handle;
  }

  void setImage(GLenum const target, GLint const level,
                GLint const internal_format, GLsizei const width,
                GLsizei const height, GLint const border,
                GLenum const format, GLenum const type, GLvoid const* data)
  {
    detail::textureImage2D(_handle, target, level, internal_format, width,
                           height, border, format, type, data);
  }

  void setSubImage(GLenum const target, GLint const level,
                   GLint const x, GLint const y,
                   GLsizei const width, GLsizei const height,
                   GLenum const format, GLenum const type, GLvoid const* data)
  {
    detail::textureSubImage2D(_handle, target, level, x, y, width, height,
                              format, type, data);
  }

  void compressedImage(GLenum const target, GLint const level,
                       GLenum const internal_format,
                       GLsizei const width, GLsizei const height,
                       GLint const border, GLsizei const size,
                       GLvoid const* data)
  {
    detail::compressedTextureImage2D(_handle, target, level, internal_format,
                                     width, height, border, size, data);
  }

  void compressedSubImage(GLenum const target, GLint const level,
                          GLint const x, GLint const y,
                          GLsizei const width, GLsizei const height,
                          GLenum const format, GLsizei const size,
                          GLvoid const* data)
  {
    detail::compressedTextureSubImage2D(_handle, target, level, x, y,
                                        width, height, format, size, data);
  }

  //! "glCopyTexImage2D defines a two-dimensional texture image with
  //! pixels from the current GL_READ_BUFFER."
  void copyImage(GLenum const target, GLint const level,
                 GLenum const internal_format,
                 GLint const x, GLint const y,
                 GLsizei const width, GLsizei const height,
                 GLint const border)
  {
    detail::copyTextureImage2D(_handle, target, level, internal_format,
                               x, y, width, height, border);
  }

  void copySubImage(GLenum const target, GLint const level,
                    GLint const x_offset, GLint y_offset,
                    GLint const x, GLint const y,
                    GLsizei const width, GLsizei const height)
  {
    detail::copyTextureSubImage2D(_handle, target, level, x_offset, y_offset,
                                  x, y, width, height);
  }

  GLint width(GLenum const target, GLint const level = 0) const
  {
    std::array<GLint, 1> const values = getTextureLevelParameters<GLint, 1>(
      *this, target, level, GL_TEXTURE_WIDTH);
    return values[0];
  }

  GLint height(GLenum const target, GLint const level = 0) const
  {
    std::array<GLint, 1> const values = getTextureLevelParameters<GLint, 1>(
      *this, target, level, GL_TEXTURE_HEIGHT);
    return values[0];
  }

private:
  Texture2D(Texture2D const&); //!< Disabled copy.
  Texture2D& operator=(Texture2D const&); //!< Disabled assign.

  GLuint const _handle;
};

NDJINN_END_NAMESPACE

namespace std {

ostream& operator<<(ostream& os, ndj::Texture2D const& tex)
{
  os << "Texture2D" << endl
     << "  Handle: " << tex.handle() << endl;
  return os;
}

} // namespace std

#endif  // NDJINN_TEXTURE2D_HPP_INCLUDED
