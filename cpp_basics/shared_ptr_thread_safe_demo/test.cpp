#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <functional>

using namespace std;

void new_section(string section, string msg) {
    cout << endl;
    cout << "#################################################################" << endl;
    cout << "# [" << section << "] " << msg << endl;
    cout << "#################################################################" << endl;
}

class Ref {
public:
    std::vector<int> m_data;

    Ref(initializer_list<int> l): m_data(l) {
        cout << "Ref(initializer_list<int> l)" << endl;
    }
    // Ref(initializer_list<int>&& l): m_data(l) {
    //     cout << "Ref(initializer_list<int>&& l)" << endl;
    // }  // error C2668: 'Ref::Ref': ambiguous call to overloaded function
    // Ref(const initializer_list<int>&& l): m_data(l) {
    //     cout << "cosnt Ref(initializer_list<int>&& l)" << endl;
    // }  // error C2668: 'Ref::Ref': ambiguous call to overloaded function
    // Ref(initializer_list<int>& l): m_data(l) {
    //     cout << "Ref(initializer_list<int>& l)" << endl;
    // }  // error C2668: 'Ref::Ref': ambiguous call to overloaded function
    // Ref(const initializer_list<int>& l): m_data(l) {
    //     cout << "const Ref(initializer_list<int>& l)" << endl;
    // }  // error C2668: 'Ref::Ref': ambiguous call to overloaded function

    string to_string() {
        stringstream ss;
        ss << "Ref(";
        bool first = true;
        for (auto v: m_data) {
            if (!first) { ss << ", "; }
            ss << v;
        }
        ss << ")";
        return ss.str();
    }
};

shared_mutex gMutex;
condition_variable gCond;


shared_ptr<Ref> thread_func_1(shared_ptr<Ref> p) {
    cout << "ready" << endl;
    shared_lock<shared_mutex> lock(gMutex);  // comment this line out, see anything happens
    cout << "running" << endl;
    shared_ptr<Ref> n{nullptr};
    n = p;
    p = nullptr;
    return n;
}

shared_ptr<Ref> thread_func_2(shared_ptr<Ref>& p) {  // demo according to https://www.zhihu.com/question/56836057
    cout << "ready" << endl;
    shared_lock<shared_mutex> lock(gMutex);  // comment this line out, see anything happens
    cout << "running" << endl;
    shared_ptr<Ref> n{nullptr};
    n = p;
    p = nullptr;
    p = n;
    return n;
}

int main()
{
    int nNumbers = 1000;
    int nThreads = 10000;
    int secsDelay = 5;
    list<thread> threads;
    {
        shared_ptr<Ref> creator{new Ref{1,2,3}};
        for (int i = 0; i < nNumbers; ++i) {
            creator->m_data.push_back(i);
        }
        unique_lock<shared_mutex> lock(gMutex);
        for (int i = 0; i < nThreads; ++i) {
            threads.push_back(thread(bind(thread_func_1, creator)));
            // threads.push_back(thread(bind(thread_func_2, std::ref(creator))));
        }
        for (int i = 0; i < secsDelay; ++i) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "counting " << i << endl;
        }
    }
    for (auto& t: threads) {
        t.join();
    }

    return 0;
}
