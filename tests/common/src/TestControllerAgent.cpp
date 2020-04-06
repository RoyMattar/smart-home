#include <iostream>

#include "TestControllerAgent.hpp"

namespace testSmartHome
{

void TestControllerAgent::PushEvent (const SmartHome::Event& a_event)
{
    m_event = a_event;
    m_event.Print();
}

} // testSmartHome