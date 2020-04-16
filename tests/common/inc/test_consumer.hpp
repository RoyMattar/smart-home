#ifndef TEST_CONSUMER_HPP
#define TEST_CONSUMER_HPP

#include "common_utils.hpp"
#include "i_event_subscriber.hpp"
#include "i_event_consumer.hpp"
#include "event.hpp"
#include "i_consumer_registrar.hpp"

namespace smart_home
{

class TestConsumer : public IEventSubscriber, public IEventConsumer, public std::tr1::enable_shared_from_this<TestConsumer>
{
public:
    TestConsumer (Event::Type const& a_eventType);
    //TestConsumer (TestConsumer const& a_other);
    //~TestConsumer ();
    //TestConsumer& operator= (TestConsumer& a_other);

    virtual void Subscribe (SharedPtr<IConsumerRegistrar> const& a_consumerRegistrar);
    virtual void Consume (SharedPtr<Event> const& a_pEvent);
    int GetID () const;
    bool IsEventDelivered () const;

private:
    static int s_id;
    
    Event::Type m_eventType;
    int m_id;
    bool m_isEventDelivered;
};

} // smart_home

#endif // TEST_CONSUMER_HPP