1. subscription/registration:
write class implementing IConsumerRegistrar
implementation of Register will turn a global bool registered into true
write class implementing IEventSubscriber, will also have GetID(), IsDelivered() (Consume turns a flag true)
call subscribe through IEventSubscriber
check if global bool is true

2. listing:
use implemented test class of IEventSubscriber
integrate flow with ConsumerMap
call Subscribe on a few instances of subscriber (test impl)
call List through IConsumerLister
iterate through the vector, call GetID, check id's

3. distribution:
declare an array of subscribers (test impl)
write test alt of EventMiddleWare - Mediate(Event) - single event
integrate flow with it
call Subscribe on a few instances of subscriber (test impl)
call Mediate
go through the array and check IsDelivered()

4. complete:
integrate with publish flow
call Subscribe on a few test agents
call Publish on a few events
check IsDelivered on the test agents