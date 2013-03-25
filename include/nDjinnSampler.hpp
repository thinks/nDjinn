// -----------------------------------------------------------------------------
//
// Copyright (C) Tommy Hinks              
// tommy[dot]hinks[at]gmail[dot]com                       
//
// Contributors: 
//             1) Tommy Hinks
//
// -----------------------------------------------------------------------------

#ifndef NDJINN_SAMPLER_HPP_INCLUDED
#define NDJINN_SAMPLER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include "nDjinnState.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glGenSamplers wrapper. May throw.
inline void 
genSamplers(GLsizei const count, GLuint* samplers) {
  glGenSamplers(count, samplers);
  checkError("glGenSamplers");
}

//! glDeleteSamplers wrapper. May throw.
inline void
deleteSamplers(GLsizei const count, GLuint const* samplers) {
  glDeleteSamplers(count, samplers);
  checkError("glDeleteSamplers");
}

//! glBindSampler wrapper. May throw.
inline void
bindSampler(GLuint const unit, GLuint const sampler) {
  glBindSampler(unit, sampler);
  checkError("glBindSampler"); 
}

//! glSamplerParameteri wrapper. May throw.
inline void 
samplerParameteri(GLuint const sampler, 
                  GLenum const pname, 
                  GLint const param) {
  glSamplerParameteri(sampler, pname, param);
  checkError("glSamplerParameteri");
}

//! glSamplerParameterf wrapper. May throw.
inline void 
samplerParameterf(GLuint const sampler, 
                  GLenum const pname, 
                  GLfloat const param) {
  glSamplerParameterf(sampler, pname, param);
  checkError("glSamplerParameterf");
}

//! glSamplerParameteriv wrapper. May throw.
inline void 
samplerParameteriv(GLuint const sampler, 
                   GLenum const pname, 
                   GLint const* param) {
  glSamplerParameteriv(sampler, pname, param);
  checkError("glSamplerParameteriv");
}

//! glSamplerParameterfv wrapper. May throw.
inline void 
samplerParameterfv(GLuint const sampler, 
                   GLenum const pname, 
                   GLfloat const* params) {
  glSamplerParameterfv(sampler, pname, params);
  checkError("glSamplerParameterfv");
}

//! glSamplerParameterIiv wrapper. May throw.
inline void
samplerParameterIiv(GLuint const sampler,
                    GLenum const pname, 
                    GLint const* params) {
  glSamplerParameterIiv(sampler, pname, params);
  checkError("glSamplerParameterIiv");
}

//! glSamplerParameterIuiv wrapper. May throw.
inline void
samplerParameterIuiv(GLuint const sampler,
                     GLenum const pname, 
                     GLuint const* params) {
  glSamplerParameterIuiv(sampler, pname, params);
  checkError("glSamplerParameterIuiv");
}

//! glGetSamplerParameteriv wrapper. May throw.
inline void 
getSamplerParameteriv(GLuint const sampler, 
                      GLenum const pname, 
                      GLint* params) {
  glGetSamplerParameteriv(sampler, pname, params);
  checkError("glSamplerParameteriv");
}

//! glGetSamplerParameterfv wrapper. May throw.
inline void 
getSamplerParameterfv(GLuint const sampler, 
                      GLenum const pname, 
                      GLfloat* params) {
  glGetSamplerParameterfv(sampler, pname, params);
  checkError("glSamplerParameterfv");
}

//! glGetSamplerParameterIiv wrapper. May throw.
inline void 
getSamplerParameterIiv(GLuint const sampler, 
                       GLenum const pname, 
                       GLint* params) {
  glGetSamplerParameterIiv(sampler, pname, params);
  checkError("glGetSamplerParameterIiv");
}

//! glGetSamplerParameterIuiv wrapper. May throw.
inline void 
getSamplerParameterIuiv(GLuint const sampler, 
                        GLenum const pname, 
                        GLuint* params) {
  glGetSamplerParameterIuiv(sampler, pname, params);
  checkError("glGetSamplerParameterIuiv");
}

//! glIsSampler wrapper. May throw.
inline GLboolean 
isSampler(GLuint const sampler) {
  GLboolean const isSampler = glIsSampler(sampler);
  checkError("glIsSampler");
  return isSampler;
}

//! Convenience, generate a single sampler handle and return it. May throw.
inline GLuint
genSampler() {
  GLuint handle = 0;
  genSamplers(1, &handle);
  return handle;
}

//! Convenience.
inline void 
deleteSampler(GLuint const& handle) {
  deleteSamplers(1, &handle);
}

template<typename T>
void 
samplerParameter(GLuint sampler, GLenum pname, T param);

template<> inline
void 
samplerParameter<GLint>(GLuint const sampler, 
                        GLenum const pname, 
                        GLint const param) {
  samplerParameteri(sampler, pname, param);
}

template<> inline
void 
samplerParameter<GLfloat>(GLuint const sampler, 
                          GLenum const pname, 
                          GLfloat const param) {
  samplerParameterf(sampler, pname, param);
}

