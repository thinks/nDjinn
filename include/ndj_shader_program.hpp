//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_SHADER_PROGRAM_HPP_INCLUDED
#define NDJ_SHADER_PROGRAM_HPP_INCLUDED

#include "nDjinnException.hpp"
#include "nDjinnError.hpp"
#include <gl/glew.h>
#include <string>
#include <map>

// -----------------------------------------------------------------------------

namespace ndj {

// -----------------------------------------------------------------------------

// shader_program
// --------------
//! DOCS

class shader_program
{
public:

    class shader
    {
    public:

        //! CTOR.
        explicit
        shader(const GLenum type)
            : _handle(0)
        {
            try {
                _handle = _create_shader(type); // May throw.
                if (_handle == 0) {
                    NDJINN_THROW("Invalid Shader program handle");
                }
            }
            catch (const std::exception&) {
                _delete_shader(_handle);        // TODO: May throw!?
                throw;                          // Re-throw.
            }
        }

        //! DTOR. Free handle resource.
        ~shader()
        { 
            try {
                _delete_shader(_handle);    // May throw.
            }
            catch (...) {
            }
        }

        GLuint 
        handle() const 
        { return _handle; }

        void
        source(const GLsizei   count, 
               const GLchar  **string,
               const GLint    *length)
        { _shader_source(_handle, count, string, length); } // May throw.

        void
        compile()
        {
            _compile_shader(_handle);                       // May throw.
            _fetch_info_log(_handle, _info_log);            // May throw.
            GLint compile_status = GL_FALSE;
            _get_shader_iv(_handle, GL_COMPILE_STATUS, 
                            &compile_status);                // May throw.
            if (compile_status == GL_FALSE) {                // May throw.
                NDJINN_THROW(
                    "Shader: Compile error: " << _handle << ": " << _info_log);
            }
        }

        const std::string&
        info_log() const
        { return _info_log; }

    private:

        static void
        _fetch_info_log(const GLuint shader, std::string &info_log)
        {
            GLint max_length = 0;
            _get_shader_iv(shader, GL_INFO_LOG_LENGTH, &max_length);
            if (max_length > 0) {
                // Info exists. The returned string is null-terminated.

                info_log.clear();
                info_log.resize(max_length);
                GLsizei log_length = 0;
                _get_shader_info_log(shader, 
                                     static_cast<GLsizei>(max_length),
                                     &log_length, // Excluding null-termination.
                                     &info_log[0]);
                info_log.resize(log_length + 1);
            }
        }

    private:    // OpenGL wrappers.

        //! glCreateShader wrapper. May throw.
        static GLuint
        _create_shader(const GLenum type)
        {
            const GLuint shader = glCreateShader(type);
            error::check(std::string("glCreateShader")); // May throw;
            return shader; 
        }

        //! glDeleteShader wrapper. May throw.
        static void
        _delete_shader(const GLuint shader)
        { 
            glDeleteShader(shader); 
            error::check(std::string("glDeleteShader")); // May throw;
        }

        //! glIsShader wrapper. May throw.
        static bool
        _is_shader(const GLuint shader)
        {
            const GLboolean is_shader = glIsShader(shader);
            error::check(std::string("glIsShader"));    // May throw;
            return (GL_TRUE == is_shader); 
        }

        //! glShaderSource wrapper. May throw.
        static void
        _shader_source(const GLuint    shader,
                       const GLsizei   count, 
                       const GLchar  **string, 
                       const GLint    *length)
        { 
            glShaderSource(shader, count, string, length); 
            error::check(std::string("glShaderSource")); // May throw;
        }

        //! glCompileShader wrapper. May throw.
        static void
        _compile_shader(const GLuint shader)
        { 
            glCompileShader(shader); 
            error::check(std::string("glCompileShader")); // May throw;
        }

        //! glGetShaderInfoLog wrapper. May throw.
        static void 
        _get_shader_info_log(const GLuint   shader,
                             const GLsizei  buf_size, 
                             GLsizei       *length, 
                             GLchar        *info_log)
        { 
            glGetShaderInfoLog(shader, buf_size, length, info_log); 
            error::check(std::string("glGetShaderInfoLog")); // May throw;
        }

        //! glGetShaderiv wrapper. May throw.
        static void
        _get_shader_iv(const GLuint shader, const GLenum pname, GLint *params)
        { 
            glGetShaderiv(shader, pname, params); 
            error::check(std::string("glGetShaderiv")); // May throw;
        }

    private:

        shader(const shader&);            //!< Disable copy CTOR.
        shader& operator=(const shader&); //!< Disable assign.

    private:    // Member variables.

        GLuint      _handle;    //!< Resource handle.
        std::string _info_log;
    };

public:

    //! POD
    struct attrib
    {
        GLenum type;
        GLint  size;
        GLint  location;
    };

    //! POD
    struct uniform
    {
        GLenum type;
        GLint  size;
        GLint  location;
    };

    typedef std::map<std::string, attrib>  _attrib_map_type;
    typedef std::map<std::string, uniform> _uniform_map_type;

public:     // Interface

