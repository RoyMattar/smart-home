#ifndef I_CONSUMER_GROUP_MT_HPP
#define I_CONSUMER_GROUP_MT_HPP

#include <vector>

#include "common_utils.hpp"
#include "i_event_consumer.hpp"

namespace smart_home
{

class IConsumerGroupMT : private advcpp::Uncopyable
{
public:
    virtual ~IConsumerGroupMT ();

    virtual void Add (SharedPtr<IEventConsumer> const& a_eventConsumer);
    virtual void Remove (SharedPtr<IEventConsumer> const& a_eventConsumer);
    virtual SharedPtr<std::vector<SharedPtr<IEventConsumer> > > GetAll () const;
};

inline IConsumerGroupMT::~IConsumerGroupMT ()
{ }

} // smart_home

#endif // I_CONSUMER_GROUP_MT_HPP