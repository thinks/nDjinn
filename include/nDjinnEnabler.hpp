//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_ENABLER_HPP_INCLUDED
#define NDJINN_ENABLER_HPP_INCLUDED

#include "nDjinnFunctions.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

class Enabler {
public:
  explicit Enabler(GLenum const flag)
    : _flag(flag)
  {
    enable(_flag);
  }

  ~Enabler() {
    disable(_flag);
  }

private:
  Enabler(Enabler const&); //!< Disabled copy.
  Enabler& operator=(Enabler const&); //!< Disabled assign.

  GLenum const _flag;
};

NDJINN_END_NAMESPACE

#endif // NDJINN_ENABLER_HPP_INCLUDED
