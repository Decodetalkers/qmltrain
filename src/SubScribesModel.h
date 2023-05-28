#pragma once

#include "Commandline.h"
#include "Interface.h"

#include <QAbstractListModel>

class SubScribesModel final : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    Q_PROPERTY(QString urlName READ urlName NOTIFY urlNameChanged)
    Q_PROPERTY(bool subscribing READ subscribing NOTIFY subscribingStatusChanged)
    Q_PROPERTY(int subscribeCounts READ subscribeCounts NOTIFY subscribeCountsChanged)
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
                    QString urlName,
                    QVector<Interfaces::UrlMessage> subsribes,
                    QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void updateSucribes();

    QString url() { return m_url; };
    QString urlName() { return m_urlName; };
    bool subscribing() { return m_subscribing; };
    int subscribeCounts() { return m_subscribes.length(); };

    QJsonObject toJson();

signals:
    void urlChanged();
    void urlNameChanged();
    void subscribingStatusChanged();
    void subscribinfosUpdate();
    void subscribeCountsChanged();

private:
    QString get_property(SubScribeRole role, int index) const;

private:
    QString m_url;
    QString m_urlName;
    QVector<Interfaces::UrlMessage> m_subscribes;
    CommandLineGet *m_subscribeCommand;
    bool m_subscribing = false;
};
