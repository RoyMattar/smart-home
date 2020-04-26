#include <iostream>
#include <dlfcn.h>

#include "i_cat.hpp"
#include "common_utils.hpp"

using namespace smart_home;

int main ()
{
    void* soHandle = dlopen("libCat.so", RTLD_NOW);
    if (!soHandle)
    {
        std::cerr << "dlopen() failed: " << dlerror() << std::endl;
    }

    void* makerSym = dlsym(soHandle, "MakeICat");
    if (!makerSym)
    {
        std::cerr << "dlsym() failed: " << dlerror() << std::endl;
    }

    typedef SharedPtr<ICat>(*ICatMaker)();
    ICatMaker makeICat = reinterpret_cast<ICatMaker>(makerSym);
    SharedPtr<ICat> icat = makeICat();

    icat->Meow();

    int closeStatus = dlclose(soHandle);
    if (0 != closeStatus)
    {
        std::cerr << "dlclose() failed: " << dlerror() << std::endl;
    }

    return 0;
}