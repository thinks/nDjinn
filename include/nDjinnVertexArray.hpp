//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_VERTEXARRAY_HPP_INCLUDED
#define NDJINN_VERTEXARRAY_HPP_INCLUDED

#include <iostream>

#include "nDjinnError.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! glGenVertexArrays wrapper. May throw.
inline void genVertexArrays(GLsizei const n, GLuint *vertexArrays) {
  glGenVertexArrays(n, vertexArrays);
  checkError("glGenVertexArrays");
}

//! glDeleteVertexArrays wrapper. May throw.
inline void deleteVertexArrays(GLsizei const n, const GLuint *vertexArrays) {
  glDeleteVertexArrays(n, vertexArrays);
  checkError("glDeleteVertexArrays");
}

//! glIsArray wrapper. May throw.
inline GLboolean isVertexArray(GLuint const vertexArray) {
  GLboolean const isVertexArray = glIsVertexArray(vertexArray);
  checkError("glIsVertexArray");
  return isVertexArray;
}

//! glBindVertexArray wrapper. May throw.
inline void bindVertexArray(GLuint const vertexArray) {
  glBindVertexArray(vertexArray);
  checkError("glBindVertexArray");
}

//! Convenience.
inline GLuint genVertexArray() {
  GLuint handle = 0;
  genVertexArrays(1, &handle);
  return handle;
}

//! Convenience.
inline void deleteVertexArray(GLuint const handle) {
  deleteVertexArrays(1, &handle);
}

} // Namespace: detail

//! DOCS
class VertexArray {
public:
  VertexArray()
    : _handle(detail::genVertexArray())
  {
    if (detail::isVertexArray(_handle) == GL_FALSE) {
      NDJINN_THROW("invalid vertex array handle: " << _handle);
    }
  }

  ~VertexArray() {
    detail::deleteVertexArray(_handle);
  }

  GLuint handle() const {
    return _handle;
  }

  void bind() const {
    detail::bindVertexArray(_handle);
  }

  void release() const {
    detail::bindVertexArray(0);
  }

private: // Member variables.
  VertexArray(VertexArray const&); //!< Disabled copy.
  VertexArray& operator=(VertexArray const&); //!< Disabled assign.

  GLuint const _handle;
};

NDJINN_END_NAMESPACE

namespace std {

inline
ostream& operator<<(ostream& os, ndj::VertexArray const& va)
{
  os << "VertexArray" << endl
     << "  Handle: " << va.handle() << endl;
  return os;
}

} // namespace std

#endif // NDJINN_VERTEXARRAY_HPP_INCLUDED
