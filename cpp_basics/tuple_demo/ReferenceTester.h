#pragma once

#include <mutex>
#include <iostream>


class ReferenceTester
{
public:
    ReferenceTester();
    ReferenceTester(ReferenceTester&& aSource) noexcept;
    ReferenceTester(ReferenceTester& aSource);
    ~ReferenceTester();

    uint32_t                                    myID{0};

public:
    static void PrintStatus(const std::string& info);
    static void Reset();

    static ReferenceTester&& GetRight();
    static ReferenceTester& GetLeft();
    static ReferenceTester GetValue();

    static std::mutex                           myMutex;
    static std::mutex                           myTestOwnerMutex;
    static uint32_t                             myInstanceCounter;
    static uint32_t                             myConstructionCounter;
    static uint32_t                             myDestructionCounter;
};
