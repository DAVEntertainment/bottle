#include <iostream>
#include <QtQml>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "status.h"


int main(int argc, char *argv[])
{
    qmlRegisterUncreatableType<Status> (  /*class of C++ to register*/
        "dav.demo", /* package name to register, for IMPORT in QML*/
        1, 0, /* version: major, minor */
        "Status",  /* component name in QML */
        "Not creatable as it is an enum type"  /* reason */
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
