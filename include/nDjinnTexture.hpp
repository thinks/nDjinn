//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_TEXTURE_HPP_INCLUDED
#define NDJINN_TEXTURE_HPP_INCLUDED

#include <array>

#include "nDjinnError.hpp"
#include "nDjinnException.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glActiveTexture wrapper. May throw.
inline void activeTexture(GLenum const texture)
{
  glActiveTexture(texture);
  checkError("glActiveTexture");
}

//! glGenTextures wrapper. May throw.
inline void genTextures(GLsizei const n, GLuint *textures)
{
  glGenTextures(n, textures);
  checkError("glGenTextures");
}

//! glDeleteTextures wrapper. May throw.
inline void deleteTextures(GLsizei const n, GLuint const* textures)
{
  glDeleteTextures(n, textures);
  checkError("glDeleteTextures");
}

//! glIsTexture wrapper. May throw.
inline GLboolean isTexture(GLuint const texture)
{
  GLboolean const result = glIsTexture(texture);
  checkError("glIsTexture");
  return result;      
}

//! glBindTexture wrapper. May throw. 
inline void
bindTexture(GLenum const target, GLuint const texture) {
  glBindTexture(target, texture);
  checkError("glBindTexture");
}

// Texture Parameters.

//! glTextureParameteri wrapper. May throw.
inline void textureParameteri(GLuint const texture, GLenum const target,
                              GLenum const pname, GLint const param)
{
  glTextureParameteriEXT(texture, target, pname, param);
  checkError("glTextureParameteriEXT");
}

//! glTextureParameterf wrapper. May throw. 
inline void textureParameterf(GLuint const texture, GLenum const target,
                              GLenum const pname, GLfloat const param)
{
  glTextureParameterfEXT(texture, target, pname, param);
  checkError("glTextureParameterfEXT");
}

//! glTextureParameteriv wrapper. May throw.
inline void textureParameteriv(GLuint const texture, GLenum const target,
                               GLenum const pname, GLint const* params)
{
  glTextureParameterivEXT(texture, target, pname, params);
  checkError("glTextureParameterivEXT");
}

//! glTextureParameterfv wrapper. May throw.
inline void textureParameterfv(GLuint const texture, GLenum const target,
                               GLenum const pname, GLfloat const* params)
{
  glTextureParameterfvEXT(texture, target, pname, params);
  checkError("glTextureParameterfvEXT");
}

//! glTextureParameterIiv wrapper. May throw.
inline void textureParameterIiv(GLuint const texture, GLenum const target,
                                GLenum const pname, GLint const* params)
{
  glTextureParameterIivEXT(texture, target, pname, params);
  checkError("glTextureParameterIivEXT");
}

//! glTextureParameterIuiv wrapper. May throw.
inline void textureParameterIuiv(GLuint const texture, GLenum const target,
                                 GLenum const pname, GLuint const* params)
{
  glTextureParameterIuivEXT(texture, target, pname, params);
  checkError("glTextureParameterIuivEXT");
}

//! Convenience.
template<typename T>
void textureParameter(GLuint texture, GLenum target, GLenum pname, T param);

//! Convenience.
template<> inline
void textureParameter<GLint>(GLuint const texture, GLenum const target,
                             GLenum const pname, GLint const param)
{
  textureParameteri(texture, target, pname, param);
}

//! Convenience.
template<> inline
void textureParameter<GLfloat>(GLuint const texture, GLenum const target,
                               GLenum const pname, GLfloat const param)
{
  textureParameterf(texture, target, pname, param);
}

//! Convenience.
template<typename T>
void textureParameterv(GLuint texture, GLenum target, GLenum pname,
                       T const* params);

//! Convenience.
template<> inline
void textureParameterv<GLint>(GLuint const texture, GLenum const target,
                              GLenum const pname, GLint const* params)
{
  textureParameteriv(texture, target, pname, params);
}

//! Convenience.
template<> inline
void textureParameterv<GLfloat>(GLuint const texture, GLenum const target,
                                GLenum const pname, GLfloat const* params)
{
  textureParameterfv(texture, target, pname, params);
}

