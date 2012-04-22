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

BEGIN_NDJINN_NAMESPACE

//! 3D texture class.
class Texture3D : public Texture
{
public:

    explicit
    Texture3D(GLenum target = GL_TEXTURE_3D);

    ~Texture3D();

public:     // 3D specific functions.

    void
    image(GLint level, GLint intFmt, 
          GLsizei w, GLsizei h, GLsizei d, 
          GLint b, GLenum fmt, GLenum type, const GLvoid *data);

    void 
    subImage(GLint level, GLint x0, GLint y0, GLint z0,
             GLsizei w, GLsizei h, GLsizei d,
             GLenum fmt, GLenum type, const GLvoid *data);
     
    void
    copySubImage(GLint level, 
                 GLint x0, GLint y0, GLint z0, 
                 GLint x, GLint y,
                 GLsizei w, GLsizei h);

    void 
    compressedImage(GLint level, GLenum intFmt, 
                    GLsizei w, GLsizei h, GLsizei d, 
                    GLint b, GLsizei size, const GLvoid *data);

    void 
    compressedSubImage(GLint level, 
                       GLint x0, GLint y0, GLint z0, 
                       GLsizei w, GLsizei h, GLsizei d, 
                       GLenum fmt, GLsizei size, const GLvoid *data);

private:    // Texture Image Specification.

    static void
    _texImage3D(GLenum target, GLint level, GLint intFmt, 
                GLsizei w, GLsizei h, GLsizei d, 
                GLint b, GLenum fmt, GLenum type, const GLvoid *data);

private:    // Alternate Texture Image Specification.

    static void 
    _texSubImage3D(GLenum target, GLint level, 
                   GLint x0, GLint y0, GLint z0,
                   GLsizei w, GLsizei h, GLsizei d,
                   GLenum fmt, GLenum type, const GLvoid *data);

    static void
    _copyTexSubImage3D(GLenum target, GLint level, 
                       GLint x0, GLint y0, GLint z0, 
                       GLint x, GLint y, 
                       GLsizei w, GLsizei h);

private:    // Compressed Texture Image.

    static void 
    _compressedTexImage3D(GLenum target, GLint level, 
                          GLenum intFmt, GLsizei w, GLsizei h, 
                          GLsizei d, GLint b, 
                          GLsizei size, const GLvoid *data);

    static void 
    _compressedTexSubImage3D(GLenum target, GLint level, 
                             GLint x0, GLint y0, GLint z0,  
                             GLsizei w, GLsizei h, GLsizei d,
                             GLenum fmt, GLsizei size, const GLvoid *data);

private:

    Texture3D(const Texture3D&);              //!< Disabled copy.
    Texture3D& operator=(const Texture3D&);   //!< Disabled assign.
};

//------------------------------------------------------------------------------

//! CTOR. May throw.
inline
Texture3D::Texture3D(const GLenum target)
    : Texture(target) // May throw.
{}


//! DTOR.
inline
Texture3D::~Texture3D()
{}

//------------------------------------------------------------------------------

//! DOCS. May throw.
inline void
Texture3D::image(const GLint    level, const GLint   intFmt, 
                 const GLsizei  w,     const GLsizei h, 
                 const GLsizei  d,     const GLint   b, 
                 const GLenum   fmt,   const GLenum  type, 
                 const GLvoid  *data)
{
    Bindor b(this);
    _texImage3D(target(), level, intFmt, w, h, d, b, fmt, type, data);     
}


//! DOCS. May throw.
inline void 
Texture3D::subImage(const GLint   level, const GLint    x0, 
                    const GLint   y0,    const GLint    z0,
                    const GLsizei w,     const GLsizei  h, 
                    const GLsizei d,     const GLenum   fmt, 
                    const GLenum  type,  const GLvoid  *data)
{
    Bindor b(this);
    _texSubImage3D(target(), level, x0, y0, z0, w, h, d, fmt, type, data);
}
    

