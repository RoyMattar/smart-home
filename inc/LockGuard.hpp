#ifndef LOCK_GUARD_HPP
#define LOCK_GUARD_HPP

#include "common_utils.hpp"
#include "Mutex.hpp"

namespace advcpp
{

class LockGuard : private Uncopyable
//Mutex RAII
{
public:
    //@brief constructor from Mutex reference - locks the Mutex
    //@param[in] a_mutex: reference to the Mutex to be locked
    LockGuard (Mutex& a_mutex) NOEXCEPTIONS;
    //@brief destructor - unlocks the mutex
    ~LockGuard () NOEXCEPTIONS;

private:
    Mutex& m_mutex;
};

} // advcpp

#endif // LOCK_GUARD_HPP