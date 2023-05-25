#pragma once

#include "Commandline.h"
#include "Interface.h"

#include <QAbstractListModel>

class SubScribesModel final : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString url READ url NOTIFY urlChanged)
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

    QString url() { return m_url; };

signals:
    void urlChanged();
private:
    QString get_property(SubScribeRole role, int index) const;

private:
    QString m_url;
    QVector<Interfaces::UrlMessage> m_subscribes;
    CommandLineGet *m_subscribeCommand;
};
