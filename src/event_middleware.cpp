#include "event_middleware.hpp"
#include "common_utils.hpp"
#include "i_pull_event_bus.hpp"
#include "i_registrar.hpp"
#include "i_distributor.hpp"
#include "i_subscriber.hpp"
#include "event.hpp"

namespace smart_home
{

EventMiddleware::EventMiddleware (SharedPtr<IPullEventBus> const& a_pullBus,
        SharedPtr<IRegistrar> const& a_registrar,
        SharedPtr<IDistributor> const& a_distributor)
    : m_pullBus(a_pullBus)
    , m_registrar(a_registrar)
    , m_distributor(a_distributor)
{ }

void EventMiddleware::RequestSubscription (SharedPtr<ISubscriber> const& a_subscriber)
{
    a_subscriber->Subscribe(m_registrar);
}

void EventMiddleware::MediateEvents ()
{
    while (true)
    {
        SharedPtr<Event> pEvent;
        m_pullBus->Pull(pEvent);
        m_distributor->Distribute(pEvent); // warning: should guarantee exception safety
    }
}

} // smart_home