#pragma once

#include "Interface.h"
#include "Commandline.h"

#include <QAbstractListModel>

class SubScribesModel final : public QAbstractListModel
{
    Q_OBJECT

public:
    enum SubScribeRole
    {
        Name     = Qt::DisplayRole,
        Password = Qt::UserRole,
        Port,
        Method,
        Url,
    };
    Q_ENUM(SubScribeRole)
    SubScribesModel(QString url,
                    QVector<Interfaces::UrlMessage> subsribes,
                    QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void updateSucribes();

private:
    QString get_property(SubScribeRole role, int index) const;

private:
    QString m_url;
    QVector<Interfaces::UrlMessage> m_subscribes;
    CommandLineGet* m_subscribeCommand;
};
