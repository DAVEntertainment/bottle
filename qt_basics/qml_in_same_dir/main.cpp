#include <iostream>
#include <QtQml>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    // register pure QML
    qmlRegisterType(
        QUrl(QStringLiteral("qrc:///coms/EditDialog.qml")),     // root qml
        "Demo.Coms",    // namespace
        1, 0,           // version
        "EditDialog"    // name of component
    );

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:///Home.qml")));

    if (engine.rootObjects().isEmpty()) {
        qCritical() << "QML not loaded";
        return -1;
    }

    return app.exec();
}
