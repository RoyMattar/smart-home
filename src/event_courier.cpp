#include <iostream> // std::cerr
#include <cassert>

#include "event_courier.hpp"
#include "common_utils.hpp"
#include "i_pull_distribution_channel.hpp"
#include "delivery_box.hpp"
#include "event.hpp"
#include "i_event_consumer.hpp"
#include "toxic_agent.hpp"

namespace smart_home
{

EventCourier::EventCourier (SharedPtr<IPullDistributionChannel> const& a_pullChannel)
    : m_pullChannel(a_pullChannel)
{ }

void EventCourier::Run ()
{
    while (true)
    {
        SharedPtr<DeliveryBox> deliveryBox;
        try
        {
            m_pullChannel->Pull(deliveryBox);
        }
        catch (IPullDistributionChannelShutdownExc const&)
        {
            break;
        }

        SharedPtr<Event> event = deliveryBox->first;
        SharedPtr<IEventConsumer> consumer = deliveryBox->second;
        try
        {
            handOutEventToConsumer(event, consumer);
        }
        catch (ToxicAgent::ToxicAgentExc const&)
        {
            break;
        }
    }
}

void EventCourier::handOutEventToConsumer (SharedPtr<Event> const& a_event, SharedPtr<IEventConsumer> const& a_consumer)
{
    try
    {
        a_consumer->Consume(a_event);
    }
    catch (ToxicAgent::ToxicAgentExc const& a_toxic)
    {
        throw;
    }
    catch (std::exception const& a_e)
    {
        std::cerr << a_e.what() << std::endl;
        assert(!"Unsafe IEventConsumer::Consume()");
        //TODO: log
    }
    catch (...)
    {
        assert(!"Non documented exception thrown by IEventConsumer::Consume()");
        //TODO: log
    }
}

} // smart_home