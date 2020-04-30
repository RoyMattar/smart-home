#ifndef CONDVAR_HPP
#define CONDVAR_HPP

#include <stdexcept>
#include <cerrno>
#include <cassert>
#include <pthread.h>
#include "mutex.hpp"
#include "common_utils.hpp"

namespace advcpp
{

class CondVar : private Uncopyable
{
public:
    //@brief default constructor
    //@exception may throw advcpp::CondVarNoResourcesExc if resources for CondVAr (other than memory) are lacking in system
    //@exception may throw advcpp::CondVarNoMemoryExc if system has not enough memory for CondVar
    CondVar ();
    ~CondVar () NOEXCEPTIONS;

    template <typename Predicate>
    //require:  Predicate   has bool operator()() - nullary boolean function operator
    //@brief waits as long as a_predicate is true
    //@param[in] a_mutex:       reference to the Mutex to be used by pthread_cond_t
    //           a_predicate:   the predicate functor - manages the condition for waiting
    void Wait (Mutex& a_mutex, Predicate a_predicate);
    //@brief wakes a waiting thread up
    void NotifyOne () NOEXCEPTIONS;
    //@brief wakes all waiting threads up
    void NotifyAll () NOEXCEPTIONS;

private:
    int TryInit () NOEXCEPTIONS;

private:
    pthread_cond_t m_condVar;
};


struct CondVarNoResourcesExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

struct CondVarNoMemoryExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

struct CondVarWrongMutexExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

struct CondVarNoLockExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};


template <typename Predicate>
void CondVar::Wait (Mutex& a_mutex, Predicate a_predicate)
{
    while (a_predicate())
    {
        switch (pthread_cond_wait(&m_condVar, &(a_mutex.GetNativeMutex())))
        {
            case 0:
                break;

            case EINVAL:
                throw CondVarWrongMutexExc();
                break;

            case EPERM:
                throw CondVarNoLockExc();
                break;

            default:
                assert(!"Non documented pthread_cond_wait error");
        }
    }
}

inline const char* CondVarNoResourcesExc::what() const NOEXCEPTIONS
{
    return "System lacks the necessary resources (other than memory) to initialize another condition variable";
}

inline const char* CondVarNoMemoryExc::what() const NOEXCEPTIONS
{
    return "Insufficient memory to initialize the condition variable";
}

inline const char* CondVarWrongMutexExc::what() const NOEXCEPTIONS
{
    return "Invalid mutex or different mutexes passed to same condition variable";
}

inline const char* CondVarNoLockExc::what() const NOEXCEPTIONS
{
    return "Mutex not owned by current thead - did you forget to lock the mutex?";
}

} // advcpp

#endif // CONDVAR_HPP