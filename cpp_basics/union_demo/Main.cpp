#include <cstdio>
#include <iostream>

#include "Demo.h"


struct S {
	int32_t	a;
	int64_t b;
	int8_t	c;
};

union U {
	int32_t a;
	int64_t b;
	int8_t 	c;
};


int main() {
	S s;
	U u;
	std::cout << "size(S) = " << sizeof(s) << std::endl;
	std::cout << "size(U) = " << sizeof(u) << std::endl;
	std::cout << "&s.a = " << (void*)&s.a << std::endl;
	std::cout << "&s.b = " << (void*)&s.b << std::endl;
	std::cout << "&s.c = " << (void*)&s.c << std::endl;
	std::cout << "&u.a = " << (void*)&u.a << std::endl;
	std::cout << "&u.b = " << (void*)&u.b << std::endl;
	std::cout << "&u.c = " << (void*)&u.c << std::endl;

	return 0;
}
