#include "demo/add.h"
#include <iostream>

// although we don't share del.h, but the symbol is there anyway,
//  we can use them by simply declare the signature,
//  with CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS enabled,
//  we don't need to specify __declspec(dllimport)
//  for functions or classes,
//  but still need for variables
int del(int, int);

// library Sub::sub is linked to Demo::demo as PRIVATE
//  so we can't access to it here.
//  although we can link Sub::sub to Demo::demo as PUBLIC,
//  then lib_ref_demo need to find_package Sub so that
//  the dependency of Sub::sub passed by Demo::demo is
//  accessible
// int sub(int, int);

int main() {
    int x = 10;
    int y = 1;
    int z = add(x, y);
    int d = del(x, y);
    // int e = sub(x, y);
    std::cout << x << " + " << y << " = " << z << std::endl;
    std::cout << x << " - " << y << " = " << d << std::endl;
    // std::cout << x << " - " << y << " = " << e << std::endl;
    return 0;
}
