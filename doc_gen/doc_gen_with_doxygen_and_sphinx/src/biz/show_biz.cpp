#include <iostream>
#include "show_biz.h"

//! Create the opera (in .cpp)
Opera::Opera() {
    std::cout << "~~~ Create Opera " << this << std::endl;
}

//! Destroy the opera (in .cpp)
Opera::~Opera() {
    std::cout << "~~~ Destroy Opera " << this << std::endl;
}

void Opera::Start() {
    std::cout << "~~~ Start Opera " << this << std::endl;
    auto op = std::make_shared<SceneOperator>(); //!< some doc in code
    __operator = std::static_pointer_cast<Operator>(op);
    __operator->Start();
}

void Opera::Stop() {
    std::cout << "~~~ Stop Opera " << this << std::endl;
    __operator->Stop();
}
