//------------------------------------------------------------------------------
//
// Contributors:
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_VERTEX_ARRAY_ATTRIB_ENABLER_HPP_INCLUDED
#define NDJINN_VERTEX_ARRAY_ATTRIB_ENABLER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"

NDJINN_BEGIN_NAMESPACE

//! glEnableVertexAttribArray wrapper. May throw.
inline void enableVertexAttribArray(GLuint const index) {
  glEnableVertexAttribArray(index);
  checkError("glEnableVertexAttribArray");
}

//! glDisableVertexAttribArray wrapper. May throw.
inline void disableVertexAttribArray(GLuint const index) {
  glDisableVertexAttribArray(index);
  checkError("glDisableVertexAttribArray");
}


//! DOCS
class VertexAttribArrayEnabler {
public:
  explicit VertexAttribArrayEnabler(GLuint const index)
    : _index(index)
  {
    enableVertexAttribArray(_index);
  }

  ~VertexAttribArrayEnabler() {
    disableVertexAttribArray(_index);
  }

private:
  //! Disabled copy.
  VertexAttribArrayEnabler(VertexAttribArrayEnabler const&);
  //! Disabled assign.
  VertexAttribArrayEnabler& operator=(VertexAttribArrayEnabler const&);

  GLuint const _index;
};

NDJINN_END_NAMESPACE

#endif // NDJINN_VERTEX_ARRAY_ATTRIB_ENABLER_HPP_INCLUDED
