#include "test_event_hub.hpp"
#include "test_controller_agent.hpp"

namespace test_smart_home
{

TestEventHub::TestEventHub (const SharedPtr<smart_home::IPullEventBuss<SharedPtr<smart_home::Event> > >& a_pullBus)
    : m_pullBus(a_pullBus)
    , m_subscribers()
{ }

void TestEventHub::Subscribe (const TestControllerAgent& a_controller)
{
    m_subscribers.push_back(a_controller);
}

void TestEventHub::DistributeEvent ()
{
    SharedPtr<smart_home::Event> pEvent;
    m_pullBus->Dequeue(pEvent);

    for (std::list<TestControllerAgent>::iterator itr = m_subscribers.begin()
    ; itr != m_subscribers.end()
    ; ++itr)
    {
        itr->PushEvent(*pEvent);
    }
}

} // test_smart_home