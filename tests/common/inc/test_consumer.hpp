#ifndef TEST_CONSUMER_HPP
#define TEST_CONSUMER_HPP

#include <cstddef> // size_t

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
    TestConsumer (Event::Type const& a_eventType, Event::Location const& a_eventLocation);
    //TestConsumer (TestConsumer const& a_other);
    //~TestConsumer ();
    //TestConsumer& operator= (TestConsumer& a_other);

    virtual void Subscribe (SharedPtr<IConsumerRegistrar> const& a_consumerRegistrar);
    virtual void Consume (SharedPtr<Event> const& a_pEvent);
    Event::Type const& GetType () const;
    Event::Location const& GetLocation () const;
    size_t CountDelivered () const;

private:
    Event::Type m_eventType;
    Event::Location m_eventLocation;
    size_t m_countDelivered;
};

inline Event::Type const& TestConsumer::GetType () const
{
    return m_eventType;
}

inline Event::Location const& TestConsumer::GetLocation () const
{
    return m_eventLocation;
}

inline size_t TestConsumer::CountDelivered () const
{
    return m_countDelivered;
}

} // smart_home

#endif // TEST_CONSUMER_HPP