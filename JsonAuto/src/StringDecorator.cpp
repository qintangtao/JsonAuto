#include "StringDecorator.h"
#include <QVariant>

class StringDecoratorPrivate
{
public:
    StringDecoratorPrivate(StringDecorator* _decorator, const QString& _value)
        : decorator(_decorator)
        , value(_value)
    {
    }

    StringDecorator* decorator{nullptr};
    QString value;
};

StringDecorator::StringDecorator(Entity* parentEntity, const QString& key, const QString& label, const QString& value)
        :   DataDecorator(parentEntity, key, label)
        ,   m_d(new StringDecoratorPrivate(this, value))
{

}

StringDecorator::~StringDecorator()
{
    if (m_d)
        delete m_d;
}

const QString& StringDecorator::value() const
{
    return m_d->value;
}

StringDecorator& StringDecorator::setValue(const QString& value)
{
    if(value != m_d->value) {
        m_d->value = value;
        emit valueChanged();
    }
    return *this;
}

QJsonValue StringDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_d->value));
}

void StringDecorator::update(const QJsonObject& _jsonObject)
{
    if (_jsonObject.contains(key())) {
        setValue(_jsonObject.value(key()).toString());
    }
}

void StringDecorator::update(const QJsonValue& jsonValue)
{
    setValue(jsonValue.toString());
}
