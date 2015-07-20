//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_ALGEBRA_HPP_INCLUDED
#define NDJINN_ALGEBRA_HPP_INCLUDED

#include <cstddef>

#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

//! Dot product.
template<typename T, std::size_t N> inline
T innerProduct(T const u[N], T const v[N]) {
  T sum = 0;
  for (std::size_t i = 0; i < N; ++i) {
      sum += u[i] * v[i];
  }
  return sum;
}

//! Cross product.
template<typename T> inline
void crossProduct(T const u[3], T const v[3], T w[3]) {
  w[0] = u[1] * v[2] - u[2] * v[1];
  w[1] = u[2] * v[0] - u[0] * v[2];
  w[2] = u[0] * v[1] - u[1] * v[0];
}

NDJINN_END_NAMESPACE

#endif // NDJINN_ALGEBRA_HPP_INCLUDED
