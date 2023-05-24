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

}
