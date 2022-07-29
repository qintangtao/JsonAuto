#include "BoolDecorator.h"
#include <QVariant>



class BoolDecoratorPrivate
{
public:
    BoolDecoratorPrivate(BoolDecorator* _decorator, bool _value)
        : decorator(_decorator)
        , value(_value)
    {
    }

    BoolDecorator* decorator{nullptr};
    bool value;
};

BoolDecorator::BoolDecorator(Entity* parentEntity, const QString& key, const QString& label, bool value)
    :  DataDecorator(parentEntity, key, label)
    , m_d(new BoolDecoratorPrivate(this, value))
{

}

BoolDecorator::~BoolDecorator()
{
    if (m_d)
        delete m_d;
}

bool BoolDecorator::value() const
{
    return m_d->value;
}

BoolDecorator& BoolDecorator::setValue(bool value)
{
    if(value != m_d->value) {
        // ...Validation here if required...
        m_d->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue BoolDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_d->value));
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
