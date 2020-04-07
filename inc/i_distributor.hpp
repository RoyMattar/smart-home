#ifndef I_DISTRIBUTOR_HPP
#define I_DISTRIBUTOR_HPP

#include "common_utils.hpp"
#include "event.hpp"

namespace smart_home
{

class IDistributor
{
public:
    virtual ~IDistributor ();

    virtual void Distribute (SharedPtr<Event> const& a_pEvent);
};

inline IDistributor::~IDistributor ()
{ }

} // smart_home

#endif // I_DISTRIBUTOR_HPP