#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>

class CommandLineGet final : public QObject
{
    Q_OBJECT

public:
    explicit CommandLineGet(QObject *parent = nullptr);

signals:
    void outPuts(QString);

public slots:
    void getOutput();
    void getHttpsOutput(QString);

private:
    QNetworkAccessManager *m_networkAcessManager;
};
