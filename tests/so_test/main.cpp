#include <iostream>

#include "i_cat.hpp"
#include "common_utils.hpp"
#include "so_lib_handler.hpp"

using namespace advcpp;
using namespace smart_home;

int main ()
{
    SOLibHandler so("libCat.so");

    typedef SharedPtr<ICat>(*CatMaker)();
    CatMaker makeCat = so.GetSymbolPtr<CatMaker>("MakeCat");
    
    SharedPtr<ICat> cat = makeCat();

    cat->Meow();

    return 0;
}