//! DOCS. May throw.
inline void
Texture3D::copySubImage(const GLint   level, const GLint   x0, 
                        const GLint   y0,    const GLint   z0, 
                        const GLint   x,     const GLint   y,
                        const GLsizei w,     const GLsizei h)
{
    Bindor b(this);
    _copyTexSubImage3D(target(), level, x0, y0, z0, x, y, w, h);
}


//! DOCS. May throw.
inline void 
Texture3D::compressedImage(const GLint   level, const GLenum intFmt, 
                           const GLsizei w,     const GLsizei h, 
                           const GLsizei d,     const GLint b, 
                           const GLsizei size,  const GLvoid *data)
{
    Bindor b(this);
    _compressedTexImage3D(target(), level, intFmt, w, h, d, b, size, data);
}


//! DOCS. May throw.
inline void 
Texture3D::compressedSubImage(const GLint   level, const GLint x0, 
                              const GLint   y0,    const GLint z0, 
                              const GLsizei w,     const GLsizei h, 
                              const GLsizei d,     const GLenum fmt, 
                              const GLsizei size,  const GLvoid *data)
{
    Bindor b(this);
    _compressedTexSubImage3D(target(), level, x0, y0, z0, 
                             w, h, d, fmt, size, data);
}

//------------------------------------------------------------------------------

//! glTexImage3D wrapper. May throw. [static]
inline void
Texture3D::_texImage3D(const GLenum  target, const GLint    level, 
                       const GLint   intFmt, const GLsizei  w, 
                       const GLsizei h,      const GLsizei  d, 
                       const GLint   b,      const GLenum   fmt, 
                       const GLenum  type,   const GLvoid  *data)
{
    glTexImage3D(target, level, intFmt, w, h, d, b, fmt, type, data);     
    Error::check("glTexImage3D"); // May throw;
}

//------------------------------------------------------------------------------

//! glCopyTexSubImage3D wrapper. May throw. [static]
inline void 
Texture3D::_texSubImage3D(const GLenum   target, const GLint   level, 
                          const GLint    x0,     const GLint   y0, 
                          const GLint    z0,     const GLsizei w, 
                          const GLsizei  h,      const GLsizei d,
                          const GLenum   fmt,    const GLenum  type, 
                          const GLvoid  *data)
{
    glTexSubImage3D(target, level, x0, y0, z0, w, h, d, fmt, type, data);
    Error::check("glTexSubImage3D"); // May throw;
}


//! glCopyTexSubImage3D wrapper. May throw. [static]
inline void
Texture3D::_copyTexSubImage3D(const GLenum  target, const GLint   level, 
                              const GLint   x0,     const GLint   y0, 
                              const GLint   z0,     const GLint   x, 
                              const GLint   y,      const GLsizei w, 
                              const GLsizei h)
{
    glCopyTexSubImage3D(target, level, x0, y0, z0, x, y, w, h);
    Error::check("glCopyTexSubImage3D"); // May throw;
}

//------------------------------------------------------------------------------

//! glCompressedTexImage3D wrapper. May throw. [static]
inline void 
Texture3D::_compressedTexImage3D(const GLenum  target, const GLint   level, 
                                 const GLenum  intFmt, const GLsizei w, 
                                 const GLsizei h,      const GLsizei d, 
                                 const GLint   b,      const GLsizei size,
                                 const GLvoid *data)
{
    glCompressedTexImage3D(target, level, intFmt, w, h, d, b, size, data);
    Error::check("glCompressedTexImage3D"); // May throw;
}


//! glCompressedTexSubImage3D wrapper. May throw. [static]
inline void 
Texture3D::_compressedTexSubImage3D(const GLenum   target, const GLint   level, 
                                    const GLint    x0,     const GLint   y0, 
                                    const GLint    z0,     const GLsizei w, 
                                    const GLsizei  h,      const GLsizei d,
                                    const GLenum   fmt,    const GLsizei size,
                                    const GLvoid  *data)
{
    glCompressedTexSubImage3D(target, level, x0, y0, z0, 
                                w, h, d, fmt, size, data);
    Error::check("glCompressedTexSubImage3D"); // May throw;
}

END_NDJINN_NAMESPACE

//------------------------------------------------------------------------------

#endif  // NDJINN_TEXTURE3D_HPP_INCLUDED
