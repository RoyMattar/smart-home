#include "toxic_agent.hpp"
#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

void ToxicAgent::Consume (SharedPtr<Event> const& a_pEvent)
{
    throw ToxicAgentExc();
}

} // smart_home