template<typename T> inline
void 
samplerParameterv(GLuint sampler, GLenum pname, T const* params);

template<> inline
void 
samplerParameterv<GLint>(GLuint const sampler, 
                         GLenum const pname, 
                         GLint const* params) {
  samplerParameteriv(sampler, pname, params);
}

template<> inline
void 
samplerParameterv<GLfloat>(GLuint const sampler, 
                           GLenum const pname, 
                           GLfloat const* params) {
  samplerParameterfv(sampler, pname, params);
}

template<typename T> inline
void 
samplerParameterIv(GLuint sampler, GLenum pname, T const* params);

template<> inline
void 
samplerParameterIv<GLint>(GLuint const sampler, 
                          GLenum const pname, 
                          GLint const* params) {
  samplerParameterIiv(sampler, pname, params);
}

template<> inline
void 
samplerParameterIv<GLuint>(GLuint const sampler, 
                           GLenum const pname, 
                           GLuint const* params) {
  samplerParameterIuiv(sampler, pname, params);
}

template<typename T> inline
void
getSamplerParameterv(GLuint sampler, GLenum pname, T* params);

template<> inline
void
getSamplerParameterv<GLint>(GLuint const sampler, 
                            GLenum const pname, 
                            GLint* params) {
  getSamplerParameteriv(sampler, pname, params);
}

template<> inline
void
getSamplerParameterv<GLfloat>(GLuint const sampler, 
                              GLenum const pname, 
                              GLfloat* params) {
  getSamplerParameterfv(sampler, pname, params);
}

template<typename T> inline
void
getSamplerParameterIv(GLuint sampler, GLenum pname, T* params);

template<> inline
void
getSamplerParameterIv<GLint>(GLuint const sampler, 
                             GLenum const pname, 
                             GLint* params) {
  getSamplerParameterIiv(sampler, pname, params);
}

template<> inline
void
getSamplerParameterIv<GLuint>(GLuint const sampler, 
                              GLenum const pname, 
                              GLuint* params) {
  glGetSamplerParameterIuiv(sampler, pname, params);
}

} // Namespace: detail.

// -----------------------------------------------------------------------------

//! DOCS
class Sampler{
public:

  explicit 
  Sampler();

  ~Sampler();

public:

  GLuint 
  handle() const;  

  void
  bind(GLuint unit = 0) const;

  void
  release(GLuint unit = 0) const;

  template<typename T>
  void 
  parameter(GLenum pname, T const param);

  template<typename T>
  void 
  parameterv(GLenum pname, T const* params);

  template<typename T>
  void 
  parameterIv(GLenum pname, T const* params);

  template<typename T>
  void
  getParameterv(GLenum pname, T* params) const;

  template<typename T>
  void
  getParameterIv(GLenum pname, T* params) const;

private:
  Sampler(Sampler const&);            //!< Disabled copy.
  Sampler& operator=(Sampler const&); //!< Disabled assign.

private: // Member variables.
  GLuint const _handle; //!< Resource handle.
};

// -----------------------------------------------------------------------------

inline
Sampler::Sampler()
  : _handle(detail::genSampler()) // May throw. 
{
  bind(); // Make sure sampler gets created.
  if (detail::isSampler(_handle) == GL_FALSE) {
    NDJINN_THROW("invalid sampler");
  }
  release();
}

inline
Sampler::~Sampler() { 
  detail::deleteSampler(_handle); 
}

// -----------------------------------------------------------------------------

inline GLuint
Sampler::handle() const { 
  return _handle; 
}

inline void 
Sampler::bind(GLuint const unit) const {
  detail::bindSampler(unit, _handle);
}

inline void 
Sampler::release(GLuint const unit) const {
  detail::bindSampler(unit, 0);
}

template<typename T> inline
void 
Sampler::parameter(GLenum const pname, T const param) {
  detail::samplerParameter<T>(_handle, pname, param);
}

template<typename T> inline
void 
Sampler::parameterv(GLenum const pname, T const* params) {
  detail::samplerParameterv<T>(_handle, pname, params);
}

template<typename T> inline
void 
Sampler::parameterIv(GLenum const pname, T const* params) {
  detail::samplerParameterIv<T>(_handle, pname, params);
}

template<typename T> inline
void
Sampler::getParameterv(GLenum const pname, T* params) const {
  detail::getSamplerParameterv<T>(_handle, pname, params);
}

template<typename T> inline
void
Sampler::getParameterIv(GLenum const pname, T* params) const {
  detail::getSamplerParameterIv<T>(_handle, pname, params);
}

// -----------------------------------------------------------------------------

//! DOCS
class SamplerBindor {
public:
  explicit
  SamplerBindor(Sampler const& sampler, GLuint const unit = 0) 
    : _sampler(sampler)
    , _unit(unit) {
    _sampler.bind(_unit);
  }

  ~SamplerBindor() {
    _sampler.release(_unit);
  }

private: // Member variables.
  Sampler const& _sampler;
  GLuint const _unit;
};

// -----------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif // NDJINN_SAMPLER_HPP_INCLUDED
