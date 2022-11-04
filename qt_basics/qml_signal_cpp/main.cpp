#include <iostream>
#include <QtQml>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "switch.h"
#include "waker.h"


int main(int argc, char *argv[])
{
    // register pure C++ type to QML
    qmlRegisterType<Switch> ( /*class of C++ to register*/
        "demo.switch", /* package name to register, for IMPORT in QML*/
        1, 0, /* version: major, minor */
        "Switch" /* component name in QML */
    );
    qmlRegisterType<Waker> (
        "demo.waker",
        1, 0,
        "Waker"
    );
    // register pure QML
    qmlRegisterType(
        QUrl(QStringLiteral("qrc:///page1.qml")),
        "demo.page1",
        1, 0,
        "Page1"
    );
    qmlRegisterType(
        QUrl(QStringLiteral("qrc:///page2.qml")),
        "demo.page2",
        1, 0,
        "Page2"
    );

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        qCritical() << "QML not loaded";
        return -1;
    }

    return app.exec();
}
