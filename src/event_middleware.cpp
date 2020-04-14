#include "event_middleware.hpp"
#include "common_utils.hpp"
#include "i_pull_event_bus.hpp"
#include "i_handlers_registrar.hpp"
#include "i_event_distributor.hpp"
#include "i_event_subscriber.hpp"
#include "event.hpp"

namespace smart_home
{

EventMiddleware::EventMiddleware (SharedPtr<IPullEventBus> const& a_pullBus,
        SharedPtr<IHandlersRegistrar> const& a_handlersRegistrar,
        SharedPtr<IEventDistributor> const& a_eventDistributor)
    : m_pullBus(a_pullBus)
    , m_handlersRegistrar(a_handlersRegistrar)
    , m_eventDistributor(a_eventDistributor)
{ }

void EventMiddleware::RequestSubscription (SharedPtr<ISubscriber> const& a_subscriber)
{
    a_subscriber->Subscribe(m_handlersRegistrar);
}

void EventMiddleware::MediateEvents ()
{
    while (true)
    {
        SharedPtr<Event> pEvent;
        m_pullBus->Pull(pEvent);
        m_eventDistributor->Distribute(pEvent); // warning: should guarantee exception safety
    }
}

} // smart_home