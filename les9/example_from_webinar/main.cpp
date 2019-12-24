#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "basereader.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    // Зарегистрируем класс
    qmlRegisterType<BaseReader>("com.vv.exampleclass", 1, 0, "BaseReader");
    engine.load(url);

    return app.exec();
}
