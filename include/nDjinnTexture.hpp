//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_TEXTURE_HPP_INCLUDED
#define NDJINN_TEXTURE_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
//#include "nDjinnState.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

//------------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

//! Texture base class. NB: DTOR is not virtual.
class Texture
{
public:

    GLenum
    target() const;

    GLuint
    handle() const;

    void
    bind();

    void
    release();

    static void
    activeTexture(GLenum texture);

    static GLboolean 
    isTexture(GLuint texture);

public:  // Texture Queries.

    void
    getImage(GLint lod, GLenum fmt, GLenum type, GLvoid *img);

    void 
    getCompressedImage(GLint lod, GLvoid *img);

public:  // Texture Parameters.

    void
    parameteri(GLenum pname, GLint param);

    void
    parameterf(GLenum pname, GLfloat param);

    void 
    parameteriv(GLenum pname, const GLint *params);

    void 
    parameterfv(GLenum pname, const GLfloat *params);

    void 
    parameterIiv(GLenum pname, const GLint *params);

    void 
    parameterIuiv(GLenum pname, const GLuint *params);

public:  // Enumerated queries.

    void 
    getParameteriv(GLenum value, GLint *data);

    void 
    getParameterfv(GLenum value, GLfloat *data);

    void 
    getParameterIiv(GLenum value, GLint *data);

    void 
    getParameterIuiv(GLenum value, GLuint *data);

    void 
    getLevelParameteriv(GLint lod, const GLenum value, GLint *data);

    void 
    getLevelParameterfv(GLint lod, const GLenum value, GLfloat *data);

protected:

    explicit
    Texture(GLenum target);

    ~Texture();

    //! DOCS
    class Bindor
    {
    public:

        //! CTOR.
        explicit
        Bindor(Texture *tex) 
            : _tex(tex) 
        { _tex->bind(); }   

        //! DTOR.
        ~Bindor() 
        { 
            try { _tex->release(); } 
            catch (...) {} 
        } 

    private:    // Member variables.

        Texture *_tex;
    };

private:    // Texture Objects.

    static void 
    _activeTexture(GLenum texture);

    static GLboolean 
    _isTexture(GLuint texture);

    static void
    _genTextures(GLsizei n, GLuint *textures);

    static void
    _deleteTextures(GLsizei n, const GLuint *textures);

    static void
    _bindTexture(GLenum target, GLuint texture);

private:    // Texture Parameters.

    static void 
    _texParameteri(GLenum target, GLenum pname, GLint param);

    static void 
    _texParameterf(GLenum target, GLenum pname, GLfloat param);

    static void 
    _texParameteriv(GLenum target, GLenum pname, const GLint *params);

    static void 
    _texParameterfv(GLenum target, GLenum pname, const GLfloat *params);

    static void 
    _texParameterIiv(GLenum target, GLenum pname, const GLint *params);

    static void 
    _texParameterIuiv(GLenum target, GLenum pname, const GLuint *params);

private:    // Enumerated queries.

    static void 
    _getTexParameteriv(GLenum target, GLenum value, GLint *data);

    static void 
    _getTexParameterfv(GLenum target, GLenum value, GLfloat *data);

    static void 
    _getTexParameterIiv(GLenum target, GLenum value, GLint *data);

    static void 
    _getTexParameterIuiv(GLenum target, GLenum value, GLuint *data);

    static void 
    _getTexLevelParameteriv(GLenum target, GLint lod, 
                            GLenum value, GLint *data);

    static void 
    _getTexLevelParameterfv(GLenum target, GLint lod, 
                            GLenum value, GLfloat *data);

private:    // Texture Queries.

    static void
    _getTexImage(GLenum tex, GLint lod, GLenum fmt, GLenum type, GLvoid *img);

    static void 
    _getCompressedTexImage(GLenum target, GLint lod, GLvoid *img);

private:

    Texture(const Texture&);            //!< Disabled copy.
    Texture& operator=(const Texture&); //!< Disabled assign.

private:    // Member variables.

    GLuint _handle; //!< Resource handle.
    GLenum _target;
};

//------------------------------------------------------------------------------

//! CTOR. May throw.
inline
Texture::Texture(const GLenum target)
    : _target(target)
    , _handle(0)
{
    try {
        _genTextures(1, &_handle);
        if (_handle == 0) {
            NDJINN_THROW("Null texture handle");
        }
    }
    catch (...) {
        _deleteTextures(1, &_handle);  // Clean up.
        throw;                         // Rethrow.
    }    
}


//! DTOR.
inline
Texture::~Texture()
{
    // TODO: release(); ?
    try { _deleteTextures(1, &_handle); }
    catch (...) {}    
}


//! Expose target.
inline GLenum
Texture::target() const
{ 
    return _target; 
}


//! Expose handle.
inline GLuint
Texture::handle() const
{ 
    return _handle; 
}


