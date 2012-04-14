//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_ERROR_HPP_INCLUDED
#define NDJ_ERROR_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnException.hpp"
#include <gl/glew.h>
#include <sstream>
#include <string>

//------------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

class Error
{
public:

    //! Throws if one or more errors are found.
    static void
    check(const std::string &caller = std::string())
    {
        std::stringstream ss;
        GLenum err = _getError();      // May throw.
        while (_isError(err)) {
            ss << _errorString(err) << " ";
            err = _getError();         // May throw!?
        }

        const std::string errStr = ss.str();
        if (!errStr.empty()) {
            NDJINN_THROW(
                "OpenGL error(s): " 
                << (caller.empty() ? "" : (caller + ": "))
                << errStr);
        }
    }

private:

    //! Convert OpenGL error type into a string.
    static std::string
    _errorString(const GLenum err)
    {
        switch (err) {
        case 0:                    return std::string(); // No error - empty.
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


    //! Returns true if the provided OpenGL error type is actually an error.
    static bool
    _isError(const GLenum err)
    { return (err != GL_NO_ERROR); }


    //! Get error type from OpenGL.
    static GLenum
    _getError()
    { 
        const GLenum err = glGetError();    // TODO: Caused an error?
        return err; 
    }
};

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif  // NDJ_ERROR_HPP_INCLUDED
