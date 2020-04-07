#ifndef I_REGISTRAR_HPP
#define I_REGISTRAR_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{
class ISubscriber;

class IRegistrar
{
public:
    virtual ~IRegistrar ();

    virtual void Register (SharedPtr<ISubscriber> const& a_newSubscriber, Event::Type a_eventType);
};

inline IRegistrar::~IRegistrar ()
{ }

} // smart_home

#endif // I_REGISTRAR_HPP