#include "IntDecorator.h"
#include <QVariant>

class IntDecorator::Implementation
{
public:
    Implementation(IntDecorator* intDecorator, int value)
        : intDecorator(intDecorator)
        , value(value)
    {
    }

    IntDecorator* intDecorator{nullptr};
    int value;
};

IntDecorator::IntDecorator(Entity* parentEntity, const QString& key, const QString& label, int value)
    :  DataDecorator(parentEntity, key, label)  
{
    m_implementation.reset(new Implementation(this, value));
}

int IntDecorator::value() const
{
    return m_implementation->value;
}

IntDecorator& IntDecorator::setValue(int value)
{
    if(value != m_implementation->value) {
        // ...Validation here if required...
        m_implementation->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue IntDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_implementation->value));
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
