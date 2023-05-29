#include "ProgressStatus.h"

#include <QRandomGenerator64>
#include <QTimer>
#include <QDebug>

ProgressStatus::ProgressStatus(QObject *parent)
  : QObject(parent)
  , m_x(new ChartValueModel(this))
  , m_y(new ChartValueModel(this))
  , m_z(new ChartValueModel(this))
{
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this] {
        int newx = QRandomGenerator64::global()->bounded(10);
        m_x->appendNewValue(newx);
        int newy = QRandomGenerator64::global()->bounded(10);
        m_y->appendNewValue(newy);
        int newz = QRandomGenerator64::global()->bounded(10);
        m_z->appendNewValue(newz);
        Q_EMIT valueChanged();
    });
    timer->start(800);
}
