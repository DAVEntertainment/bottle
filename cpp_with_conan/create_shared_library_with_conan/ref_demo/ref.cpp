#include <iostream>
#include "declare.h"

// although we don't share definition of del, but the symbol is there anyway,
//  we can use them by simply declaring the signature
#define DEF_API extern "C" __declspec(dllimport) /* extern "C" is necessary for exported symbol to name simply with C style */
DEF_API int add(int, int);

int main(int argc, char* argv[]) {
    int x = 10;
    int y = 1;

    std::cout << x << " + " << y << " = " << add(x, y) << std::endl;

    return 0;
}
