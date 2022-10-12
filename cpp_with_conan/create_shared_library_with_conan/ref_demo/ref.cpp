#include <iostream>
#include "add.h"

int main(int argc, char* argv[]) {
    int x = 10;
    int y = 1;

    std::cout << x << " + " << y << " = " << add(x, y) << std::endl;

    return 0;
}
