//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_TEXTURE_HPP_INCLUDED
#define NDJ_TEXTURE_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
//#include "nDjinnState.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

//------------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE


//! DOCS
class Texture
{
public:

    //! Call glActiveTexture wrapper. May throw.
    //! GL_TEXTURE0, etc.
    static void
    activeTexture(const GLenum texture)
    { _activeTexture(texture); } // May throw.


public:    // Texture Queries.

    //! Call glIsTexture wrapper. May throw.
    static GLboolean 
    isTexture(const GLuint texture)
    { return _isTexture(texture); } // May throw.

protected:

    //! CTOR. May throw.
    explicit
    Texture(const GLenum target)
        : _target(target)
        , _handle(0)
    {
        try {
            _genTextures(1, &_handle);
            if (_handle == 0) {
                NDJINN_THROW("Invalid texture handle: " << _handle);
            }
        }
        catch (...) {
            _deleteTextures(1, &_handle);  // Clean up.
            throw;                         // Rethrow.
        }    
    }

    //! DTOR.
    ~Texture()
    {
        try {
            // TODO: release(); ?
            _deleteTextures(1, &_handle);  // May throw.
        }
        catch (...) {
        }    
    }

    //! Expose target.
    GLenum
    target() const
    { return _target; }

    //! Expose handle.
    GLuint
    handle() const
    { return _handle; }

protected:

    //! Bind this texture. May throw.
    // TODO: Check if this object is already bound?
    void
    bind()
    { _bindTexture(_target, _handle); } // May throw.

    //! Release this texture. May throw.
    void
    release()
    { _bindTexture(_target, 0); } // May throw.

protected:

    //! Copy image into main memory. May throw.
    void
    getImage(const GLint lod, const GLenum fmt, const GLenum type, GLvoid *img)
    {
        bind();                                     // May throw.
        _getTexImage(_target, lod, fmt, type, img); // May throw.
        release();                                  // May throw.
    }

    //! Copy compressed image into main memory. May throw.
    static void 
    getCompressedImage(const GLint lod, GLvoid *img)
    { 
        bind();                                    // May throw.
        _getCompressedTexImage(_target, lod, img); // May throw.
        release();                                 // May throw.
    } 

protected:  // Texture Parameters.

    //! Set texture integer parameter. May throw.
    void
    parameteri(const GLenum pname, const GLint param)
    {
        bind();                                // May throw.
        _texParameteri(_target, pname, param); // May throw.
        release();                             // May throw.
    }

    //! Set texture float parameter. May throw.
    void
    parameterf(const GLenum pname, const GLfloat param)
    {
        bind();                                // May throw.
        _texParameterf(_target, pname, param); // May throw.
        release();                             // May throw.
    }

    //! Set texture integer array parameter. May throw.
    void 
    parameteriv(const GLenum pname, const GLint *params)
    { 
        bind();                                  // May throw.
        _texParameteriv(_target, pname, params); // May throw.
        release();                               // May throw.
    } 

    //! Set texture float array parameter. May throw.
    void 
    parameterfv(const GLenum pname, const GLfloat *params)
    { 
        bind();                                  // May throw.
        _texParameterfv(_target, pname, params); // May throw.
        release();                               // May throw.
    } 

    //! DOCS. May throw.
    void 
    parameterIiv(const GLenum pname, const GLint *params)
    { 
        bind();                                   // May throw.
        _texParameterIiv(_target, pname, params); // May throw.
        release();                                // May throw.
    } 

    //! DOCS. May throw.
    void 
    parameterIuiv(const GLenum pname, const GLuint *params)
    { 
        bind();                                    // May throw.
        _texParameterIuiv(_target, pname, params); // May throw.
        release();                                 // May throw.      
    } 

protected:  // Enumerated queries.

    //! Get texture integer parameter. May throw.
    void 
    getParameteriv(const GLenum value, GLint *data)
    { 
        bind();                                   // May throw.
        _getTexParameteriv(_target, value, data); // May throw.
        release();                                // May throw.
    } 

    //! Get texture float parameter. May throw.
    void 
    getParameterfv(const GLenum value, GLfloat *data)
    { 
        bind();                                   // May throw.
        _getTexParameterfv(_target, value, data); // May throw.
        release();                                // May throw.
    } 

    //! DOCS. May throw.
    void 
    getParameterIiv(const GLenum value, GLint *data)
    { 
        bind();                                    // May throw.
        _getTexParameterIiv(_target, value, data); // May throw.
        release();                                 // May throw.
    } 

