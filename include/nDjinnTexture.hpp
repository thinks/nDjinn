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

NDJINN_BEGIN_NAMESPACE

namespace detail {

// Texture Objects.

//! glActiveTexture wrapper. May throw.
inline void 
activeTexture(const GLenum texture) {
  glActiveTexture(texture);
  checkError("glActiveTexture"); // May throw.
}

//! glIsTexture wrapper. May throw.
inline GLboolean 
isTexture(const GLuint texture) { 
  const GLboolean result = glIsTexture(texture);
  checkError("glIsTexture"); // May throw.
  return result;      
}

//! glGenTextures wrapper. May throw. 
inline void
genTextures(const GLsizei n, GLuint *textures) {
  glGenTextures(n, textures);
  checkError("glGenTextures"); // May throw.
}

//! glDeleteTextures wrapper. May throw.
inline void
deleteTextures(const GLsizei n, const GLuint *textures) {
  glDeleteTextures(n, textures);
  checkError("glDeleteTextures"); // May throw.
}

//! glBindTexture wrapper. May throw. 
inline void
bindTexture(const GLenum target, const GLuint texture) { 
  glBindTexture(target, texture);
  checkError("glBindTexture"); // May throw.
}

// Texture Parameters.

//! glTexParameteri wrapper. May throw.
inline void 
texParameteri(const GLenum target, const GLenum pname, const GLint param) {
  glTexParameteri(target, pname, param);
  checkError("glTexParameteri"); // May throw.
}

//! glTexParameterf wrapper. May throw. 
inline void 
texParameterf(const GLenum target, const GLenum pname, const GLfloat param) {
  glTexParameterf(target, pname, param);
  checkError("glTexParameterf"); // May throw.
}

//! glTexParameteriv wrapper. May throw.
inline void 
texParameteriv(const GLenum target, const GLenum pname, const GLint *params) {
  glTexParameteriv(target, pname, params);
  checkError("glTexParameteriv"); // May throw.
}

//! glTexParameterfv wrapper. May throw. 
inline void 
texParameterfv(const GLenum target, const GLenum pname, const GLfloat *params) {
  glTexParameterfv(target, pname, params);
  checkError("glTexParameterfv"); // May throw.
}

//! glTexParameterIiv wrapper. May throw.
inline void 
texParameterIiv(const GLenum target, const GLenum pname, const GLint *params) {
  glTexParameterIiv(target, pname, params);
  checkError("glTexParameterIiv"); // May throw.
}

//! glTexParameterIuiv wrapper. May throw.
inline void 
texParameterIuiv(const GLenum target, 
                 const GLenum pname, 
                 const GLuint *params) {
  glTexParameterIuiv(target, pname, params);
  checkError("glTexParameterIuiv"); // May throw.
}

// Enumerated queries.

//! glGetTexParameteriv wrapper. May throw.
inline void 
getTexParameteriv(const GLenum target, const GLenum value, GLint *data) {
  glGetTexParameteriv(target, value, data);
  checkError("glGetTexParameteriv"); // May throw.
}

//! glGetTexParameterfv wrapper. May throw.
inline void 
getTexParameterfv(const GLenum target, const GLenum value, GLfloat *data) {
  glGetTexParameterfv(target, value, data);
  checkError("glGetTexParameterfv"); // May throw.
}

//! glGetTexParameterIiv wrapper. May throw.
inline void 
getTexParameterIiv(const GLenum target, const GLenum value, GLint *data) {
  glGetTexParameterIiv(target, value, data);
  checkError("glGetTexParameterIiv"); // May throw.
}

//! glGetTexParameterIuiv wrapper. May throw.
inline void 
getTexParameterIuiv(const GLenum target, const GLenum value, GLuint *data) {
  glGetTexParameterIuiv(target, value, data);
  checkError("glGetTexParameterIuiv"); // May throw.
}

//! glGetTexLevelParameteriv wrapper. May throw.
inline void 
getTexLevelParameteriv(const GLenum target, 
                       const GLint lod, 
                       const GLenum value, 
                       GLint *data) {
  glGetTexLevelParameteriv(target, lod, value, data);
  checkError("glGetTexLevelParameteriv"); // May throw.
}

//! glGetTexLevelParameterfv wrapper. May throw.
inline void 
getTexLevelParameterfv(const GLenum target, 
                       const GLint lod, 
                       const GLenum value, 
                       GLfloat *data) {
  glGetTexLevelParameterfv(target, lod, value, data);
  checkError("glGetTexLevelParameterfv"); // May throw.
}

// Texture Queries.

//! glGetTexImage wrapper. May throw.
inline void
getTexImage(const GLenum tex, 
            const GLint lod, 
            const GLenum fmt, 
            const GLenum type, 
            GLvoid *img) {
  glGetTexImage(tex, lod, fmt, type, img);
  checkError("glGetTexImage"); // May throw.
}

//! glGetCompressedTexImage wrapper. May throw.
inline void 
getCompressedTexImage(const GLenum target, const GLint lod, GLvoid *img) {
  glGetCompressedTexImage(target, lod, img);
  checkError("glGetCompressedTexImage"); // May throw. 
}

//! Convenience, generate a single texture handle and return it. May throw.
inline GLuint
genTexture() {
  GLuint handle = 0;
  genTextures(1, &handle);
  return handle;
}

//! Convenience.
inline void 
deleteTexture(GLuint const& handle) {
  deleteTextures(1, &handle);
}


} // Namespace: detail.

