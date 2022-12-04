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
void return_6() {  // interesting
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
void return_8() {  // interesting
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
    return i;  // interesting, no Ref&& construction
}
void return_11() {
    new_section(__FUNCTION__, "");
    create_4();
}
void return_12() {  // interesting, same as 11
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
    static Ref i;  // created when called the first time
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
    pass_value(Ref());  // interesting, destroyed before pass_0 end
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
    pass_and_return_value(Ref());  // Ref() will be destroyed before return value
    // return value destroy, after last line
    cout << __FUNCTION__ << " end"  << endl;
}
void pr_1() {
    new_section(__FUNCTION__, "");
    auto o = pass_and_return_value(Ref());  // return value is held by o
    // o will be destroyed when pr_1 exit
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

////////////////////////////////////////////////////////////////////////////
// test for instances
////////////////////////////////////////////////////////////////////////////
void pass_right_to_inst_direct(Ref&& in) {
    Ref i(in);
}
void inst_0() {
    new_section(__FUNCTION__, "");
    pass_right_to_inst_direct(Ref());
}

void pass_left_to_inst_direct(Ref& in) {
    Ref i(in);
}
void inst_1() {
    new_section(__FUNCTION__, "");
    pass_left_to_inst_direct(Ref());
}

void pass_right_to_inst_assign(Ref&& in) {
    Ref i = in;  // created with Ref(Ref& )
}
void inst_2() {
    new_section(__FUNCTION__, "");
    pass_right_to_inst_assign(Ref());
}

void pass_left_to_inst_assign(Ref& in) {
    Ref i = in;  // created with Ref(Ref& )
}
void inst_3() {
    new_section(__FUNCTION__, "");
    pass_left_to_inst_assign(Ref());
}

void pass_right_to_global(Ref&& in) {
    global = in;  // Ref& operator=(const Ref&) will be called
}
void inst_4() {
    new_section(__FUNCTION__, "");
    pass_right_to_global(Ref());
}

void move_right_to_global(Ref&& in) {
    global = std::move(in);   // Ref& operator=(const Ref&&) will be called
}
void inst_5() {
    new_section(__FUNCTION__, "");
    move_right_to_global(Ref());
}

////////////////////////////////////////////////////////////////////////////
// test for tuple instances
////////////////////////////////////////////////////////////////////////////
#include <tuple>

void tuple_0() {
    new_section(__FUNCTION__, "");
    std::tuple<Ref, bool> t(Ref(), true);
    // tuple will make its own copy
}
void tuple_1() {
    new_section(__FUNCTION__, "");
    std::tuple<Ref, bool> t(Ref(), true);
    // tuple will make its own copy
    auto i = std::get<0>(t);
    // get will make its own copy again
}
void tuple_2() {
    new_section(__FUNCTION__, "");
    Ref i;
    std::tuple<Ref, bool> t(i, true);
}
void tuple_3() {
    new_section(__FUNCTION__, "");
    Ref i;
    std::tuple<Ref, bool> t(std::move(i), true);
}
void tuple_4() {
    new_section(__FUNCTION__, "");
    Ref i;
    std::tuple<Ref*, bool> t(&i, true);
}
void tuple_5() {
    new_section(__FUNCTION__, "");
    Ref i;
    std::tuple<Ref&, bool> t(i, true);
}

std::tuple<Ref&, bool> create_ref_tuple() {
    Ref i;
    // !!! ATTETION !!!
    //  this is un-safe, by returing Ref&,
    //  cause "i" in create_ref_tuple
    //  will be destroyed after poping call stack
    return std::tuple<Ref&, bool>(i, true);
}
void tuple_6() {
    new_section(__FUNCTION__, "");
    auto t = create_ref_tuple();
    // the only instance created will be destroyed here
    cout << __FUNCTION__ << " end"  << endl;
    // creating c is un-safe
    Ref c(std::get<0>(t));
    cout << "c " << c.m_id << endl;
}

////////////////////////////////////////////////////////////////////////////
// test for function instances
////////////////////////////////////////////////////////////////////////////
#include <functional>
void bind_ref(Ref& i) {
    cout << "bind_ref " << i.m_id << endl;
}
void func_0() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = std::bind(bind_ref, std::ref(i));
    f();
}
void func_1() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = std::bind(bind_ref, i);
    // withou std::ref, another copy will be created
    f();
}

