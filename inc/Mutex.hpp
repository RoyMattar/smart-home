#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include <stdexcept> // std::exception
#include "common_utils.hpp"

namespace advcpp
{

class Mutex : private Uncopyable
//@warning: double locking or unlocking Mutex by the same thread leads to undefined behavior
{
    friend class CondVar;
    //template <class Predicate>
    //friend void CondVar::Wait(Mutex& a_mutex, Predicate a_predicate);

public:
    //@brief default constructor
    //@exception may throw advcpp::MutexNoResourcesExc if resources for Mutex (other than memory) are lacking in system
    //@exception may throw advcpp::MutexNoMemoryExc if system has not enough memory for Mutex
    Mutex ();
    ~Mutex () NOEXCEPTIONS;

    //@brief locks the Mutex
    void Lock () NOEXCEPTIONS;
    //@brief unlocks the Mutex
    void Unlock () NOEXCEPTIONS;

    //@brief returns the inner mutex - restricted for class CondVar
    PASSKEY(PasskeyCondVar, class CondVar);
    pthread_mutex_t& CondVarNativeMutex (PasskeyCondVar) NOEXCEPTIONS;

protected:
    pthread_mutex_t& GetNativeMutex () NOEXCEPTIONS;

private:
    int TryInit () NOEXCEPTIONS;

private:
    pthread_mutex_t m_mutex;
};


struct MutexNoResourcesExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};

struct MutexNoMemoryExc : public std::exception
{
    const char* what () const NOEXCEPTIONS;
};


inline pthread_mutex_t& Mutex::CondVarNativeMutex (PasskeyCondVar) NOEXCEPTIONS
{
    return m_mutex;
}

inline pthread_mutex_t& Mutex::GetNativeMutex () NOEXCEPTIONS
{
    return m_mutex;
}

inline const char* MutexNoResourcesExc::what () const NOEXCEPTIONS
{
    return "System lacks the necessary resources (other than memory) to initialize another mutex";
}

inline const char* MutexNoMemoryExc::what () const NOEXCEPTIONS
{
    return "Insufficient memory to initialize the mutex";
}

} // advcpp

#endif // MUTEX_HPP