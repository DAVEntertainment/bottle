#include <iostream>
#include <QObject>
#include <QtQml>

class Demo:
    public QObject
{
    Q_OBJECT
    QML_ANONYMOUS

public:
    Demo(QObject* aObject = nullptr):
        QObject(aObject)
    {

    }

Q_SIGNALS:

public Q_SLOTS:


};
