#include <iostream>
#include <QObject>
#include <QtQml>


class Calculator:
    public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *textArea READ textArea WRITE setTextArea NOTIFY textAreaChanged)
    QML_ANONYMOUS

public:
    Calculator(QObject* aObject = nullptr):
        QObject(aObject)
    {}

    Q_INVOKABLE void Input(QString aInput) {
        qInfo() << "Input" << aInput;

        auto shown = m_textArea->property("text").toString();

        if(aInput == QString("C")) {
            shown.clear();
        } else {
            shown += aInput;
        }

        m_textArea->setProperty("text", shown);
    }

    QObject* textArea() const {
        return m_textArea;
    }
    void setTextArea(QObject* aTextArea) {
        m_textArea = aTextArea;
    }

Q_SIGNALS:
    void textAreaChanged();

private:
    QObject *m_textArea{nullptr};
};
