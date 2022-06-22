#include <iostream>
#include <string>

#include "Demo.h"


int main()
{
    std::string s1("this is a test string!");
    std::string_view sv_s1(s1);

    std::cout << "s1    " << (void*)s1.data()    << " " << s1    << std::endl;
    std::cout << "sv_s1 " << (void*)sv_s1.data() << " " << sv_s1 << std::endl;

    const char* to_save = nullptr;
    {
        std::string s2(sv_s1);
        std::string_view sv_s2(s2);

        std::cout << "s2    " << (void*)s2.data()    << " " << s2    << std::endl;
        std::cout << "sv_s2 " << (void*)sv_s2.data() << " " << sv_s2 << std::endl;

        to_save = sv_s2.data();
    }

    std::cout << "to_save " << (void*)to_save << " " << to_save << std::endl;

    return 0;
}
