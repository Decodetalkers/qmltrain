#pragma once

#include "SubScribesModel.h"
#include <QObject>
#include <QSettings>

class StyleSettings final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(QVector<SubScribesModel *> subscribes READ subscribes NOTIFY subscribesChanged)
    Q_PROPERTY(int workingSubScribeIndex READ workingSubScribeIndex NOTIFY workingSubScribeIndexChanged)
    Q_PROPERTY(QString workingSubScribeUrl READ workingSubScribeUrl NOTIFY workingSubScribeUrlChanged)

public:
    explicit StyleSettings(QObject *parent = nullptr);
    inline QString style() const { return m_style; };
    inline QVector<SubScribesModel *> subscribes() const { return m_subscribes; }
    inline QString workingSubScribeUrl() const { return m_workingSubScribeUrl;}
    inline int workingSubScribeIndex() const { return m_workingSubScribeIndex;}

public slots:
    void setStyle(QString style);
    void removeSubScribeWithKey(QString subscribe);
    void addSubscribe(QString subscribe, QString subscribeAlias);
    void setWorkingSubScribe(QString url, int index, bool toset);
    void savetoClipBoard(QString text);

signals:
    void styleChanged();
    void subscribesChanged();
    void workingSubScribeUrlChanged();
    void workingSubScribeIndexChanged();

private:
    void getSettings();
    void saveSubScribingConfig();
    void saveSettingsConfig();

private:
    QSettings m_settings;
    QString m_style;
    QVector<SubScribesModel *> m_subscribes;
    int m_workingSubScribeIndex;
    QString m_workingSubScribeUrl;
};
