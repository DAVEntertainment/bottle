#include <iostream>
#include "boost/dll/shared_library.hpp"

// although we don't share definition of del, but the symbol is there anyway,
//  we can use them by simply declaring the signature
#define DEF_API __declspec(dllimport)
DEF_API int del(int, int);
DEF_API int add(int, int);


int main(int argc, char* argv[]) {
    int x = 10;
    int y = 1;

    // directly call functions from dll
    {
        // call public function
        std::cout << "directly calling public function from dll" << std::endl;
        std::cout << x << " + " << y << " = " << add(x, y) << std::endl;
        // call private function
        std::cout << "directly calling private function from dll" << std::endl;
        std::cout << x << " - " << y << " = " << del(x, y) << std::endl;
    }

    // dynamically load dll with boost::dll
    {
        #ifdef _DEBUG
            const char* demo_lib_name = "demod.dll";
        #else
            const char* demo_lib_name = "demo.dll";
        #endif
        boost::dll::shared_library shared(demo_lib_name);
        // call public function
        auto add_func = shared.get<int(int, int)>("add");
        std::cout << "directly calling public function from dll" << std::endl;
        std::cout << x << " + " << y << " = " << add_func(x, y) << std::endl;
        // call private function
        auto del_func = shared.get<int(int, int)>("del");
        std::cout << "directly calling private function from dll" << std::endl;
        std::cout << x << " - " << y << " = " << del_func(x, y) << std::endl;
    }

    return 0;
}
