//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_TEXTURE_HPP_INCLUDED
#define NDJINN_TEXTURE_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
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

#if 0 
// DEPRECATED - use direct state access instead!

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

#endif

// Texture Parameters.

//! glTextureParameteri wrapper. May throw.
inline void 
textureParameteri(GLuint const texture, 
                  GLenum const target, 
                  GLenum const pname, 
                  GLint const param) {
  glTextureParameteriEXT(texture, target, pname, param);
  checkError("glTextureParameteriEXT"); // May throw.
}

//! glTextureParameterf wrapper. May throw. 
inline void 
textureParameterf(GLuint const texture,
                  GLenum const target, 
                  GLenum const pname, 
                  GLfloat const param) {
  glTextureParameterfEXT(texture, target, pname, param);
  checkError("glTextureParameterfEXT"); // May throw.
}

//! DOCS
template<typename T> inline
void
textureParameter(GLuint texture, GLenum target, GLenum pname, T param);

//! DOCS
template<> inline
void
textureParameter<GLint>(GLuint const texture, 
                        GLenum const target, 
                        GLenum const pname, 
                        GLint const param) {
  textureParameteri(texture, target, pname, param);
}

//! DOCS
template<> inline
void
textureParameter<GLfloat>(GLuint const texture, 
                          GLenum const target, 
                          GLenum const pname, 
                          GLfloat const param) {
  textureParameterf(texture, target, pname, param);
}

//! glTextureParameteriv wrapper. May throw.
inline void 
textureParameteriv(GLuint const texture,
                   GLenum const target, 
                   GLenum const pname,  
                   GLint const* params) {
  glTextureParameterivEXT(texture, target, pname, params);
  checkError("glTextureParameterivEXT"); // May throw.
}

//! glTextureParameterfv wrapper. May throw. 
inline void 
textureParameterfv(GLuint const texture,
                   GLenum const target, 
                   GLenum const pname,  
                   GLfloat const* params) {
  glTextureParameterfvEXT(texture, target, pname, params);
  checkError("glTextureParameterfvEXT"); // May throw.
}

//! DOCS
template<typename T> inline
void
textureParameterv(GLuint texture, GLenum target, GLenum pname, T const* params);

//! DOCS
template<> inline
void
textureParameterv<GLint>(GLuint const texture, 
                         GLenum const target, 
                         GLenum const pname, 
                         GLint const* params) {
  textureParameteriv(texture, target, pname, params);
}

//! DOCS
template<> inline
void
textureParameterv<GLfloat>(GLuint const texture, 
                           GLenum const target, 
                           GLenum const pname, 
                           GLfloat const* params) {
  textureParameterfv(texture, target, pname, params);
}

//! glTextureParameterIiv wrapper. May throw.
inline void 
textureParameterIiv(GLuint const texture, 
                    GLenum const target, 
                    GLenum const pname, 
                    GLint const* params) {
  glTextureParameterIivEXT(texture, target, pname, params);
  checkError("glTextureParameterIivEXT"); // May throw.
}

//! glTextureParameterIuiv wrapper. May throw.
inline void 
textureParameterIuiv(GLuint const texture,
                     GLenum const target, 
                     GLenum const pname, 
                     GLuint const* params) {
  glTextureParameterIuivEXT(texture, target, pname, params);
  checkError("glTextureParameterIuivEXT"); // May throw.
}

//! DOCS
template<typename T> inline
void
textureParameterIv(GLuint texture, 
                   GLenum target, 
                   GLenum pname, 
                   T const* params);

//! DOCS
template<> inline
void
textureParameterIv<GLint>(GLuint const texture, 
                         GLenum const target, 
                         GLenum const pname, 
                         GLint const* params) {
  textureParameterIiv(texture, target, pname, params);
}

//! DOCS
template<> inline
void
textureParameterIv<GLuint>(GLuint const texture, 
                           GLenum const target, 
                           GLenum const pname, 
                           GLuint const* params) {
  textureParameterIuiv(texture, target, pname, params);
}

// Enumerated queries.