    //! CTOR.
    explicit
    shader_program()
        : _handle(0)
    {
        try {
            _handle = _create_program();    // May throw.
            if (_handle == 0) {
                NDJINN_THROW("Invalid Shader program handle");
            }
        }
        catch (...) {
            _delete_program(_handle);       // TODO: May throw!?
            throw;                          // Re-throw.
        }
    }

    //! DTOR.
    ~shader_program()
    { 
        try {
            _delete_program(_handle);   // May throw.
        }
        catch (...) {
        }
    }

public:

    void
    bind() const
    { _use_program(_handle); } // May throw.

    void
    release() const
    { _use_program(0); } // May throw.

    void
    attach_shader(const shader &sh) 
    { _attach_shader(_handle, sh.handle()); } // May throw.
    
    void
    detach_shader(const shader &sh)
    { _detach_shader(_handle, sh.handle()); } // May throw.

    void
    link()
    { 
        _link_program(_handle);                 // May throw.
        _fetch_info_log(_handle, _info_log);    // May throw.

        GLint link_status = GL_FALSE;
        _get_program_iv(_handle, GL_LINK_STATUS, 
                        &link_status); // May throw.
        if (link_status == GL_FALSE) {
            NDJINN_THROW("Shader program link error: " 
                         << _handle << ": " << _info_log);
        }

        _validate_program(_handle);
        GLint validate_status = GL_FALSE;
        _get_program_iv(_handle, GL_VALIDATE_STATUS, 
                        &validate_status); // May throw.
        if (validate_status == GL_FALSE) {
            NDJINN_THROW("Shader program validation error: " 
                            << _handle << ": " << _info_log);
        }

        _fetch_active_uniforms(_handle, _uniforms);
        _fetch_active_attribs(_handle, _attribs);
    }

    const std::string&
    info_log() const
    { return _info_log; }

public:

    const uniform*
    query_active_uniform(const std::string &name) const {
        const uniform *uni = 0;
        const _uniform_map_type::const_iterator iter =
            _uniforms.find(name);
        if (iter != _uniforms.end()) {
            uni = &iter->second;
        }
        return uni;
    }

    const attrib*
    query_active_attrib(const std::string &name) const {
        const attrib *attr = 0;
        const _attrib_map_type::const_iterator iter =
            _attribs.find(name);
        if (iter != _attribs.end()) {
            attr = &iter->second;
        }
        return attr;
    }

private:

    //! Grab info about active uniforms from OpenGL.
    static void
    _fetch_active_uniforms(const GLuint program, _uniform_map_type &uniforms)
    {
        GLint active_uniforms = 0;
        _get_program_iv(program, GL_ACTIVE_UNIFORMS, 
                        &active_uniforms); // May throw.
        GLint active_uniform_max_length = 0; 
        _get_program_iv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, 
                        &active_uniform_max_length ); // May throw.
        uniforms.clear();
        for (GLint i = 0; i < active_uniforms; ++i) {
            std::string name;            
            name.resize(active_uniform_max_length);
            GLsizei length = 0;
            uniform uni;
            _get_active_uniform(
                program,
                static_cast<GLuint>(i),
                active_uniform_max_length,
                &length,                // Exluding null-termination!
                &uni.size,
                &uni.type,
                &name[0]);              // May throw.
            name.resize(length);
            uni.location = 
                _get_uniform_location(program, name.c_str()); // May throw.
            uniforms.insert(_uniform_map_type::value_type(name, uni));
        }
    }

    //! Grab info about active attribs from OpenGL.
    static void
    _fetch_active_attribs(const GLuint program, _attrib_map_type &attribs)
    {
        GLint active_attributes = 0;
        _get_program_iv(program, GL_ACTIVE_ATTRIBUTES, 
                        &active_attributes); // May throw.
        GLint active_attribute_max_length = 0; 
        _get_program_iv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, 
                        &active_attribute_max_length ); // May throw.
        attribs.clear();
        for (GLint i = 0; i < active_attributes; ++i) {
            std::string name;
            name.resize(active_attribute_max_length);
            GLsizei length = 0;
            attrib attr;
            _get_active_attrib(
                program, 
                static_cast<GLuint>(i), 
                active_attribute_max_length,
                &length,             // Excluding null-termination!
                &attr.size,
                &attr.type,
                &name[0]);
            name.resize(length);
            attr.location = 
                _get_attrib_location(program, name.c_str()); // May throw.
            attribs.insert(_attrib_map_type::value_type(name, attr));
        }
    }

    //! Grab info log from OpenGL.
    static void
    _fetch_info_log(const GLuint program, std::string &info_log)
    {
        GLint max_length = 0;
        _get_program_iv(program, GL_INFO_LOG_LENGTH, &max_length);
        if (max_length > 0) {
            // Info exists. The returned string is null-terminated.

            info_log.clear();
            info_log.resize(max_length);
            GLsizei log_length = 0; 
            _get_program_info_log(program, 
                                  static_cast<GLsizei>(max_length),
                                  &log_length, // Excluding null-termination!
                                  &info_log[0]);
            info_log.resize(log_length);
        }
    }

