#include "ReferenceTester.h"

ReferenceTester::ReferenceTester() {
    std::cout << "Constructor" << std::endl;
    std::unique_lock<std::mutex> lock(myMutex);
    myID = myInstanceCounter;
    ++myInstanceCounter;
    ++myConstructionCounter;
}

ReferenceTester::ReferenceTester(ReferenceTester&& aSource) noexcept {
    std::cout << "Constructor &&" << std::endl;
    std::unique_lock<std::mutex> lock(myMutex);
    myID = aSource.myID;
    aSource.myID = 9999;
    ++myConstructionCounter;
}

ReferenceTester::ReferenceTester(ReferenceTester& aSource) {
    std::cout << "Constructor &" << std::endl;
    std::unique_lock<std::mutex> lock(myMutex);
    myID = myInstanceCounter;
    ++myInstanceCounter;
    ++myConstructionCounter;
}

ReferenceTester::~ReferenceTester() {
    std::cout << "Desctructor" << std::endl;
    std::unique_lock<std::mutex> lock(myMutex);
    ++myDestructionCounter;
}

void ReferenceTester::PrintStatus(const std::string& info) {
    std::cout << info << ":" << std::endl;
    std::cout << "    myInstanceCounter     = " << myInstanceCounter << std::endl;
    std::cout << "    myConstructionCounter = " << myConstructionCounter << std::endl;
    std::cout << "    myDestructionCounter  = " << myDestructionCounter << std::endl;
}

void ReferenceTester::Reset() {
    myInstanceCounter = 0;
    myConstructionCounter = 0;
    myDestructionCounter = 0;
}

std::mutex ReferenceTester::myMutex;
std::mutex ReferenceTester::myTestOwnerMutex;
uint32_t ReferenceTester::myInstanceCounter = 0;
uint32_t ReferenceTester::myConstructionCounter = 0;
uint32_t ReferenceTester::myDestructionCounter = 0;

ReferenceTester&& ReferenceTester::GetRight() {
    ReferenceTester ref;
    // return ref; // error C2440: "return": Can't convert "ReferenceTester" to "ReferenceTester &&"
    return std::move(ref);
}

ReferenceTester& ReferenceTester::GetLeft() {
    ReferenceTester ref;
    return ref; // warning C4172: returning address of local variable or temporary
}

ReferenceTester ReferenceTester::GetValue() {
    ReferenceTester ref;
    return ref;
}