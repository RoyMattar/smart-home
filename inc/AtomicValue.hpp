#ifndef ATOMIC_VALUE_HPP
#define ATOMIC_VALUE_HPP

#include "common_utils.hpp"

namespace advcpp
{

template <typename T>
//require:  T   is an integral type
class AtomicValue : private Uncopyable
{
public:
    explicit AtomicValue (T a_val = T()) NOEXCEPTIONS;
    //~AtomicValue () = default;

    void operator+= (T a_val) NOEXCEPTIONS;
    void operator-= (T a_val) NOEXCEPTIONS;
    T operator++ () NOEXCEPTIONS;
    T operator-- () NOEXCEPTIONS;

    T Value () NOEXCEPTIONS;
    void Value (T a_val) NOEXCEPTIONS;

private:
    T m_val;
};

} // advcpp

#include "inl/AtomicValue.hxx"

#endif // ATOMIC_VALUE_HPP