//! glGetTextureParameteriv wrapper. May throw.
inline void 
getTextureParameteriv(GLuint const texture, 
                      GLenum const target, 
                      GLenum const pname, 
                      GLint* params) {
  glGetTextureParameterivEXT(texture, target, pname, params);
  checkError("glGetTextureParameterivEXT"); // May throw.
}

//! glGetTextureParameterfv wrapper. May throw.
inline void 
getTextureParameterfv(GLuint const texture,
                      GLenum const target, 
                      GLenum const pname, 
                      GLfloat* params) {
  glGetTextureParameterfvEXT(texture, target, pname, params);
  checkError("glGetTextureParameterfvEXT"); // May throw.
}

//! DOCS
template <typename T>
void
getTextureParameterv(GLuint texture, 
                     GLenum target, 
                     GLenum pname, 
                     T* params);

//! DOCS
template <> inline
void
getTextureParameterv<GLint>(GLuint const texture, 
                            GLenum const target, 
                            GLenum const pname, 
                            GLint* params) {
  getTextureParameteriv(texture, target, pname, params);
}

//! DOCS
template <> inline
void
getTextureParameterv<GLfloat>(GLuint const texture, 
                              GLenum const target, 
                              GLenum const pname, 
                              GLfloat* params) {
  getTextureParameterfv(texture, target, pname, params);
}


//! glGetTextureParameterIiv wrapper. May throw.
inline void 
getTextureParameterIiv(GLuint const texture, 
                       GLenum const target, 
                       GLenum const pname, 
                       GLint* params) {
  glGetTextureParameterIivEXT(texture, target, pname, params);
  checkError("glGetTextureParameterIivEXT"); // May throw.
}

//! glGetTextureParameterIuiv wrapper. May throw.
inline void 
getTextureParameterIuiv(GLuint const texture, 
                        GLenum const target, 
                        GLenum const pname, 
                        GLuint* params) {
  glGetTextureParameterIuivEXT(texture, target, pname, params);
  checkError("glGetTexParameterIuivEXT"); // May throw.
}

//! DOCS
template <typename T>
void
getTextureParameterIv(GLuint texture, 
                      GLenum target, 
                      GLenum pname, 
                      T* params);

//! DOCS
template <> inline
void
getTextureParameterIv<GLint>(GLuint const texture, 
                             GLenum const target, 
                             GLenum const pname, 
                             GLint* params) {
  getTextureParameterIiv(texture, target, pname, params);
}

//! DOCS
template <> inline
void
getTextureParameterv<GLuint>(GLuint const texture, 
                             GLenum const target, 
                             GLenum const pname, 
                             GLuint* params) {
  getTextureParameterIuiv(texture, target, pname, params);
}



//! glGetTextureLevelParameteriv wrapper. May throw.
inline void 
getTextureLevelParameteriv(GLuint const texture, 
                           GLenum const target, 
                           GLint const level,
                           GLenum const pname, 
                           GLint* params) {
  glGetTextureLevelParameterivEXT(texture, target, level, pname, params);
  checkError("glGetTextureLevelParameterivEXT"); // May throw.
}

//! glGetTextureLevelParameterfv wrapper. May throw.
inline void 
getTextureLevelParameterfv(GLuint const texture,
                           GLenum const target, 
                           GLint const level,
                           GLenum const pname, 
                           GLfloat* params) {
  glGetTextureLevelParameterfvEXT(texture, target, level, pname, params);
  checkError("glGetTextureLevelParameterfvEXT"); // May throw.
}

//! DOCS
template <typename T>
void
getTextureLevelParameterv(GLuint texture, 
                          GLenum target,
                          GLint level, 
                          GLenum pname, 
                          T* params);

//! DOCS
template <> inline
void
getTextureLevelParameterv<GLint>(GLuint const texture, 
                                 GLenum const target,
                                 GLint const level,
                                 GLenum const pname, 
                                 GLint* params) {
  getTextureLevelParameteriv(texture, target, level, pname, params);
}

