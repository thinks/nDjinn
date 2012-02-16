//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef NDJ_EXCEPTION_HPP_INCLUDED
#define NDJ_EXCEPTION_HPP_INCLUDED

#include <sstream>
#include <string>
#include <exception>

//------------------------------------------------------------------------------

// Useful macro.

#define NDJINN_THROW(MSG) \
{std::stringstream ss; ss << "nDjinn: "; ss << MSG; throw ndj::base(ss.str());}

//------------------------------------------------------------------------------

namespace ndj  {

//------------------------------------------------------------------------------

class base : public std::exception
{
public:

    //! CTOR.
    explicit
    base(const std::string &msg)
        : std::exception()
        , _msg(msg) 
    {}

    //! Copy CTOR.
    base(const base &rhs)
        : std::exception(rhs)
        , _msg(rhs._msg)    // TODO: May throw?
    {}

    //! Assign.
    base&
    operator=(const base &rhs)
    {
        std::exception::operator=(rhs);
        _msg = rhs._msg;    // TODO: May throw?
        return *this;
    }

    //! DTOR.
    virtual 
    ~base()
    {}

    //! Exception message.
    virtual const char* 
    what() const
    { return _msg.c_str(); }

private:    // Member variables.

    std::string _msg;
};

//------------------------------------------------------------------------------

}  // Namespace: ndj.

//------------------------------------------------------------------------------

#endif	// NDJ_EXCEPTION_HPP_INCLUDED
