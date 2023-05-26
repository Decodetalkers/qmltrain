#pragma once

#include "SubScribesModel.h"
#include <QObject>
#include <QSettings>

class StyleSettings final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(QVector<SubScribesModel *> subscribes READ subscribes NOTIFY subscribesChanged)

public:
    explicit StyleSettings(QObject *parent = nullptr);
    inline QString style() const { return m_style; };
    inline QVector<SubScribesModel *> subscribes() const { return m_subscribes; }

public slots:
    void setStyle(QString style);
    void removeSubScribeWithKey(QString subscribe);
    void addSubscribe(QString subscribe, QString subscribeAlias);

signals:
    void styleChanged();
    void subscribesChanged();

private:
    void saveSubScribingConfig();

private:
    QSettings m_settings;
    QString m_style;
    QVector<SubScribesModel *> m_subscribes;
};
