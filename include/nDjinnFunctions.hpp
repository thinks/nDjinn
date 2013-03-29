//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_FUNCTIONS_HPP_INCLUDED
#define NDJINN_FUNCTIONS_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

// -----------------------------------------------------------------------------
// Blending

//! glBlendEquation wrapper. May throw.
void inline
blendEquation(GLenum const mode) {
  glBlendEquation(mode);
  checkError("glBlendEquation");
}

//! glBlendEquationi wrapper. May throw.
void inline
blendEquationi(GLuint const buf, GLenum const mode) {
  glBlendEquationi(buf, mode);
  checkError("glBlendEquationi");
}

//! glBlendEquationSeparate wrapper. May throw.
void inline 
blendEquationSeparate(GLenum const modeRgb, GLenum const modeAlpha) {
  glBlendEquationSeparate(modeRgb, modeAlpha);
  checkError("glBlendEquationSeparate");
}

//! glBlendEquationSeparatei wrapper. May throw.
void inline 
blendEquationSeparatei(GLuint const buf, 
                       GLenum const modeRgb, 
                       GLenum const modeAlpha) {
  glBlendEquationSeparatei(buf, modeRgb, modeAlpha);
  checkError("glBlendEquationSeparatei");
}

//! glBlendFunc wrapper. May throw.
void inline
blendFunc(GLenum const src, GLenum const dst) {
  glBlendFunc(src, dst);
  checkError("glBlendFunc");
}

//! glBlendFunci wrapper. May throw.
void inline 
blendFunci(GLuint const buf, GLenum const src, GLenum const dst) {
  glBlendFunci(buf, src, dst);
  checkError("glBlendFunci");
}

//! glBlendFuncSeparate wrapper. May throw.
void inline
blendFuncSeparate(GLenum const srcRgb, 
                  GLenum const dstRgb, 
                  GLenum const srcAlpha, 
                  GLenum const dstAlpha) {
  glBlendFuncSeparate(srcRgb, dstRgb, srcAlpha, dstAlpha);
  checkError("glBlendFuncSeparate");
}

//! glBlendFuncSeparatei wrapper. May throw.
void inline
blendFuncSeparatei(GLuint const buf, 
                   GLenum const srcRgb, 
                   GLenum const dstRgb, 
                   GLenum const srcAlpha, 
                   GLenum const dstAlpha) {
  glBlendFuncSeparatei(buf, srcRgb, dstRgb, srcAlpha, dstAlpha);
  checkError("glBlendFuncSeparatei");
}

//! glBlendColor wrapper. May throw.
void inline
blendColor(GLclampf const red, 
           GLclampf const green, 
           GLclampf const blue, 
           GLclampf const alpha) {
  glBlendColor(red, green, blue, alpha);
  checkError("glBlendColor");
}

// -----------------------------------------------------------------------------
// State

// glEnable wrapper. May throw.
inline void 
enable(GLenum const cap) {
  glEnable(cap);
  checkError("glEnable");
}

// glDisable wrapper. May throw.
inline void 
disable(GLenum const cap) {
  glDisable(cap);
  checkError("glDisable");
}

//! glGetBooleanv wrapper. May throw.
inline void
getBooleanv(GLenum const pname, GLboolean *data) {
  glGetBooleanv(pname, data);
  checkError("glGetBooleanv");
}

//! glGetIntegerv wrapper. May throw. 
inline void 
getIntegerv(GLenum const pname, GLint *data) {
  glGetIntegerv(pname, data);
  checkError("glGetIntegerv");
}

//! glGetInteger64v wrapper. May throw.
inline void 
getInteger64v(GLenum const pname, GLint64 *data) {
  glGetInteger64v(pname, data);
  checkError("glGetInteger64v");
}

//! glGetFloatv wrapper. May throw. 
inline void
getFloatv(GLenum const pname, GLfloat *data) {
  glGetFloatv(pname, data);
  checkError("glGetFloatv"); // May throw.
}

//! glGetDoublev wrapper. May throw.
inline void
getDoublev(GLenum const pname, GLdouble *data) {
  glGetDoublev(pname, data);
  checkError("glGetDoublev"); // May throw.
}

//! glIsEnabled wrapper. May throw. 
inline GLboolean
isEnabled(GLenum const cap) {
  const GLboolean enabled = glIsEnabled(cap);
  checkError("glIsEnabled"); // May throw.
  return enabled;
}

//! glGetString wrapper. May throw.
inline const GLubyte*
getString(GLenum const name) {
  const GLubyte *str = glGetString(name);
  checkError("glGetString");
  return str;
}

// -----------------------------------------------------------------------------
// Vertex specification

//! glVertexAttribPointer wrapper. May throw.
void inline 
vertexAttribPointer(GLuint const index, 
                    GLint const size, 
                    GLenum const type, 
                    GLboolean const normalized, 
                    GLsizei const stride, 
                    GLvoid const* pointer) {
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  checkError("glVertexAttribPointer");
}

//! glVertexAttribIPointer wrapper. May throw.
void inline
vertexAttribIPointer(GLuint const index, 
                     GLint const size, 
                     GLenum const type, 
                     GLsizei const stride, 
                     GLvoid const* pointer) {
  glVertexAttribIPointer(index, size, type, stride, pointer);
  checkError("glVertexAttribIPointer");
}

//! glVertexAttribLPointer wrapper. May throw.
void inline 
vertexAttribLPointer(GLuint const index, 
                     GLint const size, 
                     GLenum const type, 
                     GLsizei const stride, 
                     GLvoid const* pointer) {
  glVertexAttribLPointer(index, size, type, stride, pointer);
  checkError("glVertexAttribLPointer");
}

