#include <iostream>
#include <QObject>
#include <QtQml>


class Switch:
    public QObject
{
    Q_OBJECT
    /* define a property will link !!! Var / Read / Write / Notify !!! together */
    Q_PROPERTY(QObject *linkedText READ linkedText WRITE setLinkedText)
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
    QML_ANONYMOUS

public:
    Switch(QObject* object = nullptr):
        QObject(object)
    {}

    ////////////////////////////////////////////////////////////////////////////////////
    // interfaces, can be accessed in qml
    ////////////////////////////////////////////////////////////////////////////////////
public:
    Q_INVOKABLE void Open() {
        qInfo() << "Open Switch";
        if(m_linkedText) {
            m_linkedText->setProperty("text", "On");
        }
        setState(true);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    // following code is everything we've done for support of property linkedText
    ////////////////////////////////////////////////////////////////////////////////////
public:
    QObject* linkedText() const {
        return m_linkedText;
    }
    void setLinkedText(QObject* linkedText) {
        m_linkedText = linkedText;
    }

private:
    QObject *m_linkedText{nullptr};

    ////////////////////////////////////////////////////////////////////////////////////
    // following code is everything we've done for support of property state
    ////////////////////////////////////////////////////////////////////////////////////
public:
    bool state() const {
        return m_state;
    }
    void setState(bool state) {
        if (state != m_state) {
            m_state = state;
            qInfo() << "emit signal stateChanged from Switch";
            emit stateChanged(state);
        }
    }

Q_SIGNALS:
    void stateChanged(bool state);

private:
    bool m_state{false};
};
