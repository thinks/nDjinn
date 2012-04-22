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

BEGIN_NDJINN_NAMESPACE

//! 1D texture class.
class Texture1D : public Texture
{
public:

    explicit
    Texture1D(GLenum target = GL_TEXTURE_1D);

    ~Texture1D();

public:     // 1D specific functions.
    
    void
    image(GLint level, GLint intFmt, GLsizei w, GLint b, GLenum fmt, 
          GLenum type, const GLvoid *data);

    void
    copyImage(GLint level, GLenum intFmt, GLint x, GLint y, 
              GLsizei w, GLint b);

    void 
    subImage(GLint level, GLint x0, GLsizei w, GLenum fmt, GLenum type, 
             const GLvoid *data);

    void
    copySubImage(GLint level, GLint x0, GLint x, GLint y, GLsizei w);

    void 
    compressedImage(GLint level, GLenum intFmt, GLsizei w, GLint b, 
                    GLsizei size, const GLvoid *data);

    void 
    compressedSubImage(GLint level, GLint x0, GLsizei w, GLenum fmt, 
                       GLsizei size, const GLvoid *data);

private:    // 1D specific wrappers.

    static void
    _texImage1D(GLenum target, GLint level, GLint intFmt,  GLsizei w, GLint b, 
                GLenum fmt, GLenum type, const GLvoid *data);

    static void
    _copyTexImage1D(GLenum target, GLint level, GLenum intFmt, 
                    GLint x, GLint y, GLsizei w, GLint b);

    static void 
    _texSubImage1D(GLenum target, GLint level, GLint x0, GLsizei w, 
                   GLenum fmt, GLenum type, const GLvoid *data);

    static void
    _copyTexSubImage1D(GLenum target, GLint level, GLint x0, 
                       GLint x, GLint y, GLsizei w);
    static void 
    _compressedTexImage1D(GLenum target, GLint level, GLenum intFmt, GLsizei w, 
                          GLint b, GLsizei size, const GLvoid *data);

    static void 
    _compressedTexSubImage1D(GLenum target, GLint level, GLint x0, GLsizei w, 
                             GLenum fmt, GLsizei size, const GLvoid *data);

private:

    Texture1D(const Texture1D&);              //!< Disabled copy.
    Texture1D& operator=(const Texture1D&);   //!< Disabled assign.
};

//------------------------------------------------------------------------------

//! CTOR. May throw.
inline
Texture1D::Texture1D(const GLenum target)
    : Texture(target) // May throw.
{}


//! DTOR.
inline
Texture1D::~Texture1D()
{}

//------------------------------------------------------------------------------

//! Set texture data.
inline void
Texture1D::image(const GLint level, const GLint intFmt, const GLsizei w, 
                 const GLint b, const GLenum fmt, const GLenum type, 
                 const GLvoid *data)
{
    Bindor b(this);
    _texImage1D(target(), level, intFmt, w, b, fmt, type, data);//May throw.
}


//! "glCopyTexImage1D defines a one-dimensional texture image with 
//! pixels from the current GL_READ_BUFFER."
inline void
Texture1D::copyImage(const GLint level, const GLenum intFmt, const GLint x, 
                     const GLint y, const GLsizei w, const GLint b)
{
    Bindor b(this);
    _copyTexImage1D(target(), level, intFmt, x, y, w, b); // May throw.
}


//! DOCS. May throw.
inline void 
Texture1D::subImage(const GLint level, const GLint x0, const GLsizei w, 
                    const GLenum fmt, const GLenum type, const GLvoid *data)
{
    Bindor b(this);
    _texSubImage1D(target(), level, x0, w, fmt, type, data);
}


//! DOCS. May throw.
inline void
Texture1D::copySubImage(const GLint level, const GLint x0, const GLint x, 
                        const GLint y, const GLsizei w)
{
    Bindor b(this);
    _copyTexSubImage1D(target(), level, x0, x, y, w);
}


//! DOCS. May throw.
inline void 
Texture1D::compressedImage(const GLint level,  const GLenum  intFmt, 
                           const GLsizei w,    const GLint   b, 
                           const GLsizei size, const GLvoid *data)
{
    Bindor b(this);
    _compressedTexImage1D(target(), level, intFmt, w, b, size, data);
}


//! DOCS. May throw.
inline void 
Texture1D::compressedSubImage(const GLint   level, const GLint x0, 
                              const GLsizei w,     const GLenum fmt, 
                              const GLsizei size,  const GLvoid *data)
{
    Bindor b(this);
    _compressedTexSubImage1D(target(), level, x0, w, fmt, size, data);
}

//------------------------------------------------------------------------------

//! glTexImage1D wrapper. May throw. [static]
inline void
Texture1D::_texImage1D(const GLenum target, const GLint   level, 
                       const GLint  intFmt, const GLsizei w, 
                       const GLint  b,      const GLenum  fmt, 
                       const GLenum type,   const GLvoid *data)
{
    glTexImage1D(target, level, intFmt, w, b, fmt, type, data);     
    Error::check("glTexImage1D"); // May throw;
}


//! glCopyTexImage1D wrapper. May throw. [static]
inline void
Texture1D::_copyTexImage1D(const GLenum  target, const GLint level, 
                           const GLenum  intFmt, const GLint x, const GLint y, 
                           const GLsizei w,      const GLint b)
{
    glCopyTexImage1D(target, level, intFmt, x, y, w, b);
    Error::check("glCopyTexImage1D"); // May throw;
}


//! glTexSubImage1D wrapper. May throw. [static]
inline void 
Texture1D::_texSubImage1D(const GLenum  target, const GLint level, 
                          const GLint   x0,     const GLsizei w, 
                          const GLenum  fmt,    const GLenum type, 
                          const GLvoid *data)
{
    glTexSubImage1D(target, level, x0, w, fmt, type, data);
    Error::check("glTexSubImage1D"); // May throw;
}


//! glCopyTexSubImage1D wrapper. May throw. [static]
inline void
Texture1D::_copyTexSubImage1D(const GLenum target, const GLint level, 
                              const GLint  x0,     const GLint x, 
                              const GLint y,       const GLsizei w)
{
    glCopyTexSubImage1D(target, level, x0, x, y, w);
    Error::check("glCopyTexImage1D"); // May throw;
}


//! glCompressedTexImage1D wrapper. May throw. [static]
inline void 
Texture1D::_compressedTexImage1D(const GLenum  target, const GLint   level, 
                                 const GLenum  intFmt, const GLsizei w, 
                                 const GLint   b,      const GLsizei size, 
                                 const GLvoid *data)
{
    glCompressedTexImage1D(target, level, intFmt, w, b, size, data);
    Error::check("glCompressedTexImage1D"); // May throw;
}


//! glCompressedTexSubImage1D wrapper. May throw. [static]
static void 
Texture1D::_compressedTexSubImage1D(const GLenum  target, const GLint   level, 
                                    const GLint   x0,     const GLsizei w, 
                                    const GLenum  fmt,    const GLsizei size,
                                    const GLvoid *data)
{
    glCompressedTexSubImage1D(target, level, x0, w, fmt, size, data);
    Error::check("glCompressedTexSubImage1D"); // May throw;
}

END_NDJINN_NAMESPACE

//------------------------------------------------------------------------------

#endif  // NDJINN_TEXTURE1D_HPP_INCLUDED
