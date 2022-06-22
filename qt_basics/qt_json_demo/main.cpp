//
// Description: The qt json demo main file.
//


#include <iostream>

#include "qt_json.h"


int main(int argc, char *argv[])
{
    try {
        ms::demos::MyJson::WriteToFile("./test.json");
    } catch (std::exception& err) {
        std::cerr << "Write to file failed, with details: " << err.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Write to file failed, unknown error!" << std::endl;
        return 2;
    }

    return 0;
}
