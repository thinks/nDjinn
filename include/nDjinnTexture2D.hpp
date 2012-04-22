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

BEGIN_NDJINN_NAMESPACE

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

    explicit
    Texture2D(GLenum target = GL_TEXTURE_RECTANGLE/*GL_TEXTURE_2D , RECTANGLE*/);

    ~Texture2D();

public:     // 2D specific functions.

    void
    image(GLint level, GLint intFmt, 
          GLsizei w, GLsizei h, GLint b, 
          GLenum fmt, GLenum type, const GLvoid *data);

    void
    copyImage(GLint level, GLenum intFmt, 
              GLint x, GLint y, GLsizei w, GLsizei h, GLint b);

    void 
    subImage(GLint level, GLint x0, GLint y0, GLsizei w, GLsizei h,  
             GLenum fmt, GLenum type, const GLvoid *data);

    void
    copySubImage(GLint level, GLint x0, GLint y0, GLint x, GLint y, 
                 GLsizei w, GLsizei h);

    void 
    compressedImage(GLint level, GLenum intFmt, 
                    GLsizei w, GLsizei h, GLint b, 
                    GLsizei size, const GLvoid *data);

    void 
    compressedSubImage(GLint level, GLint x0, GLint y0, GLsizei w, GLsizei h, 
                       GLenum fmt, GLsizei size, const GLvoid *data);

private:    // Texture Image Specification.

    static void
    _texImage2D(GLenum target, GLint level, GLint intFmt, GLsizei w, GLsizei h, 
                GLint border, GLenum fmt, GLenum type, const GLvoid *data);

private:    // Alternate Texture Image Specification.

    static void
    _copyTexImage2D(GLenum target, GLint level, 
                    GLenum intFmt, GLint x, GLint y, 
                    GLsizei w, GLsizei h, GLint b);

    static void 
    _texSubImage2D(GLenum target, GLint level, GLint x0, GLint y0, GLsizei w, 
                   GLsizei h, GLenum fmt, GLenum type, const GLvoid *data);

    static void
    _copyTexSubImage2D(GLenum target, GLint level, GLint x0, GLint y0, GLint x, 
                       GLint y, GLsizei w, GLsizei h);

private:    // Compressed Texture Image.

    static void 
    _compressedTexImage2D(GLenum target, GLint level, GLenum intFmt, 
                          GLsizei w, GLsizei h, GLint b, GLsizei size, 
                          const GLvoid *data);

    static void 
    _compressedTexSubImage2D(GLenum target, GLint level,  GLint x0, GLint y0,
                             GLsizei w, GLsizei h, GLenum fmt, GLsizei size,
                             const GLvoid *data);

private:

    Texture2D(const Texture2D&);              //!< Disabled copy.
    Texture2D& operator=(const Texture2D&);   //!< Disabled assign.
};

//------------------------------------------------------------------------------

//! CTOR.
inline
Texture2D::Texture2D(const GLenum target)
    : Texture(target) // May throw.
{}


//! DTOR.
inline
Texture2D::~Texture2D()
{}

//------------------------------------------------------------------------------

//! Set texture data.
void
Texture2D::image(const GLint level, const GLint intFmt, const GLsizei w, 
                 const GLsizei h,   const GLint b,      const GLenum fmt, 
                 const GLenum type, const GLvoid *data)
{
    Bindor bind(this);
    _texImage2D(target(), level, intFmt, w, h, b, fmt, type, data); // MT.
}


//! "glCopyTexImage2D defines a two-dimensional texture image with 
//! pixels from the current GL_READ_BUFFER."
void
Texture2D::copyImage(const GLint level, const GLenum intFmt, 
                     const GLint x,     const GLint y, const GLsizei w,   
                     const GLsizei h,   const GLint b)
{
    Bindor bind(this);
    _copyTexImage2D(target(), level, intFmt, x, y, w, h, b); // May throw.
}


//! DOCS. May throw.
void 
Texture2D::subImage(const GLint level, const GLint x0,   const GLint y0, 
                    const GLsizei w,   const GLsizei h,  const GLenum fmt, 
                    const GLenum type, const GLvoid *data)
{
    Bindor bind(this);
    _texSubImage2D(target(), level, x0, y0, w, h, fmt, type, data); // MT.
}


