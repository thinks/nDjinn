//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_VIEWPORT_HPP_INCLUDED
#define NDJINN_VIEWPORT_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

//! glDepthRange wrapper. May throw.
inline void 
depthRange(const GLclampd n, const GLclampd f) {
  glDepthRange(n, f);
  checkError("glDepthRange");
}

//! glViewport wrapper. May throw.
inline void 
viewport(const GLint x, const GLint y, const GLsizei w, const GLsizei h) {
  glViewport(x, y, w, h);
  checkError("glViewport");
}

// TODO
//static void 
//_depth_range_f(const GLclampf n, const GLclampd f)
//{}

// TODO
//static void 
//_viewport_array_v(const GLuint first, const GLsizei count, const GLfloat *v)
//{}

// TODO
//static void 
//_viewport_indexed_f(const GLuint index, const GLfloat x, const GLfloat y, 
//                    const GLfloat w, const GLfloat h)
//{}

// TODO
//static void 
//_viewport_indexed_fv(const GLuint index, const GLfloat *v)
//{}

// TODO
//static void 
//_depth_range_array_v(const GLuint first, const GLsizei count, 
//                     const GLclampd *v)
//{}

// TODO
//static void 
//_depth_range_indexed(const GLuint index, const GLclampd n, const GLclampd f)
//{}

NDJINN_END_NAMESPACE

#endif // NDJINN_VIEWPORT_HPP_INCLUDED
