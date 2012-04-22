//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_STATE_HPP_INCLUDED
#define NDJINN_STATE_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

//! DOCS
class State
{
public:     // Enable/Disable.

    static void
    enable(GLenum cap);

    static void
    disable(GLenum cap);

public:     // Simple Queries.

    static void
    getBooleanv(GLenum pname, GLboolean *data);

    static void
    getIntegerv(GLenum pname, GLint *data);

    static void
    getInteger64v(GLenum pname, GLint64 *data);

    static void
    getFloatv(GLenum pname, GLfloat *data);

    static void
    getDoublev(GLenum pname, GLdouble *data);

    static GLboolean
    isEnabled(GLenum cap);

    // TODO: glGetBooleani_v
    // TODO: glGetIntegeri_v
    // TODO: glGetFloati_v
    // TODO: glGetInteger64i_v
    // TODO: glIsEnabledi

public:     // Pointer & String Queries.

    static const GLubyte*
    getString(GLenum name);

    // TODO: glGetStringi

private:    // Disable all kinds of construction.

    State();                        //! Disable empty CTOR.
    ~State();                       //! Disable DTOR.
    State(const State&);            //! Disable copy.
    State& operator=(const State&); //! Disabled assignment.
};

// -----------------------------------------------------------------------------

// glEnable wrapper. May throw. [static]
inline void
State::enable(const GLenum cap)
{
    glEnable(cap);
    Error::check("glEnable");
}


// glDisable wrapper. May throw. [static]
inline void
State::disable(const GLenum cap)
{
    glDisable(cap);
    Error::check("glDisable");
}

// -----------------------------------------------------------------------------

//! glGetBooleanv wrapper. May throw. [static]
inline void
State::getBooleanv(const GLenum pname, GLboolean *data)
{
    glGetBooleanv(pname, data);
    Error::check("glGetBooleanv"); // May throw.
}


//! glGetIntegerv wrapper. May throw. [static]
inline void
State::getIntegerv(const GLenum pname, GLint *data)
{
    glGetIntegerv(pname, data);
    Error::check("glGetIntegerv"); // May throw.
}


//! glGetInteger64v wrapper. May throw. [static]
inline void
State::getInteger64v(const GLenum pname, GLint64 *data)
{
    glGetInteger64v(pname, data);
    Error::check("glGetInteger64v"); // May throw.
}


//! glGetFloatv wrapper. May throw. [static]
inline void
State::getFloatv(const GLenum pname, GLfloat *data)
{
    glGetFloatv(pname, data);
    Error::check("glGetFloatv"); // May throw.
}


//! glGetDoublev wrapper. May throw. [static]
inline void
State::getDoublev(const GLenum pname, GLdouble *data)
{
    glGetDoublev(pname, data);
    Error::check("glGetDoublev"); // May throw.
}


//! glIsEnabled wrapper. May throw. [static]
inline GLboolean
State::isEnabled(const GLenum cap)
{
    const GLboolean enabled = glIsEnabled(cap);
    Error::check("glIsEnabled"); // May throw.
    return enabled;
}

// -----------------------------------------------------------------------------

//! glGetString wrapper. May throw. [static]
inline const GLubyte*
State::getString(const GLenum name)
{
    const GLubyte *str = glGetString(name);
    Error::check("glGetString");
    return str;
}

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif // NDJINN_STATE_HPP_INCLUDED
