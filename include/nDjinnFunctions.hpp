//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_FUNCTIONS_HPP_INCLUDED
#define NDJINN_FUNCTIONS_HPP_INCLUDED

#include <array>

#include "nDjinnError.hpp"
#include "nDjinnGL.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

// Blending

//! glBlendEquation wrapper. May throw.
inline void blendEquation(GLenum const mode)
{
  glBlendEquation(mode);
  checkError("glBlendEquation");
}

//! glBlendEquationi wrapper. May throw.
inline void blendEquationi(GLuint const buf, GLenum const mode) {
  glBlendEquationi(buf, mode);
  checkError("glBlendEquationi");
}

//! glBlendEquationSeparate wrapper. May throw.
inline void blendEquationSeparate(GLenum const mode_rgb,
                                  GLenum const mode_alpha)
{
  glBlendEquationSeparate(mode_rgb, mode_alpha);
  checkError("glBlendEquationSeparate");
}

//! glBlendEquationSeparatei wrapper. May throw.
inline void blendEquationSeparatei(GLuint const buf, GLenum const mode_rgb,
                                   GLenum const mode_alpha)
{
  glBlendEquationSeparatei(buf, mode_rgb, mode_alpha);
  checkError("glBlendEquationSeparatei");
}

//! glBlendFunc wrapper. May throw.
inline void blendFunc(GLenum const src, GLenum const dst) {
  glBlendFunc(src, dst);
  checkError("glBlendFunc");
}

//! glBlendFunci wrapper. May throw.
inline void blendFunci(GLuint const buf, GLenum const src, GLenum const dst) {
  glBlendFunci(buf, src, dst);
  checkError("glBlendFunci");
}

//! glBlendFuncSeparate wrapper. May throw.
inline void blendFuncSeparate(GLenum const srcRgb,
                              GLenum const dstRgb,
                              GLenum const srcAlpha,
                              GLenum const dstAlpha) {
  glBlendFuncSeparate(srcRgb, dstRgb, srcAlpha, dstAlpha);
  checkError("glBlendFuncSeparate");
}

//! glBlendFuncSeparatei wrapper. May throw.
inline void blendFuncSeparatei(GLuint const buf,
                               GLenum const srcRgb,
                               GLenum const dstRgb,
                               GLenum const srcAlpha,
                               GLenum const dstAlpha) {
  glBlendFuncSeparatei(buf, srcRgb, dstRgb, srcAlpha, dstAlpha);
  checkError("glBlendFuncSeparatei");
}

//! glBlendColor wrapper. May throw.
inline void blendColor(GLclampf const red,
                       GLclampf const green,
                       GLclampf const blue,
                       GLclampf const alpha) {
  glBlendColor(red, green, blue, alpha);
  checkError("glBlendColor");
}

// State

//! glEnable wrapper. May throw.
inline void enable(GLenum const cap)
{
  glEnable(cap);
  checkError("glEnable");
}

//! glDisable wrapper. May throw.
inline void disable(GLenum const cap)
{
  glDisable(cap);
  checkError("glDisable");
}

//! glGetBooleanv wrapper. May throw.
inline void getBooleanv(GLenum const pname, GLboolean* data) {
  glGetBooleanv(pname, data);
  checkError("glGetBooleanv");
}

//! glGetIntegerv wrapper. May throw. 
inline void getIntegerv(GLenum const pname, GLint* data)
{
  glGetIntegerv(pname, data);
  checkError("glGetIntegerv");
}

//! Convenience.
inline GLint getInteger(GLenum const pname)
{
  GLint param = 0;
  getIntegerv(pname, &param);
  return param;
}

//! Convenience.
template <std::size_t N>
inline std::array<GLint, N> getIntegers(GLenum const pname)
{
  std::array<GLint, N> params;
  getIntegerv(pname, params.data());
  return params;
}

//! glGetInteger64v wrapper. May throw.
inline void getInteger64v(GLenum const pname, GLint64* data) {
  glGetInteger64v(pname, data);
  checkError("glGetInteger64v");
}

