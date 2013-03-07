//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_STATE_HPP_INCLUDED
#define NDJINN_STATE_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

// glEnable wrapper. May throw.
inline void 
enable(const GLenum cap) {
  glEnable(cap);
  checkError("glEnable");
}

// glDisable wrapper. May throw.
inline void 
disable(const GLenum cap) {
  glDisable(cap);
  checkError("glDisable");
}

//! glGetBooleanv wrapper. May throw.
inline void
getBooleanv(const GLenum pname, GLboolean *data) {
  glGetBooleanv(pname, data);
  checkError("glGetBooleanv");
}

//! glGetIntegerv wrapper. May throw. 
inline void 
getIntegerv(const GLenum pname, GLint *data) {
  glGetIntegerv(pname, data);
  checkError("glGetIntegerv");
}

//! glGetInteger64v wrapper. May throw.
inline void 
getInteger64v(const GLenum pname, GLint64 *data) {
  glGetInteger64v(pname, data);
  checkError("glGetInteger64v");
}

//! glGetFloatv wrapper. May throw. 
inline void
getFloatv(const GLenum pname, GLfloat *data) {
  glGetFloatv(pname, data);
  checkError("glGetFloatv"); // May throw.
}

//! glGetDoublev wrapper. May throw.
inline void
getDoublev(const GLenum pname, GLdouble *data) {
  glGetDoublev(pname, data);
  checkError("glGetDoublev"); // May throw.
}

//! glIsEnabled wrapper. May throw. 
inline GLboolean
isEnabled(const GLenum cap) {
  const GLboolean enabled = glIsEnabled(cap);
  checkError("glIsEnabled"); // May throw.
  return enabled;
}

//! glGetString wrapper. May throw.
inline const GLubyte*
getString(const GLenum name) {
  const GLubyte *str = glGetString(name);
  checkError("glGetString");
  return str;
}

NDJINN_END_NAMESPACE

#endif // NDJINN_STATE_HPP_INCLUDED
