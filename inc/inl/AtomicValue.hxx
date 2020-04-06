namespace advcpp
{

template <typename T>
AtomicValue<T>::AtomicValue (T a_val) NOEXCEPTIONS
    : m_val(a_val)
{ }

template <typename T>
void AtomicValue<T>::operator+= (T a_val) NOEXCEPTIONS
{
    __sync_add_and_fetch(&m_val, a_val);
}

template <typename T>
void AtomicValue<T>::operator-= (T a_val) NOEXCEPTIONS
{
    __sync_sub_and_fetch(&m_val, a_val);
}

template <typename T>
T AtomicValue<T>::operator++ () NOEXCEPTIONS
{
    return __sync_add_and_fetch(&m_val, 1);
}

template <typename T>
T AtomicValue<T>::operator-- () NOEXCEPTIONS
{
    return __sync_sub_and_fetch(&m_val, 1);
}

template <typename T>
T AtomicValue<T>::Value () NOEXCEPTIONS
{
    return __sync_add_and_fetch(&m_val, 0);
}

template <typename T>
void AtomicValue<T>::Value (T a_val) NOEXCEPTIONS
{
    __sync_val_compare_and_swap(&m_val, m_val, a_val);
}

} // advcpp