//------------------------------------------------------------------------------

//! Texture base class. NB: DTOR is not virtual.
class Texture
{
public:
  GLenum
  target() const;

  GLuint
  handle() const;

  void
  bind() const;

  void
  release() const;

  static void
  activeTexture(GLenum texture);

  static GLboolean 
  isTexture(GLuint texture);

public: // Texture Queries.
  void
  getImage(GLint lod, GLenum fmt, GLenum type, GLvoid *img);

  void 
  getCompressedImage(GLint lod, GLvoid *img);

public: // Texture Parameters.
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

public: // Enumerated queries.
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
  explicit Texture(GLenum target);
  ~Texture();

  //! DOCS
  class Bindor
  {
  public:
    //! CTOR.
    explicit
    Bindor(Texture *tex) 
      : _tex(tex) { 
      _tex->bind(); 
    }   

    //! DTOR.
    ~Bindor() { 
      try { 
        _tex->release(); 
      } 
      catch (...) {
      } 
    } 

  private:  // Member variables.
    Texture *_tex;
  };

private:
  Texture(const Texture&);            //!< Disabled copy.
  Texture& operator=(const Texture&); //!< Disabled assign.

private:  // Member variables.

  GLuint _handle; //!< Resource handle.
  GLenum _target;
};

//------------------------------------------------------------------------------

//! CTOR. May throw.
inline
Texture::Texture(const GLenum target)
  : _target(target)
  , _handle(detail::genTexture()) // May throw. 
{
  bind();
  if (detail::isTexture(_handle) == GL_FALSE) {
    NDJINN_THROW("invalid texture handle");
  }
  release();
}

//! DTOR.
inline
Texture::~Texture() {
  detail::deleteTexture(_handle); 
}

//! Expose target.
inline GLenum
Texture::target() const { 
  return _target; 
}

//! Expose handle.
inline GLuint
Texture::handle() const { 
  return _handle; 
}

//! Bind this texture. May throw.
// TODO: Check if this object is already bound?
inline void
Texture::bind() const { 
  detail::bindTexture(_target, _handle); // May throw.
} 

//! Release this texture. May throw.
inline void
Texture::release() const { 
  detail::bindTexture(_target, 0); // May throw.
} 

//! DOCS. May throw. [static]
inline void
Texture::activeTexture(const GLenum texture) {
  return detail::activeTexture(texture);
}