    //! DOCS. May throw.
    void 
    getParameterIuiv(const GLenum value, GLuint *data)
    { 
        bind();                                     // May throw.
        _getTexParameterIuiv(_target, value, data); // May throw.
        release();                                  // May throw.
    } 

    //! DOCS. May throw.
    void 
    getLevelParameteriv(const GLint lod, const GLenum value, GLint *data)
    { 
        bind();                                             // May throw.
        _getTexLevelParameteriv(_target, lod, value, data); // May throw.
        release();                                          // May throw.
    } 

    //! DOCS. May throw.
    void 
    getLevelParameterfv(const GLint lod, const GLenum value, GLfloat *data)
    { 
        bind();                                             // May throw.
        _getTexLevelParameterfv(_target, lod, value, data); // May throw.
        release();                                          // May throw.
    } 

private:

    Texture(const Texture&);              //!< Disabled copy.
    Texture& operator=(const Texture&);   //!< Disabled assign.

private:    // Misc.

    //! glActiveTexture wrapper. May throw.
    static void
    _activeTexture(const GLenum texture)
    {
        glActiveTexture(texture);
        Error::check(std::string("glActiveTexture")); // May throw.
    }

private:    // Texture Objects.

    //! glGenTextures wrapper. May throw.
    static void
    _genTextures(const GLsizei n, GLuint *textures)
    {
        glGenTextures(n, textures);
        Error::check(std::string("glGenTextures")); // May throw.
    }

    //! glDeleteTextures wrapper. May throw.
    static void
    _deleteTextures(const GLsizei n, const GLuint *textures)
    {
        glDeleteTextures(n, textures);
        Error::check(std::string("glDeleteTextures"));  // May throw.
    }

    //! glBindTexture wrapper. May throw.
    static void
    _bindTexture(const GLenum target, const GLuint texture)
    { 
        glBindTexture(target, texture);
        Error::check(std::string("glBindTexture"));  // May throw.
    }

private:    // Texture Parameters.

    //! glTexParameteri wrapper. May throw.
    static void 
    _texParameteri(const GLenum target, const GLenum pname, const GLint param)
    {
        glTexParameteri(target, pname, param);
        Error::check(std::string("glTexParameteri")); // May throw.
    }

    //! glTexParameterf wrapper. May throw.
    static void 
    _texParameterf(const GLenum target, const GLenum pname, const GLfloat param)
    {
        glTexParameterf(target, pname, param);
        Error::check(std::string("glTexParameterf")); // May throw.
    }

    //! glTexParameteriv wrapper. May throw.
    static void 
    _texParameteriv(const GLenum target, const GLenum pname,const GLint *params)
    {
        glTexParameteriv(target, pname, params);
        Error::check(std::string("glTexParameteriv")); // May throw.
    }

    //! glTexParameterfv wrapper. May throw.
    static void 
    _texParameterfv(const GLenum target, const GLenum pname, 
                    const GLfloat *params)
    {
        glTexParameterfv(target, pname, params);
        Error::check(std::string("glTexParameterfv")); // May throw.
    }

    //! glTexParameterIiv wrapper. May throw.
    static void 
    _texParameterIiv(const GLenum target,const GLenum pname,const GLint *params)
    {
        glTexParameterIiv(target, pname, params);
        Error::check(std::string("glTexParameterIiv")); // May throw.
    }

    //! glTexParameterIuiv wrapper. May throw.
    static void 
    _texParameterIuiv(const GLenum target, const GLenum pname, 
                      const GLuint *params)
    {
        glTexParameterIuiv(target, pname, params);
        Error::check(std::string("glTexParameterIuiv")); // May throw.
    }

private:    // Enumerated queries.

    //! glGetTexParameteriv wrapper. May throw.
    static void 
    _getTexParameteriv(const GLenum target, const GLenum value, GLint *data)
    {
        glGetTexParameteriv(target, value, data);
        Error::check(std::string("glGetTexParameteriv")); // May throw.
    }

    //! glGetTexParameterfv wrapper. May throw.
    static void 
    _getTexParameterfv(const GLenum target, const GLenum value, GLfloat *data)
    {
        glGetTexParameterfv(target, value, data);
        Error::check(std::string("glGetTexParameterfv")); // May throw.
    }

