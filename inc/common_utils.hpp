#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#define NOEXCEPTIONS throw()

// Conversions
#define MILLI_TO_MICRO(x) (x)*1000
#define MICRO_TO_NANO(x) (x)*1000
#define NANO_TO_MICRO(x) (x)/1000

// SharedPtr
#if defined(__APPLE__) || (_WIN32)
#include <memory>
#define SharedPtr std::shared_ptr
#else
#include <tr1/memory> // post 2003 : ~= 2004
#define SharedPtr std::tr1::shared_ptr // to use
// tr1/memory library - de jure not part of std 2003
// de facto all compilers supporting 2003 do have a TR1 implementation
#endif // MacOS or Windows

namespace advcpp
{

class Unassignable
{
protected:
    Unassignable () { }
    ~Unassignable () { }

private:
    Unassignable& operator= (const Unassignable& a_other);
};

class Uncopyable : private Unassignable
{
protected:
    Uncopyable () { }
    ~Uncopyable () { }

private:
    Uncopyable (const Uncopyable& a_other);
};

// Restricted friendship
#define PASSKEY(PASSKEY_NAME, FRIEND_NAME)              \
    class PASSKEY_NAME                                  \
    {                                                   \
    private:                                            \
        friend FRIEND_NAME;                             \
        PASSKEY_NAME () { }                             \
        PASSKEY_NAME (const PASSKEY_NAME&);             \
        PASSKEY_NAME& operator= (const PASSKEY_NAME&);  \
    }                                                   \

} // advcpp

#endif // COMMON_UTILS_HPP