#pragma once

#include <QObject>
#include <QSettings>

class StyleSettings final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(QStringList subscribes READ subscribes NOTIFY subscribesChanged)

public:
    explicit StyleSettings(QObject *parent = nullptr);
    inline QString style() const { return m_style; };
    inline QStringList subscribes() const { return m_subscribes; }

public slots:
    void setStyle(QString style);
    void removeSubScribe();
    void addSubscribe(QString subscribe);

signals:
    void styleChanged();
    void subscribesChanged();

private:
    QSettings m_settings;
    QString m_style;
    QStringList m_subscribes;
};
