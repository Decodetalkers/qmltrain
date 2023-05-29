#pragma once

#include "ProgressStatus/ChartValueModel.h"

#include <QObject>

class ProgressStatus final : public QObject
{
    Q_OBJECT

public:
    explicit ProgressStatus(QObject *parent = nullptr);
    ~ProgressStatus() = default;

    Q_PROPERTY(ChartValueModel *x READ x NOTIFY valueChanged)
    inline ChartValueModel *x() { return m_x; }

    Q_PROPERTY(ChartValueModel *y READ y NOTIFY valueChanged)
    inline ChartValueModel *y() { return m_y; }

    Q_PROPERTY(ChartValueModel *z READ z NOTIFY valueChanged)
    inline ChartValueModel *z() { return m_z; }
    
signals:
    void valueChanged();

private:
    ChartValueModel *m_x;
    ChartValueModel *m_y;
    ChartValueModel *m_z;
};
