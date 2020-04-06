#include "TestEventHub.hpp"
#include "TestControllerAgent.hpp"

namespace testSmartHome
{

TestEventHub::TestEventHub (const SharedPtr<SmartHome::iDequeueableQueue<SharedPtr<SmartHome::Event> > >& a_pDeqableQ)
    : m_pDeqableQ(a_pDeqableQ)
    , m_subscribers()
{ }

void TestEventHub::Subscribe (const TestControllerAgent& a_controller)
{
    m_subscribers.push_back(a_controller);
}

void TestEventHub::DistributeEvent ()
{
    SharedPtr<SmartHome::Event> pEvent;
    m_pDeqableQ->Dequeue(pEvent);

    for (std::list<TestControllerAgent>::iterator itr = m_subscribers.begin()
    ; itr != m_subscribers.end()
    ; ++itr)
    {
        itr->PushEvent(*pEvent);
    }
}

} // testSmartHome