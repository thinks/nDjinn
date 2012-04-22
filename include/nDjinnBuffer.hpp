//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJINN_BUFFER_HPP_INCLUDED
#define NDJINN_BUFFER_HPP_INCLUDED

#include "nDjinnNamespace.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>

// -----------------------------------------------------------------------------

BEGIN_NDJINN_NAMESPACE

//! DOCS
class Buffer
{
public:     // Selecting a Buffer for Writing.

    static void
    drawBuffer(GLenum buf);

    static void
    drawBuffers(GLsizei n, const GLenum *bufs);

public:     // Fine Control of Buffer Updates.

    static void 
    colorMask(GLboolean r, GLboolean g, GLboolean b, GLboolean a);

    static void 
    colorMaski(GLuint buf, GLboolean r, GLboolean g, GLboolean b, GLboolean a);

    static void 
    depthMask(GLboolean mask);

    static void 
    stencilMask(GLuint mask);

    static void 
    stencilMaskSeparate(GLenum face, GLuint mask);

public:     // Clearing the Buffers.

    static void 
    clear(GLbitfield buf);        

    static void 
    clearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);    

    static void 
    clearDepth(GLclampd d);        

    static void 
    clearDepthf(GLclampf d);

    static void 
    clearStencil(GLint s);

    static void 
    clearBufferiv(GLenum buf, GLint drawbuffer, const GLint *value);

    static void 
    clearBufferfv(GLenum buf, GLint drawbuffer, const GLfloat *value);

    static void 
    clearBufferuiv(GLenum buf, GLint drawbuffer, const GLuint *value);

    static void 
    clearBufferfi(GLenum buf, GLint drawbuffer, GLfloat depth, GLint stencil);

private:    // Disable all kinds of construction.

    Buffer();                         //!< Disable CTOR.
    ~Buffer();                        //!< Disable DTOR.
    Buffer(const Buffer&);            //!< Disable copy.
    Buffer& operator=(const Buffer&); //!< Disable assignment.
};

// -----------------------------------------------------------------------------

//! glDrawBuffer wrapper. May throw. [static]
inline void
Buffer::drawBuffer(const GLenum buf)
{ 
    glDrawBuffer(buf);
    Error::check("glDrawBuffer"); // May throw.
} 


//! glDrawBuffers wrapper. May throw. [static]
inline void
Buffer::drawBuffers(const GLsizei n, const GLenum *bufs)
{ 
    glDrawBuffers(n, bufs);
    Error::check("glDrawBuffers"); // May throw.
} 

// -----------------------------------------------------------------------------

//! glColorMask wrapper. May throw. [static]
inline void 
Buffer::colorMask(const GLboolean r, const GLboolean g, 
                  const GLboolean b, const GLboolean a)
{
    glColorMask(r, g, b, a);
    Error::check("glColorMask"); // May throw.
}


//! glColorMaski wrapper. May throw. [static]
inline void 
Buffer::colorMaski(const GLuint buf, const GLboolean r, const GLboolean g, 
                   const GLboolean b, const GLboolean a)
{
    glColorMaski(buf, r, g, b, a);
    Error::check("glColorMaski"); // May throw.
}


//! glDepthMask wrapper. May throw. [static]
inline void 
Buffer::depthMask(const GLboolean mask)
{
    glDepthMask(mask);
    Error::check("glColorMask"); // May throw.
}


//! glStencilMask wrapper. May throw. [static]
inline void 
Buffer::stencilMask(const GLuint mask)
{
    glStencilMask(mask);
    Error::check("glStencilMask"); // May throw.
}


//! glStencilMaskSeparate wrapper. May throw. [static]
inline void 
Buffer::stencilMaskSeparate(const GLenum face, const GLuint mask)
{
    glStencilMaskSeparate(face, mask);
    Error::check("glStencilMaskSeparate"); // May throw.
}

// -----------------------------------------------------------------------------

//! glClear wrapper. May throw. [static]
inline void 
Buffer::clear(const GLbitfield buf)
{
    glClear(buf);
    Error::check("glClear"); // May throw.        
}


//! glClearColor wrapper. May throw. [static]
inline void 
Buffer::clearColor(const GLclampf r, const GLclampf g, 
            const GLclampf b, const GLclampf a)
{
    glClearColor(r, g, b, a);
    Error::check("glClearColor"); // May throw.        
}


//! glClearDepth wrapper. May throw. [static]
inline void 
Buffer::clearDepth(const GLclampd d)
{
    glClearDepth(d);
    Error::check("glClearDepth"); // May throw.        
}


//! glClearDepthf wrapper. May throw. [static]
inline void 
Buffer::clearDepthf(const GLclampf d)
{
    glClearDepthf(d);
    Error::check("glClearDepthf"); // May throw.        
}


//! glClearStencil wrapper. May throw. [static]
inline void 
Buffer::clearStencil(const GLint s)
{
    glClearStencil(s);
    Error::check("glClearStencil"); // May throw.        
}


//! glClearBufferiv wrapper. May throw. [static]
inline void 
Buffer::clearBufferiv(const GLenum  buf, 
                      const GLint   drawbuffer, 
                      const GLint  *value)
{
    glClearBufferiv(buf, drawbuffer, value);
    Error::check("glClearBufferiv"); // May throw.        
}


//! glClearBufferfv wrapper. May throw. [static]
inline void 
Buffer::clearBufferfv(const GLenum   buf, 
                      const GLint    drawbuffer, 
                      const GLfloat *value)
{
    glClearBufferfv(buf, drawbuffer, value);
    Error::check("glClearBufferfv"); // May throw.        
}


//! glClearBufferuiv wrapper. May throw. [static]
inline void 
Buffer::clearBufferuiv(const GLenum  buf, 
                       const GLint   drawbuffer, 
                       const GLuint *value)
{
    glClearBufferuiv(buf, drawbuffer, value);
    Error::check("glClearBufferuiv"); // May throw.        
}


//! glClearBufferfi wrapper. May throw. [static]
inline void 
Buffer::clearBufferfi(const GLenum  buf, 
                      const GLint   drawbuffer, 
                      const GLfloat depth, 
                      const GLint   stencil)
{
    glClearBufferfi(buf, drawbuffer, depth, stencil);
    Error::check("glClearBufferfi"); // May throw.
}

END_NDJINN_NAMESPACE

// -----------------------------------------------------------------------------

#endif  // NDJINN_BUFFER_HPP_INCLUDED
