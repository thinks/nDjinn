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
T innerProduct(const T u[N], const T v[N]) {
  T sum = 0;
  for (std::size_t i = 0; i < N; ++i) {
      sum += u[i] * v[i];
  }
  return sum;
}



NDJINN_END_NAMESPACE

#endif // NDJINN_ALGEBRA_HPP_INCLUDED
