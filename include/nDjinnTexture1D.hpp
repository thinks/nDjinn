//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

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

//! glTexImage1D wrapper. May throw.
inline void
texImage1D(const GLenum target, 
           const GLint level, 
           const GLint intFmt, 
           const GLsizei w, 
           const GLint b,      
           const GLenum fmt, 
           const GLenum type,   
           const GLvoid *data) {
  glTexImage1D(target, level, intFmt, w, b, fmt, type, data);     
  checkError("glTexImage1D"); // May throw;
}

//! glCopyTexImage1D wrapper. May throw.
inline void
copyTexImage1D(const GLenum target, 
               const GLint level, 
               const GLenum intFmt, 
               const GLint x, 
               const GLint y, 
               const GLsizei w,      
               const GLint b) {
  glCopyTexImage1D(target, level, intFmt, x, y, w, b);
  checkError("glCopyTexImage1D"); // May throw;
}

//! glTexSubImage1D wrapper. May throw.
inline void 
texSubImage1D(const GLenum target, 
              const GLint level, 
              const GLint x0,     
              const GLsizei w, 
              const GLenum fmt,    
              const GLenum type, 
              const GLvoid *data) {
  glTexSubImage1D(target, level, x0, w, fmt, type, data);
  checkError("glTexSubImage1D"); // May throw;
}

//! glCopyTexSubImage1D wrapper. May throw.
inline void
copyTexSubImage1D(const GLenum target, 
                  const GLint level, 
                  const GLint x0,     
                  const GLint x, 
                  const GLint y,       
                  const GLsizei w) {
  glCopyTexSubImage1D(target, level, x0, x, y, w);
  checkError("glCopyTexImage1D"); // May throw;
}

//! glCompressedTexImage1D wrapper. May throw.
inline void 
compressedTexImage1D(const GLenum target, 
                     const GLint level, 
                     const GLenum intFmt, 
                     const GLsizei w, 
                     const GLint b,
                     const GLsizei size, 
                     const GLvoid *data) {
  glCompressedTexImage1D(target, level, intFmt, w, b, size, data);
  checkError("glCompressedTexImage1D"); // May throw;
}

//! glCompressedTexSubImage1D wrapper. May throw.
inline void 
compressedTexSubImage1D(const GLenum target, 
                        const GLint level, 
                        const GLint x0,     
                        const GLsizei w, 
                        const GLenum fmt,    
                        const GLsizei size,
                        const GLvoid *data) {
  glCompressedTexSubImage1D(target, level, x0, w, fmt, size, data);
  checkError("glCompressedTexSubImage1D"); // May throw;
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
        const GLvoid *data);

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
           const GLvoid *data);

  void
  copySubImage(GLint level, GLint x0, GLint x, GLint y, GLsizei w);

  void 
  compressedImage(GLint level, 
                  GLenum intFmt, 
                  GLsizei w, 
                  GLint b, 
                  GLsizei size, 
                  const GLvoid *data);

  void 
  compressedSubImage(GLint level, 
                     GLint x0, 
                     GLsizei w, 
                     GLenum fmt, 
                     GLsizei size, 
                     const GLvoid *data);
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
  Bindor bind(this);
  detail::texImage1D(target(), level, intFmt, w, b, fmt, type, data);
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
  Bindor bind(this);
  detail::copyTexImage1D(target(), level, intFmt, x, y, w, b);
}

//! DOCS. May throw.
inline void 
Texture1D::subImage(const GLint level, 
                    const GLint x0, 
                    const GLsizei w, 
                    const GLenum fmt, 
                    const GLenum type, 
                    const GLvoid *data) {
  Bindor bind(this);
  detail::texSubImage1D(target(), level, x0, w, fmt, type, data);
}

//! DOCS. May throw.
inline void
Texture1D::copySubImage(const GLint level, 
                        const GLint x0, 
                        const GLint x, 
                        const GLint y, 
                        const GLsizei w) {
  Bindor bind(this);
  detail::copyTexSubImage1D(target(), level, x0, x, y, w);
}

//! DOCS. May throw.
inline void 
Texture1D::compressedImage(const GLint level,  
                           const GLenum intFmt, 
                           const GLsizei w,    
                           const GLint b, 
                           const GLsizei size, 
                           const GLvoid *data) {
  Bindor bind(this);
  detail::compressedTexImage1D(target(), level, intFmt, w, b, size, data);
}

//! DOCS. May throw.
inline void 
Texture1D::compressedSubImage(const GLint level, 
                              const GLint x0, 
                              const GLsizei w,     
                              const GLenum fmt, 
                              const GLsizei size,  
                              const GLvoid *data) {
  Bindor bind(this);
  detail::compressedTexSubImage1D(target(), level, x0, w, fmt, size, data);
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE1D_HPP_INCLUDED