//! Convenience.
template<typename T>
void textureParameterIv(GLuint texture, GLenum target, GLenum pname,
                        T const* params);

//! Convenience.
template<> inline
void textureParameterIv<GLint>(GLuint const texture, GLenum const target,
                               GLenum const pname, GLint const* params)
{
  textureParameterIiv(texture, target, pname, params);
}

//! Convenience.
template<> inline
void textureParameterIv<GLuint>(GLuint const texture, GLenum const target,
                               GLenum const pname, GLuint const* params)
{
  textureParameterIuiv(texture, target, pname, params);
}

// Enumerated queries.

//! glGetTextureParameteriv wrapper. May throw.
inline void getTextureParameteriv(GLuint const texture, GLenum const target,
                                  GLenum const pname, GLint* params)
{
  glGetTextureParameterivEXT(texture, target, pname, params);
  checkError("glGetTextureParameterivEXT");
}

//! glGetTextureParameterfv wrapper. May throw.
inline void getTextureParameterfv(GLuint const texture, GLenum const target,
                                  GLenum const pname, GLfloat* params)
{
  glGetTextureParameterfvEXT(texture, target, pname, params);
  checkError("glGetTextureParameterfvEXT");
}

//! glGetTextureParameterIiv wrapper. May throw.
inline void getTextureParameterIiv(GLuint const texture, GLenum const target,
                                   GLenum const pname, GLint* params)
{
  glGetTextureParameterIivEXT(texture, target, pname, params);
  checkError("glGetTextureParameterIivEXT"); // May throw.
}

//! glGetTextureParameterIuiv wrapper. May throw.
inline void getTextureParameterIuiv(GLuint const texture, GLenum const target,
                                    GLenum const pname, GLuint* params)
{
  glGetTextureParameterIuivEXT(texture, target, pname, params);
  checkError("glGetTexParameterIuivEXT");
}

//! glGetTextureLevelParameteriv wrapper. May throw.
inline void getTextureLevelParameteriv(GLuint const texture,
                                       GLenum const target,
                                       GLint const level, GLenum const pname,
                                       GLint* params)
{
  glGetTextureLevelParameterivEXT(texture, target, level, pname, params);
  checkError("glGetTextureLevelParameterivEXT");
}

//! glGetTextureLevelParameterfv wrapper. May throw.
inline void getTextureLevelParameterfv(GLuint const texture,
                                       GLenum const target, GLint const level,
                                       GLenum const pname, GLfloat* params)
{
  glGetTextureLevelParameterfvEXT(texture, target, level, pname, params);
  checkError("glGetTextureLevelParameterfvEXT");
}

//! Convenience.
template <typename T>
void getTextureParameterv(GLuint texture, GLenum target, GLenum pname,
                          T* params);

//! Convenience.
template <> inline
void getTextureParameterv<GLint>(GLuint const texture, GLenum const target,
                                 GLenum const pname, GLint* params)
{
  getTextureParameteriv(texture, target, pname, params);
}

//! Convenience.
template <> inline
void getTextureParameterv<GLfloat>(GLuint const texture, GLenum const target,
                                   GLenum const pname, GLfloat* params)
{
  getTextureParameterfv(texture, target, pname, params);
}

//! Convenience.
template <typename T>
void getTextureParameterIv(GLuint texture, GLenum target, GLenum pname,
                           T* params);

//! Convenience.
template <> inline
void getTextureParameterIv<GLint>(GLuint const texture, GLenum const target,
                                  GLenum const pname, GLint* params)
{
  getTextureParameterIiv(texture, target, pname, params);
}

//! Convenience.
template <> inline
void getTextureParameterv<GLuint>(GLuint const texture, GLenum const target,
                                  GLenum const pname, GLuint* params)
{
  getTextureParameterIuiv(texture, target, pname, params);
}

//! Convenience.
template <typename T>
void getTextureLevelParameterv(GLuint texture, GLenum target, GLint level,
                               GLenum pname, T* params);

//! Convenience.
template <> inline
void getTextureLevelParameterv<GLint>(GLuint const texture,
                                      GLenum const target,
                                      GLint const level, GLenum const pname,
                                      GLint* params)
{
  getTextureLevelParameteriv(texture, target, level, pname, params);
}

