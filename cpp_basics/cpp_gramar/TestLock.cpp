#include <atomic>
#include <iostream>
#include <gtest/gtest.h>

std::atomic<bool> locIsLocked{false};

class Lock
{
public:
    Lock() {
        locIsLocked.store(true);
    }
    ~Lock() {
        locIsLocked.store(false);
    }
};

void
LockAndThrow()
{
    Lock lock;
    throw std::exception();
}

TEST(Lock, BasicLock)
{
    EXPECT_EQ(locIsLocked.load(), false);
    {
        Lock lock;
        EXPECT_EQ(locIsLocked.load(), true);
    }
    EXPECT_EQ(locIsLocked.load(), false);
}

TEST(Lock, BrokenLock)
{
    EXPECT_THROW(LockAndThrow(), std::exception);
    EXPECT_EQ(locIsLocked.load(), false);
}
