//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_ERROR_HPP_INCLUDED
#define NDJINN_ERROR_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include <gl/glew.h>
#include <sstream>
#include <string>

//------------------------------------------------------------------------------

NDJINN_BEGIN_NAMESPACE

namespace detail {

//! Convert OpenGL error type into a string.
inline std::string
errorString(const GLenum err) {
  switch (err) {
  //case 0:                    return std::string(); // No error - empty.
  case GL_NO_ERROR:          return std::string("GL_NO_ERROR"); 
  case GL_INVALID_ENUM:      return std::string("GL_INVALID_ENUM");
  case GL_INVALID_VALUE:     return std::string("GL_INVALID_VALUE");
  case GL_INVALID_OPERATION: return std::string("GL_INVALID_OPERATION");
  case GL_STACK_OVERFLOW:    return std::string("GL_STACK_OVERFLOW");
  case GL_STACK_UNDERFLOW:   return std::string("GL_STACK_UNDERFLOW");
  case GL_OUT_OF_MEMORY:     return std::string("GL_OUT_OF_MEMORY");
  case GL_TABLE_TOO_LARGE:   return std::string("GL_TABLE_TOO_LARGE");
  default:                   return std::string("UNKNOWN GL_ERROR");
  }
}

//! Returns true if the provided OpenGL error type is actually an 
//! error.
inline bool
isError(const GLenum err) { 
  return (err != GL_NO_ERROR); 
}

//! Get error type from OpenGL.
inline GLenum
getError() { 
  const GLenum err = glGetError(); // TODO: Caused an error?
  return err; 
}

} // Namespace: detail.

//------------------------------------------------------------------------------

//! Throws if one or more errors are found.
inline void
checkError(const std::string &caller)
{
  std::stringstream ss;
  GLenum err = detail::getError();      // May throw.
  while (detail::isError(err)) {
    ss << detail::errorString(err) << " ";
    err = detail::getError();         // May throw!?
  }

  const std::string errStr = ss.str();
  if (!errStr.empty()) {
    NDJINN_THROW(
      "OpenGL error(s): " 
      << (caller.empty() ? "" : (caller + ": "))
      << errStr);
  }
}

NDJINN_END_NAMESPACE

#endif  // NDJINN_ERROR_HPP_INCLUDED
