#include <stdexcept> // std::overflow_error, std::underflow_error

namespace advcpp
{

template <class T>
CyclicFifo<T>::CyclicFifo (size_t a_capacity)
    : m_cntr(a_capacity, T())
    , m_capacity(a_capacity)
    , m_numOfElems(0)
    , m_tailIndex(0)
    , m_headIndex(0)
{ }

template <class T>
void CyclicFifo<T>::PushBack (const T& a_elem)
{
    if (m_numOfElems == m_capacity)
    {
        throw std::overflow_error("Reached max capacity");
    }

    m_cntr[m_tailIndex] = a_elem;
    m_tailIndex = (m_tailIndex + 1) % m_capacity;
    ++m_numOfElems;
}

template <class T>
T CyclicFifo<T>::PopFront ()
{
    if (m_numOfElems == 0)
    {
        throw std::underflow_error("Nothing to pop");
    }

    T elem = m_cntr[m_headIndex];
    m_headIndex = (m_headIndex + 1) % m_capacity;
    --m_numOfElems;

    return elem;
}

template <class T>
size_t CyclicFifo<T>::NumOfElems () const NOEXCEPTIONS
{
    return m_numOfElems;
}

template <class T>
size_t CyclicFifo<T>::Capacity () const NOEXCEPTIONS
{
    return m_capacity;
}

} // advcpp