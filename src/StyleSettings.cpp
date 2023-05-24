#include "StyleSettings.h"
#include <QDebug>
#include <QQuickStyle>

StyleSettings::StyleSettings(QObject *parent)
  : QObject(parent)
  , m_settings(QSettings())
  , m_style(std::visit([this]() -> QString {
      auto settings = m_settings.value(QLatin1String("style")).toString();
      return settings;
  }))
{
}

void
StyleSettings::setStyle(QString style)
{
    m_settings.setValue(QLatin1String("style"), style);
    m_style = style;
    Q_EMIT styleChanged();
    qDebug() << "Style is :" << style;
}