    //! glGetTexParameterIiv wrapper. May throw.
    static void 
    _getTexParameterIiv(const GLenum target, const GLenum value, GLint *data)
    {
        glGetTexParameterIiv(target, value, data);
        Error::check(std::string("glGetTexParameterIiv")); // May throw.
    }

    //! glGetTexParameterIuiv wrapper. May throw.
    static void 
    _getTexParameterIuiv(const GLenum target, const GLenum value, GLuint *data)
    {
        glGetTexParameterIuiv(target, value, data);
        Error::check(std::string("glGetTexParameterIuiv")); // May throw.
    }

    //! glGetTexLevelParameteriv wrapper. May throw.
    static void 
    _getTexLevelParameteriv(const GLenum target, const GLint lod, 
                            const GLenum value, GLint *data)
    {
        glGetTexLevelParameteriv(target, lod, value, data);
        Error::check(std::string("glGetTexLevelParameteriv")); // May throw.
    }

    //! glGetTexLevelParameterfv wrapper. May throw.
    static void 
    _getTexLevelParameterfv(const GLenum target, const GLint lod, 
                            const GLenum value, GLfloat *data)
    {
        glGetTexLevelParameterfv(target, lod, value, data);
        Error::check(std::string("glGetTexLevelParameterfv")); // May throw.
    }

private:    // Texture Queries.

    //! glGetTexImage wrapper. May throw.
    static void
    _getTexImage(const GLenum tex, const GLint lod, const GLenum fmt, 
                 const GLenum type, GLvoid *img)
    {
        glGetTexImage(tex, lod, fmt, type, img);
        Error::check(std::string("glGetTexImage")); // May throw.
    }

    //! glGetCompressedTexImage wrapper. May throw.
    static void 
    _getCompressedTexImage(const GLenum target, const GLint lod, GLvoid *img)
    {
        glGetCompressedTexImage(target, lod, img);
        Error::check(std::string("glGetCompressedTexImage")); // May throw. 
    }

    //! glIsTexture wrapper. May throw.
    static GLboolean 
    _isTexture(const GLuint texture)
    {
        const GLboolean result = glIsTexture(texture);
        Error::check(std::string("glIsTexture"));   // May throw.
        return result;
    }

private:    // Member variables.

    GLuint _handle;     //!< Resource handle.
    GLenum _target;
};

//------------------------------------------------------------------------------

//! 1D texture class.
class Texture1D : public Texture
{
public:

    //! CTOR. May throw.
    Texture1D(const GLenum target = GL_TEXTURE_1D)
        : Texture(target) // May throw.
    {}

    //! DTOR.
    ~Texture1D()
    {}

public:     // 1D specific functions.
    
    //! Set texture data.
    void
    image(const GLint level, const GLint intFmt, const GLsizei w, const GLint b,       
          const GLenum fmt, const GLenum type, const GLvoid *data)
    {
        bind();                                          // May throw.
        _texImage1D(target(), level, intFmt, w, b, fmt, type, data);//May throw.
        release();                                       // May throw.
    }

    //! "glCopyTexImage1D defines a one-dimensional texture image with 
    //! pixels from the current GL_READ_BUFFER."
    void
    copyImage(const GLint level, const GLenum intFmt, 
              const GLint x, const GLint y, const GLsizei w, const GLint b)
    {
        bind();                                               // May throw.
        _copyTexImage1D(target(), level, intFmt, x, y, w, b); // May throw.
        release();                                            // May throw.
    }

    //! DOCS. May throw.
    void 
    subImage(const GLint level, const GLint x0, const GLsizei w, 
             const GLenum fmt, const GLenum type, const GLvoid *data)
    {
        bind();
        _texSubImage1D(target(), level, x0, w, fmt, type, data);
        release();
    }

    //! DOCS. May throw.
    void
    copySubImage(const GLint level, const GLint x0, 
                 const GLint x, const GLint y, const GLsizei w)
    {
        bind();
        _copyTexSubImage1D(target(), level, x0, x, y, w);
        release();
    }

    //! DOCS. May throw.
    void 
    compressedImage(const GLint level, const GLenum intFmt, const GLsizei w, 
                    const GLint b, const GLsizei size, const GLvoid *data)
    {
        bind();
        _compressedTexImage1D(target(), level, intFmt, w, b, size, data);
        release();
    }

    //! DOCS. May throw.
    void 
    compressedSubImage(const GLint level, const GLint x0, const GLsizei w, 
                       const GLenum fmt, const GLsizei size, const GLvoid *data)
    {
        bind();
        _compressedTexSubImage1D(target(), level, x0, w, fmt, size, data);
        release();
    }

private:    // 1D specific wrappers.

