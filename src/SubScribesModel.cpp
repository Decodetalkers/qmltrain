#include "SubScribesModel.h"
#include "src/Interface.h"

SubScribesModel::SubScribesModel(QString url,
                                 QVector<Interfaces::UrlMessage> subscribes,
                                 QObject *parent)
  : QAbstractListModel(parent)
  , m_url(url)
  , m_subscribes(subscribes)
  , m_subscribeCommand(new CommandLineGet(this))
{
    connect(m_subscribeCommand, &CommandLineGet::suribesUpdate, this, [this](auto subscribes) {
        //qDebug() << subscribes;
        beginResetModel();
        m_subscribes.clear();
        m_subscribes = subscribes;
        endResetModel();
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
