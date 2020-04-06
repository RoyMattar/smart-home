#include "AtomicFlag.hpp"
#include "AtomicValue.hpp"
#include "common_utils.hpp"

namespace advcpp
{

AtomicValue<bool>::AtomicValue (bool a_flag) NOEXCEPTIONS
    : m_flag(a_flag)
{ }

void AtomicValue<bool>::operator= (bool a_newFlag) NOEXCEPTIONS
{
    a_newFlag ? Set() : Clear();
}

AtomicValue<bool>::operator bool () const NOEXCEPTIONS
{
    return Get();
}

bool AtomicValue<bool>::operator! () const NOEXCEPTIONS
{
    return !Get();
}

bool AtomicValue<bool>::Get () const NOEXCEPTIONS
{
    int* pFlag = const_cast<int*>(&m_flag);
    return __sync_add_and_fetch(pFlag, 0);
}

void AtomicValue<bool>::Set () NOEXCEPTIONS
{
    __sync_val_compare_and_swap(&m_flag, 0, 1);
}

void AtomicValue<bool>::Clear () NOEXCEPTIONS
{
    __sync_val_compare_and_swap(&m_flag, 1, 0);
}

} // advcpp