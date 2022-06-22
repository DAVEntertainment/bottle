#include <list>
#include <functional>

#include <gtest/gtest.h>

#include "ReferenceTester.h"

bool locOutputToConsole = false;

TEST(Reference, LeftValueAssign)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        ReferenceTester inst;
        ReferenceTester::PrintStatus("direct left"); // 1 1 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);

        auto& ref = inst;
        ReferenceTester::PrintStatus("direct left ref"); // 1 1 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);
    }
    ReferenceTester::PrintStatus("direct left - done"); // 1 1 1
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, LeftValueReturn)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        auto& ref = ReferenceTester::GetLeft(); // not safe, unknown behavior
        ReferenceTester::PrintStatus("left"); // 1 1 1
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);
    }

    ReferenceTester::PrintStatus("left - done"); // 1 1 1
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, RightValueAssign)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        ReferenceTester inst;
        ReferenceTester::PrintStatus("direct right"); // 1 1 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);

        auto&& ref = inst;
        ReferenceTester::PrintStatus("direct right ref"); // 1 1 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);
    }

    ReferenceTester::PrintStatus("direct right - done"); // 1 1 1
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, RightValueReturn)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        auto&& ref = ReferenceTester::GetRight();
        ReferenceTester::PrintStatus("right"); // 1 1 1
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);
    }

    ReferenceTester::PrintStatus("right - done"); // 1 1 1
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, Value)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        auto ref = ReferenceTester::GetValue();
        ReferenceTester::PrintStatus("value"); // 1 1 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);
    }

    ReferenceTester::PrintStatus("value - done"); // 1 1 1
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, VectorOfSharedPointers)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    // test vec shared_ptr
    ReferenceTester::Reset();
    {
        std::vector<std::shared_ptr<ReferenceTester>> vec;
        vec.push_back(std::make_shared<ReferenceTester>());
        vec.push_back(std::make_shared<ReferenceTester>());
        vec.push_back(std::make_shared<ReferenceTester>());

        ReferenceTester::PrintStatus("vec shared_ptr"); // 3 3 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 3);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);
    }
    ReferenceTester::PrintStatus("vec shared_ptr - done"); // 3 3 3
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 3);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 3);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, VectorOfMovedValue)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::vector<ReferenceTester> vec;
        vec.push_back(std::move(ReferenceTester()));
        vec.push_back(std::move(ReferenceTester()));
        vec.push_back(std::move(ReferenceTester()));

        ReferenceTester::PrintStatus("vec moved"); // 3 9 6
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);
    }

    ReferenceTester::PrintStatus("vec moved - done"); // 3 9 9
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 9);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, VectorOfValue)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::vector<ReferenceTester> vec;
        vec.push_back(ReferenceTester());
        vec.push_back(ReferenceTester());
        vec.push_back(ReferenceTester());

        ReferenceTester::PrintStatus("vec value"); // 3 9 6
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);
    }

    ReferenceTester::PrintStatus("vec value - done"); // 3 9 9
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 9);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, VectorValueLoop)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::vector<ReferenceTester> vec;
        vec.push_back(ReferenceTester());
        vec.push_back(ReferenceTester());
        vec.push_back(ReferenceTester());

        ReferenceTester::PrintStatus("vec value loop init"); // 3 9 6
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);

        for (auto r : vec) { std::cout << "."; } std::cout << std::endl;
        ReferenceTester::PrintStatus("vec value loop "); // 6 12 9
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 6);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 12);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 9);
    }

    ReferenceTester::PrintStatus("vec value loop - done"); // 6 12 12
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 6);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 12);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 12);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, VectorLeftValueLoop)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::vector<ReferenceTester> vec;
        vec.push_back(ReferenceTester());
        vec.push_back(ReferenceTester());
        vec.push_back(ReferenceTester());

        ReferenceTester::PrintStatus("vec left value loop init"); // 3 9 6
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);

        for (auto& r : vec) { std::cout << "."; } std::cout << std::endl;
        ReferenceTester::PrintStatus("vec left value loop &"); // 3 9 6
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);
    }

    ReferenceTester::PrintStatus("vec left value loop - done"); // 3 9 9
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 9);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, VectorRightValueLoop)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::vector<ReferenceTester> vec;
        vec.push_back(ReferenceTester());
        vec.push_back(ReferenceTester());
        vec.push_back(ReferenceTester());

        ReferenceTester::PrintStatus("vec right value loop init"); // 3 9 6
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);

        for (auto&& r : vec) { std::cout << "."; } std::cout << std::endl;
        ReferenceTester::PrintStatus("vec right value loop &&"); // 3 9 6
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);
    }

    ReferenceTester::PrintStatus("vec right value loop - done"); // 3 9 9
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 9);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, ListOfMovedValue)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::list<ReferenceTester> list;
        list.push_back(std::move(ReferenceTester()));
        list.push_back(std::move(ReferenceTester()));
        list.push_back(std::move(ReferenceTester()));

        ReferenceTester::PrintStatus("list moved"); // 3 6 3
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 3);
    }

    ReferenceTester::PrintStatus("list moved - done"); // 3 6 6
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, ListOfValue)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::list<ReferenceTester> list;
        list.push_back(ReferenceTester());
        list.push_back(ReferenceTester());
        list.push_back(ReferenceTester());

        ReferenceTester::PrintStatus("list value"); // 3 6 3
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 3);
    }

    ReferenceTester::PrintStatus("list value - done"); // 3 6 6
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, ListValueLoop)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::list<ReferenceTester> list;
        list.push_back(ReferenceTester());
        list.push_back(ReferenceTester());
        list.push_back(ReferenceTester());

        ReferenceTester::PrintStatus("list value loop init"); // 3 6 3
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 3);

        for (auto r : list) { std::cout << "."; } std::cout << std::endl;
        ReferenceTester::PrintStatus("list value loop "); // 6 9 6
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 6);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);
    }

    ReferenceTester::PrintStatus("list value loop - done"); // 6 9 9
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 6);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 9);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 9);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, ListLeftValueLoop)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::list<ReferenceTester> list;
        list.push_back(ReferenceTester());
        list.push_back(ReferenceTester());
        list.push_back(ReferenceTester());

        ReferenceTester::PrintStatus("list left value loop init"); // 3 6 3
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 3);

        for (auto& r : list) { std::cout << "."; } std::cout << std::endl;
        ReferenceTester::PrintStatus("list left value loop &"); // 3 6 3
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 3);
    }

    ReferenceTester::PrintStatus("list left value loop - done"); // 3 6 6
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, ListRightValueLoop)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    // const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        std::list<ReferenceTester> list;
        list.push_back(ReferenceTester());
        list.push_back(ReferenceTester());
        list.push_back(ReferenceTester());

        ReferenceTester::PrintStatus("list right value loop init"); // 3 6 3
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 3);

        for (auto&& r : list) { std::cout << "."; } std::cout << std::endl;
        ReferenceTester::PrintStatus("list right value loop &&"); // 3 6 3
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 3);
    }

    ReferenceTester::PrintStatus("list loop - done"); // 3 6 6
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 3);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 6);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 6);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, BindTempValue)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        auto func = [] (ReferenceTester& aInstance) {};

        auto bf = std::bind(func, ReferenceTester());
        ReferenceTester::PrintStatus("bind temp - bind"); // 1 2 1
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 2);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);

        bf();
        ReferenceTester::PrintStatus("bind temp - called"); // 1 2 1
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 2);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);
    }

    ReferenceTester::PrintStatus("bind temp - done"); // 1 2 2
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 2);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 2);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, BindLocalVariable)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        auto func = [] (ReferenceTester& aInstance) {};
        auto inst = ReferenceTester();

        auto bf = std::bind(func, inst);
        ReferenceTester::PrintStatus("bind local - bind"); // 2 2 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 2);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 2);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);

        bf();
        ReferenceTester::PrintStatus("bind local - called"); // 2 2 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 2);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 2);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);
    }

    ReferenceTester::PrintStatus("bind local - done"); // 2 2 2
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 2);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 2);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 2);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, BindLocalVariableRef)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    {
        auto func = [] (ReferenceTester& aInstance) {};
        auto inst = ReferenceTester();

        auto bf = std::bind(func, std::ref(inst));
        ReferenceTester::PrintStatus("bind std::ref - bind"); // 1 1 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);

        bf();
        ReferenceTester::PrintStatus("bind std::ref - called"); // 1 1 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);
    }

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}

TEST(Reference, BindLocalVariableRefAndCallOutsideLifeCycle)
{
    std::unique_lock<std::mutex> lock(ReferenceTester::myTestOwnerMutex);
    const bool locOutputToConsole = true;

    if (!locOutputToConsole) {
        testing::internal::CaptureStdout();
    }

    ReferenceTester::Reset();
    std::function<void(void)> funcOut;
    {
        auto func = [] (ReferenceTester& aInstance) {};
        auto inst = ReferenceTester();

        auto funcOut = std::bind(func, std::ref(inst));
        ReferenceTester::PrintStatus("bind std::ref - bind"); // 1 1 0
        EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
        EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
        EXPECT_EQ(ReferenceTester::myDestructionCounter, 0);
    }
    // funcOut(); // error: C++ exception with description "bad function call" thrown in the test body.
    ReferenceTester::PrintStatus("bind std::ref - done"); // 1 1 1
    EXPECT_EQ(ReferenceTester::myInstanceCounter, 1);
    EXPECT_EQ(ReferenceTester::myConstructionCounter, 1);
    EXPECT_EQ(ReferenceTester::myDestructionCounter, 1);

    if (!locOutputToConsole) {
        testing::internal::GetCapturedStdout();
    }
}
