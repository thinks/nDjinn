//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_TEXTURE2D_HPP_INCLUDED
#define NDJINN_TEXTURE2D_HPP_INCLUDED

#include <array>
#include <iostream>
#include <string>

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

//!
inline std::string channelTypeToString(GLint const type)
{
  using std::string;
  string str;
  switch (type)
  {
  case GL_NONE:
    str = string("GL_NONE");
    break;
  case GL_SIGNED_NORMALIZED:
    str = string("GL_SIGNED_NORMALIZED");
    break;
  case GL_UNSIGNED_NORMALIZED:
    str = string("GL_UNSIGNED_NORMALIZED");
    break;
  case GL_FLOAT:
    str = string("GL_FLOAT");
    break;
  case GL_INT:
    str = string("GL_INT");
    break;
  case GL_UNSIGNED_INT:
    str = string("GL_UNSIGNED_INT");
    break;
  default:
    str = string("Unknown channel type");
  }
  return str;
}

inline std::string internalFormatToString(GLint const internal_format)
{
  using std::string;
  string str;
  switch (internal_format)
  {
  // TODO: Add internal format!
  default:
    str = string("Unknown internal format");
  }
  return str;
}

inline std::string booleanToString(GLint const boolean)
{
  using std::string;
  string str;
  switch (boolean)
  {
  case GL_TRUE:
    str = string("GL_TRUE");
    break;
  case GL_FALSE:
    str = string("GL_FALSE");
    break;
  default:
    str = string("Unknown boolean");
  }
  return str;
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

inline
ostream& operator<<(ostream& os, ndj::Texture2D const& tex)
{
  using ndj::getTextureParameters;
  using ndj::getTextureLevelParameters;
  using ndj::detail::channelTypeToString;
  using ndj::detail::internalFormatToString;
  using ndj::detail::booleanToString;

  // Requires OpenGL version 4.5+
  //array<GLint, 1> const target = getTextureParameters<GLint, 1>(
  //  tex, GL_TEXTURE_2D, 0, GL_TEXTURE_TARGET);

  GLuint const handle = tex.handle();

  //GLenum const target = tex.target();
  GLenum const target = GL_TEXTURE_2D;
  GLint const level = 0;

  GLint const width = tex.width(target);
  GLint const height = tex.height(target);

  array<GLint, 1> const internal_format = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_INTERNAL_FORMAT);
  array<GLint, 1> const red_type = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_RED_TYPE);
  array<GLint, 1> const green_type = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_GREEN_TYPE);
  array<GLint, 1> const blue_type = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_BLUE_TYPE);
  array<GLint, 1> const alpha_type = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_ALPHA_TYPE);
  array<GLint, 1> const depth_type = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_DEPTH_TYPE);
  array<GLint, 1> const red_size = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_RED_SIZE);
  array<GLint, 1> const green_size = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_GREEN_SIZE);
  array<GLint, 1> const blue_size = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_BLUE_SIZE);
  array<GLint, 1> const alpha_size = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_ALPHA_SIZE);
  array<GLint, 1> const depth_size = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_DEPTH_SIZE);
  //array<GLint, 1> const buffer_offset = getTextureLevelParameters<GLint, 1>(
  //  tex, target, level, GL_TEXTURE_BUFFER_OFFSET);
  //array<GLint, 1> const buffer_size = getTextureLevelParameters<GLint, 1>(
  //  tex, target, level, GL_TEXTURE_BUFFER_SIZE);

  os << "Texture2D" << endl
     << "  Handle: " << handle << endl
     << "  Target: " << target << endl
     << "  Width: " << width << endl
     << "  Height: " << height << endl
     << "  Internal format: "
       << internalFormatToString(internal_format[0]) << endl
     << "  Red type:   " << channelTypeToString(red_type[0]) << endl
     << "  Green type: " << channelTypeToString(green_type[0]) << endl
     << "  Blue type:  " << channelTypeToString(blue_type[0]) << endl
     << "  Alpha type: " << channelTypeToString(alpha_type[0]) << endl
     << "  Depth type: " << channelTypeToString(depth_type[0]) << endl
     << "  Red size:   " << red_size[0] << " [bits] " << endl
     << "  Green size: " << green_size[0] << " [bits] " << endl
     << "  Blue size:  " << blue_size[0] << " [bits] " << endl
     << "  Alpha size: " << alpha_size[0] << " [bits] " << endl
     << "  Depth size: " << depth_size[0] << " [bits] " << endl;
     //<< "  Buffer offset: " << buffer_offset[0] << endl
     //<< "  Buffer size: " << buffer_size[0] << endl;

  array<GLint, 1> const is_compressed = getTextureLevelParameters<GLint, 1>(
    tex, target, level, GL_TEXTURE_COMPRESSED);
  os << "  Compressed: " << booleanToString(is_compressed[0]) << endl;
  if (is_compressed[0] == GL_TRUE)
  {
    array<GLint, 1> const compressed_size_in_bytes =
      getTextureLevelParameters<GLint, 1>(
        tex, target, level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE);
    os << "  Compressed size: " << compressed_size_in_bytes[0]
       << " [bytes]" << endl;
  }

  return os;
}

} // namespace std

#endif  // NDJINN_TEXTURE2D_HPP_INCLUDED
