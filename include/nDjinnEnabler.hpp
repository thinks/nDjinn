// -----------------------------------------------------------------------------
//
// Copyright (C) Tommy Hinks              
// tommy[dot]hinks[at]gmail[dot]com                       
//
// Contributors: 
//             1) Tommy Hinks
//
// -----------------------------------------------------------------------------

#ifndef NDJINN_ENABLER_HPP_INCLUDED
#define NDJINN_ENABLER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnFunctions.hpp"

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

//! DOCS
class Enabler {
public:
  explicit
  Enabler(GLenum const flag) 
    : _flag(flag) {
    enable(_flag);
  }

  ~Enabler() {
    disable(_flag);
  }

private: // Member variables.
  GLenum const _flag;
};

// -----------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif // NDJINN_ENABLER_HPP_INCLUDED
