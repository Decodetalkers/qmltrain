#pragma once
#include <QDebug>
#include <QPair>
#include <QString>
#include <format>
#include <variant>

namespace Interfaces {
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
    QPair<QString, QString> secret;
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

inline QDebug
operator<<(QDebug d, const SSMessage &message)
{
    d << "sheme :" << message.scheme << ","
      << std::format("Secret use : {}, and content: {}",
                     message.secret.first.toStdString(),
                     message.secret.second.toStdString())
      << ","
      << "username:" << message.username << ","
      << "port" << message.port << ","
      << "password" << message.password << ","
      << "hint" << message.hint;

    return d;
}

inline QDebug
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

inline QDebug
operator<<(QDebug d, const UrlMessage &message)
{
    std::visit(overloaded{[d](auto arg) { d << arg; }}, message);
    return d;
}

}
