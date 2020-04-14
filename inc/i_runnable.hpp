#ifndef I_RUNNABLE_HPP
#define I_RUNNABLE_HPP

#include "common_utils.hpp"

namespace advcpp
{

class IRunnable : private Unassignable
{
public:
    //IRunnable () = default;
    //IRunnable (const IRunnable& a_other) = default;
    virtual ~IRunnable () { }

    virtual void Run () = 0;
};

} // advcpp

#endif // I_RUNNABLE_HPP