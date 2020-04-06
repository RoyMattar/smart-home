#include <cassert>
#include <cerrno>
#include <pthread.h>
#include <unistd.h> // usleep()

#include "CondVar.hpp"
#include "Mutex.hpp"
#include "common_utils.hpp"

namespace advcpp
{

CondVar::CondVar ()
{
    switch (TryInit())
    {
        case 0:
            break;
        
        case EAGAIN:
            throw CondVarNoResourcesExc();
            break;

        case ENOMEM:
            throw CondVarNoMemoryExc();
            break;

        case EBUSY:
            assert(!"Detected an attempt to reinitialize the condition variable - did you call pthread_cond_init() again?");
            break;

        case EINVAL:
            assert(!"Invalid condition variable attributes - did you change the attributes of pthread_cond_init()?");
            break;
        
        default:
            assert(!"Non documented pthread_cond_init() error");
    }
}

CondVar::~CondVar () NOEXCEPTIONS
{
    switch (pthread_cond_destroy(&m_condVar))
    {
        case 0:
            break;

        case EBUSY:
            assert(!"Condition variable is already referenced by another thread");
            break;

        case EINVAL:
            assert(!"Invalid condition variable sent to pthread_cond_destroy()");
            break;

        default:
            assert(!"Non documented pthread_cond_destroy() error");
    }
}

void CondVar::NotifyOne () NOEXCEPTIONS
{
    switch (pthread_cond_signal(&m_condVar))
    {
        case 0:
            break;
        
        case EINVAL:
            assert(!"Uninitialized condition variable");
            break;
        
        default:
            assert(!"Non documented pthread_cond_signal() error");
    }
}

void CondVar::NotifyAll () NOEXCEPTIONS
{
    switch (pthread_cond_broadcast(&m_condVar))
    {
        case 0:
            break;

        case EINVAL:
            assert(!"Uninitialized condition variable");
            break;

        default:
            assert(!"Non documented pthread_cond_broadcast() error");
    }
}

int CondVar::TryInit () NOEXCEPTIONS
{
    const unsigned char numOfTries = 3;
    unsigned char mSecsWait = 4;
    int statusCode = -1;

    for (unsigned char tryNum = 0; tryNum < numOfTries; ++tryNum)
    {
        statusCode = pthread_cond_init(&m_condVar, 0);
        if (statusCode != EAGAIN)
        {
            break;
        }
        usleep(MILLI_TO_MICRO(mSecsWait));
        mSecsWait *= 2;
    }

    return statusCode;
}

} // advcpp