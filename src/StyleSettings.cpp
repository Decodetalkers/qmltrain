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
  , m_subscribes({"a", "b", "c", "e"})
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

void
StyleSettings::addSubscribe(QString subscribe)
{
    m_subscribes.append(subscribe);
    Q_EMIT subscribesChanged();
}

void StyleSettings::removeSubScribe()
{
    if (m_subscribes.length() == 1) {
        return;
    }
    m_subscribes.pop_back();
    Q_EMIT subscribesChanged();
}
void StyleSettings::removeSubScribeWithKey(QString subscribe)
{
    m_subscribes.removeOne(subscribe);
    Q_EMIT subscribesChanged();
}
