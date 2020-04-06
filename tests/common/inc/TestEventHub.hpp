#ifndef TEST_EVENT_HUB_HPP
#define TEST_EVENT_HUB_HPP

#include <list>

#include "common_utils.hpp"
#include "iDequeueableQueue.hpp"
#include "Event.hpp"

namespace testSmartHome
{
class TestControllerAgent;

class TestEventHub
{
public:
    TestEventHub (const SharedPtr<SmartHome::iDequeueableQueue<SharedPtr<SmartHome::Event> > >& a_pDeqableQ);
    //TestEventHub (const TestEventHub& a_other) = default;
    //~TestEventHub () = default;
    //TestEventHub& operator= (const TestEventHub& a_other) = default;

    void Subscribe (const TestControllerAgent& a_controller);
    void DistributeEvent ();

private:
    SharedPtr<SmartHome::iDequeueableQueue<SharedPtr<SmartHome::Event> > > m_pDeqableQ;
    std::list<TestControllerAgent> m_subscribers;
};

} // testSmartHome

#endif // TEST_EVENT_HUB_HPP