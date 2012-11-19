//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_BUFFER_HPP_INCLUDED
#define NDJINN_BUFFER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

//! glDrawBuffer wrapper. May throw.
inline void
drawBuffer(const GLenum buf) { 
  glDrawBuffer(buf);
  checkError("glDrawBuffer");
} 

//! glDrawBuffers wrapper. May throw.
inline void
drawBuffers(const GLsizei n, const GLenum *bufs) { 
  glDrawBuffers(n, bufs);
  checkError("glDrawBuffers");
} 

//! glColorMask wrapper. May throw.
inline void 
colorMask(const GLboolean r, 
          const GLboolean g, 
          const GLboolean b, 
          const GLboolean a) {
  glColorMask(r, g, b, a);
  checkError("glColorMask");
}

//! glColorMaski wrapper. May throw.
inline void 
colorMaski(const GLuint buf, 
           const GLboolean r, 
           const GLboolean g, 
           const GLboolean b, 
           const GLboolean a) {
  glColorMaski(buf, r, g, b, a);
  checkError("glColorMaski"); 
}

//! glDepthMask wrapper. May throw.
inline void 
depthMask(const GLboolean mask) {
  glDepthMask(mask);
  checkError("glColorMask");
}

//! glStencilMask wrapper. May throw.
inline void 
stencilMask(const GLuint mask)
{
  glStencilMask(mask);
  checkError("glStencilMask");
}

//! glStencilMaskSeparate wrapper. May throw.
inline void 
stencilMaskSeparate(const GLenum face, const GLuint mask) {
  glStencilMaskSeparate(face, mask);
  checkError("glStencilMaskSeparate");
}

//! glClear wrapper. May throw.
inline void 
clear(const GLbitfield buf) {
  glClear(buf);
  checkError("glClear");        
}

//! glClearColor wrapper. May throw.
inline void 
clearColor(const GLclampf r, 
           const GLclampf g, 
           const GLclampf b, 
           const GLclampf a) {
  glClearColor(r, g, b, a);
  checkError("glClearColor");
}

//! glClearDepth wrapper. May throw.
inline void 
clearDepth(const GLclampd d) {
  glClearDepth(d);
  checkError("glClearDepth");
}

//! glClearDepthf wrapper. May throw. 
inline void 
clearDepthf(const GLclampf d) {
  glClearDepthf(d);
  checkError("glClearDepthf");
}

//! glClearStencil wrapper. May throw.
inline void 
clearStencil(const GLint s) {
  glClearStencil(s);
  checkError("glClearStencil");
}

//! glClearBufferiv wrapper. May throw.
inline void 
clearBufferiv(const GLenum buf, const GLint drawbuffer, const GLint *value) {
  glClearBufferiv(buf, drawbuffer, value);
  checkError("glClearBufferiv"); // May throw.        
}

//! glClearBufferfv wrapper. May throw.
inline void 
clearBufferfv(const GLenum buf, const GLint drawbuffer, const GLfloat *value) {
  glClearBufferfv(buf, drawbuffer, value);
  checkError("glClearBufferfv"); // May throw.        
}

//! glClearBufferuiv wrapper. May throw.
inline void 
clearBufferuiv(const GLenum buf, const GLint drawbuffer, const GLuint *value) {
  glClearBufferuiv(buf, drawbuffer, value);
  checkError("glClearBufferuiv"); // May throw.        
}

//! glClearBufferfi wrapper. May throw.
inline void 
clearBufferfi(const GLenum buf, 
              const GLint drawbuffer, 
              const GLfloat depth, 
              const GLint stencil) {
  glClearBufferfi(buf, drawbuffer, depth, stencil);
  checkError("glClearBufferfi"); // May throw.
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_BUFFER_HPP_INCLUDED
