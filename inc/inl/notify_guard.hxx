#include <exception> // std::uncaught_exception

namespace advcpp
{

template <typename Predicate, typename NormalHandler>
NotifyGuard<Predicate, NormalHandler>::NotifyGuard (CondVar& a_condVar, Mutex& a_mutex
        , Predicate a_predicate, NormalHandler a_normal, bool a_all)
    : m_condVar(a_condVar)
    , m_normal(a_normal)
    , m_all(a_all)
    //, m_engaged(true)
{
    m_condVar.Wait(a_mutex, a_predicate);
}

template <typename Predicate, typename NormalHandler>
NotifyGuard<Predicate, NormalHandler>::~NotifyGuard () NOEXCEPTIONS
{
    if (std::uncaught_exception()) // called because of an exception
    {
        !m_all ? m_condVar.NotifyOne() : m_condVar.NotifyAll();
    }
    else // no exception
    {
        m_normal();
    }
}

/*
template <typename Predicate, typename NormalHandler>
NotifyGuard<Predicate, NormalHandler>::~NotifyGuard () NOEXCEPTIONS
{
    if (m_engaged)
    {
        !m_all ? m_condVar.NotifyOne() : m_condVar.NotifyAll();
    }
    else
    {
        m_normal();
    }
}
*/

/*
template <typename Predicate, typename NormalHandler>
void NotifyGuard<Predicate, NormalHandler>::Disengage () NOEXCEPTIONS
{
    m_engaged = false;
}
*/

} // advcpp