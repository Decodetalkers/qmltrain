#include "Commandline.h"
#include "Interface.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QProcess>
#include <QRegularExpression>

#include <ranges>

using namespace Interfaces;

[[nodiscard]] static inline auto
decodeUrl(QString urlorigin) -> UrlMessage
{
    if (urlorigin.startsWith("vmess://")) {
        urlorigin.remove(0, 8);
        auto json            = QByteArray::fromBase64(urlorigin.toLocal8Bit());
        QJsonObject document = QJsonDocument::fromJson(json).object();
        return VmessMessage{
          .ps   = document["ps"].toString(),
          .add  = document["add"].toString(),
          .port = document["port"].toInt(),
          .id   = document["id"].toString(),
          .aid  = document["aid"].toInt(),
          .net  = document["net"].toString(),
          .type = document["type"].toString(),
          .host = document["host"].toString(),
          .path = document["path"].toString(),
          .tls  = document["tls"].toString(),
          .sni  = document["sni"].toString(),
        };
    }
    QUrl url         = urlorigin;
    QString userName = QByteArray::fromBase64(url.userName().toLocal8Bit());
    QStringList keys = userName.split(':');

    return SSMessage{.scheme   = url.scheme(),
                     .method   = {keys[0], keys[1]},
                     .username = url.userName(),
                     .port     = url.port(),
                     .password = url.password(),
                     .hint     = url.fragment()};
}

CommandLineGet::CommandLineGet(QObject *parent)
  : QObject(parent)
  , m_networkAcessManager(new QNetworkAccessManager(this))
{
    connect(
      m_networkAcessManager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply) {
          if (reply->error()) {
              qDebug() << reply->errorString();
              Q_EMIT endGetHttpsStatus(Failed);
              return;
          }

          QString answer0 = QByteArray::fromBase64(reply->readAll());
          auto result     = answer0.split(QRegularExpression("[\r\n]"), Qt::SkipEmptyParts) |
                        std::views::transform([](auto &p) { return decodeUrl(p); }) |
                        to_helper<QVector<UrlMessage>>();
          Q_EMIT suribesUpdate(result);
          Q_EMIT endGetHttpsStatus(Successed);
      });
}

void
CommandLineGet::getOutput()
{
    QProcess *process = new QProcess(this);
    connect(process, &QProcess::finished, this, [this, process](int, QProcess::ExitStatus) {
        auto output     = process->readAllStandardOutput();
        QString message = QString::fromLocal8Bit(output);
        Q_EMIT outPuts(message);
    });
    process->start("ls", {"-la", "/"});
    qDebug() << "Output get";
}

void
CommandLineGet::getHttpsOutput(QString url)
{
    Q_EMIT startGetHttps();
    QNetworkRequest request;
    request.setUrl(url);
    m_networkAcessManager->get(request);
}
