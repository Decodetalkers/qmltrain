#pragma once

#include <QObject>

class ChartValueModel : public QObject
{
    Q_OBJECT

public:
    explicit ChartValueModel(QObject *parent = nullptr);
    ~ChartValueModel() = default;

    Q_PROPERTY(int initialValue READ initialValue NOTIFY valuesChanged)
    inline int initialValue() { return m_initialValue; }

    Q_PROPERTY(int firstValue READ firstValue NOTIFY valuesChanged)
    inline int firstValue() { return m_firstValue; }

    Q_PROPERTY(int secondValue READ secondValue NOTIFY valuesChanged)
    inline int secondValue() { return m_secondValue; }

    Q_PROPERTY(int thirdValue READ thirdValue NOTIFY valuesChanged)
    inline int thirdValue() { return m_thirdValue; }

    Q_PROPERTY(int forthValue READ forthValue NOTIFY valuesChanged)
    inline int forthValue() { return m_forthValue; }

    Q_PROPERTY(int fifthValue READ fifthValue NOTIFY valuesChanged)
    inline int fifthValue() { return m_fifthValue; }

    Q_PROPERTY(int sixthValue READ sixthValue NOTIFY valuesChanged)
    inline int sixthValue() { return m_sixthValue; }

    Q_PROPERTY(int seventhValue READ secondValue NOTIFY valuesChanged)
    inline int seventhValue() { return m_seventhValue; }

    Q_PROPERTY(int eighthValue READ eighthValue NOTIFY valuesChanged)
    inline int eighthValue() { return m_eighthValue; }

    Q_PROPERTY(int nighthValue READ nighthValue NOTIFY valuesChanged)
    inline int nighthValue() { return m_nighthValue; }

    void appendNewValue(int value);

signals:
    void valuesChanged();

private:
    int m_initialValue{9};
    int m_firstValue{0};
    int m_secondValue{0};
    int m_thirdValue{0};
    int m_forthValue{0};
    int m_fifthValue{0};
    int m_sixthValue{0};
    int m_seventhValue{0};
    int m_eighthValue{0};
    int m_nighthValue{0};
};
