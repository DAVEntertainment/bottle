#include "add.h"
#include <iostream>

// although we don't share del.h, but the symbol is there anyway,
//  we can use them by simply declare the signature
int del(int, int);

int main() {
    int x = 10;
    int y = 1;
    int z = add(x, y);
    int d = del(x, y);
    std::cout << x << " + " << y << " = " << z << std::endl;
    std::cout << x << " - " << y << " = " << d << std::endl;
    return 0;
}
