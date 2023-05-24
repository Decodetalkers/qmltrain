#include "SubScribesModel.h"
#include <functional>
#include <qhash.h>

SubScribesModel::SubScribesModel(QObject *parent)
  : QAbstractListModel(parent)
{
}

int
SubScribesModel::rowCount(const QModelIndex &) const
{
    return m_subscribes.count();
}

QVariant
SubScribesModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount()) {
        return get_property(static_cast<SubScribeRole>(role), index.row());
    }
    return QVariant();
}

QHash<int, QByteArray>
SubScribesModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{
      {Name, "Name"}, {Password, "Password"}, {Port, "Port"}, {Method, "Method"}};
    return roles;
}

void
SubScribesModel::init()
{
}

QString
SubScribesModel::get_property(SubScribesModel::SubScribeRole role, int index) const
{
    return std::visit(overloaded{[role](Interfaces::SSMessage message) -> QString {
                                     switch (role) {
                                     case Name:
                                         return message.username;
                                     case Password:
                                         return message.password;
                                     case Port:
                                         return QString::number(message.port);
                                     case Method:
                                         return message.method.first;
                                     }
                                     return message.username;
                                 },
                                 [role](Interfaces::VmessMessage message) -> QString {
                                     switch (role) {
                                     case Name:
                                         return message.id;
                                     case Password:
                                         return message.ps;
                                     case Port:
                                         return QString::number(message.port);
                                     case Method:
                                         return message.type;
                                     }
                                     return QString();
                                 },
                                 [](auto) { return QString(); }},
                      this->m_subscribes[index]);
}
