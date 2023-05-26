#pragma once

#include "Interface.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>

class CommandLineGet final : public QObject
{
    Q_OBJECT

public:
    explicit CommandLineGet(QObject *parent = nullptr);

    enum GetHttpStatus
    {
        Successed,
        Failed,
    };
    Q_ENUM(GetHttpStatus)

signals:
    void outPuts(QString);
    void suribesUpdate(QVector<Interfaces::UrlMessage>);
    void startGetHttps();
    void endGetHttpsStatus(GetHttpStatus);

public slots:
    void getOutput();
    void getHttpsOutput(QString);

private:
    QNetworkAccessManager *m_networkAcessManager;
};