    //! glTexImage1D wrapper. May throw.
    static void
    _texImage1D(const GLenum target, const GLint level, const GLint intFmt, 
                const GLsizei w, const GLint b, const GLenum fmt, 
                const GLenum type, const GLvoid *data)
    {
        glTexImage1D(target, level, intFmt, w, b, fmt, type, data);     
        Error::check("glTexImage1D"); // May throw;
    }

    //! glCopyTexImage1D wrapper. May throw.
    static void
    _copyTexImage1D(const GLenum target, const GLint level, const GLenum intFmt, 
                    const GLint x, const GLint y, 
                    const GLsizei w, const GLint b)
    {
        glCopyTexImage1D(target, level, intFmt, x, y, w, b);
        Error::check("glCopyTexImage1D"); // May throw;
    }

    //! glTexSubImage1D wrapper. May throw.
    static void 
    _texSubImage1D(const GLenum target, const GLint level, const GLint x0, 
                   const GLsizei w, const GLenum fmt, const GLenum type, 
                   const GLvoid *data)
    {
        glTexSubImage1D(target, level, x0, w, fmt, type, data);
        Error::check("glTexSubImage1D"); // May throw;
    }

    //! glCopyTexSubImage1D wrapper. May throw.
    static void
    _copyTexSubImage1D(const GLenum target, const GLint level, 
                       const GLint x0, const GLint x, const GLint y, 
                       const GLsizei w)
    {
        glCopyTexSubImage1D(target, level, x0, x, y, w);
        Error::check("glCopyTexImage1D"); // May throw;
    }

    //! glCompressedTexImage1D wrapper. May throw.
    static void 
    _compressedTexImage1D(const GLenum target, const GLint level, 
                          const GLenum intFmt, const GLsizei w, const GLint b, 
                          const GLsizei size, const GLvoid *data)
    {
        glCompressedTexImage1D(target, level, intFmt, w, b, size, data);
        Error::check("glCompressedTexImage1D"); // May throw;
    }

    //! glCompressedTexSubImage1D wrapper. May throw.
    static void 
    _compressedTexSubImage1D(const GLenum target, const GLint level, 
                             const GLint x0, const GLsizei w, 
                             const GLenum fmt, const GLsizei size,
                             const GLvoid *data)
    {
        glCompressedTexSubImage1D(target, level, x0, w, fmt, size, data);
        Error::check("glCompressedTexSubImage1D"); // May throw;
    }

private:

    Texture1D(const Texture1D&);              //!< Disabled copy.
    Texture1D& operator=(const Texture1D&);   //!< Disabled assign.
};

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

    //! CTOR.
    explicit
    Texture2D(const GLenum target = GL_TEXTURE_RECTANGLE)
        : Texture(target) // May throw.
    {}

    //! DTOR.
    ~Texture2D()
    {}

public:     // 2D specific functions.

    //! Set texture data.
    void
    image(const GLint level, const GLint intFmt, const GLsizei w, 
          const GLsizei h, const GLint b, const GLenum fmt, const GLenum type, 
          const GLvoid *data)
    {
        bind();                                             // May throw.
        _texImage2D(target(), level, intFmt, w, h, b, fmt, type, data); // MT.
        release();                                          // May throw.
    }

    //! "glCopyTexImage2D defines a two-dimensional texture image with 
    //! pixels from the current GL_READ_BUFFER."
    void
    copyImage(const GLint level, const GLenum intFmt, 
              const GLint x, const GLint y, 
              const GLsizei w, const GLsizei h, const GLint b)
    {
        bind(); // May throw.
        _copyTexImage2D(target(), level, intFmt, x, y, w, h, b); // May throw.
        release(); // May throw.
    }

    //! DOCS. May throw.
    void 
    subImage(const GLint level, const GLint x0, const GLint y0, 
             const GLsizei w, const GLsizei h,  const GLenum fmt, 
             const GLenum type, const GLvoid *data)
    {
        bind(); // May throw.
        _texSubImage2D(target(), level, x0, y0, w, h, fmt, type, data); // MT.
        release(); // May throw.
    }

    //! DOCS. May throw.
    void
    copySubImage(const GLint level, const GLint x0, const GLint y0, 
                 const GLint x, const GLint y, const GLsizei w, const GLsizei h)
    {
        bind();
        _copyTexSubImage2D(target(), level, x0, y0, x, y, w, h);
        release();
    }

    //! DOCS. May throw.
    void 
    compressedImage(const GLint level, const GLenum intFmt, 
                    const GLsizei w, const GLsizei h, const GLint b, 
                    const GLsizei size, const GLvoid *data)
    {
        bind();
        _compressedTexImage2D(target(), level, intFmt, w, h, b, size, data);//MT
        release();
    }

    //! DOCS. May throw.
    void 
    compressedSubImage(const GLint level, const GLint x0, const GLint y0,
                       const GLsizei w, const GLsizei h, const GLenum fmt, 
                       const GLsizei size, const GLvoid *data)
    {
        bind();
        _compressedTexSubImage2D(target(), level, x0, y0, w,h, fmt, size, data);
        release();
    }

