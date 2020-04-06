#ifndef THREAD_HPP
#define THREAD_HPP

#include <stdexcept> // std::exception
#include <cstddef> // size_t
#include <pthread.h>
#include <sys/types.h> // useconds_t
#include "common_utils.hpp"
#include "Runnable.hpp"
#include "SharedPtr.hpp"
#include "AtomicFlag.hpp"

namespace advcpp
{

class Thread : private Uncopyable
{
public:
    Thread (const SharedPtr<Runnable>& a_pRunnable);
    ~Thread () NOEXCEPTIONS;

    //@brief joins - will go into blocking if thread has not yet terminated
    //@exception may throw ThreadDeadlockExc if two threads are attempting to join each other, or a thread is attempting to join itself
    //@exception may throw ThreadInvalidExc if another thread is already waiting to join on the same thread
    void Join ();
    //@brief tries to join - will return if thread has not yet terminated
    //@retval true if successfully joined or if thread had already been joined/detached, false otherwise
    //@exception may throw ThreadDeadlockExc if two threads are attempting to join each other, or a thread is attempting to join itself
    //@exception may throw ThreadInvalidExc if another thread is already waiting to join on the same thread
    bool TryJoin ();
    //@brief tries to join with a timeout - will return if thread has not yet terminated by the timeout mentioned
    //@retval true if successfully joined or if thread had already been joined/detached, false otherwise
    //@exception may throw ThreadDeadlockExc if two threads are attempting to join each other, or a thread is attempting to join itself
    //@exception may throw ThreadInvalidTimeExc if a_timeout is greater than 1e9 when converted to nanoseconds
    bool TimedJoin (useconds_t a_timeout);
    //@brief detaches
    //@warning a detached thread could survive until the end of the program while still not having finished its work
    void Detach () NOEXCEPTIONS;
    //@retval true if none of Join/TryJoin/TimedJoin/Detach had been called, false otherwise
    bool Joinable () const NOEXCEPTIONS;
    //@brief cancells the thread (asynchronous - not delayed until next cancellation point)
    //@exception may throw ThreadUncancellableExc if thread had already been joined/detached
    void Cancel ();

private:
    static void* threadCallBack (void* a_args);

private:
    SharedPtr<Runnable> m_pRunnable;
    pthread_t m_tid;
    AtomicFlag m_joinable;
};

struct ThreadNoResourcesExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

struct ThreadDeadlockExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

struct ThreadInvalidExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

struct ThreadInvalidTimeExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

struct ThreadUncancellableExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

inline bool Thread::Joinable () const NOEXCEPTIONS
{
    return m_joinable;
}

inline const char* ThreadNoResourcesExc::what () const NOEXCEPTIONS
{
    return "Insufficient resources to create another thread";
}

inline const char* ThreadDeadlockExc::what () const NOEXCEPTIONS
{
    return "A deadlock was detected (e.g. two threads tried to join with each other), or the thread to be joined is the calling thread";
}

inline const char* ThreadInvalidExc::what () const NOEXCEPTIONS
{
    return "Another thread is already waiting to join with this thread";
}

inline const char* ThreadInvalidTimeExc::what () const NOEXCEPTIONS
{
    return "Time value mentioned is invalid (greater than 1e9 when converted to nanoseconds)";
}

inline const char* ThreadUncancellableExc::what () const NOEXCEPTIONS
{
    return "Thread has been joined or detached";
}

} // advcpp

#endif // THREAD_HPP