#ifndef NOTIFY_GUARD_HPP
#define NOTIFY_GUARD_HPP

#include "common_utils.hpp"
#include "condvar.hpp"
#include "mutex.hpp"

namespace advcpp
{

template <typename Predicate, typename NormalHandler>
//require:  Predicate           has bool operator()() - nullary boolean function operator
//          NormalHandler   has operator()() - nullary function operator (retval is ignored)
class NotifyGuard : private Uncopyable
{
public:
    //@brief: Calls void CondVar::Wait(Mutex& a_mutex, Predicate a_predicate)
    //@param[in]: a_condvar - the condition variable which notify action shall be guarded
    //            a_mutex - to be passed to CondVar::Wait
    //            a_predicate - to be passed to CondVar::Wait
    //            a_normal - a handler which function operator shall be called
    //                       in case of normal exit of scope ***OR*** in case Disengage() had not been called
    //            a_all - whether CondVar::NotifyOne or CondVar::NotifyAll should be called
    NotifyGuard (CondVar& a_condVar, Mutex& a_mutex, Predicate a_predicate
                , NormalHandler a_normal, bool a_all = false);

    //@brief:  If stack is unwound due to an exception having been thrown,
    //         notifies either one or all of waiting threads - depending on m_all.
    //         Otherwise, in case of normal exit of scope, no Notify is called and
    //         NormalHandler's function operator is called instead.
    //         
    //***OR*** Either one or all of waiting threads are notified - depending on m_all.
    //         If Disengage() had been called, no Notify is called and
    //         NormalHandler's function operator is called instead.
    ~NotifyGuard () NOEXCEPTIONS;

    //@brief:  Disengages NotifyGuard from guarding the notify action. When ~NotifyGuard()
    //         is called, NormalHandler's function operation will be called instead
    //void Disengage () NOEXCEPTIONS;

private:
    CondVar& m_condVar;
    NormalHandler m_normal;
    bool m_all;
    //bool m_engaged;
};

} // advcpp

#include "inl/notify_guard.hxx"

#endif // NOTIFY_GUARD_HPP