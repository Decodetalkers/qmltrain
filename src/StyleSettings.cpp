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
  , m_subscribes({})
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
    m_subscribes.append(new SubScribesModel(subscribe, {}, this));
    Q_EMIT subscribesChanged();
}

void
StyleSettings::removeSubScribeWithKey(QString subscribe)
{
    int index     = 0;
    bool hasmatch = false;
    for (; index < m_subscribes.length(); ++index) {
        if (subscribe == m_subscribes[index]->url()) {
            hasmatch = true;
            break;
        }
    }
    if (hasmatch) {
        m_subscribes.removeAt(index);
    }
    Q_EMIT subscribesChanged();
}