//! Bind this texture. May throw.
// TODO: Check if this object is already bound?
inline void
Texture::bind()
{ 
    _bindTexture(_target, _handle); // May throw.
} 


//! Release this texture. May throw.
inline void
Texture::release()
{ 
    _bindTexture(_target, 0); // May throw.
} 


//! DOCS. May throw. [static]
inline void
Texture::activeTexture(const GLenum texture)
{
    return _activeTexture(texture);
}


//! DOCS. May throw. [static]
inline GLboolean
Texture::isTexture(const GLenum texture)
{
    return _isTexture(texture);
}

//------------------------------------------------------------------------------

//! Copy image into main memory. May throw.
inline void
Texture::getImage(const GLint   lod, 
                  const GLenum  fmt, 
                  const GLenum  type, 
                  GLvoid       *img)
{
    Bindor b(this);
    _getTexImage(_target, lod, fmt, type, img); // May throw.
}


//! Copy compressed image into main memory. May throw.
inline void 
Texture::getCompressedImage(const GLint lod, GLvoid *img)
{ 
    Bindor b(this);
    _getCompressedTexImage(_target, lod, img); // May throw.
}

//------------------------------------------------------------------------------

//! Set texture integer parameter. May throw.
inline void
Texture::parameteri(const GLenum pname, const GLint param)
{
    Bindor b(this);
    _texParameteri(_target, pname, param); // May throw.
}


//! Set texture float parameter. May throw.
inline void
Texture::parameterf(const GLenum pname, const GLfloat param)
{
    Bindor b(this);
    _texParameterf(_target, pname, param); // May throw.
}


//! Set texture integer array parameter. May throw.
inline void 
Texture::parameteriv(const GLenum pname, const GLint *params)
{ 
    Bindor b(this);
    _texParameteriv(_target, pname, params); // May throw.
} 


//! Set texture float array parameter. May throw.
inline void 
Texture::parameterfv(const GLenum pname, const GLfloat *params)
{ 
    Bindor b(this);
    _texParameterfv(_target, pname, params); // May throw.
} 


//! DOCS. May throw.
inline void 
Texture::parameterIiv(const GLenum pname, const GLint *params)
{ 
    Bindor b(this);
    _texParameterIiv(_target, pname, params); // May throw.
} 


//! DOCS. May throw.
inline void 
Texture::parameterIuiv(const GLenum pname, const GLuint *params)
{ 
    Bindor b(this);
    _texParameterIuiv(_target, pname, params); // May throw.
} 

//------------------------------------------------------------------------------

//! Get texture integer parameter. May throw.
inline void 
Texture::getParameteriv(const GLenum value, GLint *data)
{ 
    Bindor b(this);
    _getTexParameteriv(_target, value, data); // May throw.
} 


//! Get texture float parameter. May throw.
inline void 
Texture::getParameterfv(const GLenum value, GLfloat *data)
{ 
    Bindor b(this);
    _getTexParameterfv(_target, value, data); // May throw.
} 


//! DOCS. May throw.
inline void 
Texture::getParameterIiv(const GLenum value, GLint *data)
{ 
    Bindor b(this);
    _getTexParameterIiv(_target, value, data); // May throw.
} 


//! DOCS. May throw.
inline void 
Texture::getParameterIuiv(const GLenum value, GLuint *data)
{ 
    Bindor b(this);
    _getTexParameterIuiv(_target, value, data); // May throw.
} 


//! DOCS. May throw.
inline void 
Texture::getLevelParameteriv(const GLint lod, const GLenum value, GLint *data)
{ 
    Bindor b(this);
    _getTexLevelParameteriv(_target, lod, value, data); // May throw.
} 


//! DOCS. May throw.
inline void 
Texture::getLevelParameterfv(const GLint lod, const GLenum value, GLfloat *data)
{ 
    Bindor b(this);
    _getTexLevelParameterfv(_target, lod, value, data); // May throw.
} 

//------------------------------------------------------------------------------

//! glActiveTexture wrapper. May throw. [static]
inline void 
Texture::_activeTexture(const GLenum texture)
{
    glActiveTexture(texture);
    Error::check("glActiveTexture"); // May throw.
}


//! glIsTexture wrapper. May throw. [static]
inline GLboolean 
Texture::_isTexture(const GLuint texture)
{ 
    const GLboolean result = glIsTexture(texture);
    Error::check("glIsTexture"); // May throw.
    return result;      
}


//! glGenTextures wrapper. May throw. [static]
inline void
Texture::_genTextures(const GLsizei n, GLuint *textures)
{
    glGenTextures(n, textures);
    Error::check("glGenTextures"); // May throw.
}


//! glDeleteTextures wrapper. May throw. [static]
inline void
Texture::_deleteTextures(const GLsizei n, const GLuint *textures)
{
    glDeleteTextures(n, textures);
    Error::check("glDeleteTextures"); // May throw.
}