void bind_value(Ref i) {
    cout << "bind_value " << i.m_id << endl;
}
void func_2() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = std::bind(bind_value, std::ref(i));
    // std::ref will make sure bind ref of "i" to "f", no copy created
    cout << __FUNCTION__ << " binded" << endl;
    f();  // another copy will be created when calling bind_value
}
void func_3() {  // by this way, 3 instances will created
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = std::bind(bind_value, i);
    // bind will create a copy of i
    cout << __FUNCTION__ << " binded" << endl;
    f();  // another copy will be created when calling bind_value
}

////////////////////////////////////////////////////////////////////////////
// test for lambda instances
////////////////////////////////////////////////////////////////////////////
// without local variable
void lambda_0() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = [](Ref in) {
        cout << "lambda call " << in.m_id << endl;
    };
    cout << __FUNCTION__ << " lambda created" << endl;
    f(i);
}
void lambda_1() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = [](Ref& in) {
        cout << "lambda call " << in.m_id << endl;
    };
    cout << __FUNCTION__ << " lambda created" << endl;
    f(i);
}
// with local variable
//  call lambda directly
void lambda_2() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = [&]() {
        cout << "lambda call (i = " << i.m_id << ")" << endl;
    };
    cout << __FUNCTION__ << " lambda created" << endl;
    f();
}
void lambda_3() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = [=]() { // catch with Ref(const Ref& )
        cout << "lambda call (i = " << i.m_id << ")" << endl;
    };
    cout << __FUNCTION__ << " lambda created" << endl;
    f();
}
//  bind nothing
void lambda_4() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = std::bind([&]() {
        cout << "lambda call (i = " << i.m_id << ")" << endl;
    });
    cout << __FUNCTION__ << " lambda created" << endl;
    f();
}
void lambda_5() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = std::bind([=]() {
        cout << "lambda call (i = " << i.m_id << ")" << endl;
    });
    cout << __FUNCTION__ << " lambda created" << endl;
    f();
}
void lambda_6() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto lam = [=]() {
        cout << "lambda call (i = " << i.m_id << ")" << endl;
    };  // lambda will catch an instance
    cout << __FUNCTION__ << " lambda created" << endl;
    lam();
    auto f = std::bind(lam);   // bind will create another instance
    cout << __FUNCTION__ << " binded" << endl;
    f();
}
//  bind input
void lambda_7() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = std::bind([=](Ref& in) {
        cout << "lambda call (i = " << i.m_id << ")" << endl;
        cout << "lambda call (in = " << in.m_id << ")" <<endl;
    }, std::ref(i));
    cout << __FUNCTION__ << " lambda created" << endl;
    f();
}
void lambda_8() {
    new_section(__FUNCTION__, "");
    Ref i;
    auto f = std::bind([&](Ref& in) {
        cout << "lambda call (i = " << i.m_id << ")" << endl;
        cout << "lambda call (in = " << in.m_id << ")" <<endl;
    }, std::ref(i));
    cout << __FUNCTION__ << " lambda created" << endl;
    f();
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

    ////////////////////////////////////////////////////////////////////////////
    // test for instances
    ////////////////////////////////////////////////////////////////////////////
    inst_0();
    inst_1();
    inst_2();
    inst_3();
    inst_4();
    inst_5();

    ////////////////////////////////////////////////////////////////////////////
    // test for tuple instances
    ////////////////////////////////////////////////////////////////////////////
    tuple_0();
    tuple_1();
    tuple_2();
    tuple_3();
    tuple_4();
    tuple_5();
    tuple_6();

    ////////////////////////////////////////////////////////////////////////////
    // test for function instances
    ////////////////////////////////////////////////////////////////////////////
    func_0();
    func_1();
    func_2();
    func_3();

    ////////////////////////////////////////////////////////////////////////////
    // test for lambda instances
    ////////////////////////////////////////////////////////////////////////////
    lambda_0();
    lambda_1();
    lambda_2();
    lambda_3();
    lambda_4();
    lambda_5();
    lambda_6();
    lambda_7();
    lambda_8();

    new_section(__FUNCTION__, "exit");
    return 0;
}
