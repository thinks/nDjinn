//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_TEXTURE2D_HPP_INCLUDED
#define NDJINN_TEXTURE2D_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
//#include "nDjinnState.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include "nDjinnTexture.hpp"
#include <gl/glew.h>

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

#if 0 
// DEPRECATED - use direct state access instead!  

//! glTexImage2D wrapper. May throw.
inline void
texImage2D(const GLenum target, 
           const GLint level, 
           const GLint intFmt, 
           const GLsizei w,     
           const GLsizei h,      
           const GLint b, 
           const GLenum fmt,    
           const GLenum type, 
           const GLvoid *data) {
  glTexImage2D(target, level, intFmt, w, h, b, fmt, type, data);     
  checkError("glTexImage2D"); // May throw;
}

//! glCopyTexImage2D wrapper. May throw.
inline void
copyTexImage2D(const GLenum target, 
              const GLint level, 
              const GLenum intFmt, 
              const GLint x, 
              const GLint y,        
              const GLsizei w,      
              const GLsizei h,      
              const GLint b) {
  glCopyTexImage2D(target, level, intFmt, x, y, w, h, b);
  checkError("glCopyTexImage2D"); // May throw;
}

//! glTexSubImage2D wrapper. May throw.
inline void 
texSubImage2D(const GLenum target, 
              const GLint level, 
              const GLint x0,     
              const GLint y0, 
              const GLsizei w,      
              const GLsizei h,
              const GLenum fmt,    
              const GLenum type, 
              const GLvoid *data) {
  glTexSubImage2D(target, level, x0, y0, w, h, fmt, type, data);
  checkError("glTexSubImage2D"); // May throw;
}

//! glCopyTexSubImage2D wrapper. May throw.
inline void
copyTexSubImage2D(const GLenum target, 
                  const GLint level, 
                  const GLint x0,     
                  const GLint y0, 
                  const GLint x,      
                  const GLint y, 
                  const GLsizei w,      
                  const GLsizei h) {
  glCopyTexSubImage2D(target, level, x0, y0, x, y, w, h);
  checkError("glCopyTexSubImage2D"); // May throw;
}

//! glCompressedTexImage2D wrapper. May throw.
inline void 
compressedTexImage2D(const GLenum target, 
                     const GLint level, 
                     const GLenum intFmt, 
                     const GLsizei w, 
                     const GLsizei h,     
                     const GLint b, 
                     const GLsizei size,  
                     const GLvoid *data) {
  glCompressedTexImage2D(target, level, intFmt, w, h, b, size, data);
  checkError("glCompressedTexImage2D"); // May throw;
}

//! glCompressedTexSubImage2D wrapper. May throw.
inline void 
compressedTexSubImage2D(const GLenum target, 
                        const GLint level, 
                        const GLint x0,     
                        const GLint y0,
                        const GLsizei w,      
                        const GLsizei h,
                        const GLenum fmt,    
                        const GLsizei size,
                        const GLvoid *data) {
  glCompressedTexSubImage2D(target, level, x0, y0, w, h, fmt, size, data);
  checkError("glCompressedTexSubImage2D"); // May throw;
}

#endif

//! glTextureImage2D wrapper. May throw.
inline void
textureImage2D(GLuint const texture, 
               GLenum const target, 
               GLint const level, 
               GLint const intFmt, 
               GLsizei const w,     
               GLsizei const h,      
               GLint const b, 
               GLenum const fmt,    
               GLenum const type, 
               GLvoid const* data) {
  glTextureImage2DEXT(texture, target, level, intFmt, w, h, b, fmt, type, data);     
  checkError("glTextureImage2DEXT"); // May throw;
}

//! glCopyTextureImage2D wrapper. May throw.
inline void
copyTextureImage2D(GLuint const texture,
                   GLenum const target, 
                   GLint const level, 
                   GLenum const intFmt, 
                   GLint const x, 
                   GLint const y,        
                   GLsizei const w,      
                   GLsizei const h,      
                   GLint const b) {
  glCopyTextureImage2DEXT(texture, target, level, intFmt, x, y, w, h, b);
  checkError("glCopyTextureImage2DEXT"); // May throw;
}

//! glTextureSubImage2D wrapper. May throw.
inline void 
textureSubImage2D(GLuint const texture,
                  GLenum const target, 
                  GLint const level, 
                  GLint const x0,     
                  GLint const y0, 
                  GLsizei const w,      
                  GLsizei const h,
                  GLenum const fmt,    
                  GLenum const type, 
                  GLvoid const* data) {
  glTextureSubImage2DEXT(texture, target, level, x0, y0, w, h, fmt, type, data);
  checkError("glTextureSubImage2DEXT"); // May throw;
}

//! glCopyTextureSubImage2D wrapper. May throw.
inline void
copyTextureSubImage2D(GLuint const texture,
                      GLenum const target, 
                      GLint const level, 
                      GLint const x0,     
                      GLint const y0, 
                      GLint const x,      
                      GLint const y, 
                      GLsizei const w,      
                      GLsizei const h) {
  glCopyTextureSubImage2DEXT(texture, target, level, x0, y0, x, y, w, h);
  checkError("glCopyTextureSubImage2DEXT"); // May throw;
}



//! glCompressedTextureImage2D wrapper. May throw.
inline void 
compressedTextureImage2D(GLuint const texture,
  const GLenum target, 
                     const GLint level, 
                     const GLenum intFmt, 
                     const GLsizei w, 
                     const GLsizei h,     
                     const GLint b, 
                     const GLsizei size,  
                     const GLvoid *data) {
  glCompressedTextureImage2DEXT(
    texture, target, level, intFmt, w, h, b, size, data);
  checkError("glCompressedTextureImage2DEXT"); // May throw;
}

