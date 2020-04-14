#ifndef EVENT_MIDDLEWARE_HPP
#define EVENT_MIDDLEWARE_HPP

#include <tr1/unordered_map>

#include "common_utils.hpp"
#include "event.hpp"
#include "i_pull_event_bus.hpp"
#include "i_handlers_registrar.hpp"
#include "i_event_distributor.hpp"
#include "i_event_subscriber.hpp"

namespace smart_home
{

class EventMiddleware : private advcpp::Uncopyable
{
public:
    EventMiddleware (SharedPtr<IPullEventBus> const& a_pullBus,
        SharedPtr<IHandlersRegistrar> const& a_handlersRegistrar,
        SharedPtr<IEventDistributor> const& a_eventDistributor); // or refs?
    //~EventMiddleware () = default;

    void RequestSubscription (SharedPtr<ISubscriber> const& a_subscriber);
    void MediateEvents ();

private:
    SharedPtr<IPullEventBus> m_pullBus;
    SharedPtr<IHandlersRegistrar> m_handlersRegistrar;
    SharedPtr<IEventDistributor> m_eventDistributor;
};

} // smart_home

#endif // EVENT_MIDDLEWARE_HPP