//! glGetFloatv wrapper. May throw. 
inline void getFloatv(GLenum const pname, GLfloat* data) {
  glGetFloatv(pname, data);
  checkError("glGetFloatv");
}

//! glGetDoublev wrapper. May throw.
inline void getDoublev(GLenum const pname, GLdouble* data) {
  glGetDoublev(pname, data);
  checkError("glGetDoublev");
}

//! glIsEnabled wrapper. May throw. 
inline GLboolean isEnabled(GLenum const cap) {
  const GLboolean enabled = glIsEnabled(cap);
  checkError("glIsEnabled");
  return enabled;
}

//! glGetString wrapper. May throw.
inline const GLubyte* getString(GLenum const name) {
  GLubyte const* str = glGetString(name);
  checkError("glGetString");
  return str;
}

// Vertex specification

//! glVertexAttribPointer wrapper. May throw.
inline void vertexAttribPointer(GLuint const index,
                                GLint const size,
                                GLenum const type,
                                GLboolean const normalized,
                                GLsizei const stride,
                                GLvoid const* pointer) {
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  checkError("glVertexAttribPointer");
}

//! glVertexAttribIPointer wrapper. May throw.
inline void vertexAttribIPointer(GLuint const index,
                                 GLint const size,
                                 GLenum const type,
                                 GLsizei const stride,
                                 GLvoid const* pointer) {
  glVertexAttribIPointer(index, size, type, stride, pointer);
  checkError("glVertexAttribIPointer");
}

//! glVertexAttribLPointer wrapper. May throw.
inline void vertexAttribLPointer(GLuint const index,
                                 GLint const size,
                                 GLenum const type,
                                 GLsizei const stride,
                                 GLvoid const* pointer) {
  glVertexAttribLPointer(index, size, type, stride, pointer);
  checkError("glVertexAttribLPointer");
}

//! glVertexAttribDivisor wrapper. May throw.
inline void vertexAttribDivisor(GLuint const index, GLuint const divisor) {
  glVertexAttribDivisor(index, divisor);
  checkError("glVertexAttribDivisor");
}

//! glDrawRangeElements wrapper. May throw.
inline void drawRangeElements(GLenum const mode,
                              GLuint const start,
                              GLuint const end,
                              GLsizei const count,
                              GLenum const type,
                              GLvoid const* indices) {
  glDrawRangeElements(mode, start, end, count, type, indices);
  checkError("glDrawRangeElements");
}

// Viewport

//! glDepthRange wrapper. May throw.
inline void depthRange(GLclampd const n, GLclampd const f) {
  glDepthRange(n, f);
  checkError("glDepthRange");
}

