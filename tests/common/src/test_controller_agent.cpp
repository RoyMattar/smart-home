#include <iostream>

#include "test_controller_agent.hpp"

namespace test_smart_home
{

TestControllerAgent::TestControllerAgent ()
    : m_event("", "", "", "")
{ }

void TestControllerAgent::PushEvent (const smart_home::Event& a_event)
{
    m_event = a_event;
    m_event.Print();
}

} // test_smart_home