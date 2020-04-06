#ifndef TEST_CONTROLLER_AGENT_HPP
#define TEST_CONTROLLER_AGENT_HPP

#include "Event.hpp"

namespace testSmartHome
{

class TestControllerAgent
{
public:
    //TestControllerAgent () = default;
    //TestControllerAgent (const TestControllerAgent& a_other) = default;
    //~TestControllerAgent () = default;
    //TestControllerAgent& operator= (const TestControllerAgent& a_other) = default;

    void PushEvent (const SmartHome::Event& a_event); // prints
    const SmartHome::Event& GetEvent () const;

private:
    SmartHome::Event m_event;
};

inline const SmartHome::Event& TestControllerAgent::GetEvent () const
{
    return m_event;
}

} // testSmartHome

#endif // TEST_CONTROLLER_AGENT_HPP