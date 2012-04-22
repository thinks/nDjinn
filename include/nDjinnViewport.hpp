//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_VIEWPORT_HPP_INCLUDED
#define NDJ_VIEWPORT_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include "nDjinnState.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

//! DOCS
class Viewport
{
public:

    //! Call glDepthRange wrapper. May throw.
    static void 
    setDepthRange(const GLclampd n, const GLclampd f)
    { _depthRange(n, f); } // May throw.

    //! Call glViewport wrapper. May throw.
    static void 
    setViewport(const GLint x, const GLint y, const GLsizei w, const GLsizei h)
    { _viewport(x, y, w, h); } // May throw.

public:

    //! Query depth range. May throw.
    static void
    getDepthRange(GLdouble dr[2])
    { State::getDoublev(GL_DEPTH_RANGE, dr); } // May throw.

    //! Query viewport dimensions. May throw.
    static void
    getViewport(GLint vp[4])
    { State::getIntegerv(GL_VIEWPORT, vp); } // May throw.

private:    // Controlling Viewport.

    // TODO
    //static void 
    //_depth_range_array_v(const GLuint first, const GLsizei count, 
    //                     const GLclampd *v)
    //{}

    // TODO
    //static void 
    //_depth_range_indexed(const GLuint index, const GLclampd n, const GLclampd f)
    //{}

    //! glDepthRange wrapper. May throw.
    static void 
    _depthRange(const GLclampd n, const GLclampd f)
    {
        glDepthRange(n, f);
        Error::check("glDepthRange"); // May throw.
    }

    // TODO
    //static void 
    //_depth_range_f(const GLclampf n, const GLclampd f)
    //{}

    // TODO
    //static void 
    //_viewport_array_v(const GLuint first, const GLsizei count, const GLfloat *v)
    //{}

    // TODO
    //static void 
    //_viewport_indexed_f(const GLuint index, const GLfloat x, const GLfloat y, 
    //                    const GLfloat w, const GLfloat h)
    //{}

    // TODO
    //static void 
    //_viewport_indexed_fv(const GLuint index, const GLfloat *v)
    //{}

    //! glViewport wrapper. May throw.
    static void 
    _viewport(const GLint x, const GLint y, const GLsizei w, const GLsizei h)
    {
        glViewport(x, y, w, h);
        Error::check("glViewport"); // May throw.
    }
};

// -----------------------------------------------------------------------------

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif  // NDJ_VIEWPORT_HPP_INCLUDED
