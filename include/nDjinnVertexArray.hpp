//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_VERTEX_ARRAY_HPP_INCLUDED
#define NDJINN_VERTEX_ARRAY_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

inline void 
genVertexArrays(GLsizei const n, GLuint *vertexArrays) {
  glGenVertexArrays(n, vertexArrays);
  checkError("glGenVertexArrays");
}

inline void 
deleteVertexArrays(GLsizei const n, const GLuint *vertexArrays) {
  glDeleteVertexArrays(n, vertexArrays);
  checkError("glDeleteVertexArrays");
}

inline void 
bindVertexArray(GLuint const vertexArray) {
  glBindVertexArray(vertexArray);
  checkError("glBindVertexArray");
}

inline GLboolean 
isVertexArray(GLuint const vertexArray) {
  GLboolean const isVertexArray = glIsVertexArray(vertexArray);
  checkError("glIsVertexArray");
  return isVertexArray;
}

//! Convenience, generate a single buffer handle and return it. May throw.
inline GLuint
genVertexArray() {
  GLuint handle = 0;
  genVertexArrays(1, &handle);
  return handle;
}

//! Convenience.
inline void 
deleteVertexArray(GLuint const handle) {
  deleteVertexArrays(1, &handle);
}

} // Namespace: detail

// -----------------------------------------------------------------------------

//! DOCS
class VertexArray {
public:
  explicit 
  VertexArray();

  ~VertexArray();

public:
  GLuint 
  handle() const;  

  void 
  bind() const;

  void 
  release() const;

private: // Member variables.
  GLuint const _handle;
};

// -----------------------------------------------------------------------------

inline
VertexArray::VertexArray()
  : _handle(detail::genVertexArray()) // May throw. 
{
  bind(); // Make sure vertex array gets created.
  if (detail::isVertexArray(_handle) == GL_FALSE) {
    NDJINN_THROW("invalid vertex array");
  }
  release();
}

inline
VertexArray::~VertexArray() { 
  detail::deleteVertexArray(_handle); 
}

// -----------------------------------------------------------------------------

inline void 
VertexArray::bind() const {
  detail::bindVertexArray(_handle);
}

inline void 
VertexArray::release() const {
  detail::bindVertexArray(0);
}

// -----------------------------------------------------------------------------

//! DOCS
class VertexArrayBindor {
public:
  explicit
  VertexArrayBindor(VertexArray const& array) 
    : _array(array) {
    _array.bind();
  }

  ~VertexArrayBindor() {
    _array.release();
  }

private: // Member variables.
  VertexArray const& _array;
};

// -----------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif // NDJINN_VERTEX_ARRAY_HPP_INCLUDED
