//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_EXCEPTION_HPP_INCLUDED
#define NDJINN_EXCEPTION_HPP_INCLUDED

#include <exception>
#include <sstream>
#include <string>

#include "nDjinnNamespace.hpp"

// Useful macro for throwing.
#define NDJINN_THROW(MSG) \
{std::stringstream ss; ss << "nDjinn: "; ss << MSG; throw ndj::Exception(ss.str());}

NDJINN_BEGIN_NAMESPACE

class Exception {
public:
  //! CTOR.
  explicit Exception(std::string const& msg)
      : _msg(msg) {
  }

  //! Exception message.
  virtual char const* what() const {
    return _msg.c_str(); 
  }

private: // Member variables.
  std::string _msg;
};

NDJINN_END_NAMESPACE

#endif	// NDJINN_EXCEPTION_HPP_INCLUDED
