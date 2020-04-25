#include <iostream>
#include <exception> // std::terminate()
#include <cassert>
#include <cerrno>
#include <pthread.h>
#include <time.h> // struct timespec, clock_gettime()
#include "thread.hpp"
//#include "SharedPtr.hpp"
#include "i_runnable.hpp"
#include "atomic_flag.hpp"

namespace advcpp
{

Thread::Thread (const SharedPtr<IRunnable>& a_runnable)
    : m_runnable(a_runnable)
    , m_isJoinable(true)
{
    int statusCode = pthread_create(&m_tid, NULL, threadCallBack, this);
    if (0 != statusCode) {
        assert(EINVAL != statusCode);
        assert(EPERM != statusCode);
        switch (statusCode)
        {
            case EAGAIN:
                throw ThreadNoResourcesExc();
            default:
                assert(!"Non documented pthread_create() error");
        }
    }

    statusCode = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    assert(EINVAL != statusCode);
}

Thread::~Thread () NOEXCEPTIONS
{
    if (m_isJoinable)
    {
        assert(!"Thread is left joinable");
        std::terminate();
    }
}

void Thread::Join ()
{
    if (!m_isJoinable)
    {
        return;
    }

    switch (pthread_join(m_tid, NULL))
    {
        case 0:
            m_isJoinable = false;
            break;
        case EDEADLK:
            throw ThreadDeadlockExc();
            break;
        case EINVAL:
            throw ThreadInvalidExc();
            break;
        case ESRCH:
            assert(!"No thread with m_tid could be found");
            break;
        default:
            assert(!"Non documented pthread_join() error");
    }
}

bool Thread::TryJoin ()
{
    if (!m_isJoinable)
    {
        return true;
    }

    bool joined = false;

    switch (pthread_tryjoin_np(m_tid, NULL))
    {
        case 0:
            joined = true;
            m_isJoinable = false;
            break;
        case EBUSY:
            //thread has not yet terminated
            break;
        case EDEADLK:
            throw ThreadDeadlockExc();
            break;
        case EINVAL:
            throw ThreadInvalidExc();
            break;
        case ESRCH:
            assert(!"No thread with m_tid could be found");
            break;
        default:
            assert(!"Non documented pthread_tryjoin_np() error");
    }

    return joined;
}

bool Thread::TimedJoin (useconds_t a_timeout)
{
    if (!m_isJoinable)
    {
        return true;
    }

    bool joined = false;
    struct timespec ts;

    assert(clock_gettime(CLOCK_REALTIME, &ts) != -1);
    ts.tv_nsec += MICRO_TO_NANO(a_timeout);

    switch (pthread_timedjoin_np(m_tid, NULL, &ts))
    {
        case 0:
            joined = true;
            m_isJoinable = false;
            break;
        case ETIMEDOUT:
            //timed out before thread has terminated
            break;
        case EDEADLK:
            throw ThreadDeadlockExc();
            break;
        case EINVAL:
            throw ThreadInvalidTimeExc(); // ThreadInvalidExc could have also been appropriate
            break;
        case ESRCH:
            assert(!"No thread with m_tid could be found");
            break;
        default:
            assert(!"Non documented pthread_timedjoin_np() error");
    }

    return joined;
}

void Thread::Detach () NOEXCEPTIONS
{
    if (!m_isJoinable)
    {
        return;
    }

    switch (pthread_detach(m_tid))
    {
        case 0:
            m_isJoinable = false;
            break;
        case EINVAL:
            assert(!"Thread was not created as a joinable thread");
            break;
        case ESRCH:
            assert(!"No thread with m_tid could be found");
            break;
        default:
            assert(!"Non documented pthread_detach() error");
    }
}

void Thread::CancelAsync ()
{
    int statusCode = pthread_cancel(m_tid);
    if (ESRCH == statusCode)
    {
        throw ThreadUncancellableExc();
    }
}

void* Thread::threadCallBack (void* a_this)
{
    assert(a_this);
    const Thread* myThis = reinterpret_cast<const Thread*>(a_this);

    try
    {
        myThis->m_runnable->Run();
    }
    catch (const std::exception& a_e)
    {
        std::cerr << a_e.what() << std::endl;
        assert(!"Unsafe IRunnable");
    }
    catch (...)
    {
        assert(!"Non documented exception thrown by IRunnable");
    }
    
    return 0;
}

} // advcpp