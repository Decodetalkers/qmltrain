#pragma once

#include <QObject>
#include <QSettings>

class StyleSettings final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)

public:
    explicit StyleSettings(QObject *parent = nullptr);
    inline QString style() const { return m_style; };

public slots:
    void setStyle(QString style);

signals:
    void styleChanged();

private:
    QSettings m_settings;
    QString m_style;
};
