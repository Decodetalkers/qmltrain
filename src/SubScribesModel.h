#pragma once

#include "Interface.h"

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
    };
    Q_ENUM(SubScribeRole)
    SubScribesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void init();

private:
    QString get_property(SubScribeRole role, int index) const;

private:
    QVector<Interfaces::UrlMessage> m_subscribes;
};
