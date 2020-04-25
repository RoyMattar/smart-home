#include "lock_guard.hpp"

namespace advcpp
{

template <typename Runnable>
void ThreadGroupMT<Runnable>::Add (SharedPtr<Runnable> a_runnable, size_t a_numOfThreads)
{
    LockGuard lg(m_groupMutex);
    for (size_t i = 0; i < a_numOfThreads; ++i)
    {
        m_group.push_back(std::make_pair(a_runnable, SharedPtr<Thread>(new Thread(a_runnable))));
    }
}

template <typename Runnable>
size_t ThreadGroupMT<Runnable>::NumOfThreads () const NOEXCEPTIONS
{
    LockGuard lg(const_cast<ThreadGroupMT*>(this)->m_groupMutex);
    return m_group.size();
}

template <typename Runnable>
void ThreadGroupMT<Runnable>::Join (size_t a_threadIndex)
{
    LockGuard lg(m_groupMutex);
    m_group.at(a_threadIndex).second->Join();
    m_group.erase(m_group.begin() + a_threadIndex);
}

template <typename Runnable>
bool ThreadGroupMT<Runnable>::TryJoin (size_t a_threadIndex)
{
    LockGuard lg(m_groupMutex);

    bool result = m_group.at(a_threadIndex).second->TryJoin();
    if (result)
    {
        m_group.erase(m_group.begin() + a_threadIndex);
    }
    return result;
}

template <typename Runnable>
bool ThreadGroupMT<Runnable>::TimedJoin (size_t a_threadIndex, useconds_t a_timeout)
{
    LockGuard lg(m_groupMutex);

    bool result = m_group.at(a_threadIndex).second->TimedJoin(a_timeout);
    if (result)
    {
        m_group.erase(m_group.begin() + a_threadIndex);
    }
    return result;
}

template <typename Runnable>
void ThreadGroupMT<Runnable>::Detach (size_t a_threadIndex)
{
    LockGuard lg(m_groupMutex);
    m_group.at(a_threadIndex).second->Detach();
    m_group.erase(m_group.begin() + a_threadIndex);
}

template <typename Runnable>
bool ThreadGroupMT<Runnable>::Joinable (size_t a_threadIndex) const NOEXCEPTIONS
{
    LockGuard lg(const_cast<ThreadGroupMT*>(this)->m_groupMutex);
    return m_group.at(a_threadIndex).second->IsJoinable();
}

template <typename Runnable>
void ThreadGroupMT<Runnable>::CancelAsync (size_t a_threadIndex)
{
    LockGuard lg(m_groupMutex);
    m_group.at(a_threadIndex).second->CancelAsync();
}

} // advcpp