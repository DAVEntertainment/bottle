#include <iostream>
#include <QObject>
#include <QtQml>


class Waker:
    public QObject
{
    Q_OBJECT
    /* define a property will link !!! Var / Read / Write !!! together */
    Q_PROPERTY(QObject *linkedText READ linkedText WRITE setlinkedText) /* NOTIFY is not a must */
    Q_PROPERTY(bool leftFoot READ leftFoot WRITE setLeftFoot NOTIFY leftFootChanged)
    QML_ANONYMOUS

public:
    Waker(QObject* object = nullptr):
        QObject(object)
    {}

    ////////////////////////////////////////////////////////////////////////////////////
    // following code is a loop to walk
    ////////////////////////////////////////////////////////////////////////////////////
public:
    Q_INVOKABLE void WalkOneStep() {
        qInfo() << "WalkOneStep";
        if(m_linkedText) {
            auto text = m_linkedText->property("text").toString();
            if(text.size() > 35) {
                text.clear();
            }
            text += m_leftFoot? "/" : "\\";
            m_linkedText->setProperty("text", text);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    // following code is everything we've done for support of property linkedText
    ////////////////////////////////////////////////////////////////////////////////////
public:
    QObject* linkedText() const {
        return m_linkedText;
    }
    void setlinkedText(QObject* linkedText) {
        m_linkedText = linkedText;
    }

private:
    QObject *m_linkedText{nullptr};

    ////////////////////////////////////////////////////////////////////////////////////
    // following code is everything we've done for support of property leftFoot
    ////////////////////////////////////////////////////////////////////////////////////
public:
    bool leftFoot() const {
        return m_leftFoot;
    }
    void setLeftFoot(bool leftFoot) {
        if(m_leftFoot != leftFoot) {
            m_leftFoot = leftFoot;
            qInfo() << "emit signal leftFootChanged from Walker";
            emit leftFootChanged(m_leftFoot);
        }
    }

signals:
    void leftFootChanged(bool left);

private:
    bool m_leftFoot{false};
};
