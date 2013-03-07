// -----------------------------------------------------------------------------
//
// Copyright (C) Tommy Hinks              
// tommy[dot]hinks[at]gmail[dot]com                       
//
// Contributors: 
//             1) Tommy Hinks
//
// -----------------------------------------------------------------------------

#ifndef NDJINN_BLEND_HPP_INCLUDED
#define NDJINN_BLEND_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

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

NDJINN_END_NAMESPACE

#endif // NDJINN_BLEND_HPP_INCLUDED
