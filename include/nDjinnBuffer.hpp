//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_BUFFER_HPP_INCLUDED
#define NDJ_BUFFER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

//! DOCS
class Buffer
{
public:

    //! Call glDrawBuffer wrapper. May throw.
    static void
    drawBuffer(const GLenum buf)
    { _drawBuffer(buf); } // May throw.

    //! Call glDrawBuffers wrapper. May throw.
    static void
    drawBuffers(const GLsizei n, const GLenum *buf)
    { _draw_buffers(n, buf); } // May throw.

public:

    //! Call glColorMask wrapper. May throw.
    static void 
    colorMask(const GLboolean r, const GLboolean g, 
              const GLboolean b, const GLboolean a)
    { _colorMask(r, g, b, a); } // May throw.

    //! Call glColorMaski wrapper. May throw.
    static void 
    colorMaski(const GLuint buf, const GLboolean r, const GLboolean g, 
               const GLboolean b, const GLboolean a)
    { _colorMaski(buf, r, g, b, a); } // May throw.

    //! Call glDepthMask wrapper. May throw.
    static void 
    depthMask(const GLboolean mask)
    { _depthMask(mask); } // May throw.

    //! Call glStencilMask wrapper. May throw.
    static void 
    stencilMask(const GLuint mask)
    { _stencilMask(mask); } // May throw.

    //! Call glStencilMaskSeparate wrapper. May throw.
    static void 
    stencilMaskSeparate(const GLenum face, const GLuint mask)
    { _stencilMaskSeparate(face, mask); } // May throw.

public:

    //! Call glClear wrapper. May throw.
    static void 
    clear(const GLbitfield buf)
    { _clear(buf); } // May throw.        

    //! Call glClearColor wrapper. May throw.
    static void 
    clearColor(const GLclampf r, const GLclampf g, 
               const GLclampf b, const GLclampf a)
    { _clearColor(r, g, b, a); } // May throw.        

    //! Call glClearDepth wrapper. May throw.
    static void 
    clearDepth(const GLclampd d)
    { _clearDepth(d); } // May throw.        

    //! Call glClearDepthf wrapper. May throw.
    static void 
    clearDepth_f(const GLclampf d)
    { _clearDepth_f(d); } // May throw.        

    //! Call glClearStencil wrapper. May throw.
    static void 
    clearStencil(const GLint s)
    { _clearStencil(s); } // May throw.        

    //! Call glClearBufferiv wrapper. May throw.
    static void 
    clearBufferiv(const GLenum buffer, const GLint drawbuffer, 
                  const GLint *value)
    { _clearBufferiv(buffer, drawbuffer, value); } // May throw. 

    //! Call glClearBufferfv wrapper. May throw.
    static void 
    clearBufferfv(const GLenum buffer, const GLint drawbuffer, 
                  const GLfloat *value)
    { _clearBufferfv(buffer, drawbuffer, value); } // May throw. 

    //! Call glClearBufferuiv wrapper. May throw.
    static void 
    clearBufferuiv(const GLenum buffer, const GLint drawbuffer, 
                   const GLuint *value)
    { _clearBufferuiv(buffer, drawbuffer, value); } // May throw.        

    //! Call glClearBufferfi wrapper. May throw.
    static void 
    clearBufferfi(const GLenum buffer, const GLint drawbuffer, 
                     const GLfloat depth, const GLint stencil)
    { _clearBufferfi(buffer, drawbuffer, depth, stencil); } // May throw.

// ------------------------------------

private:    // Selecting a Buffer for Writing.

    //! glDrawBuffer wrapper. May throw.
    static void 
    _drawBuffer(const GLenum buf)
    {
        glDrawBuffer(buf);
        Error::check("glDrawBuffer"); // May throw.
    }

    //! glDrawBuffers wrapper. May throw.
    static void 
    _drawBuffers(const GLsizei n, const GLenum *bufs)
    {
        glDrawBuffers(n, bufs);
        Error::check("glDrawBuffer"); // May throw.
    }

private:    // Fine Control of Buffer Updates.