private:    // Texture Image Specification.

    //! glTexImage2D wrapper. May throw.
    static void
    _texImage2D(const GLenum target, const GLint level, const GLint intFmt, 
                const GLsizei w, const GLsizei h, const GLint border, 
                const GLenum fmt, const GLenum type, const GLvoid *data)
    {
        glTexImage2D(target, level, intFmt, w, h, b, fmt, type, data);     
        Error::check("glTexImage2D"); // May throw;
    }

private:    // Alternate Texture Image Specification.

    //! glCopyTexImage2D wrapper. May throw.
    static void
    _copyTexImage2D(const GLenum target, const GLint level, 
                    const GLenum intFmt, const GLint x, const GLint y, 
                    const GLsizei w, const GLsizei h, const GLint b)
    {
        glCopyTexImage2D(target, level, intfmt, x, y, w, h, b);
        Error::check("glCopyTexImage2D"); // May throw;
    }

    //! glTexSubImage2D wrapper. May throw.
    static void 
    _texSubImage2D(const GLenum target, const GLint level, const GLint x0, 
                   const GLint y0, const GLsizei w, const GLsizei h,
                   const GLenum fmt, const GLenum type, const GLvoid *data)
    {
        glTexSubImage2D(target, level, x0, y0, w, h, fmt, type, data);
        Error::check("glTexSubImage2D"); // May throw;
    }

    //! glCopyTexSubImage2D wrapper. May throw.
    static void
    _copyTexSubImage2D(const GLenum target, const GLint level, 
                       const GLint x0, const GLint y0, 
                       const GLint x, const GLint y, 
                       const GLsizei w, const GLsizei h)
    {
        glCopyTexSubImage2D(target, level, x0, y0, x, y, w, h);
        Error::check("glCopyTexSubImage2D"); // May throw;
    }

private:    // Compressed Texture Image.

    //! glCompressedTexImage2D wrapper. May throw.
    static void 
    _compressedTexImage2D(const GLenum target, const GLint level, 
                          const GLenum intFmt, const GLsizei w, const GLsizei h,
                          const GLint b, const GLsizei size, const GLvoid *data)
    {
        glCompressedTexImage2D(target, level, intFmt, w, h, b, size, data);
        Error::check("glCompressedTexImage2D"); // May throw;
    }

    //! glCompressedTexSubImage2D wrapper. May throw.
    static void 
    _compressedTexSubImage2D(const GLenum target, const GLint level, 
                             const GLint x0, const GLint y0,
                             const GLsizei w, const GLsizei h,
                             const GLenum fmt, const GLsizei size,
                             const GLvoid *data)
    {
        glCompressedTexSubImage2D(target,level,x0,y0,w,h,fmt,size,data);
        Error::check("glCompressedTexSubImage2D"); // May throw;
    }

private:

    Texture2D(const Texture2D&);              //!< Disabled copy.
    Texture2D& operator=(const Texture2D&);   //!< Disabled assign.
};

//------------------------------------------------------------------------------

//! 3D texture class.
class texture3D : public Texture
{
public:

    //! CTOR. May throw.
    Texture3D(const GLenum target = GL_TEXTURE_3D)
        : Texture(target) // May throw.
    {}

    //! DTOR.
    ~Texture3D()
    {}

public:     // 3D specific functions.

    //! DOCS. May throw.
    void
    image(const GLint level, const GLint intFmt, const GLsizei w, 
          const GLsizei h, const GLsizei d, const GLint b, const GLenum fmt, 
          const GLenum type, const GLvoid *data)
    {
        bind();
        _texImage3D(target(), level, intFmt, w, h, d, b, fmt, type, data);     
        release();
    }

