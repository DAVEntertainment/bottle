#include <iostream>
#include <memory>

#include "Demo.h"


class PrivateConstructor;


void CreateWithFunction();
std::shared_ptr<PrivateConstructor> CreateSharedPointer();
std::shared_ptr<PrivateConstructor> CreateSharedPointerWithMakeShared();


class PrivateConstructor final
{
public:
    ~PrivateConstructor() {
        std::cout << "  destroyed" << std::endl;
    };

private:
    PrivateConstructor() {
        std::cout << "  created" << std::endl;
    };
    PrivateConstructor(PrivateConstructor&) {
        std::cout << "  created from ref" << std::endl;
    };
    PrivateConstructor(PrivateConstructor&&) {
        std::cout << "  created from right-ref" << std::endl;
    };

    friend void CreateWithFunction();
    friend std::shared_ptr<PrivateConstructor> CreateSharedPointer();
    // friend std::shared_ptr<PrivateConstructor> CreateSharedPointerWithMakeShared(); // not working
    // friend std::shared_ptr<PrivateConstructor> std::make_shared<PrivateConstructor>(); // not working
};


void CreateWithFunction()
{
    std::cout << "CreateWithFunction:" << std::endl;
    PrivateConstructor c;
}

std::shared_ptr<PrivateConstructor> CreateSharedPointer()
{
    std::cout << "CreateSharedPointer:" << std::endl;
    return std::shared_ptr<PrivateConstructor>(new PrivateConstructor());
}

std::shared_ptr<PrivateConstructor> CreateSharedPointerWithMakeShared()
{
    std::cout << "CreateSharedPointerWithMakeShared:" << std::endl;
    // return std::make_shared<PrivateConstructor>(); // can't create instance from this
    return nullptr;
}

int main()
{
    CreateWithFunction();

    {   // add {} to make sure p0 destroyed before p1 created
        auto p0 = CreateSharedPointer();
    }

    {
        auto p1 = CreateSharedPointerWithMakeShared();
    }

    return 0;
}
