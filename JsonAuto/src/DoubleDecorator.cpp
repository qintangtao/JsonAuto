#include "DoubleDecorator.h"
#include <QVariant>

class DoubleDecoratorPrivate
{
public:
    DoubleDecoratorPrivate(DoubleDecorator* _decorator, double _value)
        : decorator(_decorator)
        , value(_value)
    {
    }

    DoubleDecorator* decorator{nullptr};
    double value;
};

DoubleDecorator::DoubleDecorator(Entity* parentEntity, const QString& key, const QString& label, double value)
    :  DataDecorator(parentEntity, key, label)  
    , m_d(new DoubleDecoratorPrivate(this, value))
{

}

DoubleDecorator::~DoubleDecorator()
{
    if (m_d)
        delete m_d;
}

double DoubleDecorator::value() const
{
    return m_d->value;
}

DoubleDecorator& DoubleDecorator::setValue(double value)
{
    if(value != m_d->value) {
        // ...Validation here if required...
        m_d->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue DoubleDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_d->value));
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
