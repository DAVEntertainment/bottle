#include <string>
#include "ref.h"

using std::string;

uint32_t Ref::m_instCount = 0;

void new_section(string section, string msg) {
    cout << endl;
    cout << "#################################################################" << endl;
    cout << "# [" << section << "] " << msg << endl;
    cout << "#################################################################" << endl;
}

void test_0() {
    new_section(__FUNCTION__, "");
    auto p = new Ref();
    delete p;
}

void test_1() {
    new_section(__FUNCTION__, "");
    Ref i;
    Ref c(i);
}

void test_2() {
    new_section(__FUNCTION__, "");
    const Ref i;
    Ref c(i);
}

void test_3() {
    new_section(__FUNCTION__, "");
    const Ref i;
    Ref c(std::move(i));
}

void test_4() {
    new_section(__FUNCTION__, "");
    Ref i;
    Ref c(std::move(i));
}

Ref create_1() {
    return Ref();
}
void test_5() {
    new_section(__FUNCTION__, "");
    create_1();
}
void test_6() {
    new_section(__FUNCTION__, "");
    auto i = create_1();
}

Ref create_2() {
    return create_1();
}
void test_7() {
    new_section(__FUNCTION__, "");
    create_2();
}
void test_8() {
    new_section(__FUNCTION__, "");
    auto i = create_2();
}

Ref create_3() {
    auto i = create_1();
    return i;
}
void test_9() {
    new_section(__FUNCTION__, "");
    create_3();
}
void test_10() {
    new_section(__FUNCTION__, "");
    auto i = create_3();
}

Ref create_4() {
    Ref i = create_1();
    return i;
}
void test_11() {
    new_section(__FUNCTION__, "");
    create_4();
}
void test_12() {
    new_section(__FUNCTION__, "");
    auto i = create_4();
}

Ref global;
const Ref& use_global() {
    return global;
}
void test_13() {
    new_section(__FUNCTION__, "");
    auto i = use_global();
}
void test_14() {
    new_section(__FUNCTION__, "");
    Ref i = use_global();
}
void test_15() {
    new_section(__FUNCTION__, "");
    auto& i = use_global();
}

Ref use_1() {
    return use_global();
}
void test_16() {
    new_section(__FUNCTION__, "");
    auto i = use_1();
}
void test_17() {
    new_section(__FUNCTION__, "");
    auto& i = use_1();
}



int main()
{
    new_section(__FUNCTION__, "enter");

    test_0();
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    test_8();
    test_9();
    test_10();
    test_11();
    test_12();
    test_13();
    test_14();
    test_15();
    test_16();
    test_17();

    new_section(__FUNCTION__, "exit");
    return 0;
}
