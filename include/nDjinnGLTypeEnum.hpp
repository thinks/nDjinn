//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_GLTYPEENUM_HPP_INCLUDED
#define NDJINN_GLTYPEENUM_HPP_INCLUDED

#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

//! Generic.
template <class T>
struct GLTypeEnum;

//! Specialization.
template<>
struct GLTypeEnum<GLfloat> {
  static GLenum const value = GL_FLOAT;
};

//! Specialization.
template<>
struct GLTypeEnum<GLuint> {
  static GLenum const value = GL_UNSIGNED_INT;
};

//! Specialization.
template<>
struct GLTypeEnum<GLushort> {
  static GLenum const value = GL_UNSIGNED_SHORT;
};

NDJINN_END_NAMESPACE

#endif // NDJINN_GLTYPEENUM_HPP_INCLUDED
