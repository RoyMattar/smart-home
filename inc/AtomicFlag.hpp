#ifndef ATOMIC_FLAG_HPP
#define ATOMIC_FLAG_HPP

#include "AtomicValue.hpp"
#include "common_utils.hpp"

namespace advcpp
{

typedef AtomicValue<bool> AtomicFlag;

template <>
class AtomicValue<bool> : private Uncopyable
{
public:
    AtomicValue (bool a_flag = false) NOEXCEPTIONS;
    //~AtomicValue () = default;

    void operator= (bool a_newFlag) NOEXCEPTIONS;
    operator bool () const NOEXCEPTIONS;
    bool operator! () const NOEXCEPTIONS;

    bool Get () const NOEXCEPTIONS;
    void Set () NOEXCEPTIONS;
    void Clear () NOEXCEPTIONS;

private:
    int m_flag;
};

} // advcpp

#endif // ATOMIC_FLAG_HPP