//! glViewport wrapper. May throw.
inline void viewport(GLint const x,
                     GLint const y,
                     GLsizei const w,
                     GLsizei const h) {
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

// Buffer

//! glDrawBuffer wrapper. May throw.
inline void drawBuffer(GLenum const buf)
{
  glDrawBuffer(buf);
  checkError("glDrawBuffer");
} 

//! glDrawBuffers wrapper. May throw.
inline void drawBuffers(GLsizei const n, GLenum const* bufs)
{
  glDrawBuffers(n, bufs);
  checkError("glDrawBuffers");
}

//! Convenience.
template <std::size_t N> inline
void drawBuffers(std::array<GLenum, N> const& bufs)
{
  drawBuffers(static_cast<GLsizei>(bufs.size()), bufs.data());
}

//! glColorMask wrapper. May throw.
inline void colorMask(GLboolean const r, 
                      GLboolean const g,
                      GLboolean const b,
                      GLboolean const a) {
  glColorMask(r, g, b, a);
  checkError("glColorMask");
}

//! glColorMaski wrapper. May throw.
inline void colorMaski(GLuint const buf, 
                       GLboolean const r,
                       GLboolean const g,
                       GLboolean const b,
                       GLboolean const a) {
  glColorMaski(buf, r, g, b, a);
  checkError("glColorMaski"); 
}

//! glDepthMask wrapper. May throw.
inline void depthMask(GLboolean const mask) {
  glDepthMask(mask);
  checkError("glColorMask");
}

//! glStencilMask wrapper. May throw.
inline void stencilMask(GLuint const mask) {
  glStencilMask(mask);
  checkError("glStencilMask");
}

//! glStencilMaskSeparate wrapper. May throw.
inline void stencilMaskSeparate(GLenum const face, GLuint const mask) {
  glStencilMaskSeparate(face, mask);
  checkError("glStencilMaskSeparate");
}

//! glClear wrapper. May throw.
inline void clear(GLbitfield const buf) {
  glClear(buf);
  checkError("glClear");        
}

//! glClearColor wrapper. May throw.
inline void clearColor(GLclampf const r, 
                       GLclampf const g,
                       GLclampf const b,
                       GLclampf const a) {
  glClearColor(r, g, b, a);
  checkError("glClearColor");
}

//! Convenience, set glClearColor from a 4-element array.
inline void clearColor(GLclampf const color[4]) {
  clearColor(color[0], color[1], color[2], color[3]);
}

//! glClearDepth wrapper. May throw.
inline void clearDepth(GLclampd const d) {
  glClearDepth(d);
  checkError("glClearDepth");
}

//! glClearDepthf wrapper. May throw. 
inline void clearDepthf(GLclampf const d) {
  glClearDepthf(d);
  checkError("glClearDepthf");
}

//! glClearStencil wrapper. May throw.
inline void clearStencil(GLint const s) {
  glClearStencil(s);
  checkError("glClearStencil");
}

//! glClearBufferiv wrapper. May throw.
inline void clearBufferiv(GLenum const buf,
                          GLint const drawbuffer,
                          GLint const* value) {
  glClearBufferiv(buf, drawbuffer, value);
  checkError("glClearBufferiv");
}

//! glClearBufferfv wrapper. May throw.
inline void clearBufferfv(GLenum const buf,
                          GLint const drawbuffer,
                          GLfloat const* value) {
  glClearBufferfv(buf, drawbuffer, value);
  checkError("glClearBufferfv");
}

//! glClearBufferuiv wrapper. May throw.
inline void clearBufferuiv(GLenum const buf,
                           GLint const drawbuffer,
                           GLuint const* value) {
  glClearBufferuiv(buf, drawbuffer, value);
  checkError("glClearBufferuiv");
}

//! glClearBufferfi wrapper. May throw.
inline void clearBufferfi(GLenum const buf, GLint const drawbuffer,
                          GLfloat const depth, GLint const stencil) {
  glClearBufferfi(buf, drawbuffer, depth, stencil);
  checkError("glClearBufferfi");
}

// Reading pixels

//! glReadPixels wrapper. May throw.
inline void readPixels(GLint const x, GLint const y, GLsizei const width,
                       GLsizei const height, GLenum const format,
                       GLenum const type, GLvoid* data)
{
  glReadPixels(x, y, width, height, format, type, data);
  checkError("glReadPixels");
}

//! glReadBuffer wrapper. May throw.
inline void readBuffer(GLenum const mode)
{
  glReadBuffer(mode);
  checkError("glReadBuffer");
}

#if 0 // Not in GLEW yet...
//! glNamedFramebufferReadBuffer. May throw.
inline void namedFramebufferReadBuffer(GLuint const framebuffer,
                                       GLenum const mode)
{
  glNamedFramebufferReadBufferEXT(framebuffer, mode);
  checkError("glNamedFramebufferReadBufferEXT");
}
#endif

// Rasterization

inline void lineWidth(GLfloat const width)
{
  glLineWidth(width);
  checkError("glLineWidth");
}

inline void cullFace(GLenum const mode)
{
  glCullFace(mode);
  checkError("glCullFace");
}

inline void frontFace(GLenum const mode)
{
  glFrontFace(mode);
  checkError("glFrontFace");
}

NDJINN_END_NAMESPACE

#endif // NDJINN_VERTEX_ARRAY_HPP_INCLUDED
