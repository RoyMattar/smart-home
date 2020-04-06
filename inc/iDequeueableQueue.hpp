#ifndef I_DEQUEUEABLE_QUEUE
#define I_DEQUEUEABLE_QUEUE

#include "common_utils.hpp"

namespace SmartHome
{

template <typename T>
class iDequeueableQueue
{
public:
    virtual ~iDequeueableQueue () NOEXCEPTIONS;

    virtual void Dequeue (T& a_elemRef) = 0;
    virtual size_t NumOfElems () const NOEXCEPTIONS = 0;
    virtual size_t Capacity () const NOEXCEPTIONS = 0;
};

template <typename T>
iDequeueableQueue<T>::~iDequeueableQueue () NOEXCEPTIONS
{ }

} // SmartHome

#endif // I_DEQUEUEABLE_QUEUE