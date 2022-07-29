#include "DoubleDecorator.h"
#include <QVariant>

class DoubleDecorator::Implementation
{
public:
    Implementation(DoubleDecorator* DoubleDecorator, double value)
        : DoubleDecorator(DoubleDecorator)
        , value(value)
    {
    }

    DoubleDecorator* DoubleDecorator{nullptr};
    double value;
};

DoubleDecorator::DoubleDecorator(Entity* parentEntity, const QString& key, const QString& label, double value)
    :  DataDecorator(parentEntity, key, label)  
{
    m_implementation.reset(new Implementation(this, value));
}

double DoubleDecorator::value() const
{
    return m_implementation->value;
}

DoubleDecorator& DoubleDecorator::setValue(double value)
{
    if(value != m_implementation->value) {
        // ...Validation here if required...
        m_implementation->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue DoubleDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_implementation->value));
}

void DoubleDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        setValue( jsonObject.value(key()).toDouble());
    } else {
        setValue(0.0f);
    }
}

void DoubleDecorator::update(const QJsonValue& jsonValue)
{
    setValue( jsonValue.toDouble());
}