private:    // OpenGL wrappers.

    //! glCreateProgram wrapper. May throw.
    static GLuint
    _create_program()
    { 
        const GLuint program = glCreateProgram();
        error::check("glCreateProgram"); // May throw;
        return program; 
    }

    //! glDeleteProgram wrapper. May throw.
    static void
    _delete_program(const GLuint program)
    { 
        glDeleteProgram(program); 
        error::check("glDeleteProgram"); // May throw;
    }

    //! glUseProgram wrapper. May throw.
    static void
    _use_program(const GLuint program)
    { 
        glUseProgram(program); 
        error::check("glUseProgram"); // May throw;
    }

    //! glAttachShader wrapper. May throw.
    static void
    _attach_shader(const GLuint program, const GLuint shader)
    { 
        glAttachShader(program, shader); 
        error::check("glAttachShader"); // May throw;
    }

    //! glDetachShader wrapper. May throw.
    static void
    _detach_shader(const GLuint program, const GLuint shader)
    { 
        glDetachShader(program, shader); 
        error::check("glDetachShader"); // May throw;
    }

    //! glLinkProgram wrapper. May throw.
    static void
    _link_program(const GLuint program)
    { 
        glLinkProgram(program); 
        error::check("glLinkProgram"); // May throw;
    }

    //! glValidateProgram wrapper. May throw.
    static void
    _validate_program(const GLuint program)
    { 
        glValidateProgram(program); 
        error::check("glValidateProgram"); // May throw;
    }

    //! glIsProgram wrapper. May throw.
    static bool
    _is_program(const GLuint program)
    {
        const GLboolean is_program = glIsProgram(program);
        error::check("glIsProgram"); // May throw;
        return (GL_TRUE == is_program);
    }

    //! glGetActiveAttrib wrapper. May throw.
    static void
    _get_active_attrib(const GLuint   program, 
                       const GLuint   index,
                       const GLsizei  buf_size,
                       GLsizei       *length,
                       GLint         *size,
                       GLenum        *type,
                       GLchar        *name)
    { 
        glGetActiveAttrib(program, index, buf_size, length, size, type, name); 
        error::check("glGetActiveAttrib"); // May throw;
    }

    //! glGetAttriLocation wrapper. May throw.
    static GLint
    _get_attrib_location(const GLuint program, const GLchar *name)
    { 
        GLint loc = glGetAttribLocation(program, name); 
        error::check("glGetAttribLocation"); // May throw;
        return loc;
    }

    //! glGetActiveUniform wrapper. May throw.
    static void
    _get_active_uniform(const GLuint   program, 
                        const GLuint   index,
                        const GLsizei  buf_size,
                        GLsizei       *length,
                        GLint         *size,
                        GLenum        *type,
                        GLchar        *name)
    { 
        glGetActiveUniform(program, index, buf_size, length, size, type, name); 
        error::check("glGetActiveUniform"); // May throw;    
    }

    //! glGetUniformLocation wrapper. May throw.
    static GLint
    _get_uniform_location(const GLuint program, const GLchar *name)
    {
        GLint loc = glGetUniformLocation(program, name);
        error::check("glGetUniformLocation"); // May throw;
        return loc; 
    }

    //! glGetProgramiv wrapper. May throw.
    static void
    _get_program_iv(const GLuint program, const GLenum pname, GLint *params)
    { 
        glGetProgramiv(program, pname, params); 
        error::check("glGetProgramiv"); // May throw;
    }

    //! glGetProgramInfoLog wrapper. May throw.
    static void
    _get_program_info_log(const GLuint   program, 
                          const GLsizei  buf_size,
                          GLsizei       *length,
                          GLchar        *info_log)
    { 
        glGetProgramInfoLog(program, buf_size, length, info_log); 
        error::check("glGetProgramInfoLog"); // May throw;
    }

private:        // Member variables.

    GLuint            _handle;      //!< Resource handle.
    std::string       _info_log;
    _attrib_map_type  _attribs;
    _uniform_map_type _uniforms;    
};

// -----------------------------------------------------------------------------

}   // Namespace: ndj.

// -----------------------------------------------------------------------------

#endif // NDJ_SHADER_PROGRAM_HPP_INCLUDED



//glCreateShaderProgram is equivalent (assuming no errors are generated) to:
//
//    const GLuint shader = glCreateShader(type);
//    if (shader) {
//        glShaderSource(shader, count, strings, NULL);
//        glCompileShader(shader);
//        const GLuint program = glCreateProgram();
//        if (program) {
//            GLint compiled = GL_FALSE;
//            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
//            glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);
//            if (compiled) {
//                glAttachShader(program, shader);
//                glLinkProgram(program);
//                glDetachShader(program, shader);
//            }
//            // append-shader-info-log-to-program-info-log
//        }
//        glDeleteShader(shader);
//        return program;
//    } else {
//        return 0;
//    }
