#pragma once
#include <iostream>

namespace Demo0 {

    class Father
    {
    public:
        Father() {
            std::cout << "Father Const" << std::endl;
        }
        Father(Father&) {
            std::cout << "Father Const&" << std::endl;
        }
        Father(Father&&) {
            std::cout << "Father Const&&" << std::endl;
        }
    };

    class Children :
        public Father
    {
    public:
        Children() {
            std::cout << "Children Const" << std::endl;
        }
        Children(Children& aAnother):
            Father(aAnother)
        {
            std::cout << "Children Const&" << std::endl;
        }
        Children(Children&& aAnother):
            Father(std::move(aAnother))
        {
            std::cout << "Children Const&&" << std::endl;
        }
    };

    class Base
    {
    public:
        Base()
        {
            Foo();
        }

        virtual void
        Foo()
        {
            std::cout << "Base::Foo(void)" << std::endl;
        }
    };

    class Derived : public Base
    {
    public:
        Derived()
        {
            Foo();
        }

        virtual void
        Foo()
        override
        {
            std::cout << "Derived::Foo(void)" << std::endl;
        }
    };
}

void RunDemo0() {
    std::cout << "# " << __FUNCTION__ << " ##########################" << std::endl;
    
    std::cout << "#  ##########################" << std::endl;
    Demo0::Derived();
}