//! glEnableVertexAttribArray wrapper. May throw.
void inline
enableVertexAttribArray(GLuint const index) {
  glEnableVertexAttribArray(index);
  checkError("glEnableVertexAttribArray");
}

//! glDisableVertexAttribArray wrapper. May throw.
void inline
disableVertexAttribArray(GLuint const index) {
  glDisableVertexAttribArray(index);
  checkError("glDisableVertexAttribArray");
}

//! glVertexAttribDivisor wrapper. May throw.
void inline
vertexAttribDivisor(GLuint const index, GLuint const divisor) {
  glVertexAttribDivisor(index, divisor);
  checkError("glVertexAttribDivisor");
}

//! glDrawRangeElements wrapper. May throw.
void inline
drawRangeElements(GLenum const mode, 
                  GLuint const start, 
                  GLuint const end, 
                  GLsizei const count, 
                  GLenum const type, 
                  GLvoid const* indices) {
  glDrawRangeElements(mode, start, end, count, type, indices);
  checkError("glDrawRangeElements");
}

// -----------------------------------------------------------------------------
// Viewport

//! glDepthRange wrapper. May throw.
inline void 
depthRange(GLclampd const n, GLclampd const f) {
  glDepthRange(n, f);
  checkError("glDepthRange");
}

//! glViewport wrapper. May throw.
inline void 
viewport(GLint const x, GLint const y, GLsizei const w, GLsizei const h) {
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

// -----------------------------------------------------------------------------
// Buffer

//! glDrawBuffer wrapper. May throw.
inline void
drawBuffer(GLenum const buf) { 
  glDrawBuffer(buf);
  checkError("glDrawBuffer");
} 

//! glDrawBuffers wrapper. May throw.
inline void
drawBuffers(GLsizei const n, GLenum const* bufs) { 
  glDrawBuffers(n, bufs);
  checkError("glDrawBuffers");
} 

//! glColorMask wrapper. May throw.
inline void 
colorMask(GLboolean const r, 
          GLboolean const g, 
          GLboolean const b, 
          GLboolean const a) {
  glColorMask(r, g, b, a);
  checkError("glColorMask");
}

//! glColorMaski wrapper. May throw.
inline void 
colorMaski(GLuint const buf, 
           GLboolean const r, 
           GLboolean const g, 
           GLboolean const b, 
           GLboolean const a) {
  glColorMaski(buf, r, g, b, a);
  checkError("glColorMaski"); 
}

//! glDepthMask wrapper. May throw.
inline void 
depthMask(GLboolean const mask) {
  glDepthMask(mask);
  checkError("glColorMask");
}

//! glStencilMask wrapper. May throw.
inline void 
stencilMask(GLuint const mask) {
  glStencilMask(mask);
  checkError("glStencilMask");
}

//! glStencilMaskSeparate wrapper. May throw.
inline void 
stencilMaskSeparate(GLenum const face, GLuint const mask) {
  glStencilMaskSeparate(face, mask);
  checkError("glStencilMaskSeparate");
}

//! glClear wrapper. May throw.
inline void 
clear(GLbitfield const buf) {
  glClear(buf);
  checkError("glClear");        
}

//! glClearColor wrapper. May throw.
inline void 
clearColor(GLclampf const r, 
           GLclampf const g, 
           GLclampf const b, 
           GLclampf const a) {
  glClearColor(r, g, b, a);
  checkError("glClearColor");
}

//! glClearDepth wrapper. May throw.
inline void 
clearDepth(GLclampd const d) {
  glClearDepth(d);
  checkError("glClearDepth");
}

//! glClearDepthf wrapper. May throw. 
inline void 
clearDepthf(GLclampf const d) {
  glClearDepthf(d);
  checkError("glClearDepthf");
}

//! glClearStencil wrapper. May throw.
inline void 
clearStencil(GLint const s) {
  glClearStencil(s);
  checkError("glClearStencil");
}

//! glClearBufferiv wrapper. May throw.
inline void 
clearBufferiv(GLenum const buf, GLint const drawbuffer, GLint const* value) {
  glClearBufferiv(buf, drawbuffer, value);
  checkError("glClearBufferiv"); // May throw.        
}

//! glClearBufferfv wrapper. May throw.
inline void 
clearBufferfv(GLenum const buf, GLint const drawbuffer, GLfloat const* value) {
  glClearBufferfv(buf, drawbuffer, value);
  checkError("glClearBufferfv"); // May throw.        
}

//! glClearBufferuiv wrapper. May throw.
inline void 
clearBufferuiv(GLenum const buf, GLint const drawbuffer, GLuint const* value) {
  glClearBufferuiv(buf, drawbuffer, value);
  checkError("glClearBufferuiv"); // May throw.        
}

//! glClearBufferfi wrapper. May throw.
inline void 
clearBufferfi(GLenum const buf, 
              GLint const drawbuffer, 
              GLfloat const depth, 
              GLint const stencil) {
  glClearBufferfi(buf, drawbuffer, depth, stencil);
  checkError("glClearBufferfi"); // May throw.
}

// -----------------------------------------------------------------------------
// Rasterization

inline void
lineWidth(GLfloat const width) {
  glLineWidth(width);
  checkError("glLineWidth");
}

// -----------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif // NDJINN_VERTEX_ARRAY_HPP_INCLUDED
