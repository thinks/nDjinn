//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_UNITCUBE_HPP_INCLUDED
#define NDJINN_UNITCUBE_HPP_INCLUDED

#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

class UnitCube {
public:
  //! Returns an array of 8 vertices.
  template <typename V> static /*constexpr*/
  V const* vertices() {
    static V const v[] = {
      V(1),  V(1),  V(1),
      V(-1), V(1),  V(1),
      V(-1), V(-1), V(1),
      V(1),  V(-1), V(1),
      V(1),  V(-1), V(-1),
      V(-1), V(-1), V(-1),
      V(-1), V(1),  V(-1),
      V(1),  V(1),  V(-1)
    };
    return v;
  }

  //! Returns an array of 8 3D texture coordinates.
  template <typename T> static /*constexpr*/
  T const* texture3() {
    static T const t[] = {
      T(1), T(1), T(1),
      T(0), T(1), T(1),
      T(0), T(0), T(1),
      T(1), T(0), T(1),
      T(1), T(0), T(0),
      T(0), T(0), T(0),
      T(0), T(1), T(0),
      T(1), T(1), T(0)
    };
    return t;
  }

  //! Returns an array of 3 * 12 triangle indices.
  template <typename I> static /*constexpr*/
  I const* indices() {
    static I const i[] = {
      0, 2, 1,
      0, 3, 2,
      1, 2, 6,
      6, 5, 1,
      4, 5, 6,
      6, 7, 4,
      2, 3, 6,
      6, 3, 7,
      0, 7, 3,
      0, 4, 7,
      0, 1, 5,
      0, 5, 4
    };
    return i;
  }
};

NDJINN_END_NAMESPACE

#endif // NDJINN_UNITCUBE_HPP_INCLUDED
