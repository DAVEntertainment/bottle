#pragma once


//!
//! function add, a method to add
//!
//! @param a one data
//! @param b another data
//! @return sum of a and b
//!
int add(int a, int b);

class Operator
{
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
};

class SceneOperator:
    public Operator
{
public:
    SceneOperator();
    virtual ~SceneOperator();
    virtual void Start();
    virtual void Stop();
};
