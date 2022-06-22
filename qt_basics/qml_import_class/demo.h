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
        QObject::connect(this, SIGNAL(changed()), this, SLOT(procChange()));
    }

Q_SIGNALS:
    void
    changed();

public Q_SLOTS:
    void
    procChange()
    {
        qWarning() << "I'm out";
    }
};
