#ifndef TEST_CONTROLLER_AGENT_HPP
#define TEST_CONTROLLER_AGENT_HPP

#include "event.hpp"

namespace test_smart_home
{

class TestControllerAgent
{
public:
    TestControllerAgent ();
    //TestControllerAgent (const TestControllerAgent& a_other) = default;
    //~TestControllerAgent () = default;
    //TestControllerAgent& operator= (const TestControllerAgent& a_other) = default;

    void PushEvent (const smart_home::Event& a_event); // prints
    const smart_home::Event& GetEvent () const;

private:
    smart_home::Event m_event;
};

inline const smart_home::Event& TestControllerAgent::GetEvent () const
{
    return m_event;
}

} // test_smart_home

#endif // TEST_CONTROLLER_AGENT_HPP