#include <stdexcept> // std::exception
#include "lock_guard.hpp"
#include "notify_guard.hpp"
#include "composite_predicates.hpp"

namespace advcpp
{

namespace // anonymous
{

struct WaitableBoundedQueueShutdownExc : public std::exception
{
    const char* what() const NOEXCEPTIONS
    {
        return "WaitableBoundedQueue is shutting down";
    }
};

struct OccDataSpaceNotifier
{
    OccDataSpaceNotifier (CondVar& a_newOccDataSpace)
        : m_newOccDataSpace(a_newOccDataSpace)
    { }

    void operator() () NOEXCEPTIONS
    {
        m_newOccDataSpace.NotifyOne();
    }

    CondVar& m_newOccDataSpace;
};

struct FreeDataSpaceNotifier
{
    FreeDataSpaceNotifier (CondVar& a_newFreeDataSpace)
        : m_newFreeDataSpace(a_newFreeDataSpace)
    { }

    void operator() () NOEXCEPTIONS
    {
        m_newFreeDataSpace.NotifyOne();
    }

    CondVar& m_newFreeDataSpace;
};

} // anonymous

template <typename T, typename Q>
struct WaitableBoundedQueue<T, Q>::IsNotFull
{
    IsNotFull (const WaitableBoundedQueue<T, Q>& a_wbq)
        : m_wbq(a_wbq)
    { }

    bool operator() () const NOEXCEPTIONS
    {
        return m_wbq.m_boundedQueue.NumOfElems() < m_wbq.m_boundedQueue.Capacity();
    }

    const WaitableBoundedQueue<T, Q>& m_wbq;
};

template <typename T, typename Q>
struct WaitableBoundedQueue<T, Q>::IsNotEmpty
{
    IsNotEmpty (const WaitableBoundedQueue<T, Q>& a_wbq)
        : m_wbq(a_wbq)
    { }

    bool operator() () const NOEXCEPTIONS
    {
        return m_wbq.m_boundedQueue.NumOfElems() > 0;
    }

    const WaitableBoundedQueue<T, Q>& m_wbq;
};

template <typename T, typename Q>
struct WaitableBoundedQueue<T, Q>::IsNotShuttingDown
{
    IsNotShuttingDown (const WaitableBoundedQueue<T, Q>& a_wbq)
        : m_wbq(a_wbq)
    { }

    bool operator() () const NOEXCEPTIONS
    {
        return !m_wbq.isShutdown();
    }

    const WaitableBoundedQueue<T, Q>& m_wbq;
};


template <typename T, typename Q>
WaitableBoundedQueue<T, Q>::WaitableBoundedQueue (size_t a_capacity)
    : m_boundedQueue(a_capacity)
    , m_isShutdown(false)
    , m_queueMutex()
    , m_newFreeDataSpace()
    , m_newOccDataSpace()
{ }

template <typename T, typename Q>
WaitableBoundedQueue<T, Q>::~WaitableBoundedQueue () NOEXCEPTIONS
{
    turnShutdownOn();

    m_newFreeDataSpace.NotifyAll();
    m_newOccDataSpace.NotifyAll();
}

template <typename T, typename Q>
void WaitableBoundedQueue<T, Q>::Enqueue (const T& a_elem)
{
    LockGuard lg(m_queueMutex);
    
    NotifyGuard<
        AndPredicate<IsNotFull, IsNotShuttingDown>, OccDataSpaceNotifier
        > ng(
        m_newFreeDataSpace, m_queueMutex
        , And(IsNotFull(*this), IsNotShuttingDown(*this))
        , OccDataSpaceNotifier(m_newOccDataSpace));

    if (isShutdown())
    {
        throw WaitableBoundedQueueShutdownExc();
    }

    m_boundedQueue.PushBack(a_elem);

    //ng.Disengage();
}

template <typename T, typename Q>
void WaitableBoundedQueue<T, Q>::Dequeue (T& a_elemRef)
{
    LockGuard lg(m_queueMutex);

    NotifyGuard<
        AndPredicate<IsNotEmpty, IsNotShuttingDown>, FreeDataSpaceNotifier
        > ng(
        m_newOccDataSpace, m_queueMutex
        , And(IsNotEmpty(*this), IsNotShuttingDown(*this))
        , FreeDataSpaceNotifier(m_newFreeDataSpace));

    if (isShutdown())
    {
        throw WaitableBoundedQueueShutdownExc();
    }

    a_elemRef = m_boundedQueue.PopFront();

    //ng.Disengage();
}

template <typename T, typename Q>
size_t WaitableBoundedQueue<T, Q>::NumOfElems () const NOEXCEPTIONS
{
    return m_boundedQueue.NumOfElems();
}

template <typename T, typename Q>
size_t WaitableBoundedQueue<T, Q>::Capacity () const NOEXCEPTIONS
{
    return m_boundedQueue.Capacity();
}

template <typename T, typename Q>
bool WaitableBoundedQueue<T, Q>::isShutdown () const NOEXCEPTIONS
{
    return m_isShutdown;
}

template <typename T, typename Q>
void WaitableBoundedQueue<T, Q>::turnShutdownOn () NOEXCEPTIONS
{
    m_isShutdown.Set();
}

} // advcpp