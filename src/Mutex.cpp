#include <cassert>
#include <cerrno>
#include <pthread.h>
#include <unistd.h> // usleep()

#include "Mutex.hpp"
#include "common_utils.hpp"

namespace advcpp
{

Mutex::Mutex ()
{
    switch (TryInit())
    {
        case 0:
            break;

        case EAGAIN:
            throw MutexNoResourcesExc();
            break;

        case ENOMEM:
            throw MutexNoMemoryExc();
            break;

        case EPERM:
            assert(!"No permissions to perform the operation - did you change the attributes of pthread_mutex_init()?");
            break;

        case EBUSY:
            assert(!"Detected an attempt to reinitialize the mutex - did you call pthread_mutex_init() again?");
            break;

        case EINVAL:
            assert(!"Invalid mutex attributes - did you change the attributes of pthread_mutex_init()?");
            break;

        default:
            assert(!"Non documented pthread_mutex_init() error");
    }
}

Mutex::~Mutex () NOEXCEPTIONS
{
    switch (pthread_mutex_destroy(&m_mutex))
    {
        case 0:
            break;

        case EBUSY:
            assert(!"Mutex is already locked (pthread_mutex_lock()) or referenced (pthread_cond_wait()) by another thread");
            break;

        case EINVAL:
            assert(!"Invalid mutex sent to pthread_mutex_destroy()");
            break;

        default:
            assert(!"Non documented pthread_mutex_destroy() error");
    }
}

void Mutex::Lock () NOEXCEPTIONS
{
    switch (pthread_mutex_lock(&m_mutex))
    {
        case 0:
            break;

        case EINVAL:
            assert(!"Mutex had not been properly initialized - did you change the call to pthread_mutex_init()?");
            break;

        case EDEADLK:
            assert(!"Mutex had already been locked by the calling thread - did you change the mutex attributes to 'error-checking'?");
            break;

        default:
            assert(!"Non documented pthread_mutex_lock() error");
    }
    // Double locking the mutex will lead to undefined behavior
}

void Mutex::Unlock () NOEXCEPTIONS
{
    switch (pthread_mutex_unlock(&m_mutex))
    {
        case 0:
            break;

        case EINVAL:
            assert(!"Mutex had not been properly initialized - did you change the call to pthread_mutex_init()?");
            break;

        case EPERM:
            assert(!"Calling thread does not own the mutex - did you change the mutex attributes to 'error-checking'?");
            break;

        default:
            assert(!"Non documented pthread_mutex_unlock() error");
    }
    // Double unlocking the mutex will lead to undefined behavior
}

int Mutex::TryInit () NOEXCEPTIONS
{
    const unsigned char numOfTries = 3;
    unsigned char mSecsWait = 4;
    int statusCode = -1;

    for (unsigned char tryNum = 0; tryNum < numOfTries; ++tryNum)
    {
        statusCode = pthread_mutex_init(&m_mutex, 0);
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