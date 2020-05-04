#ifndef SO_LIB_HANDLER_HPP
#define SO_LIB_HANDLER_HPP

#include <stdexcept> // std::exception
#include <string>
#include <dlfcn.h>

#include "common_utils.hpp"

namespace advcpp
{

class SOLibHandler : private Uncopyable
{
public:
    //@exception: throws DLOpenExc
    SOLibHandler (const char* a_libName, int a_flags = RTLD_NOW);
    ~SOLibHandler () NOEXCEPTIONS;

    template <typename SP>
    //@exception: throws DLSymExc
    SP GetSymbolPtr (const char* a_symbolName) const;

private:
    void* m_handle;
};

struct DLSymExc : public std::exception
{
    DLSymExc (std::string const& a_dlerror);
    ~DLSymExc () NOEXCEPTIONS;
    virtual const char* what () const NOEXCEPTIONS;
    std::string m_what;
};

template <typename SP>
SP SOLibHandler::GetSymbolPtr (const char* a_symbolName) const
{
    void* symPtr = dlsym(m_handle, a_symbolName);
    if (symPtr == 0)
    {
        throw DLSymExc(dlerror());
    }
    return reinterpret_cast<SP>(symPtr);
}

} // advcpp

#endif // SO_LIB_HANDLER_HPP