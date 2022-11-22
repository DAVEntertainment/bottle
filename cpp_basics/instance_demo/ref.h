#pragma once

#include <iostream>

using std::cout;
using std::endl;

class Ref final
{
public:
    uint32_t m_id{0};
    static uint32_t m_instCount;

    Ref()
    {
        m_id = m_instCount++;
        cout << "Ref() " << m_id << endl;
    }
    Ref(Ref&& )
    {
        m_id = m_instCount++;
        cout << "Ref(Ref&& ) " << m_id << endl;
    }
    Ref(const Ref&& )
    {
        m_id = m_instCount++;
        cout << "Ref(const Ref&& ) " << m_id << endl;
    }
    Ref(Ref& )
    {
        m_id = m_instCount++;
        cout << "Ref(Ref& ) " << m_id << endl;
    }
    Ref(const Ref& )
    {
        m_id = m_instCount++;
        cout << "Ref(const Ref& ) " << m_id << endl;
    }
    ~Ref() {
        cout << "~Ref() " << m_id << endl;
    }
};
