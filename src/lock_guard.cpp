#include "lock_guard.hpp"
#include "mutex.hpp"
#include "common_utils.hpp"

namespace advcpp
{

LockGuard::LockGuard (Mutex& a_mutex) NOEXCEPTIONS
    : m_mutex(a_mutex)
{
    m_mutex.Lock();
}

LockGuard::~LockGuard () NOEXCEPTIONS
{
    m_mutex.Unlock();
}

} // advcpp