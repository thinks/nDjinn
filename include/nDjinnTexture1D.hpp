//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------
#if 0
#ifndef NDJINN_TEXTURE1D_HPP_INCLUDED
#define NDJINN_TEXTURE1D_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
//#include "nDjinnState.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include "nDjinnTexture.hpp"
#include <gl/glew.h>

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {


//! glTextureImage1D wrapper. May throw.
inline void
textureImage1D(GLuint const texture,
               GLenum const target, 
               GLint const level, 
               GLint const intFmt, 
               GLsizei const w, 
               GLint const b,      
               GLenum const fmt, 
               GLenum const type,   
               GLvoid const* data) {
  glTextureImage1DEXT(texture, target, level, intFmt, w, b, fmt, type, data);     
  checkError("glTextureImage1DEXT"); // May throw;
}

//! glCopyTextureImage1D wrapper. May throw.
inline void
copyTextureImage1D(GLuint const texture, 
                   GLenum const target, 
                   GLint const level, 
                   GLenum const intFmt, 
                   GLint const x, 
                   GLint const y, 
                   GLsizei const w,      
                   GLint const b) {
  glCopyTextureImage1DEXT(texture, target, level, intFmt, x, y, w, b);
  checkError("glCopyTextureImage1DEXT"); // May throw;
}

//! glTextureSubImage1D wrapper. May throw.
inline void 
textureSubImage1D(GLuint const texture,
                  GLenum const target, 
                  GLint const level, 
                  GLint const x0,     
                  GLsizei const w, 
                  GLenum const fmt,    
                  GLenum const type, 
                  GLvoid const* data) {
  glTextureSubImage1DEXT(texture, target, level, x0, w, fmt, type, data);
  checkError("glTextureSubImage1DEXT"); // May throw;
}

//! glCopyTextureSubImage1D wrapper. May throw.
inline void
copyTextureSubImage1D(GLuint const texture, 
                      GLenum const target, 
                      GLint const level, 
                      GLint const x0,     
                      GLint const x, 
                      GLint const y,       
                      GLsizei const w) {
  glCopyTextureSubImage1DEXT(texture, target, level, x0, x, y, w);
  checkError("glCopyTexImage1DEXT"); // May throw;
}

//! glCompressedTextureImage1D wrapper. May throw.
inline void 
compressedTextureImage1D(GLuint const texture,
                         GLenum const target, 
                         GLint const level, 
                         GLenum const intFmt, 
                         GLsizei const w, 
                         GLint const b,
                         GLsizei const size, 
                         GLvoid const* data) {
  glCompressedTextureImage1DEXT(
    texture, target, level, intFmt, w, b, size, data);
  checkError("glCompressedTexImage1DEXT"); // May throw;
}

//! glCompressedTextureSubImage1D wrapper. May throw.
inline void 
compressedTextureSubImage1D(GLuint const texture,
                            GLenum const target, 
                            GLint const level, 
                            GLint const x0,     
                            GLsizei const w, 
                            GLenum const fmt,    
                            GLsizei const size,
                            GLvoid const* data) {
  glCompressedTextureSubImage1DEXT(
    texture, target, level, x0, w, fmt, size, data);
  checkError("glCompressedTexSubImage1DEXT"); // May throw;
}

} // Namespace: detail.

//------------------------------------------------------------------------------

//! 1D texture class.
class Texture1D : public Texture {
public:

  explicit Texture1D(GLenum target = GL_TEXTURE_1D);
  ~Texture1D();

public:     // 1D specific functions.
    
  void
  image(GLint level, 
        GLint intFmt, 
        GLsizei w, 
        GLint b, 
        GLenum fmt, 
        GLenum type, 
        GLvoid const* data);

  void
  copyImage(GLint level, 
            GLenum intFmt, 
            GLint x, 
            GLint y, 
            GLsizei w, 
            GLint b);

  void 
  subImage(GLint level, 
           GLint x0, 
           GLsizei w, 
           GLenum fmt, 
           GLenum type, 
           GLvoid const* data);

  void
  copySubImage(GLint level, GLint x0, GLint x, GLint y, GLsizei w);

  void 
  compressedImage(GLint level, 
                  GLenum intFmt, 
                  GLsizei w, 
                  GLint b, 
                  GLsizei size, 
                  GLvoid const* data);

  void 
  compressedSubImage(GLint level, 
                     GLint x0, 
                     GLsizei w, 
                     GLenum fmt, 
                     GLsizei size, 
                     GLvoid const* data);
};

//------------------------------------------------------------------------------

//! CTOR. May throw.
inline
Texture1D::Texture1D(const GLenum target)
  : Texture(target) { // May throw.
}

//! DTOR.
inline
Texture1D::~Texture1D() {
}

//------------------------------------------------------------------------------

//! Set texture data. May throw.
inline void
Texture1D::image(const GLint level, 
                 const GLint intFmt, 
                 const GLsizei w, 
                 const GLint b, 
                 const GLenum fmt, 
                 const GLenum type, 
                 const GLvoid *data) {
  detail::textureImage1D(
    handle(), target(), level, intFmt, w, b, fmt, type, data);
}

//! "glCopyTexImage1D defines a one-dimensional texture image with 
//! pixels from the current GL_READ_BUFFER." May throw.
inline void
Texture1D::copyImage(const GLint level, 
                     const GLenum intFmt, 
                     const GLint x, 
                     const GLint y, 
                     const GLsizei w, 
                     const GLint b) {
  detail::copyTextureImage1D(
    handle(), target(), level, intFmt, x, y, w, b);
}

//! DOCS. May throw.
inline void 
Texture1D::subImage(const GLint level, 
                    const GLint x0, 
                    const GLsizei w, 
                    const GLenum fmt, 
                    const GLenum type, 
                    const GLvoid *data) {
  detail::textureSubImage1D(
    handle(), target(), level, x0, w, fmt, type, data);
}

//! DOCS. May throw.
inline void
Texture1D::copySubImage(const GLint level, 
                        const GLint x0, 
                        const GLint x, 
                        const GLint y, 
                        const GLsizei w) {
  detail::copyTextureSubImage1D(
    handle(), target(), level, x0, x, y, w);
}

//! DOCS. May throw.
inline void 
Texture1D::compressedImage(const GLint level,  
                           const GLenum intFmt, 
                           const GLsizei w,    
                           const GLint b, 
                           const GLsizei size, 
                           const GLvoid *data) {
  detail::compressedTextureImage1D(
    handle(), target(), level, intFmt, w, b, size, data);
}

//! DOCS. May throw.
inline void 
Texture1D::compressedSubImage(const GLint level, 
                              const GLint x0, 
                              const GLsizei w,     
                              const GLenum fmt, 
                              const GLsizei size,  
                              const GLvoid *data) {
  detail::compressedTextureSubImage1D(
    handle(), target(), level, x0, w, fmt, size, data);
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE1D_HPP_INCLUDED
#endif
