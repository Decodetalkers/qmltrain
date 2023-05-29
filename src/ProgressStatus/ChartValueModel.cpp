#include "ChartValueModel.h"

ChartValueModel::ChartValueModel(QObject *parent)
  : QObject(parent)
{
}

void
ChartValueModel::appendNewValue(int value)
{
    m_initialValue = m_fifthValue;
    m_firstValue   = m_secondValue;
    m_secondValue  = m_thirdValue;
    m_thirdValue   = m_forthValue;
    m_forthValue   = m_fifthValue;
    m_fifthValue   = m_sixthValue;
    m_sixthValue   = m_seventhValue;
    m_seventhValue = m_eighthValue;
    m_eighthValue  = m_nighthValue;
    m_nighthValue  = value;
    Q_EMIT valuesChanged();
}
