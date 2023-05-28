#pragma once
#include <QDebug>
#include <QJsonObject>
#include <QPair>
#include <QString>
#include <format>
#include <variant>

namespace rng = std::ranges;

template<typename C>
struct to_helper
{};

// This actually does the work
template<typename Container, rng::range R>
requires std::convertible_to<rng::range_value_t<R>, typename Container::value_type> Container
operator|(R &&r, to_helper<Container>)
{
    return Container{r.begin(), r.end()};
}

template<typename T>
concept JsonAble = requires(T a)
{
    {
        a.toJson()
    } -> std::convertible_to<QJsonObject>;
};
template<class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

// in cpp 20, noneeded again
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

namespace Interfaces {

struct SSMessage
{
    QString scheme;
    QPair<QString, QString> method;
    QString username;
    int port;
    QString password;
    QString hint;
    QJsonObject toJson() const;
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
    QJsonObject toJson() const;
};

using UrlMessage = std::variant<SSMessage, VmessMessage>;

inline QDebug
operator<<(QDebug d, const SSMessage &message)
{
    d << "sheme :" << message.scheme << ","
      << std::format("Secret use : {}, and content: {}",
                     message.method.first.toStdString(),
                     message.method.second.toStdString())
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

[[nodiscard]] UrlMessage
get_urlmessage_from_json(QJsonObject object);

}
