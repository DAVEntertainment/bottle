#include <iostream>
#include <QtQml>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "signal_source.h"


int main(int argc, char *argv[])
{
    // register pure C++ type to QML
    qmlRegisterType<SignalSource> ( /*class of C++ to register*/
        "demo.sig", /* package name to register, for IMPORT in QML*/
        1, 0, /* version: major, minor */
        "SignalSource" /* component name in QML */
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
