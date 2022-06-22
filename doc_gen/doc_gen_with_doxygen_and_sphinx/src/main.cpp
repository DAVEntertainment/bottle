#include <iostream>
#include "common/math.h"
#include "biz/show_biz.h"

int main(int argc, char* argv[]) {

    int a = 1;
    int b = 2;
    int c = add(a, b);

    Opera opera;
    opera.Start();
    opera.Stop();

    opera.Start();
    opera.Stop();

    return 0;
}