//! Convenience.
template <> inline
void getTextureLevelParameterv<GLfloat>(GLuint const texture,
                                        GLenum const target,
                                        GLint const level, GLenum const pname,
                                        GLfloat* params)
{
  getTextureLevelParameterfv(texture, target, level, pname, params);
}

// Texture Queries.

//! glGetTextureImage wrapper. May throw.
inline void getTextureImage(GLuint const texture, GLenum const target,
                            GLint const level, GLenum const format,
                            GLenum const type, GLvoid* pixels)
{
  glGetTextureImageEXT(texture, target, level, format, type, pixels);
  checkError("glGetTextureImageEXT");
}

//! glGetCompressedTexImage wrapper. May throw.
inline void getCompressedTextureImage(GLuint const texture, GLenum const target,
                                      GLint const level, GLvoid* pixels)
{
  glGetCompressedTextureImageEXT(texture, target, level, pixels);
  checkError("glGetCompressedTextureImageEXT");
}

//! Convenience.
inline GLuint genTexture()
{
  GLuint handle = 0;
  genTextures(1, &handle);
  return handle;
}

//! Convenience.
inline void deleteTexture(GLuint const& handle)
{
  deleteTextures(1, &handle);
}

} // namespace detail

//! Set the active texture unit. May throw.
inline void activeTexture(GLenum const unit)
{
  detail::activeTexture(unit);
}

//! Bind @a texture to @a target.
template <typename T> inline
void bindTexture(GLenum const target, T const& texture)
{
  detail::bindTexture(target, texture.handle());
}

//! Release binding for @a target.
inline void releaseTexture(GLenum const target)
{
  detail::bindTexture(target, 0);
}

// Set texture parameter(s).

template <typename T, typename P> inline
void setTextureParameter(T const& texture, GLenum const target,
                         GLenum const pname, P const pvalue)
{
  detail::textureParameter(texture.handle(), target, pname, pvalue);
}

template <typename T, typename P, std::size_t N> inline
void setTextureParameters(T const& texture, GLenum const target,
                          GLenum const pname, std::array<P, N> const& pvalues)
{
  detail::textureParameterv(texture.handle(), target, pname, pvalues.data());
}

template <typename T, typename P, std::size_t N> inline
void setTextureParametersI(T const& texture, GLenum const target,
                           GLenum const pname, std::array<P, N> const& pvalues)
{
  detail::textureParameterIv(texture.handle(), target, pname, pvalues.data());
}

// Get texture parameter(s).

template <typename P, std::size_t N, typename T> inline
std::array<P, N> getTextureParameters(T const& texture, GLenum const target,
                                      GLenum const pname)
{
  std::array<P, N> pvalues;
  detail::getTextureParameterv(texture.handle(), target, pname, pvalues.data());
  return pvalues;
}

template <typename P, std::size_t N, typename T> inline
std::array<P, N> getTextureParametersI(T const& texture, GLenum const target,
                                       GLenum const pname)
{
  std::array<P, N> pvalues;
  detail::getTextureParameterIv(texture.handle(), target, pname,
                                pvalues.data());
  return pvalues;
}

template <typename P, std::size_t N, typename T> inline
std::array<P, N> getTextureLevelParameters(T const& texture,
                                           GLenum const target,
                                           GLint const level,
                                           GLenum const pname)
{
  std::array<P, N> pvalues;
  detail::getTextureLevelParameterv(texture.handle(), target, level, pname,
                                    pvalues.data());
  return pvalues;
}

// Texture Queries.

//! Copy image into main memory. May throw.
template <typename T> inline
void getTextureImage(T const& texture, GLenum const target, GLint const lod,
                     GLenum const format, GLenum const type, GLvoid* pixels)
{
  detail::getTextureImage(texture.handle(), target, lod, format, type, pixels);
}

//! Copy compressed image into main memory. May throw.
template <typename T> inline
void getCompressedTextureImage(T const& texture, GLenum const target,
                               GLint const lod, GLvoid* pixels)
{
  detail::getCompressedTextureImage(texture.handle(), target, lod, pixels);
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_TEXTURE_HPP_INCLUDED
