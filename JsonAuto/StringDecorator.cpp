#include "StringDecorator.h"
#include <QVariant>

class StringDecorator::Implementation
{
public:
    Implementation(StringDecorator* _stringDecorator, const QString& _value)
        : stringDecorator(_stringDecorator)
        , value(_value)
    {
    }

    StringDecorator* stringDecorator{nullptr};
    QString value;
};

StringDecorator::StringDecorator(Entity* parentEntity, const QString& key, const QString& label, const QString& value)
        :   DataDecorator(parentEntity, key, label)
{
    m_implementation.reset(new Implementation(this, value));
}

const QString& StringDecorator::value() const
{
    return m_implementation->value;
}

StringDecorator& StringDecorator::setValue(const QString& value)
{
    if(value != m_implementation->value) {
        m_implementation->value = value;
        emit valueChanged();
    }
    return *this;
}

QJsonValue StringDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_implementation->value));
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
