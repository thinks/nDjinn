//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_TEXTURE3D_HPP_INCLUDED
#define NDJINN_TEXTURE3D_HPP_INCLUDED

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

//! glTexImage3D wrapper. May throw.
inline void
texImage3D(const GLenum target, 
           const GLint level, 
           const GLint intFmt, 
           const GLsizei w, 
           const GLsizei h,      
           const GLsizei d, 
           const GLint b,      
           const GLenum fmt, 
           const GLenum type,   
           const GLvoid *data) {
  glTexImage3D(target, level, intFmt, w, h, d, b, fmt, type, data);     
  checkError("glTexImage3D"); 
}

//! glCopyTexSubImage3D wrapper. May throw.
inline void 
texSubImage3D(const GLenum target, 
              const GLint level, 
              const GLint x0,     
              const GLint y0, 
              const GLint z0,     
              const GLsizei w, 
              const GLsizei h,      
              const GLsizei d,
              const GLenum fmt,    
              const GLenum type, 
              const GLvoid *data) {
  glTexSubImage3D(target, level, x0, y0, z0, w, h, d, fmt, type, data);
  checkError("glTexSubImage3D");
}

//! glCopyTexSubImage3D wrapper. May throw.
inline void
copyTexSubImage3D(const GLenum target, 
                  const GLint level, 
                  const GLint x0,     
                  const GLint y0, 
                  const GLint z0,     
                  const GLint x, 
                  const GLint y,      
                  const GLsizei w, 
                  const GLsizei h) {
  glCopyTexSubImage3D(target, level, x0, y0, z0, x, y, w, h);
  checkError("glCopyTexSubImage3D"); 
}

//! glCompressedTexImage3D wrapper. May throw.
inline void 
compressedTexImage3D(const GLenum target, 
                     const GLint level, 
                     const GLenum intFmt, 
                     const GLsizei w, 
                     const GLsizei h,      
                     const GLsizei d, 
                     const GLint b,      
                     const GLsizei size,
                     const GLvoid *data) {
  glCompressedTexImage3D(texture, target, level, intFmt, w, h, d, b, size, data);
  checkError("glCompressedTexImage3D");
}

//! glCompressedTexSubImage3D wrapper. May throw. 
inline void 
compressedTexSubImage3D(const GLenum target, 
                        const GLint level, 
                        const GLint x0,     
                        const GLint y0, 
                        const GLint z0,     
                        const GLsizei w, 
                        const GLsizei h,      
                        const GLsizei d,
                        const GLenum fmt,    
                        const GLsizei size,
                        const GLvoid *data) {
  glCompressedTexSubImage3D(target, level, x0, y0, z0, 
                            w, h, d, fmt, size, data);
  checkError("glCompressedTexSubImage3D");
}

#endif

//! glTextureImage3D wrapper. May throw.
inline void
textureImage3D(const GLuint texture,
               const GLenum target, 
               const GLint level, 
               const GLint intFmt, 
               const GLsizei w, 
               const GLsizei h,      
               const GLsizei d, 
               const GLint b,      
               const GLenum fmt, 
               const GLenum type,   
               const GLvoid *data) {
  glTextureImage3DEXT(
    texture, target, level, intFmt, w, h, d, b, fmt, type, data);     
  checkError("glTextureImage3DEXT"); 
}

//! glTextureSubImage3D wrapper. May throw.
inline void 
textureSubImage3D(const GLuint texture,
                  const GLenum target, 
                  const GLint level, 
                  const GLint x0,     
                  const GLint y0, 
                  const GLint z0,     
                  const GLsizei w, 
                  const GLsizei h,      
                  const GLsizei d,
                  const GLenum fmt,    
                  const GLenum type, 
                  const GLvoid *data) {
  glTextureSubImage3DEXT(
    texture,target, level, x0, y0, z0, w, h, d, fmt, type, data);
  checkError("glTextureSubImage3DEXT");
}

//! glCopyTextureSubImage3D wrapper. May throw.
inline void
copyTextureSubImage3D(const GLuint texture,
                      const GLenum target, 
                      const GLint level, 
                      const GLint x0,     
                      const GLint y0, 
                      const GLint z0,     
                      const GLint x, 
                      const GLint y,      
                      const GLsizei w, 
                      const GLsizei h) {
  glCopyTextureSubImage3DEXT(texture, target, level, x0, y0, z0, x, y, w, h);
  checkError("glCopyTextureSubImage3DEXT"); 
}

//! glCompressedTextureImage3D wrapper. May throw.
inline void 
compressedTextureImage3D(const GLuint texture,
                         const GLenum target, 
                         const GLint level, 
                         const GLenum intFmt, 
                         const GLsizei w, 
                         const GLsizei h,      
                         const GLsizei d, 
                         const GLint b,      
                         const GLsizei size,
                         const GLvoid *data) {
  glCompressedTextureImage3DEXT(
    texture, target, level, intFmt, w, h, d, b, size, data);
  checkError("glCompressedTextureImage3DEXT");
}

