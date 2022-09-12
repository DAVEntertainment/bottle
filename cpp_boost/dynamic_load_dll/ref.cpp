#include <iostream>
#include "boost/dll/shared_library.hpp"
#include "boost/dll/runtime_symbol_info.hpp"

// although we don't share definition of del, but the symbol is there anyway,
//  we can use them by simply declaring the signature
#define DEF_API extern "C" __declspec(dllimport) /* extern "C" is necessary for exported symbol to name simply with C style */
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
        auto exe = boost::dll::program_location();
        auto exe_root = boost::dll::program_location().parent_path();
        auto demo_lib_path = exe_root / demo_lib_name;
        std::cout << "executing " << exe << std::endl;
        std::cout << "loading " << demo_lib_path << std::endl;
        boost::dll::shared_library shared(demo_lib_path);
        if (shared.is_loaded()) {
            std::cout << "load success" << std::endl;
            // call public function
            if(shared.has("add")) {
                auto add_func = shared.get<int(int, int)>("add");
                std::cout << "dynamically calling public function from " << demo_lib_path << std::endl;
                std::cout << x << " + " << y << " = " << add_func(x, y) << std::endl;
            } else {
                std::cout << "\"add \"not exists" << std::endl;
            }
            // call private function
            if(shared.has("del")) {
                auto del_func = shared.get<int(int, int)>("del");
                std::cout << "dynamically calling private function from " << demo_lib_path << std::endl;
                std::cout << x << " - " << y << " = " << del_func(x, y) << std::endl;
            } else {
                std::cout << "\"del\" not exists" << std::endl;
            }
        } else {
            std::cout << "load failed, abort !" << std::endl;
        }
    }

    return 0;
}
