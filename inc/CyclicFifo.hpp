#ifndef CYCLIC_FIFO_HPP
#define CYCLIC_FIFO_HPP

#include <vector>
#include <cstddef> // size_t
#include "common_utils.hpp"

namespace advcpp
{

template <typename T>
//require:  T    has default ctor, copy ctor and operator=
class CyclicFifo
{
public:
    //@brief constructor from size_t
    //@param[in] a_capacity: the inner container's maximum capacity
    //@exception may throw std::bad_alloc while initializing the inner container with T's
    explicit CyclicFifo (size_t a_capacity);
    //CyclicFifo (const CyclicFifo& a_other) = default;
    //~CyclicFifo () = default;
    //CyclicFifo& operator= (const CyclicFifo& a_other) = default;

    //@brief inserts an element to the end of CyclicFifo
    //@param[in] a_elem: the element to be inserted
    //@exception may throw std::overflow_error if the inner container has reached maximum capacity
    //@exception may throw std::bad_alloc while inserting a_elem into the inner container
    void PushBack (const T& a_elem);
    //@brief returns the first element in CyclicFifo; this element is removed from the inner container
    //@exception may throw std::underflow_error if there are no elements in the inner container
    T PopFront ();
    //@brief returns the current number of elements stored in CyclicFifo
    size_t NumOfElems () const NOEXCEPTIONS;
    //@brief returns the maximum capacity of CyclicFifo
    size_t Capacity () const NOEXCEPTIONS;

private:
    std::vector<T> m_cntr;
    size_t m_capacity;
    size_t m_numOfElems;
    size_t m_tailIndex;
    size_t m_headIndex;
};

} // advcpp

#include "inl/CyclicFifo.hxx"

#endif // CYCLIC_FIFO_HPP