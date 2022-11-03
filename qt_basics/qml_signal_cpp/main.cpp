#include <iostream>
#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "calculator.h"


int main(int argc, char *argv[])
{
    qmlRegisterType<Calculator>("com.pack", 1, 0, "Calculator");

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
