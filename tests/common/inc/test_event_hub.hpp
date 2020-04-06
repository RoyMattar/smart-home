#ifndef TEST_EVENT_HUB_HPP
#define TEST_EVENT_HUB_HPP

#include <list>

#include "common_utils.hpp"
#include "i_pull_event_bus.hpp"
#include "event.hpp"

namespace test_smart_home
{
class TestControllerAgent;

class TestEventHub
{
public:
    TestEventHub (const SharedPtr<smart_home::IPullEventBuss<SharedPtr<smart_home::Event> > >& a_pullBus);
    //TestEventHub (const TestEventHub& a_other) = default;
    //~TestEventHub () = default;
    //TestEventHub& operator= (const TestEventHub& a_other) = default;

    void Subscribe (const TestControllerAgent& a_controller);
    void DistributeEvent ();

private:
    SharedPtr<smart_home::IPullEventBuss<SharedPtr<smart_home::Event> > > m_pullBus;
    std::list<TestControllerAgent> m_subscribers;
};

} // test_smart_home

#endif // TEST_EVENT_HUB_HPP