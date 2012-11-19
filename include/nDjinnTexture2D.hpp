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

} // Namespace: detail.

//------------------------------------------------------------------------------

//! 2D texture class.
class Texture2D : public Texture
{
public:

  //! Return currently bound 2D texture Id. 
  //! TODO: Slow to query OpenGL, should probably keep track 
  //!       of this ourselves.
  //static GLuint 
  //binding()
  //{
  //    GLint params = 0;
  //    state::get_integer(GL_TEXTURE_BINDING_2D, &params);
  //    return static_cast<GLuint>(params);
  //}

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
        const GLvoid *data);

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
           const GLvoid *data);

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
                  const GLvoid *data);

  void 
  compressedSubImage(GLint level, 
                     GLint x0, 
                     GLint y0, 
                     GLsizei w, 
                     GLsizei h, 
                     GLenum fmt, 
                     GLsizei size, 
                     const GLvoid *data);

private:

  Texture2D(const Texture2D&);              //!< Disabled copy.
  Texture2D& operator=(const Texture2D&);   //!< Disabled assign.
};

//------------------------------------------------------------------------------

//! CTOR.
inline
Texture2D::Texture2D(const GLenum target)
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
  Bindor bind(this);
  detail::texImage2D(target(), level, intFmt, w, h, b, fmt, type, data);
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
  Bindor bind(this);
  detail::copyTexImage2D(target(), level, intFmt, x, y, w, h, b);
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
  Bindor bind(this);
  detail::texSubImage2D(target(), level, x0, y0, w, h, fmt, type, data);
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
  Bindor bind(this);
  detail::copyTexSubImage2D(target(), level, x0, y0, x, y, w, h);
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
  Bindor bind(this);
  detail::compressedTexImage2D(target(), level, intFmt, w, h, b, size, data);
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
  Bindor bind(this);
  detail::compressedTexSubImage2D(target(), level, x0, y0, w, h, 
                                  fmt, size, data);
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE2D_HPP_INCLUDED