    //! DOCS. May throw.
    void 
    subImage(const GLint level, const GLint x0, const GLint y0, const GLint z0,
             const GLsizei w, const GLsizei h, const GLsizei d,
             const GLenum fmt, const GLenum type, const GLvoid *data)
    {
        bind();
        _texSubImage3D(target(), level, x0, y0, z0, w, h, d, fmt, type, data);
        release();
    }
     
    //! DOCS. May throw.
    void
    copySubImage(const GLint level, const GLint x0, const GLint y0, 
                 const GLint z0, const GLint x, const GLint y,
                 const GLsizei w, const GLsizei h)
    {
        bind();
        _copyTexSubImage3D(target(), level, x0, y0, z0, x, y, w, h);
        release();
    }

    //! DOCS. May throw.
    void 
    compressedImage(const GLint level, const GLenum intFmt, const GLsizei w, 
                    const GLsizei h, const GLsizei d, const GLint b, 
                    const GLsizei size, const GLvoid *data)
    {
        bind();
        _compressedTexImage3D(target(), level, intFmt, w, h, d, b, size, data);
        release();
    }

    //! DOCS. May throw.
    void 
    compressedSubImage(const GLint level, const GLint x0, const GLint y0, 
                       const GLint z0, const GLsizei w, const GLsizei h, 
                       const GLsizei d, const GLenum fmt, const GLsizei size,
                       const GLvoid *data)
    {
        bind();
        _compressedTexSubImage3D(target(), level, x0, y0, z0, 
                                 w, h, d, fmt, size, data);
        release();
    }

private:    // Texture Image Specification.

    //! glTexImage3D wrapper. May throw.
    static void
    _texImage3D(const GLenum target, const GLint level, 
                const GLint intFmt, const GLsizei w, const GLsizei h, 
                const GLsizei d, const GLint b, const GLenum fmt, 
                const GLenum type, const GLvoid *data)
    {
        glTexImage3D(target, level, intFmt, w, h, d, b, fmt, type, data);     
        Error::check("glTexImage3D"); // May throw;
    }

private:    // Alternate Texture Image Specification.

    //! glCopyTexSubImage3D wrapper. May throw.
    static void 
    _texSubImage3D(const GLenum target, const GLint level, 
                   const GLint x0, const GLint y0, const GLint z0,
                   const GLsizei w, const GLsizei h, const GLsizei d,
                   const GLenum fmt, const GLenum type, const GLvoid *data)
    {
        glTexSubImage3D(target, level, x0, y0, z0, w, h, d, fmt, type, data);
        Error::check("glTexSubImage3D"); // May throw;
    }

    //! glCopyTexSubImage3D wrapper. May throw.
    static void
    _copyTexSubImage3D(const GLenum target, const GLint level, 
                       const GLint x0, const GLint y0, 
                       const GLint z0, const GLint x, const GLint y,
                       const GLsizei w, const GLsizei h)
    {
        glCopyTexSubImage3D(target, level, x0, y0, z0, x, y, w, h);
        Error::check("glCopyTexSubImage3D"); // May throw;
    }

private:    // Compressed Texture Image.

    //! glCompressedTexImage3D wrapper. May throw.
    static void 
    _compressedTexImage3D(const GLenum target, const GLint level, 
                          const GLenum intFmt, const GLsizei w, const GLsizei h, 
                          const GLsizei d, const GLint b, const GLsizei size,
                          const GLvoid *data)
    {
        glCompressedTexImage3D(target, level, intFmt, w, h, d, b, size, data);
        Error::check("glCompressedTexImage3D"); // May throw;
    }

    //! glCompressedTexSubImage3D wrapper. May throw.
    static void 
    _compressedTexSubImage3D(const GLenum target, const GLint level, 
                             const GLint x0, const GLint y0, const GLint z0,  
                             const GLsizei w, const GLsizei h, const GLsizei d,
                             const GLenum fmt, const GLsizei size,
                             const GLvoid *data)
    {
        glCompressedTexSubImage3D(target, level, x0, y0, z0, 
                                  w, h, d, fmt, size, data);
        Error::check("glCompressedTexSubImage3D"); // May throw;
    }

private:

    Texture3D(const Texture3D&);              //!< Disabled copy.
    Texture3D& operator=(const Texture3D&);   //!< Disabled assign.
};

END_NDJINN_NAMESPACE

//------------------------------------------------------------------------------

#endif  // NDJ_TEXTURE_HPP_INCLUDED