//! glBindTexture wrapper. May throw. [static]
inline void
Texture::_bindTexture(const GLenum target, const GLuint texture)
{ 
    glBindTexture(target, texture);
    Error::check("glBindTexture"); // May throw.
}

//------------------------------------------------------------------------------

//! glTexParameteri wrapper. May throw. [static]
inline void 
Texture::_texParameteri(const GLenum target, 
                        const GLenum pname, 
                        const GLint  param)
{
    glTexParameteri(target, pname, param);
    Error::check("glTexParameteri"); // May throw.
}

//! glTexParameterf wrapper. May throw. [static]
inline void 
Texture::_texParameterf(const GLenum  target, 
                        const GLenum  pname, 
                        const GLfloat param)
{
    glTexParameterf(target, pname, param);
    Error::check("glTexParameterf"); // May throw.
}


//! glTexParameteriv wrapper. May throw. [static]
inline void 
Texture::_texParameteriv(const GLenum  target, 
                         const GLenum  pname,
                         const GLint  *params)
{
    glTexParameteriv(target, pname, params);
    Error::check("glTexParameteriv"); // May throw.
}


//! glTexParameterfv wrapper. May throw. [static]
inline void 
Texture::_texParameterfv(const GLenum   target, 
                         const GLenum   pname, 
                         const GLfloat *params)
{
    glTexParameterfv(target, pname, params);
    Error::check("glTexParameterfv"); // May throw.
}


//! glTexParameterIiv wrapper. May throw. [static]
inline void 
Texture::_texParameterIiv(const GLenum  target,
                          const GLenum  pname,
                          const GLint  *params)
{
    glTexParameterIiv(target, pname, params);
    Error::check("glTexParameterIiv"); // May throw.
}


//! glTexParameterIuiv wrapper. May throw. [static]
inline void 
Texture::_texParameterIuiv(const GLenum  target, 
                           const GLenum  pname, 
                           const GLuint *params)
{
    glTexParameterIuiv(target, pname, params);
    Error::check("glTexParameterIuiv"); // May throw.
}

//------------------------------------------------------------------------------

//! glGetTexParameteriv wrapper. May throw. [static]
inline void 
Texture::_getTexParameteriv(const GLenum  target, 
                            const GLenum  value, 
                            GLint        *data)
{
    glGetTexParameteriv(target, value, data);
    Error::check("glGetTexParameteriv"); // May throw.
}


//! glGetTexParameterfv wrapper. May throw. [static]
inline void 
Texture::_getTexParameterfv(const GLenum  target, 
                            const GLenum  value, 
                            GLfloat      *data)
{
    glGetTexParameterfv(target, value, data);
    Error::check("glGetTexParameterfv"); // May throw.
}


//! glGetTexParameterIiv wrapper. May throw. [static]
inline void 
Texture::_getTexParameterIiv(const GLenum  target, 
                             const GLenum  value, 
                             GLint        *data)
{
    glGetTexParameterIiv(target, value, data);
    Error::check("glGetTexParameterIiv"); // May throw.
}


//! glGetTexParameterIuiv wrapper. May throw. [static]
inline void 
Texture::_getTexParameterIuiv(const GLenum  target, 
                              const GLenum  value, 
                              GLuint       *data)
{
    glGetTexParameterIuiv(target, value, data);
    Error::check("glGetTexParameterIuiv"); // May throw.
}


//! glGetTexLevelParameteriv wrapper. May throw. [static]
inline void 
Texture::_getTexLevelParameteriv(const GLenum  target, 
                                 const GLint   lod, 
                                 const GLenum  value, 
                                 GLint        *data)
{
    glGetTexLevelParameteriv(target, lod, value, data);
    Error::check("glGetTexLevelParameteriv"); // May throw.
}


//! glGetTexLevelParameterfv wrapper. May throw. [static]
inline void 
Texture::_getTexLevelParameterfv(const GLenum  target, 
                                 const GLint   lod, 
                                 const GLenum  value, 
                                 GLfloat      *data)
{
    glGetTexLevelParameterfv(target, lod, value, data);
    Error::check("glGetTexLevelParameterfv"); // May throw.
}

//------------------------------------------------------------------------------

//! glGetTexImage wrapper. May throw. [static]
inline void
Texture::_getTexImage(const GLenum tex, const GLint lod, const GLenum fmt, 
                     const GLenum type, GLvoid *img)
{
    glGetTexImage(tex, lod, fmt, type, img);
    Error::check("glGetTexImage"); // May throw.
}


//! glGetCompressedTexImage wrapper. May throw. [static]
inline void 
Texture::_getCompressedTexImage(const GLenum  target, 
                                const GLint   lod, 
                                GLvoid       *img)
{
    glGetCompressedTexImage(target, lod, img);
    Error::check("glGetCompressedTexImage"); // May throw. 
}

END_NDJINN_NAMESPACE

//------------------------------------------------------------------------------

#endif  // NDJINN_TEXTURE_HPP_INCLUDED
