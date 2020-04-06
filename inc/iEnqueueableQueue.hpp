#ifndef I_ENQUEUEABLE_QUEUE_HPP
#define I_ENQUEUEABLE_QUEUE_HPP

#include "common_utils.hpp"

namespace SmartHome
{

template <typename T>
class iEnqueueableQueue
{
public:
    virtual ~iEnqueueableQueue () NOEXCEPTIONS;

    virtual void Enqueue (const T& a_elem) = 0;
    virtual size_t NumOfElems () const NOEXCEPTIONS = 0;
    virtual size_t Capacity () const NOEXCEPTIONS = 0;
};

template <typename T>
iEnqueueableQueue<T>::~iEnqueueableQueue () NOEXCEPTIONS
{ }

} // SmartHome

#endif // I_ENQUEUEABLE_QUEUE_HPP