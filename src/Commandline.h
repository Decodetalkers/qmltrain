#pragma once

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
};
