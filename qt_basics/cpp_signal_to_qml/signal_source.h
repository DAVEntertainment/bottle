#ifndef SIGNAL_SOURCE_H
#define SIGNAL_SOURCE_H

#include <iostream>
#include <QObject>
#include <Qtimer>
#include <QtQml>


class SignalSource:
    public QObject
{
    Q_OBJECT
    QML_ANONYMOUS

public:
    SignalSource(QObject* object = nullptr):
        QObject(object)
    {
        // bind walkOneStep to onWalkOneStep
        QObject::connect(this, SIGNAL(walkOneStep()), this, SLOT(onWalkOneStep()));
        // bind timer to walkOneStep
        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(doWalkOneStep()));
        m_timer->start(1000);
    }

    virtual ~SignalSource() {
        if(m_timer != nullptr) {
            delete m_timer;
            m_timer = nullptr;
        }
    }

public Q_SLOTS: // register slot to timer, as trigger
    void doWalkOneStep() {
        std::cout << "walk one step" << std::endl;
        Q_EMIT walkOneStep();
    }

Q_SIGNALS:
    void walkOneStep();

private Q_SLOTS:
    void onWalkOneStep() {
        std::cout << "onWalkOneStep" << std::endl;
    }

private:
    QTimer* m_timer{nullptr};
};

#endif // SIGNAL_SOURCE_H
