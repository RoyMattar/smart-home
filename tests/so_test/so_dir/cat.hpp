#ifndef CAT_HPP
#define CAT_HPP

#include "i_cat.hpp"
#include "common_utils.hpp"

namespace smart_home
{

class Cat : public ICat
{
public:
    //Cat () = default;
    //Cat (Cat const& a_other) = default;
    //~Cat () = default;
    //Cat& operator= (Cat const& a_other) = default;

    virtual void Meow () const NOEXCEPTIONS;
};

} // smart_home

#endif // CAT_HPP