#include "BoolDecorator.h"
#include <QVariant>

class BoolDecorator::Implementation
{
public:
    Implementation(BoolDecorator* _decorator, bool _value)
        : decorator(_decorator)
        , value(_value)
    {
    }

    BoolDecorator* decorator{nullptr};
    bool value;
};

BoolDecorator::BoolDecorator(Entity* parentEntity, const QString& key, const QString& label, bool value)
    :  DataDecorator(parentEntity, key, label)
{
    m_implementation.reset(new Implementation(this, value));
}

bool BoolDecorator::value() const
{
    return m_implementation->value;
}

BoolDecorator& BoolDecorator::setValue(bool value)
{
    if(value != m_implementation->value) {
        // ...Validation here if required...
        m_implementation->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue BoolDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_implementation->value));
}

void BoolDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        setValue( jsonObject.value(key()).toBool());
    } else {
        setValue(false);
    }
}

void BoolDecorator::update(const QJsonValue& jsonValue)
{
    setValue( jsonValue.toBool());
}
