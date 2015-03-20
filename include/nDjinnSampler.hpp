//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_SAMPLER_HPP_INCLUDED
#define NDJINN_SAMPLER_HPP_INCLUDED

#include "nDjinnError.hpp"
#include "nDjinnException.hpp"
#include "nDjinnGL.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glGenSamplers wrapper. May throw.
inline void genSamplers(GLsizei const count, GLuint* samplers) {
  glGenSamplers(count, samplers);
  checkError("glGenSamplers");
}

//! glDeleteSamplers wrapper. May throw.
inline void deleteSamplers(GLsizei const count, GLuint const* samplers) {
  glDeleteSamplers(count, samplers);
  checkError("glDeleteSamplers");
}

//! glBindSampler wrapper. May throw.
inline void bindSampler(GLuint const unit, GLuint const sampler) {
  glBindSampler(unit, sampler);
  checkError("glBindSampler"); 
}

//! glSamplerParameteri wrapper. May throw.
inline void samplerParameteri(GLuint const sampler, 
                              GLenum const pname,
                              GLint const param) {
  glSamplerParameteri(sampler, pname, param);
  checkError("glSamplerParameteri");
}

//! glSamplerParameterf wrapper. May throw.
inline void samplerParameterf(GLuint const sampler, 
                              GLenum const pname,
                              GLfloat const param) {
  glSamplerParameterf(sampler, pname, param);
  checkError("glSamplerParameterf");
}

//! glSamplerParameteriv wrapper. May throw.
inline void samplerParameteriv(GLuint const sampler, 
                               GLenum const pname,
                               GLint const* param) {
  glSamplerParameteriv(sampler, pname, param);
  checkError("glSamplerParameteriv");
}

//! glSamplerParameterfv wrapper. May throw.
inline void samplerParameterfv(GLuint const sampler, 
                               GLenum const pname,
                               GLfloat const* params) {
  glSamplerParameterfv(sampler, pname, params);
  checkError("glSamplerParameterfv");
}

//! glGetSamplerParameteriv wrapper. May throw.
inline void getSamplerParameteriv(GLuint const sampler, 
                                  GLenum const pname,
                                  GLint* params) {
  glGetSamplerParameteriv(sampler, pname, params);
  checkError("glSamplerParameteriv");
}

//! glGetSamplerParameterfv wrapper. May throw.
inline void getSamplerParameterfv(GLuint const sampler,
                                  GLenum const pname,
                                  GLfloat* params) {
  glGetSamplerParameterfv(sampler, pname, params);
  checkError("glSamplerParameterfv");
}

//! glIsSampler wrapper. May throw.
inline GLboolean isSampler(GLuint const sampler) {
  GLboolean const isSampler = glIsSampler(sampler);
  checkError("glIsSampler");
  return isSampler;
}

//! Convenience, generate a single sampler handle and return it. May throw.
inline GLuint genSampler() {
  GLuint handle = 0;
  genSamplers(1, &handle);
  return handle;
}

//! Convenience.
inline void deleteSampler(GLuint const& handle) {
  deleteSamplers(1, &handle);
}

//! Generic.
template<typename T> void
samplerParameter(GLuint sampler, GLenum pname, T param);

//! GLint specialization.
template<> inline void
samplerParameter<GLint>(GLuint const sampler, 
                        GLenum const pname, 
                        GLint const param) {
  samplerParameteri(sampler, pname, param);
}

//! GLfloat specialization.
template<> inline void
samplerParameter<GLfloat>(GLuint const sampler, 
                          GLenum const pname, 
                          GLfloat const param) {
  samplerParameterf(sampler, pname, param);
}

//! Generic.
template<typename T> inline void
samplerParameterv(GLuint sampler, GLenum pname, T const* params);

//! GLint specialization.
template<> inline void
samplerParameterv<GLint>(GLuint const sampler, 
                         GLenum const pname, 
                         GLint const* params) {
  samplerParameteriv(sampler, pname, params);
}

//! GLfloat specialization.
template<> inline void
samplerParameterv<GLfloat>(GLuint const sampler, 
                           GLenum const pname, 
                           GLfloat const* params) {
  samplerParameterfv(sampler, pname, params);
}

//! Generic.
template<typename T> inline void
getSamplerParameterv(GLuint sampler, GLenum pname, T* params);

//! GLint specialization.
template<> inline void
getSamplerParameterv<GLint>(GLuint const sampler, 
                            GLenum const pname, 
                            GLint* params) {
  getSamplerParameteriv(sampler, pname, params);
}

//! GLfloat specialization.
template<> inline void
getSamplerParameterv<GLfloat>(GLuint const sampler, 
                              GLenum const pname, 
                              GLfloat* params) {
  getSamplerParameterfv(sampler, pname, params);
}

} // Namespace: detail.

//! DOCS
class Sampler{
public:
  Sampler()
    : _handle(detail::genSampler())
  {
    bind(); // Make sure sampler gets created.
    if (detail::isSampler(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid sampler");
    }
    release();
  }

  ~Sampler() {
    detail::deleteSampler(_handle);
  }

  GLuint handle() const {
    return _handle;
  }

  void bind(GLuint const unit = 0) const {
    detail::bindSampler(unit, _handle);
  }

  void release(GLuint const unit = 0) const {
    detail::bindSampler(unit, 0);
  }

  template<typename T> void parameter(GLenum const pname, T* params) const {
    detail::getSamplerParameterv<T>(_handle, pname, params);
  }

  template<typename T> void setParameter(GLenum const pname, T const* params) {
    detail::samplerParameterv<T>(_handle, pname, params);
  }

  template<typename T> void setParameter(GLenum const pname, T const param) {
    detail::samplerParameterv<T>(_handle, pname, param);
  }

private:
  Sampler(Sampler const&); //!< Disabled copy.
  Sampler& operator=(Sampler const&); //!< Disabled assign.

  GLuint const _handle; //!< Resource handle.
};

NDJINN_END_NAMESPACE

#endif // NDJINN_SAMPLER_HPP_INCLUDED