//! DOCS. May throw. [static]
inline GLboolean
Texture::isTexture(const GLenum texture) {
  return detail::isTexture(texture);
}

//------------------------------------------------------------------------------

//! Copy image into main memory. May throw.
inline void
Texture::getImage(const GLint lod, 
                  const GLenum fmt, 
                  const GLenum type, 
                  GLvoid *img) {
  Bindor bind(this);
  detail::getTexImage(_target, lod, fmt, type, img); // May throw.
}

//! Copy compressed image into main memory. May throw.
inline void 
Texture::getCompressedImage(const GLint lod, GLvoid *img) { 
  Bindor bind(this);
  detail::getCompressedTexImage(_target, lod, img); // May throw.
}

//------------------------------------------------------------------------------

//! Set texture integer parameter. May throw.
inline void
Texture::parameteri(const GLenum pname, const GLint param) {
  Bindor bind(this);
  detail::texParameteri(_target, pname, param); // May throw.
}

//! Set texture float parameter. May throw.
inline void
Texture::parameterf(const GLenum pname, const GLfloat param) {
  Bindor bind(this);
  detail::texParameterf(_target, pname, param); // May throw.
}

//! Set texture integer array parameter. May throw.
inline void 
Texture::parameteriv(const GLenum pname, const GLint *params) { 
  Bindor bind(this);
  detail::texParameteriv(_target, pname, params); // May throw.
} 

//! Set texture float array parameter. May throw.
inline void 
Texture::parameterfv(const GLenum pname, const GLfloat *params) { 
  Bindor bind(this);
  detail::texParameterfv(_target, pname, params); // May throw.
} 

//! DOCS. May throw.
inline void 
Texture::parameterIiv(const GLenum pname, const GLint *params) { 
  Bindor bind(this);
  detail::texParameterIiv(_target, pname, params); // May throw.
} 

//! DOCS. May throw.
inline void 
Texture::parameterIuiv(const GLenum pname, const GLuint *params) { 
  Bindor bind(this);
  detail::texParameterIuiv(_target, pname, params); // May throw.
} 

//------------------------------------------------------------------------------

//! Get texture integer parameter. May throw.
inline void 
Texture::getParameteriv(const GLenum value, GLint *data) { 
  Bindor bind(this);
  detail::getTexParameteriv(_target, value, data); // May throw.
} 

//! Get texture float parameter. May throw.
inline void 
Texture::getParameterfv(const GLenum value, GLfloat *data) { 
  Bindor bind(this);
  detail::getTexParameterfv(_target, value, data); // May throw.
} 

//! DOCS. May throw.
inline void 
Texture::getParameterIiv(const GLenum value, GLint *data)
{ 
  Bindor bind(this);
  detail::getTexParameterIiv(_target, value, data); // May throw.
} 

//! DOCS. May throw.
inline void 
Texture::getParameterIuiv(const GLenum value, GLuint *data) { 
  Bindor bind(this);
  detail::getTexParameterIuiv(_target, value, data); // May throw.
} 

//! DOCS. May throw.
inline void 
Texture::getLevelParameteriv(const GLint lod, const GLenum value, GLint *data) { 
  Bindor bind(this);
  detail::getTexLevelParameteriv(_target, lod, value, data); // May throw.
} 

//! DOCS. May throw.
inline void 
Texture::getLevelParameterfv(const GLint lod, 
                             const GLenum value, 
                             GLfloat *data) { 
  Bindor bind(this);
  detail::getTexLevelParameterfv(_target, lod, value, data); // May throw.
} 

//------------------------------------------------------------------------------

//! DOCS
class TextureBindor {
public:
  explicit
  TextureBindor(Texture const& texture) 
    : _texture(texture) {
    _texture.bind();
  }

  ~TextureBindor() {
    _texture.release();
  }

private: // Member variables.
  Texture const& _texture;
};

//------------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE_HPP_INCLUDED
