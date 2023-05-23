#include "Commandline.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QProcess>
#include <QRegularExpression>
#include <variant>

template<class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

// in cpp 20, noneeded again
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

struct SSMessage
{
    QString scheme;
    QString hostname;
    QString username;
    int port;
    QString password;
    QString hint;
};

struct VmessMessage
{
    QString ps;
    QString add;
    int port;
    QString id;
    int aid;
    QString net;
    QString type;
    QString host;
    QString path;
    QString tls;
    QString sni;
};

using UrlMessage = std::variant<SSMessage, VmessMessage>;

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
    QUrl url = urlorigin;
    return SSMessage{.scheme   = url.scheme(),
                     .hostname = url.host(),
                     .username = url.userName(),
                     .port     = url.port(),
                     .password = url.password(),
                     .hint     = url.fragment()};
}

QDebug
operator<<(QDebug d, const SSMessage &message)
{
    d << "sheme :" << message.scheme << ","
      << "hostname:" << message.hostname << ","
      << "username:" << message.username << ","
      << "port" << message.port << ","
      << "password" << message.password << ","
      << "hint" << message.hint;

    return d;
}

QDebug
operator<<(QDebug d, const VmessMessage &message)
{
    d << "ps :" << message.ps << ","
      << "add:" << message.add << ","
      << "port:" << message.port << ","
      << "id" << message.id << ","
      << "aid" << message.aid << ","
      << "net" << message.net << ","
      << "type" << message.type << ","
      << "host" << message.host << ","
      << "path" << message.path << ","
      << "tls" << message.tls << ","
      << "sni" << message.sni;

    return d;
}

QDebug
operator<<(QDebug d, const UrlMessage &message)
{
    std::visit(overloaded{[d](auto arg) { d << arg; }}, message);
    return d;
}

CommandLineGet::CommandLineGet(QObject *parent)
  : QObject(parent)
  , m_networkAcessManager(new QNetworkAccessManager(this))
{
    connect(
      m_networkAcessManager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply) {
          if (reply->error()) {
              qDebug() << reply->errorString();
              return;
          }

          QString answer0 = QByteArray::fromBase64(reply->readAll());
          auto result     = answer0.split(QRegularExpression("[\r\n]"), Qt::SkipEmptyParts);
          for (auto res : result) {
              qDebug() << decodeUrl(res);
          }
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
    QNetworkRequest request;
    request.setUrl(url);
    m_networkAcessManager->get(request);
}
