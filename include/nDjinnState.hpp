//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_STATE_HPP_INCLUDED
#define NDJ_STATE_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

//! DOCS
class State
{
public:

    static void
    enable(const GLenum cap)
    { _enable(cap); } // May throw.

    static void
    disable(const GLenum cap)
    { _disable(cap); } // May throw.

public:

    static void
    getBoolean(const GLenum pname, GLboolean *data)
    { _getBoolean_v(pname, data); } // May throw.

    static void
    getInteger(const GLenum pname, GLint *data)
    { _getInteger_v(pname, data); } // May throw.

    static void
    getInteger64(const GLenum pname, GLint64 *data)
    { _getInteger64_v(pname, data); } // May throw.

    static void
    getFloat(const GLenum pname, GLfloat *data)
    { _getFloat_v(pname, data); } // May throw.

    static void
    getDouble(const GLenum pname, GLdouble *data)
    { _getDouble_v(pname, data); } // May throw.

    static GLboolean
    isEnabled(const GLenum cap)
    { _isEnabled(cap); } // May throw.

public:

    static const GLubyte*
    getString(const GLenum name)
    { return _getString(name); } // May throw.

// ------------------------------------

private:    // Enable/Disable.

    // glEnable wrapper. May throw.
    static void
    _enable(const GLenum cap)
    {
        glEnable(cap);
        Error::check("glEnable");
    }

    // glDisable wrapper. May throw.
    static void
    _disable(const GLenum cap)
    {
        glDisable(cap);
        Error::check("glDisable");
    }

private:    // Simple Queries.

    //! glGetBooleanv wrapper. May throw.
    static void
    _getBooleanv(const GLenum pname, GLboolean *data)
    {
        glGetBooleanv(pname, data);
        Error::check("glGetBooleanv"); // May throw.
    }

    //! glGetIntegerv wrapper. May throw.
    static void
    _getIntegerv(const GLenum pname, GLint *data)
    {
        glGetIntegerv(pname, data);
        Error::check("glGetIntegerv"); // May throw.
    }

    //! glGetInteger64v wrapper. May throw.
    static void
    _getInteger64v(const GLenum pname, GLint64 *data)
    {
        glGetInteger64v(pname, data);
        Error::check("glGetInteger64v"); // May throw.
    }

    //! glGetFloatv wrapper. May throw.
    static void
    _getFloatv(const GLenum pname, GLfloat *data)
    {
        glGetFloatv(pname, data);
        Error::check("glGetFloatv"); // May throw.
    }

    //! glGetDoublev wrapper. May throw.
    static void
    _getDoublev(const GLenum pname, GLdouble *data)
    {
        glGetDoublev(pname, data);
        Error::check("glGetDoublev"); // May throw.
    }

    // TODO: glGetBooleani_v
    // TODO: glGetIntegeri_v
    // TODO: glGetFloati_v
    // TODO: glGetInteger64i_v
    
    //! glIsEnabled wrapper. May throw.
    static GLboolean
    _isEnabled(const GLenum cap)
    {
        const GLboolean enabled = glIsEnabled(cap);
        Error::check("glIsEnabled"); // May throw.
        return enabled;
    }

    // TODO: glIsEnabledi

private:    // Pointer & String Queries.

    //! glGetString wrapper. May throw.
    static const GLubyte*
    _getString(const GLenum name)
    {
        const GLubyte *str = glGetString(name);
        Error::check("glGetString");
        return str;
    }

    // TODO: glGetStringi

private:    // Disable all kinds of construction.

    State();                        //! Disable empty CTOR.
    ~State();                       //! Disable DTOR.
    State(const State&);            //! Disable copy.
    State& operator=(const State&); //! Disabled assignment.
};

// -----------------------------------------------------------------------------

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif // NDJ_STATE_HPP_INCLUDED
