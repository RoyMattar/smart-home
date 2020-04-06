#include <iostream>
#include <string>

#include "Event.hpp"
#include "common_utils.hpp"

namespace SmartHome
{

Event::Event ()
    : m_type()
    , m_timestamp()
    , m_payload()
    , m_location()
{ }

Event::Event (const EventType& a_type, const EventTimestamp& a_timestamp
        , const EventPayload& a_payload, const EventLocation& a_location)
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
              << "Event location: " << m_location << std::endl;
}

} // SmartHome