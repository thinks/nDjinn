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
  glCompressedTexImage3D(target, level, intFmt, w, h, d, b, size, data);
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
        const GLvoid *data);

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
           const GLvoid *data);
   
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
                  const GLvoid *data);

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
                     const GLvoid *data);

private:

  Texture3D(const Texture3D&);              //!< Disabled copy.
  Texture3D& operator=(const Texture3D&);   //!< Disabled assign.
};

//------------------------------------------------------------------------------

//! CTOR. May throw.
inline
Texture3D::Texture3D(const GLenum target)
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
  Bindor bind(this);
  detail::texImage3D(target(), level, intFmt, w, h, d, b, fmt, type, data);     
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
  Bindor bind(this);
  detail::texSubImage3D(target(), level, x0, y0, z0, w, h, d, 
                        fmt, type, data);
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
  Bindor bind(this);
  detail::copyTexSubImage3D(target(), level, x0, y0, z0, x, y, w, h);
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
  Bindor bind(this);
  detail::compressedTexImage3D(target(), level, intFmt, w, h, d, 
                               b, size, data);
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
  Bindor bind(this);
  detail::compressedTexSubImage3D(target(), level, x0, y0, z0, 
                                  w, h, d, fmt, size, data);
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE3D_HPP_INCLUDED
