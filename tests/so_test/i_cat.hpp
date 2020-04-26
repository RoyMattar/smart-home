#ifndef I_CAT_HPP
#define I_CAT_HPP

#include "common_utils.hpp"

namespace smart_home
{

class ICat
{
public:
    virtual ~ICat () NOEXCEPTIONS;

    virtual void Meow () const NOEXCEPTIONS;
};

inline ICat::~ICat () NOEXCEPTIONS { }

} // smart_home

extern "C"
{
    SharedPtr<smart_home::ICat> MakeICat ();
}

#endif // I_CAT_HPP