#include "mu_test.h"

#include "common_utils.hpp"
#include "event.hpp"
#include "i_consumer_registrar.hpp"
#include "i_event_subscriber.hpp"
#include "i_event_consumer.hpp"
#include "test_consumer.hpp"

using namespace advcpp;
using namespace smart_home;

bool g_isRegistered = false;

class TestRegistrar : public IConsumerRegistrar
{
public:
    //TestRegistrar ();
    //TestRegistrar (TestRegistrar const& a_other);
    //~TestRegistrar ();
    //TestRegistrar& operator= (TestRegistrar const& a_other);

    virtual void Register (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_newConsumer)
    {
        g_isRegistered = true;
    }

    virtual void Deregister (Event::Type const& a_eventType, SharedPtr<IEventConsumer> const& a_oldConsumer)
    { }
};

UNIT(registration)
    SharedPtr<IConsumerRegistrar> reg(new TestRegistrar());
    SharedPtr<IEventSubscriber> sub(new TestConsumer("type_fire"));

    ASSERT_EQUAL(g_isRegistered, false);
    sub->Subscribe(reg);
    ASSERT_EQUAL(g_isRegistered, true);
END_UNIT

TEST_SUITE(registration)
    TEST(registration)
END_SUITE