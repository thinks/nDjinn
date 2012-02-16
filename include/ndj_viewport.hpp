//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_VIEWPORT_HPP_INCLUDED
#define NDJ_VIEWPORT_HPP_INCLUDED

#include "ndj_error.hpp"
#include "ndj_state.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

namespace ndj {

// -----------------------------------------------------------------------------

//! DOCS
class viewport
{
public:

    //! Call glDepthRange wrapper. May throw.
    static void 
    set_depth_range(const GLclampd n, const GLclampd f)
    { _depth_range(n, f); } // May throw.

    //! Call glViewport wrapper. May throw.
    static void 
    set_viewport(const GLint x, const GLint y, const GLsizei w, const GLsizei h)
    { _viewport(x, y, w, h); } // May throw.

public:

    //! Query depth range. May throw.
    static void
    get_depth_range(GLdouble dr[2])
    { state::get_double(GL_DEPTH_RANGE, dr); } // May throw.

    //! Query viewport dimensions. May throw.
    static void
    get_viewport(GLint vp[4])
    { state::get_integer(GL_VIEWPORT, vp); } // May throw.

// ------------------------------------

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
    _depth_range(const GLclampd n, const GLclampd f)
    {
        glDepthRange(n, f);
        error::check("glDepthRange"); // May throw.
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
        error::check("glViewport"); // May throw.
    }
};

// -----------------------------------------------------------------------------

}   // Namespace: ndj.

// -----------------------------------------------------------------------------

#endif  // NDJ_VIEWPORT_HPP_INCLUDED
