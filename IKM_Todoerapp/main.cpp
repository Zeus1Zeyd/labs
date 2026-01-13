#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "databasemanager.h"
#include "taskmodel.h"
#include <QIcon>

int main(int argc, char *argv[])
{
    // устанавливаем стиль ДО создания QGuiApplication
    qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");

    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon("app_icon.jpeg"));

    // инициализация базы данных
    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase()) {
        qCritical() << "Failed to connect to database!";
        return -1;
    }

    // создание модели задач
    TaskModel taskModel(&dbManager);

    QQmlApplicationEngine engine;

    // регистрация C++ объектов для QML
    engine.rootContext()->setContextProperty("taskModel", &taskModel);
    engine.rootContext()->setContextProperty("dbManager", &dbManager);

    const QUrl url(QStringLiteral("qrc:/Todoer/Main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
