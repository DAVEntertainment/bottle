#pragma once
#include <iostream>

namespace Demo1 {

    class Base {
    public:
        Base() { foo(); }
        virtual void foo(void) {
            std::cout << "Base::foo(void)" << std::endl; 
        }
        virtual void callFoo(void) { 
            foo(); 
        } 
    };

    class Derived : public Base {
    public:
        Derived() {
            foo();
        }
        void foo(void) {
            std::cout << "Derived::foo(void)" << std::endl;
        }
    };
}


void RunDemo1() {
    std::cout << "# " << __FUNCTION__ << " ##########################" << std::endl;
    Demo1::Base* p = new Demo1::Derived(); 
    p->callFoo();
    if(p) {
        delete p;
    }
}
