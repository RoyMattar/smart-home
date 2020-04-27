#ifndef I_CAT_HPP
#define I_CAT_HPP

#include "common_utils.hpp"

namespace smart_home
{

class ICat
{
public:
    //ICat () = default;
    //ICat (ICat const& a_other) = default;
    virtual ~ICat () NOEXCEPTIONS;
    //ICat& operator= (ICat const& a_other) = default;

    virtual void Meow () const NOEXCEPTIONS = 0;
};

} // smart_home

#endif // I_CAT_HPP