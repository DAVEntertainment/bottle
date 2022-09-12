#include "declare.h"

int add(int a, int b) {
    return a + b;
}

DEF_API int del(int, int);
int del(int a, int b) {
    return a - b;
}
