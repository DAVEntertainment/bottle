#include <iostream>
#include <fstream>
#include <memory>
#include <thread>

#include "GetTimeStamp.h"

#define DO_NOTHING 0
#define DETACH 1

void LoopForever() {
    std::ofstream of("interview_demo.log", std::ios::trunc);
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto stamp = GetTimeStamp();
        std::cout << stamp << std::endl;
        of << stamp << std::endl;
    };
}

int main(int argc, char** argv)
{
    auto a = new std::thread(LoopForever);
    if(DO_NOTHING) {
        // do nothing, main thread will exit directly,
        // LoopForever thread resource will be collected, too
    } else if(DETACH) {
        a->detach();// detach will put LoopForever thread to background,
                    // but LoopForever won't run forever, it will exit
                    // once main thread exit
    } else {
        a->join();  // join will wait until LoopForever exit, which is never
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
