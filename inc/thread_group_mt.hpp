#ifndef THREAD_GROUP_MT_HPP
#define THREAD_GROUP_MT_HPP

#include <vector>
#include <utility> // std::pair
#include <cstddef> // size_t
#include <sys/types.h> // useconds_t

#include "common_utils.hpp"
#include "thread.hpp"
#include "mutex.hpp"

namespace advcpp
{

template <typename Runnable>
//require:  Runnable    is a derived class of IRunnable
//                      implements Run()
class ThreadGroupMT : private Uncopyable
{
public:
    //ThreadGroupMT () = default;
    //~ThreadGroupMT () = default;

    //@brief adds a_numOfThreads to the group, running on a_runnable
    //@exception may throw std::bad_alloc
    void Add (SharedPtr<Runnable> a_runnable, size_t a_numOfThreads = 1);
    //@retval returns current number of threads in group
    size_t NumOfThreads () const NOEXCEPTIONS;
    //@brief joins the thread and removes its entry from the group
    //@exception may throw Thread::Join() exceptions
    //@exception may throw std::out_of_range if a_threadIndex is out of bounds
    void Join (size_t a_threadIndex);
    //@brief tries to join the thread; if succesful, the thread entry is removed from the group
    //@retval true if succesfully joined, false otherwise
    //@exception may throw Thread::TryJoin() exceptions
    //@exception may throw std::out_of_range if a_threadIndex is out of bounds
    bool TryJoin (size_t a_threadIndex);
    //@brief tries to join the thread with a maximum timeout; if succesful, the thread entry is removed from the group
    //@retval true if successfully joined, false if timed out before joining
    //@exception may throw Thread::TimedJoin() exceptions
    //@exception may throw std::out_of_range if a_threadIndex is out of bounds
    bool TimedJoin (size_t a_threadIndex, useconds_t a_timeout);
    //@brief detaches the thread and removes its entry from the group
    //@exception may throw std::out_of_range if a_threadIndex is out of bounds
    void Detach (size_t a_threadIndex);
    //@retval true if none of Join/TryJoin/TimedJoin/Detach had been called, false otherwise
    bool Joinable (size_t a_threadIndex) const NOEXCEPTIONS;
    //@brief cancels the thread (asynchronously - not delayed until next cancellation point)
    //@warning the thread remains joinable
    //@exception may throw Thread::CancelAsync() exceptions
    //@exception may throw std::out_of_range if a_threadIndex is out of bounds
    void CancelAsync (size_t a_threadIndex);

private:
    typedef std::pair<SharedPtr<Runnable>, SharedPtr<Thread> > ThreadPair;
    typedef std::vector<ThreadPair> GroupType;

private:
    GroupType m_group;
    Mutex m_groupMutex;
};

#include "inl/thread_group_mt.hxx"

} // smart_home

#endif // THREAD_GROUP_MT_HPP