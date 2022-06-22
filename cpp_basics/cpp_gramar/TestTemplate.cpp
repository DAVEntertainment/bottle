#include <gtest/gtest.h>
#include <iostream>

template<typename T>
class TempRoot {
public:
    virtual T
    GetData() {
        std::cout << "Root" << std::endl;
        T a{};
        a += 2;
        return a;
    }
};

template<typename T>
class TempNode :
    public TempRoot<T>
{
public:
    virtual T
    GetData() {
        std::cout << "Node" << std::endl;
        return TempRoot<T>::GetData()*3;
    }
};

TEST(Template, Inherit) {
    TempNode<int> demo;
    EXPECT_EQ(6, demo.GetData());
}

