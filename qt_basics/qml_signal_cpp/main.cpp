#include <iostream>
#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "switch.h"


int main(int argc, char *argv[])
{
    qmlRegisterType<Switch> ( /*class of C++ to register*/
        "demo.calc", /* package name to register, for IMPORT in QML*/
        1, 0, /* version: major, minor */
        "Switch" /* component name in QML */
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
