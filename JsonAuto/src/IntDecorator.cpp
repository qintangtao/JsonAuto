#include "IntDecorator.h"
#include <QVariant>

class IntDecoratorPrivate
{
public:
    IntDecoratorPrivate(IntDecorator* _decorator, int _value)
        : decorator(_decorator)
        , value(_value)
    {
    }

    IntDecorator* decorator{nullptr};
    int value;
};

IntDecorator::IntDecorator(Entity* parentEntity, const QString& key, const QString& label, int value)
    :  DataDecorator(parentEntity, key, label)  
    ,  m_d(new IntDecoratorPrivate(this, value))
{

}

IntDecorator::~IntDecorator()
{
    if (m_d)
        delete m_d;
}

int IntDecorator::value() const
{
    return m_d->value;
}

IntDecorator& IntDecorator::setValue(int value)
{
    if(value != m_d->value) {
        // ...Validation here if required...
        m_d->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue IntDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_d->value));
}

void IntDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        setValue( jsonObject.value(key()).toInt());
    } else {
        setValue(0);
    }
}
void IntDecorator::update(const QJsonValue& jsonValue)
{
    setValue( jsonValue.toInt());
}
