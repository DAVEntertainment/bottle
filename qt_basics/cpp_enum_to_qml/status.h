#pragma once
#include <QObject>

// ref: https://qml.guide/enums-in-qt-qml/

// need to register with qmlRegisterUncreatableType
//  see main.cpp
class Status
{
    Q_GADGET

public:
    enum Value {
        Open = 1,
        Close = 2
    };
    Q_ENUM(Value)

private:
    explicit Status() = delete;
};
