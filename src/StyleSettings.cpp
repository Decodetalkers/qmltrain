#include "StyleSettings.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QQuickStyle>
#include <QStandardPaths>
#include <format>

static QString
get_config_path()
{
    return QString::fromStdString(
      std::format("{}/{}/subscribes.json",
                  QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).toStdString(),
                  qApp->organizationName().toStdString()));
}

static QString
get_settings_path()
{
    return QString::fromStdString(
      std::format("{}/{}/settings.json",
                  QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).toStdString(),
                  qApp->organizationName().toStdString()));
}

StyleSettings::StyleSettings(QObject *parent)
  : QObject(parent)
  , m_settings(QSettings())
  , m_style(std::visit([this]() -> QString {
      auto settings = m_settings.value(QLatin1String("style")).toString();
      return settings;
  }))
  , m_subscribes(std::visit([this]() -> QVector<SubScribesModel *> {
      QFile file(get_config_path());
      if (!file.exists() && !file.isReadable()) {
          return {};
      }
      file.open(QIODevice::ReadOnly | QIODevice::Text);
      auto bytes                        = file.readAll();
      QJsonDocument document            = QJsonDocument::fromJson(bytes);
      QJsonArray array                  = document.array();
      QVector<SubScribesModel *> models = {};
      for (auto object : array) {
          QVector<Interfaces::UrlMessage> messages;
          auto topObject  = object.toObject();
          auto subscribes = topObject["subscribes"].toArray();
          for (auto sub : subscribes) {
              auto object = sub.toObject();
              if (object["interfaceName"].toString() == "SS") {
                  messages.append(Interfaces::SSMessage{
                    .scheme   = object["scheme"].toString(),
                    .method   = std::invoke([object]() -> QPair<QString, QString> {
                        QJsonObject secret = object["secret"].toObject();
                        return {secret["method"].toString(), secret["secretContent"].toString()};
                    }),
                    .username = object["username"].toString(),
                    .port     = object["port"].toInt(),

                    .password = object["password"].toString(),
                    .hint     = object["hint"].toString(),

                  });
              } else if (object["interfaceName"].toString() == "VMess") {
                  messages.append(Interfaces::VmessMessage{
                    .ps   = object["ps"].toString(),
                    .add  = object["add"].toString(),
                    .port = object["port"].toInt(),
                    .id   = object["id"].toString(),
                    .aid  = object["aid"].toInt(),
                    .net  = object["net"].toString(),
                    .type = object["type"].toString(),
                    .host = object["host"].toString(),
                    .path = object["path"].toString(),
                    .tls  = object["tls"].toString(),
                    .sni  = object["sni"].toString(),
                  });
              }
          }
          models.append(new SubScribesModel(topObject["url"].toString(),
                                            topObject["urlName"].toString(),
                                            topObject["updateTime"].toString(),
                                            messages,
                                            this));
      }
      return models;
  }))
  , m_workingSubScribeIndex(-1)
  , m_workingSubScribeUrl(QString())
{
    getSettings();
    for (auto subs : m_subscribes) {
        connect(
          subs, &SubScribesModel::subscribinfosUpdate, this, &StyleSettings::saveSubScribingConfig);
    }
}

void
StyleSettings::setStyle(QString style)
{
    m_settings.setValue(QLatin1String("style"), style);
    m_style = style;
    Q_EMIT styleChanged();
    qDebug() << "Style is :" << style;
}

void
StyleSettings::addSubscribe(QString subscribe, QString subscribeAlias)
{
    auto subs = new SubScribesModel(
      subscribe, subscribeAlias, QDateTime::currentDateTime().toString("dd.MM.yyyy"), {}, this);
    connect(
      subs, &SubScribesModel::subscribinfosUpdate, this, &StyleSettings::saveSubScribingConfig);
    m_subscribes.append(subs);
    saveSubScribingConfig();
    Q_EMIT subscribesChanged();
}

void
StyleSettings::removeSubScribeWithKey(QString subscribe)
{
    int index     = 0;
    bool hasmatch = false;
    for (; index < m_subscribes.length(); ++index) {
        if (subscribe == m_subscribes[index]->url()) {
            hasmatch = true;
            break;
        }
    }
    if (hasmatch) {
        m_subscribes.removeAt(index);
        saveSubScribingConfig();
    }
    Q_EMIT subscribesChanged();
}

void
StyleSettings::saveSubScribingConfig()
{
    QJsonArray array;
    for (auto subscrib : m_subscribes) {
        array.append(subscrib->toJson());
    }
    QJsonDocument document;
    document.setArray(array);
    QByteArray bytes = document.toJson(QJsonDocument::Indented);
    QFile file(get_config_path());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream iStream(&file);
        iStream.setEncoding(QStringConverter::Encoding::Utf8);
        iStream << bytes;
        file.close();
    } else {
        qWarning() << "Cannot save config";
    }
}

void
StyleSettings::saveSettingsConfig()
{
    QJsonDocument document;
    document.setObject({
      {"workingSubScribeUrl", m_workingSubScribeUrl},
      {"workingSubScribeIndex", m_workingSubScribeIndex},
    });
    QByteArray bytes = document.toJson(QJsonDocument::Indented);
    QFile file(get_settings_path());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream iStream(&file);
        iStream.setEncoding(QStringConverter::Encoding::Utf8);
        iStream << bytes;
        file.close();
    } else {
        qWarning() << "Cannot save config";
    }
}

void
StyleSettings::getSettings()
{
    QFile file(get_settings_path());
    if (!file.exists() && !file.isReadable()) {
        return;
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto bytes                = file.readAll();
    QJsonDocument document    = QJsonDocument::fromJson(bytes);
    QJsonObject settingobject = document.object();
    m_workingSubScribeIndex   = settingobject["workingSubScribeIndex"].toInt();
    m_workingSubScribeUrl     = settingobject["workingSubScribeUrl"].toString();
}

void
StyleSettings::setWorkingSubScribe(QString url, int index, bool toset)
{
    if (!toset) {
        m_workingSubScribeIndex = -1;
    } else {
        m_workingSubScribeIndex = index;
        m_workingSubScribeUrl   = url;
    }
    saveSettingsConfig();
    Q_EMIT workingSubScribeUrlChanged();
    Q_EMIT workingSubScribeIndexChanged();
}
