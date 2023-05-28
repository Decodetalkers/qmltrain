#include "SubScribesModel.h"
#include "src/Interface.h"
#include <QJsonArray>

SubScribesModel::SubScribesModel(QString url,
                                 QString urlName,
                                 QString updateTime,
                                 QVector<Interfaces::UrlMessage> subscribes,
                                 QObject *parent)
  : QAbstractListModel(parent)
  , m_url(url)
  , m_urlName(urlName)
  , m_updateTime(updateTime)
  , m_subscribes(subscribes)
  , m_subscribeCommand(new CommandLineGet(this))
{
    connect(m_subscribeCommand, &CommandLineGet::suribesUpdate, this, [this](auto subscribes) {
        beginResetModel();
        m_subscribes.clear();
        m_subscribes = subscribes;
        endResetModel();
        m_updateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy");
        Q_EMIT updateTimeChanged();
        Q_EMIT subscribeCountsChanged();
        Q_EMIT subscribinfosUpdate();
    });
    connect(m_subscribeCommand, &CommandLineGet::startGetHttps, this, [this] {
        m_subscribing = true;
        Q_EMIT subscribingStatusChanged();
    });
    connect(m_subscribeCommand,
            &CommandLineGet::endGetHttpsStatus,
            this,
            [this](CommandLineGet::GetHttpStatus) {
                m_subscribing = false;
                Q_EMIT subscribingStatusChanged();
            });
}

int
SubScribesModel::rowCount(const QModelIndex &) const
{
    return m_subscribes.count();
}

QVariant
SubScribesModel::data(const QModelIndex &index, int role) const
{
    if (role == Url) {
        return m_url;
    }
    if (index.row() < rowCount()) {
        return get_property(static_cast<SubScribeRole>(role), index.row());
    }
    return QVariant();
}

QHash<int, QByteArray>
SubScribesModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{
      {Name, "name"}, {Password, "password"}, {Port, "port"}, {Method, "method"}, {Url, "url"}};
    return roles;
}

void
SubScribesModel::updateSucribes()
{
    m_subscribeCommand->getHttpsOutput(m_url);
}

QString
SubScribesModel::get_property(SubScribesModel::SubScribeRole role, int index) const
{
    return std::visit(overloaded{[role](Interfaces::SSMessage message) -> QString {
                                     switch (role) {
                                     case Name:
                                         return QString::fromStdString(
                                           std::format("{}-SS", message.hint.toStdString()));
                                     case Password:
                                         return message.password;
                                     case Port:
                                         return QString::number(message.port);
                                     case Method:
                                         return message.method.first;
                                     [[unlikely]] default:
                                         break;
                                     }
                                     return message.username;
                                 },
                                 [role](Interfaces::VmessMessage message) -> QString {
                                     switch (role) {
                                     case Name:
                                         return QString::fromStdString(
                                           std::format("{}-Vmess", message.ps.toStdString()));
                                     case Password:
                                         return message.id;
                                     case Port:
                                         return QString::number(message.port);
                                     case Method:
                                         return message.type;
                                     [[unlikely]] default:
                                         break;
                                     }
                                     return QString();
                                 },
                                 [](auto) { return QString(); }},
                      this->m_subscribes[index]);
}

QJsonObject
SubScribesModel::toJson()
{
    return {{"urlName", this->m_urlName},
            {"url", this->m_url},
            {"updateTime", this->m_updateTime},
            {"subscribes", std::invoke([this]() -> QJsonArray {
                 auto array = QJsonArray();
                 for (auto subscribe : m_subscribes) {
                     array.append(
                       std::visit(overloaded{[](Interfaces::SSMessage message) -> QJsonObject {
                                                 return message.toJson();
                                             },
                                             [](Interfaces::VmessMessage message) -> QJsonObject {
                                                 return message.toJson();
                                             }},
                                  subscribe));
                 }
                 return array;
             })}};
}
