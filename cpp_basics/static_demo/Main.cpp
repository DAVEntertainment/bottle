#include <iostream>
#include <vector>

#include "Demo.h"
#include "Common.h"


int main()
{
    std::cout << "Share 0 static pointer: " << GetStaticPointerFromShare0() << std::endl;
    std::cout << "Share 1 static pointer: " << GetStaticPointerFromShare1() << std::endl;
    std::cout << "Share 0 inline pointer: " << GetInlinePointerFromShare0() << std::endl;
    std::cout << "Share 1 inline pointer: " << GetInlinePointerFromShare1() << std::endl;

    return 0;
}
