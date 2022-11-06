#include "add.h"
#include <iostream>

// although we don't share del.h, but the symbol is there anyway,
//  we can use them by simply declare the signature
DEF_API int del(int, int);

// even if we declare product here(in either way),
//  the symbol of "product" cannot be found,
//  cause product is not declared when export with DEF_API
// DEF_API int product(int, int);
// // int product(int, int);

int main() {
    int x = 10;
    int y = 1;
    int z = add(x, y);
    int d = del(x, y);
    // int e = product(x, y);
    std::cout << x << " + " << y << " = " << z << std::endl;
    std::cout << x << " - " << y << " = " << d << std::endl;
    // std::cout << x << " * " << y << " = " << e << std::endl;
    return 0;
}
