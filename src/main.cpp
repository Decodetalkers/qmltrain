#include "Commandline.h"
#include "StyleSettings.h"

#include <QApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QSettings>

inline auto
buildStyles() -> const QStringList
{
    return {QLatin1String("basic"),
            QLatin1String("Fusion"),
            QLatin1String("Imagine"),
            QLatin1String("Material"),
            QLatin1String("Universal")};
}

void
registerGlobalTypes()
{
    qmlRegisterSingletonType<CommandLineGet>(
      "Command.Base", 1, 0, "CommandLineGet", [](QQmlEngine *, QJSEngine *) -> QObject * {
          return new CommandLineGet;
      });
    qmlRegisterSingletonType<CommandLineGet>(
      "Command.Base", 1, 0, "StyleSettings", [](QQmlEngine *, QJSEngine *) -> QObject * {
          return new StyleSettings;
      });
}

int
main(int argc, char *argv[])
{
    QApplication::setApplicationName("Marine");
    QApplication::setOrganizationName("QtProject");
    QApplication app(argc, argv);

    QSettings settings;

    const QString styleInSettings = settings.value("style").toString();
    if (styleInSettings.isEmpty()) {
        settings.setValue(QLatin1String("style"), "Material");
    }

    registerGlobalTypes();
    // QIcon::setThemeName("breeze");

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle(settings.value("style").toString());
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

    engine.setInitialProperties({{"buildInStyles", buildStyles()}});
    engine.load(url);

    return app.exec();
}
