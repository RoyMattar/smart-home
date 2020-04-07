#include <iostream>
#include <string>

#include "event.hpp"
#include "common_utils.hpp"

namespace smart_home
{

Event::Event (const Type& a_type, const Timestamp& a_timestamp
        , const Payload& a_payload, const Location& a_location)
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

} // smart_home