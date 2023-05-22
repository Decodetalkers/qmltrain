#include "src/Commandline.h"

#include <QApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

void
registerGlobalTypes()
{
    qmlRegisterSingletonType<CommandLineGet>(
      "Command.Base", 1, 0, "CommandLineGet", [](QQmlEngine *, QJSEngine *) -> QObject * {
          return new CommandLineGet;
      });
}

int
main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    registerGlobalTypes();
    // QIcon::setThemeName("breeze");

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");
    const QUrl url(u"qrc:/marine/qml/Main.qml"_qs);
    QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreated,
      &app,
      [url](QObject *obj, const QUrl &objUrl) {
          if (!obj && url == objUrl)
              QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
