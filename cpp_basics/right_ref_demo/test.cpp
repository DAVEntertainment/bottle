#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::string;
using std::cout;
using std::endl;

void new_section(string section, string msg) {
    cout << endl;
    cout << "#################################################################" << endl;
    cout << "# [" << section << "] " << msg << endl;
    cout << "#################################################################" << endl;
}


class Ref final
{
public:
    std::vector<int> m_data;

    std::string to_string() {
        std::stringstream ss;
        for (auto v: m_data) {
            ss << v << ", ";
        }
        return ss.str();
    }
};

void test_move_ref() {
    new_section(__FUNCTION__, "");

    Ref o;
    Ref n;

    o.m_data = std::vector<int>{1, 2, 3};

    cout << "Ref before move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;

    n = std::move(o);
    cout << "Ref after move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;
}


class Cover final {
public:
    Ref m_ref;

    std::string to_string() {
        std::stringstream ss;
        ss << "cover(" << m_ref.to_string() << "), ";
        return ss.str();
    }
};

void test_move_cover() {
    new_section(__FUNCTION__, "");

    Cover o;
    Cover n;

    o.m_ref.m_data = std::vector<int>{1, 2, 3};

    cout << "Cover before move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;

    n = std::move(o);
    cout << "Cover after move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;
}


class Mix final
{
public:
    std::vector<int> m_data;
    int m_index{0};

    std::string to_string() {
        std::stringstream ss;
        for (auto v: m_data) {
            ss << v << ", ";
        }
        ss << ": " << m_index;
        return ss.str();
    }
};

void test_move_mix() {
    new_section(__FUNCTION__, "");

    Mix o;
    Mix n;

    o.m_data = std::vector<int>{1, 2, 3};
    o.m_index = 5;

    cout << "Mix before move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;

    n = std::move(o);
    cout << "Mix after move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;
}


class MixAddr final
{
public:
    std::vector<int> m_data;
    std::vector<int>* m_dynamic{nullptr};

    std::string to_string() {
        std::stringstream ss;
        for (auto v: m_data) {
            ss << v << ", ";
        }
        ss << ": ";
        if (nullptr == m_dynamic) {
            ss << "nullptr";
        } else {
            ss << m_dynamic << "(";
            for (auto v: *m_dynamic) {
                ss << v << ", ";
            }
            ss << ")";
        }
        return ss.str();
    }
    ~MixAddr() {
        if (nullptr != m_dynamic) {
            // // deleting m_dynamic will cause program crash
            // //   because 'n = std::move(o)' only copy m_dynamic,
            // //   but only one instance of std::vector<int> is created,
            // //   so 'delete m_dynamic' will be executed twice,
            // //   this will trigger program crash
            // delete m_dynamic;
            m_dynamic = nullptr;
        }
    }
};

void test_move_mixaddr() {
    new_section(__FUNCTION__, "");

    MixAddr o;
    MixAddr n;

    o.m_data = std::vector<int>{1, 2, 3};
    o.m_dynamic = new std::vector<int>{5, 6, 7};

    cout << "MixAddr before move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;

    n = std::move(o);
    cout << "MixAddr after move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;
}


class Head final {
public:
    Ref m_ref;
    Ref* m_dynamic{nullptr};

    std::string to_string() {
        std::stringstream ss;
        ss << "head(" << m_ref.to_string() << "), ";
        if (nullptr == m_dynamic) {
            ss << "nullptr";
        } else {
            ss << m_dynamic << "(" << m_dynamic->to_string() << ")";
        }
        return ss.str();
    }
    ~Head() {
        if (nullptr == m_dynamic) {
            // // this should cause program crash like MixAddr, but not.
            // //   why? maybe latency of cleanup ?
            delete m_dynamic;
            m_dynamic = nullptr;
        }
    }
};

void test_move_head() {
    new_section(__FUNCTION__, "");

    Head o;
    Head n;

    o.m_ref.m_data = std::vector<int>{1, 2, 3};
    o.m_dynamic = new Ref{};
    o.m_dynamic->m_data = std::vector<int>{4, 5, 6};

    cout << "Head before move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;

    n = std::move(o);
    cout << "Head after move: " << endl;
    cout << "   o: " << o.to_string() << endl;
    cout << "   n: " << n.to_string() << endl;
}



int main()
{
    test_move_mixaddr();
    test_move_head();
    test_move_ref();
    test_move_mix();
    test_move_cover();

    return 0;
}
