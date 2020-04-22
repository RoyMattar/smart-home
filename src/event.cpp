#include <iostream>
#include <string>

#include "event.hpp"
#include "common_utils.hpp"

namespace smart_home
{

Event::Location::Location (Floor const& a_floor, Room const& a_room)
    : m_floor(a_floor)
    , m_room(a_room)
{ }

Event::Event (Type const& a_type, Timestamp const& a_timestamp
             , Payload const& a_payload, Location const& a_location) NOEXCEPTIONS
    : m_type(a_type)
    , m_timestamp(a_timestamp)
    , m_payload(a_payload)
    , m_location(a_location)
{ }

void Event::Print () const NOEXCEPTIONS
{
    std::cout << "Event type: " << m_type << std::endl
              << "Event timestamp: " << m_timestamp << std::endl
              << "Event payload: " << m_payload << std::endl
              << "Event location: Floor " << m_location.GetFloor()
                              << " Room " << m_location.GetRoom() << std::endl;
}

} // smart_home