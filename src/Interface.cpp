#include "Interface.h"
#include <expected>
namespace Interfaces {

QJsonObject
SSMessage::toJson() const
{
    return {{"interfaceName", "SS"},
            {"sheme", this->scheme},
            {"secret", std::invoke([this]() -> QJsonObject {
                 return {
                   {"method", this->method.first},
                   {"secretContent", this->method.second},
                 };
             })},
            {"username", this->username},
            {"port", this->port},
            {"password", this->password},
            {"hint", this->hint}};
}

QJsonObject
VmessMessage::toJson() const
{
    return {
      {"interfaceName", "VMess"},
      {"ps", this->ps},
      {"add", this->add},
      {"port", this->port},
      {"id", this->id},
      {"aid", this->aid},
      {"net", this->net},
      {"type", this->type},
      {"host", this->host},
      {"path", this->path},
      {"tls", this->tls},
      {"sni", this->sni},
    };
}

UrlMessage
get_urlmessage_from_json(QJsonObject object)
{
    if (object["interfaceName"].toString() == "SS") {
        return SSMessage{
          .scheme   = object["scheme"].toString(),
          .method   = std::invoke([object]() -> QPair<QString, QString> {
              QJsonObject secret = object["secret"].toObject();
              return {secret["method"].toString(), secret["secretContent"].toString()};
          }),
          .username = object["username"].toString(),
          .port     = object["port"].toInt(),

          .password = object["password"].toString(),
          .hint     = object["hint"].toString(),

        };
    } else if (object["interfaceName"].toString() == "VMess") {
        return VmessMessage{
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
        };
    }
    return SSMessage();
}

}
