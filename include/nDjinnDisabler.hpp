//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_DISABLER_HPP_INCLUDED
#define NDJINN_DISABLER_HPP_INCLUDED

#include "nDjinnFunctions.hpp"
#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

class Disabler {
public:
  explicit Disabler(GLenum const flag)
    : _flag(flag)
  {
    disable(_flag);
  }

  ~Disabler() {
    enable(_flag);
  }

private:
  Disabler(Disabler const&); //!< Disabled copy.
  Disabler& operator=(Disabler const&); //!< Disabled assign.

  GLenum const _flag;
};

NDJINN_END_NAMESPACE

#endif // NDJINN_DISABLER_HPP_INCLUDED
