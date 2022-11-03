#include <iostream>
#include <QObject>
#include <QtQml>


class Switch:
    public QObject
{
    Q_OBJECT
    /* define a property will link !!! Var / Read / Write / Notify !!! together */
    Q_PROPERTY(QObject *linkedText READ linkedText WRITE setlinkedText NOTIFY linkedTextChanged) 
    QML_ANONYMOUS

public:
    Switch(QObject* object = nullptr):
        QObject(object)
    {}

    // interfaces, can be accessed in qml
    Q_INVOKABLE void Open() {
        qInfo() << "Open Switch";
        m_linkedText->setProperty("text", "On");
    }

    Q_INVOKABLE void Close() {
        qInfo() << "Close Switch";
        m_linkedText->setProperty("text", "Off");
    }

public:
    // following code is everything we've done for support of property linkedText
    QObject* linkedText() const {
        return m_linkedText;
    }
    void setlinkedText(QObject* linkedText) {
        m_linkedText = linkedText;
    }

Q_SIGNALS:
    void linkedTextChanged();

private:
    QObject *m_linkedText{nullptr};
};
