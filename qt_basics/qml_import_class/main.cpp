#include <iostream>
#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "demo.h"

int main(int argc, char *argv[])
{
    // very import to register C++ class to QML
    // com.pack is where QML will import the class
    // Demo is the class name imported
    qmlRegisterType<Demo>("com.pack", 1, 0, "Demo");

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