//! glCompressedTextureSubImage2D wrapper. May throw.
inline void 
compressedTextureSubImage2D(GLuint const texture, 
                            GLenum const target, 
                            GLint const level, 
                            GLint const x0,     
                            GLint const y0,
                            GLsizei const w,      
                            GLsizei const h,
                            GLenum const fmt,    
                            GLsizei const size,
                            GLvoid const* data) {
  glCompressedTextureSubImage2DEXT(
    texture, target, level, x0, y0, w, h, fmt, size, data);
  checkError("glCompressedTextureSubImage2DEXT"); // May throw;
}

} // Namespace: detail.

//------------------------------------------------------------------------------

//! 2D texture class.
class Texture2D : public Texture
{
public:
  explicit Texture2D(GLenum target = GL_TEXTURE_RECTANGLE/*GL_TEXTURE_2D*/);
  ~Texture2D();

public:     // 2D specific functions.
  void
  image(GLint level, 
        GLint intFmt, 
        GLsizei w, 
        GLsizei h, 
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
            GLsizei h, 
            GLint b);

  void 
  subImage(GLint level, 
           GLint x0, 
           GLint y0, 
           GLsizei w, 
           GLsizei h,  
           GLenum fmt, 
           GLenum type, 
           GLvoid const* data);

  void
  copySubImage(GLint level, 
               GLint x0, 
               GLint y0, 
               GLint x, 
               GLint y, 
               GLsizei w, 
               GLsizei h);

  void 
  compressedImage(GLint level, 
                  GLenum intFmt, 
                  GLsizei w, 
                  GLsizei h, 
                  GLint b, 
                  GLsizei size, 
                  GLvoid const* data);

  void 
  compressedSubImage(GLint level, 
                     GLint x0, 
                     GLint y0, 
                     GLsizei w, 
                     GLsizei h, 
                     GLenum fmt, 
                     GLsizei size, 
                     GLvoid const* data);

  GLint
  width(GLint level = 0) const;

  GLint 
  height(GLint level = 0) const;
};

//------------------------------------------------------------------------------

//! CTOR.
inline
Texture2D::Texture2D(GLenum const target)
  : Texture(target) { // May throw.
}

//! DTOR.
inline
Texture2D::~Texture2D() {
}

//------------------------------------------------------------------------------

//! Set texture data.
inline void
Texture2D::image(const GLint level, 
                 const GLint intFmt, 
                 const GLsizei w, 
                 const GLsizei h,   
                 const GLint b,      
                 const GLenum fmt, 
                 const GLenum type, 
                 const GLvoid *data) {
  detail::textureImage2D(
    handle(), target(), level, intFmt, w, h, b, fmt, type, data);
}

//! "glCopyTexImage2D defines a two-dimensional texture image with 
//! pixels from the current GL_READ_BUFFER."
inline void
Texture2D::copyImage(const GLint level, 
                     const GLenum intFmt, 
                     const GLint x,     
                     const GLint y, 
                     const GLsizei w,   
                     const GLsizei h,   
                     const GLint b) {
  detail::copyTextureImage2D(
    handle(), target(), level, intFmt, x, y, w, h, b);
}

//! DOCS. May throw.
inline void 
Texture2D::subImage(const GLint level, 
                    const GLint x0,   
                    const GLint y0, 
                    const GLsizei w,   
                    const GLsizei h,  
                    const GLenum fmt, 
                    const GLenum type, 
                    const GLvoid *data) {
  detail::textureSubImage2D(
    handle(), target(), level, x0, y0, w, h, fmt, type, data);
}

//! DOCS. May throw.
inline void
Texture2D::copySubImage(const GLint level, 
                        const GLint x0, 
                        const GLint y0,    
                        const GLint x, 
                        const GLint y,     
                        const GLsizei w, 
                        const GLsizei h) {
  detail::copyTextureSubImage2D(
    handle(), target(), level, x0, y0, x, y, w, h);
}

//! DOCS. May throw.
inline void 
Texture2D::compressedImage(const GLint level, 
                           const GLenum intFmt, 
                           const GLsizei w,     
                           const GLsizei h, 
                           const GLint b,     
                           const GLsizei size, 
                           const GLvoid *data) {
  detail::compressedTextureImage2D(
    handle(), target(), level, intFmt, w, h, b, size, data);
}

//! DOCS. May throw.
inline void 
Texture2D::compressedSubImage(const GLint level, 
                              const GLint x0, 
                              const GLint y0,    
                              const GLsizei w,     
                              const GLsizei h,     
                              const GLenum fmt, 
                              const GLsizei size,  
                              const GLvoid *data) {
  detail::compressedTextureSubImage2D(
    handle(), target(), level, x0, y0, w, h, fmt, size, data);
}

GLint
Texture2D::width(GLint const level) const {
  GLint w = 0;
  detail::getTextureLevelParameterv<GLint>(
    handle(), target(), level, GL_TEXTURE_WIDTH, &w);
  return w;
}

GLint 
Texture2D::height(GLint const level) const {
  GLint h = 0;
  detail::getTextureLevelParameterv<GLint>(
    handle(), target(), level, GL_TEXTURE_HEIGHT, &h);
  return h;

}

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE2D_HPP_INCLUDED