//! DOCS
template <> inline
void
getTextureLevelParameterv<GLfloat>(GLuint const texture, 
                                   GLenum const target, 
                                   GLint const level,
                                   GLenum const pname, 
                                   GLfloat* params) {
  getTextureLevelParameterfv(texture, target, level, pname, params);
}

// Texture Queries.


//! glGetTextureImage wrapper. May throw.
inline void
getTextureImage(GLuint const texture, 
                GLenum const target,
                GLint const level,
                GLenum const format, 
                GLenum const type, 
                GLvoid *pixels) {
  glGetTextureImageEXT(texture, target, level, format, type, pixels);
  checkError("glGetTextureImageEXT"); // May throw.
}

//! glGetCompressedTexImage wrapper. May throw.
inline void 
getCompressedTextureImage(GLuint const texture, 
                          GLenum const target,
                          GLint const level, 
                          GLvoid *img) {
  glGetCompressedTextureImageEXT(texture, target, level, img);
  checkError("glGetCompressedTextureImageEXT"); // May throw. 
}

//! Convenience, generate a single texture handle and return it. May throw.
inline GLuint
genTexture() {
  GLuint handle = 0;
  genTextures(1, &handle);
  return handle;
}

//! Convenience, delete a single texture handle.
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

public: // Texture Queries.
  void
  getImage(GLint lod, GLenum fmt, GLenum type, GLvoid *img);

  void 
  getCompressedImage(GLint lod, GLvoid *img);

public: // Texture Parameters.
  template <typename T>
  void
  parameter(GLenum pname, T param);

  template <typename T>
  void
  parameterv(GLenum pname, T const* params);

  template <typename T>
  void 
  parameterIv(GLenum pname, T const* params);

public: // Enumerated queries.
  template <typename T>
  void 
  getParameterv(GLenum pname, T* params) const;

  template <typename T>
  void
  getParameterIv(GLenum pname, T* params) const;

  template <typename T>
  void
  getLevelParameterv(GLenum pname, T* params) const;

protected:
  explicit Texture(GLenum target);
  ~Texture();

private:
  Texture(Texture const&);            //!< Disabled copy.
  Texture& operator=(Texture const&); //!< Disabled assign.

private:  // Member variables.
  GLuint const _handle; //!< Resource handle.
  GLenum const _target;
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
    NDJINN_THROW("invalid texture");
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

//------------------------------------------------------------------------------

//! Copy image into main memory. May throw.
inline void
Texture::getImage(GLint const lod, 
                  GLenum const fmt, 
                  GLenum const type, 
                  GLvoid *img) {
  detail::getTextureImage(_handle, _target, lod, fmt, type, img); // May throw.
}

//! Copy compressed image into main memory. May throw.
inline void 
Texture::getCompressedImage(GLint const lod, GLvoid *img) { 
  detail::getCompressedTextureImage(_handle, _target, lod, img); // May throw.
}

//------------------------------------------------------------------------------

template<typename T> inline 
void
Texture::parameter(GLenum const pname, T const param) {
  detail::textureParameter<T>(_handle, _target, pname, param); // May throw.
}

template<typename T> inline 
void
Texture::parameterv(GLenum const pname, T const* params) {
  detail::textureParameterv<T>(_handle, _target, pname, params); // May throw.
}

template<typename T> inline 
void
Texture::parameterIv(GLenum const pname, T const* params) {
  detail::textureParameterIv<T>(_handle, _target, pname, params); // May throw.
}

//------------------------------------------------------------------------------

template <typename T> inline
void 
Texture::getParameterv(GLenum const pname, T* params) const {
  detail::getTextureParameterv<T>(_handle, _target, pname, params);
}

template <typename T> inline
void
Texture::getParameterIv(GLenum const pname, T* params) const {
  detail::getTextureParameterIv<T>(_handle, _target, pname, params);
}

template <typename T> inline
void
Texture::getLevelParameterv(GLenum const pname, T* params) const {
  detail::getTextureLevelParameterIv<T>(_handle, _target, pname, params);
}

//------------------------------------------------------------------------------

//! DOCS. May throw.
inline void
activeTexture(GLenum const unit) {
  detail::activeTexture(unit);
}

//------------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE_HPP_INCLUDED
