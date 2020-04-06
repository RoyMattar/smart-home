#ifndef WAITABLE_BOUNDED_QUEUE_HPP
#define WAITABLE_BOUNDED_QUEUE_HPP

#include <cstddef> // size_t
#include "common_utils.hpp"
#include "cyclic_fifo.hpp"
#include "mutex.hpp"
#include "condvar.hpp"
#include "atomic_flag.hpp"

namespace advcpp
{

template <typename T, typename Q = CyclicFifo<T> >
//require:  T   has default construcor, copy constructor and assignment operator
//          Q   has constructor from size_t, PushBack(), PopFront(), NumOfElems() and Capacity()
class WaitableBoundedQueue : private Uncopyable
{
public:
    //@brief constructor from size_t
    //@param[in] a_capacity: the queue's maximum capacity
    //@exception may throw std::bad_alloc while initializing Q with T's
    WaitableBoundedQueue (size_t a_capacity);
    ~WaitableBoundedQueue () NOEXCEPTIONS;

    //@brief enqueues an element into the queue
    //@param[in] a_elem: the element to be enqueued
    //@exception may throw advcpp::WaitableBoundedQueueShutdownExc if the queue is being shut down by another thread
    virtual void Enqueue (const T& a_elem);
    //@brief dequeues an element from the queue
    //@param[out] a_elemRef: reference to T in which the dequeued element shall be stored
    //@exception may throw advcpp::WaitableBoundedQueueShutdownExc if the queue is being shut down by another thread
    virtual void Dequeue (T& a_elemRef);
    //@brief returns number of elements in the queue.
    virtual size_t NumOfElems () const NOEXCEPTIONS;
    //@brief returns the maximum capacity of the queue.
    virtual size_t Capacity () const NOEXCEPTIONS;

private:
    struct IsNotFull;
    struct IsNotEmpty;
    struct IsNotShuttingDown;

private:
    bool isShutdown () const NOEXCEPTIONS;
    void turnShutdownOn () NOEXCEPTIONS;

private:
    Q m_boundedQueue;
    AtomicFlag m_isShutdown;
    Mutex m_queueMutex;
    CondVar m_newFreeDataSpace;
    CondVar m_newOccDataSpace;
};

} // advcpp

#include "inl/waitable_bounded_queue.hxx"

#endif // WAITABLE_BOUNDED_QUEUE_HPP