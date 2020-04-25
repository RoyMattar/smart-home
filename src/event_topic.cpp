#include <iostream>

#include "event_topic.hpp"
#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

const Event::Type EventTopic::ANY_TYPE = "*";
const Event::Location EventTopic::ANY_LOCATION(ANY_FLOOR, ANY_ROOM);
const Event::Location::Floor EventTopic::ANY_FLOOR = "*";
const Event::Location::Room EventTopic::ANY_ROOM = "*";

EventTopic::EventTopic (Event::Type const& a_type, Event::Location const& a_location) NOEXCEPTIONS
    : m_type(a_type)
    , m_location(a_location)
{ }

EventTopic::EventTopic (Event const& a_event) NOEXCEPTIONS
    : m_type(a_event.GetType())
    , m_location(a_event.GetLocation())
{ }

void EventTopic::Print () const NOEXCEPTIONS
{
    std::cout << "t-" << m_type << ":"
              << "f-" << m_location.GetFloor() << ":"
              << "r-" << m_location.GetRoom();
}

} // smart_home