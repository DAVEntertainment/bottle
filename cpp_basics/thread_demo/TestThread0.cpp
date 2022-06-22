#include <iostream>
#include <memory>
#include <thread>

#include "GetTimeStamp.h"

#define DETACH 1

void LoopForever() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << GetTimeStamp() << std::endl;
    };
}

int main(int argc, char** argv)
{
    std::thread a(LoopForever);
    if(DETACH) {
        a.detach(); // detach will put LoopForever thread to background,
                    // but LoopForever won't run forever, it will exit
                    // once main thread exit
    } else {
        a.join();   // join will wait until LoopForever exit, which is never
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
