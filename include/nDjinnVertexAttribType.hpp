//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_VERTEX_ATTRIB_TYPE_HPP_INCLUDED
#define NDJINN_VERTEX_ATTRIB_TYPE_HPP_INCLUDED

#include "nDjinnGL.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

//! Generic.
template <class T>
struct VertexAttribType;

//! Specialization.
template <>
struct VertexAttribType<GLfloat> {
  static GLenum const VALUE = GL_FLOAT;
};

NDJINN_END_NAMESPACE

#endif // NDJINN_VERTEX_ATTRIB_TYPE_HPP_INCLUDED