//! DOCS. May throw.
void
Texture2D::copySubImage(const GLint   level, const GLint x0, 
                        const GLint   y0,    const GLint x, 
                        const GLint   y,     const GLsizei w, 
                        const GLsizei h)
{
    Bindor bind(this);
    _copyTexSubImage2D(target(), level, x0, y0, x, y, w, h);
}


//! DOCS. May throw.
void 
Texture2D::compressedImage(const GLint   level, const GLenum intFmt, 
                           const GLsizei w,     const GLsizei h, 
                           const GLint   b,     const GLsizei size, 
                           const GLvoid *data)
{
    Bindor bind(this);
    _compressedTexImage2D(target(), level, intFmt, w, h, b, size, data);//MT
}


//! DOCS. May throw.
void 
Texture2D::compressedSubImage(const GLint   level, const GLint   x0, 
                              const GLint   y0,    const GLsizei w,     
                              const GLsizei h,     const GLenum  fmt, 
                              const GLsizei size,  const GLvoid *data)
{
    Bindor bind(this);
    _compressedTexSubImage2D(target(), level, x0, y0, w,h, fmt, size, data);
}

//------------------------------------------------------------------------------

//! glTexImage2D wrapper. May throw. [static]
inline void
Texture2D::_texImage2D(const GLenum  target, const GLint level, 
                       const GLint   intFmt, const GLsizei w,     
                       const GLsizei h,      const GLint b, 
                       const GLenum  fmt,    const GLenum type, 
                       const GLvoid *data)
{
    glTexImage2D(target, level, intFmt, w, h, b, fmt, type, data);     
    Error::check("glTexImage2D"); // May throw;
}

//------------------------------------------------------------------------------

//! glCopyTexImage2D wrapper. May throw. [static]
inline void
Texture2D::_copyTexImage2D(const GLenum  target, const GLint level, 
                           const GLenum  intFmt, const GLint x, 
                           const GLint y,        const GLsizei w,      
                           const GLsizei h,      const GLint b)
{
    glCopyTexImage2D(target, level, intFmt, x, y, w, h, b);
    Error::check("glCopyTexImage2D"); // May throw;
}


//! glTexSubImage2D wrapper. May throw. [static]
inline void 
Texture2D::_texSubImage2D(const GLenum  target, const GLint   level, 
                          const GLint   x0,     const GLint   y0, 
                          const GLsizei w,      const GLsizei h,
                          const GLenum  fmt,    const GLenum  type, 
                          const GLvoid *data)
{
    glTexSubImage2D(target, level, x0, y0, w, h, fmt, type, data);
    Error::check("glTexSubImage2D"); // May throw;
}


//! glCopyTexSubImage2D wrapper. May throw. [static]
inline void
Texture2D::_copyTexSubImage2D(const GLenum  target, const GLint   level, 
                              const GLint   x0,     const GLint   y0, 
                              const GLint   x,      const GLint   y, 
                              const GLsizei w,      const GLsizei h)
{
    glCopyTexSubImage2D(target, level, x0, y0, x, y, w, h);
    Error::check("glCopyTexSubImage2D"); // May throw;
}

//------------------------------------------------------------------------------

//! glCompressedTexImage2D wrapper. May throw. [static]
inline void 
Texture2D::_compressedTexImage2D(const GLenum target, const GLint level, 
                                 const GLenum intFmt, const GLsizei w, 
                                 const GLsizei h,     const GLint b, 
                                 const GLsizei size,  const GLvoid *data)
{
    glCompressedTexImage2D(target, level, intFmt, w, h, b, size, data);
    Error::check("glCompressedTexImage2D"); // May throw;
}


//! glCompressedTexSubImage2D wrapper. May throw. [static]
inline void 
Texture2D::_compressedTexSubImage2D(const GLenum  target, const GLint level, 
                                    const GLint   x0,     const GLint y0,
                                    const GLsizei w,      const GLsizei h,
                                    const GLenum  fmt,    const GLsizei size,
                                    const GLvoid *data)
{
    glCompressedTexSubImage2D(target,level,x0,y0,w,h,fmt,size,data);
    Error::check("glCompressedTexSubImage2D"); // May throw;
}

END_NDJINN_NAMESPACE

//------------------------------------------------------------------------------

#endif  // NDJINN_TEXTURE2D_HPP_INCLUDED
