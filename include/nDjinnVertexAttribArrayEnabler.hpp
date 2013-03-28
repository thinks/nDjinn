// -----------------------------------------------------------------------------
//
// Copyright (C) Tommy Hinks              
// tommy[dot]hinks[at]gmail[dot]com                       
//
// Contributors: 
//             1) Tommy Hinks
//
// -----------------------------------------------------------------------------

#ifndef NDJINN_VERTEX_ARRAY_ATTRIB_ENABLER_HPP_INCLUDED
#define NDJINN_VERTEX_ARRAY_ATTRIB_ENABLER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnFunctions.hpp"

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

//! DOCS
class VertexAttribArrayEnabler {
public:
  explicit
  VertexAttribArrayEnabler(GLuint const index) 
    : _index(index) {
    enableVertexAttribArray(_index);
  }

  ~VertexAttribArrayEnabler() {
    disableVertexAttribArray(_index);
  }

private: // Member variables.
  GLuint const _index;
};

// -----------------------------------------------------------------------------

NDJINN_END_NAMESPACE

#endif // NDJINN_VERTEX_ARRAY_ATTRIB_ENABLER_HPP_INCLUDED
