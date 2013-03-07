// -----------------------------------------------------------------------------
//
// Copyright (C) Tommy Hinks              
// tommy[dot]hinks[at]gmail[dot]com                       
//
// Contributors: 
//             1) Tommy Hinks
//
// -----------------------------------------------------------------------------

#ifndef NDJINN_VERTEX_HPP_INCLUDED
#define NDJINN_VERTEX_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

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

NDJINN_END_NAMESPACE

#endif // NDJINN_VERTEX_HPP_INCLUDED