//! glCompressedTextureSubImage3D wrapper. May throw. 
inline void 
compressedTextureSubImage3D(const GLuint texture,
                            const GLenum target, 
                            const GLint level, 
                            const GLint x0,     
                            const GLint y0, 
                            const GLint z0,     
                            const GLsizei w, 
                            const GLsizei h,      
                            const GLsizei d,
                            const GLenum fmt,    
                            const GLsizei size,
                            const GLvoid *data) {
  glCompressedTextureSubImage3DEXT(
    texture, target, level, x0, y0, z0, w, h, d, fmt, size, data);
  checkError("glCompressedTextureSubImage3DEXT");
}

} // Namespace: detail.

//------------------------------------------------------------------------------

//! 3D texture class.
class Texture3D : public Texture
{
public:
  explicit Texture3D(GLenum target = GL_TEXTURE_3D);
  ~Texture3D();

public:     // 3D specific functions.

  void
  image(GLint level, 
        GLint intFmt, 
        GLsizei w, 
        GLsizei h, 
        GLsizei d, 
        GLint b, 
        GLenum fmt, 
        GLenum type, 
        GLvoid const* data);

  void 
  subImage(GLint level, 
           GLint x0, 
           GLint y0, 
           GLint z0,
           GLsizei w, 
           GLsizei h, 
           GLsizei d,
           GLenum fmt, 
           GLenum type, 
           GLvoid const* data);
   
  void
  copySubImage(GLint level, 
               GLint x0, 
               GLint y0, 
               GLint z0, 
               GLint x, 
               GLint y,
               GLsizei w, 
               GLsizei h);

  void 
  compressedImage(GLint level, 
                  GLenum intFmt, 
                  GLsizei w, 
                  GLsizei h, 
                  GLsizei d, 
                  GLint b, 
                  GLsizei size, 
                  GLvoid const* data);

  void 
  compressedSubImage(GLint level, 
                     GLint x0, 
                     GLint y0, 
                     GLint z0, 
                     GLsizei w, 
                     GLsizei h, 
                     GLsizei d, 
                     GLenum fmt, 
                     GLsizei size, 
                     GLvoid const* data);
};

//------------------------------------------------------------------------------

//! CTOR. May throw.
inline
Texture3D::Texture3D(GLenum const target)
    : Texture(target) { // May throw.
}

//! DTOR.
inline
Texture3D::~Texture3D() {
}

//------------------------------------------------------------------------------

//! DOCS. May throw.
inline void
Texture3D::image(const GLint level, 
                 const GLint intFmt, 
                 const GLsizei w,     
                 const GLsizei h, 
                 const GLsizei d,     
                 const GLint b, 
                 const GLenum fmt,   
                 const GLenum type, 
                 const GLvoid *data) {
  detail::textureImage3D(
    handle(), target(), level, intFmt, w, h, d, b, fmt, type, data);     
}

//! DOCS. May throw.
inline void 
Texture3D::subImage(const GLint level, 
                    const GLint x0, 
                    const GLint y0,    
                    const GLint z0,
                    const GLsizei w,     
                    const GLsizei h, 
                    const GLsizei d,     
                    const GLenum fmt, 
                    const GLenum type,  
                    const GLvoid *data) {
  detail::textureSubImage3D(
    handle(), target(), level, x0, y0, z0, w, h, d, fmt, type, data);
}
    
//! DOCS. May throw.
inline void
Texture3D::copySubImage(const GLint level, 
                        const GLint x0, 
                        const GLint y0,    
                        const GLint z0, 
                        const GLint x,     
                        const GLint y,
                        const GLsizei w,     
                        const GLsizei h) {
  detail::copyTextureSubImage3D(
    handle(), target(), level, x0, y0, z0, x, y, w, h);
}

//! DOCS. May throw.
inline void 
Texture3D::compressedImage(const GLint level, 
                           const GLenum intFmt, 
                           const GLsizei w,     
                           const GLsizei h, 
                           const GLsizei d,     
                           const GLint b, 
                           const GLsizei size,  
                           const GLvoid *data) {
  detail::compressedTextureImage3D(
    handle(), target(), level, intFmt, w, h, d, b, size, data);
}

//! DOCS. May throw.
inline void 
Texture3D::compressedSubImage(const GLint level, 
                              const GLint x0, 
                              const GLint y0,    
                              const GLint z0, 
                              const GLsizei w,     
                              const GLsizei h, 
                              const GLsizei d,     
                              const GLenum fmt, 
                              const GLsizei size,  
                              const GLvoid *data) {
  detail::compressedTextureSubImage3D(
    handle(), target(), level, x0, y0, z0, w, h, d, fmt, size, data);
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE3D_HPP_INCLUDED
