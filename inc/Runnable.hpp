#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

#include "common_utils.hpp"

namespace advcpp
{

class Runnable : private Unassignable
{
public:
    //Runnable () = default;
    //Runnable (const Runnable& a_other) = default;
    virtual ~Runnable () { }

    virtual void Run () = 0;
};

} // advcpp

#endif // RUNNABLE_HPP