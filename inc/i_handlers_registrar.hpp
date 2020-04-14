#ifndef I_HANDLERS_REGISTRAR_HPP
#define I_HANDLERS_REGISTRAR_HPP

#include "common_utils.hpp"
#include "event.hpp"
#include "i_event_handler.hpp"

namespace smart_home
{

class IHandlersRegistrar
{
public:
    virtual ~IHandlersRegistrar ();

    virtual void Register (Event::Type a_eventType, SharedPtr<IEventHandler> const& a_eventHandler);
};

inline IHandlersRegistrar::~IHandlersRegistrar ()
{ }

} // smart_home

#endif // I_HANDLERS_REGISTRAR_HPP