    //! glColorMask wrapper. May throw.
    static void 
    _colorMask(const GLboolean r, const GLboolean g, 
               const GLboolean b, const GLboolean a)
    {
        glColorMask(r, g, b, a);
        Error::check("glColorMask"); // May throw.
    }

    //! glColorMaski wrapper. May throw.
    static void 
    _colorMaski(const GLuint buf, const GLboolean r, const GLboolean g, 
                const GLboolean b, const GLboolean a)
    {
        glColorMaski(buf, r, g, b, a);
        Error::check("glColorMaski"); // May throw.
    }

    //! glDepthMask wrapper. May throw.
    static void 
    _depthMask(const GLboolean mask)
    {
        glDepthMask(mask);
        Error::check("glColorMask"); // May throw.
    }

    //! glStencilMask wrapper. May throw.
    static void 
    _stencilMask(const GLuint mask)
    {
        glStencilMask(mask);
        Error::check("glStencilMask"); // May throw.
    }

    //! glStencilMaskSeparate wrapper. May throw.
    static void 
    _stencilMaskSeparate(const GLenum face, const GLuint mask)
    {
        glStencilMaskSeparate(face, mask);
        Error::check("glStencilMaskSeparate"); // May throw.
    }

private:    // Clearing the Buffers.

    //! glClear wrapper. May throw.
    static void 
    _clear(const GLbitfield buf)
    {
        glClear(buf);
        Error::check("glClear"); // May throw.        
    }

    //! glClearColor wrapper. May throw.
    static void 
    _clearColor(const GLclampf r, const GLclampf g, 
                const GLclampf b, const GLclampf a)
    {
        glClearColor(r, g, b, a);
        Error::check("glClearColor"); // May throw.        
    }

    //! glClearDepth wrapper. May throw.
    static void 
    _clearDepth(const GLclampd d)
    {
        glClearDepth(d);
        Error::check("glClearDepth"); // May throw.        
    }

    //! glClearDepthf wrapper. May throw.
    static void 
    _clearDepthf(const GLclampf d)
    {
        glClearDepthf(d);
        Error::check("glClearDepthf"); // May throw.        
    }

    //! glClearStencil wrapper. May throw.
    static void 
    _clearStencil(const GLint s)
    {
        glClearStencil(s);
        Error::check("glClearStencil"); // May throw.        
    }

    //! glClearBufferiv wrapper. May throw.
    static void 
    _clearBufferiv(const GLenum buffer, const GLint drawbuffer, 
                   const GLint *value)
    {
        glClearBufferiv(buffer, drawbuffer, value);
        Error::check("glClearBufferiv"); // May throw.        
    }

    //! glClearBufferfv wrapper. May throw.
    static void 
    _clearBufferfv(const GLenum buffer, const GLint drawbuffer, 
                   const GLfloat *value)
    {
        glClearBufferfv(buffer, drawbuffer, value);
        Error::check("glClearBufferfv"); // May throw.        
    }

    //! glClearBufferuiv wrapper. May throw.
    static void 
    _clearBufferuiv(const GLenum buffer, const GLint drawbuffer, 
                    const GLuint *value)
    {
        glClearBufferuiv(buffer, drawbuffer, value);
        Error::check("glClearBufferuiv"); // May throw.        
    }

    //! glClearBufferfi wrapper. May throw.
    static void 
    _clearBufferfi(const GLenum buffer, const GLint drawbuffer, 
                   const GLfloat depth, const GLint stencil)
    {
        glClearBufferfi(buffer, drawbuffer, depth, stencil);
        Error::check("glClearBufferfi"); // May throw.
    }

private:    // Disable all kinds of construction.

    Buffer();                         //!< Disable CTOR.
    ~Buffer();                        //!< Disable DTOR.
    Buffer(const Buffer&);            //!< Disable copy.
    Buffer& operator=(const Buffer&); //!< Disable assignment.
};

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif  // NDJ_BUFFER_HPP_INCLUDED
