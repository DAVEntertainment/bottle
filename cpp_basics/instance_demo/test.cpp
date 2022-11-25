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


////////////////////////////////////////////////////////////////////////////
// test for return instances
////////////////////////////////////////////////////////////////////////////
void return_0() {
    new_section(__FUNCTION__, "");
    auto p = new Ref();
    delete p;
}

void return_1() {
    new_section(__FUNCTION__, "");
    Ref i;
    Ref c(i);
}

void return_2() {
    new_section(__FUNCTION__, "");
    const Ref i;
    Ref c(i);
}

void return_3() {
    new_section(__FUNCTION__, "");
    const Ref i;
    Ref c(std::move(i));
}

void return_4() {
    new_section(__FUNCTION__, "");
    Ref i;
    Ref c(std::move(i));
}

Ref create_1() {
    return Ref();
}
void return_5() {
    new_section(__FUNCTION__, "");
    create_1();
}
void return_6() {
    new_section(__FUNCTION__, "");
    auto i = create_1();
}

Ref create_2() {
    return create_1();
}
void return_7() {
    new_section(__FUNCTION__, "");
    create_2();
}
void return_8() {
    new_section(__FUNCTION__, "");
    auto i = create_2();
}

Ref create_3() {
    auto i = create_1();
    return i;
}
void return_9() {
    new_section(__FUNCTION__, "");
    create_3();
}
void return_10() {
    new_section(__FUNCTION__, "");
    auto i = create_3();
}

Ref create_4() {
    Ref i = create_1();
    return i;
}
void return_11() {
    new_section(__FUNCTION__, "");
    create_4();
}
void return_12() {
    new_section(__FUNCTION__, "");
    auto i = create_4();
}

Ref global;
const Ref& use_global() {
    return global;
}
void return_13() {
    new_section(__FUNCTION__, "");
    auto i = use_global();
}
void return_14() {
    new_section(__FUNCTION__, "");
    Ref i = use_global();
}
void return_15() {
    new_section(__FUNCTION__, "");
    auto& i = use_global();
}

Ref use_1() {
    return use_global();
}
void return_16() {
    new_section(__FUNCTION__, "");
    auto i = use_1();
}
void return_17() {
    new_section(__FUNCTION__, "");
    auto& i = use_1();
}

Ref use_static() {
    static Ref i;
    return i;
}
void return_18() {
    new_section(__FUNCTION__, "");
    auto i = use_static();
}
void return_19() {
    new_section(__FUNCTION__, "");
    auto i = use_static();
}

////////////////////////////////////////////////////////////////////////////
// test for parameter passing instances
////////////////////////////////////////////////////////////////////////////
void pass_value(Ref in) {
}
void pass_0() {
    new_section(__FUNCTION__, "");
    pass_value(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pass_1() {
    new_section(__FUNCTION__, "");
    Ref i;
    pass_value(i);
    cout << __FUNCTION__ << " end"  << endl;
}
void pass_2() {
    new_section(__FUNCTION__, "");
    Ref i;
    pass_value(std::move(i));
    cout << __FUNCTION__ << " end"  << endl;
}

void pass_ref(Ref& in) {
}
void pass_3() {
    new_section(__FUNCTION__, "");
    pass_ref(Ref());
}
void pass_4() {
    new_section(__FUNCTION__, "");
    Ref i;
    pass_ref(i);
}
void pass_5() {
    new_section(__FUNCTION__, "");
    Ref i;
    pass_ref(std::move(i));
}

void pass_right_ref(Ref&& in) {
}
void pass_6() {
    new_section(__FUNCTION__, "");
    pass_right_ref(Ref());
}
void pass_7() {
    new_section(__FUNCTION__, "");
    Ref i;
    pass_right_ref(std::move(i));
}

void pass_const_right_ref(const Ref&& in) {
}
void pass_8() {
    new_section(__FUNCTION__, "");
    pass_const_right_ref(Ref());
}
void pass_9() {
    new_section(__FUNCTION__, "");
    Ref i;
    pass_const_right_ref(std::move(i));
}

////////////////////////////////////////////////////////////////////////////
// test for parameter passing and return instances
////////////////////////////////////////////////////////////////////////////
Ref pass_and_return_value(Ref in) {
    cout << "pass_and_return_value" << endl;
    return in;
}
void pr_0() {
    new_section(__FUNCTION__, "");
    pass_and_return_value(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_1() {
    new_section(__FUNCTION__, "");
    auto o = pass_and_return_value(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_2() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto o = pass_and_return_value(i);
    cout << __FUNCTION__ << " end"  << endl;
}

Ref pass_and_return_ref(Ref& in) {
    cout << "pass_and_return_ref" << endl;
    return in;
}
void pr_3() {
    new_section(__FUNCTION__, "");
    pass_and_return_ref(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_4() {
    new_section(__FUNCTION__, "");
    auto o = pass_and_return_ref(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_5() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto o = pass_and_return_ref(i);
    cout << __FUNCTION__ << " end"  << endl;
}

Ref pass_and_return_right_ref(Ref&& in) {
    cout << "pass_and_return_right_ref" << endl;
    return in;
}
void pr_6() {
    new_section(__FUNCTION__, "");
    pass_and_return_right_ref(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_7() {
    new_section(__FUNCTION__, "");
    auto o = pass_and_return_right_ref(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_8() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto o = pass_and_return_right_ref(std::move(i));
    cout << __FUNCTION__ << " end"  << endl;
}

Ref pass_and_return_const_right_ref(const Ref&& in) {
    cout << "pass_and_return_const_right_ref" << endl;
    return in;
}
void pr_9() {
    new_section(__FUNCTION__, "");
    pass_and_return_const_right_ref(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_10() {
    new_section(__FUNCTION__, "");
    auto o = pass_and_return_const_right_ref(Ref());
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_11() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto o = pass_and_return_const_right_ref(std::move(i));
    cout << __FUNCTION__ << " end"  << endl;
}


int main()
{
    new_section(__FUNCTION__, "enter");

    ////////////////////////////////////////////////////////////////////////////
    // test for return instances
    ////////////////////////////////////////////////////////////////////////////
    return_0();
    return_1();
    return_2();
    return_3();
    return_4();
    return_5();
    return_6();
    return_7();
    return_8();
    return_9();
    return_10();
    return_11();
    return_12();
    return_13();
    return_14();
    return_15();
    return_16();
    return_17();
    return_18();
    return_19();

    ////////////////////////////////////////////////////////////////////////////
    // test for parameter passing instances
    ////////////////////////////////////////////////////////////////////////////
    pass_0();
    pass_1();
    pass_2();
    pass_3();
    pass_4();
    pass_5();
    pass_6();
    pass_7();
    pass_8();
    pass_9();

    ////////////////////////////////////////////////////////////////////////////
    // test for parameter passing and return instances
    ////////////////////////////////////////////////////////////////////////////
    pr_0();
    pr_1();
    pr_2();
    pr_3();
    pr_4();
    pr_5();
    pr_6();
    pr_7();
    pr_8();
    pr_9();
    pr_10();
    pr_11();

    new_section(__FUNCTION__, "exit");
    return 0;
}
