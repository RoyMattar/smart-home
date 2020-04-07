#ifndef EVENT_MIDDLEWARE_HPP
#define EVENT_MIDDLEWARE_HPP

#include <tr1/unordered_map>

#include "common_utils.hpp"
#include "event.hpp"
#include "i_pull_event_bus.hpp"
#include "i_registrar.hpp"
#include "i_distributor.hpp"
#include "i_subscriber.hpp"

namespace smart_home
{

class EventMiddleware : private advcpp::Uncopyable
{
public:
    EventMiddleware (SharedPtr<IPullEventBus> const& a_pullBus,
        SharedPtr<IRegistrar> const& a_registrar,
        SharedPtr<IDistributor> const& a_distributor); // or refs?
    //~EventMiddleware () = default;

    void RequestSubscription (SharedPtr<ISubscriber> const& a_subscriber);
    void MediateEvents ();

private:
    SharedPtr<IPullEventBus> m_pullBus;
    SharedPtr<IRegistrar> m_registrar;
    SharedPtr<IDistributor> m_distributor;
};

} // smart_home

#endif // EVENT_MIDDLEWARE_HPP