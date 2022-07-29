#include "EnumeratorDecorator.h"
#include <QVariant>

class EnumeratorDecorator::Implementation
{
public:
    Implementation(EnumeratorDecorator* _decorator, int _value, const std::map<int, QString>& _descriptionMapper)
        : decorator(_decorator)
        , value(_value)
        , descriptionMapper(_descriptionMapper)
    {
    }

    EnumeratorDecorator* decorator{nullptr};
    int value;
    std::map<int, QString> descriptionMapper;
};

EnumeratorDecorator::EnumeratorDecorator(Entity* parentEntity, const QString& key, const QString& label, int value, const std::map<int, QString>& descriptionMapper)
    : DataDecorator(parentEntity, key, label)
{
    m_implementation.reset(new Implementation(this, value, descriptionMapper));
}

int EnumeratorDecorator::value() const
{
    return m_implementation->value;
}

QString EnumeratorDecorator::valueDescription() const
{
    if (m_implementation->descriptionMapper.find(m_implementation->value) != m_implementation->descriptionMapper.end()) {
        return m_implementation->descriptionMapper.at(m_implementation->value);
    } else {
        return {};
    }
}

EnumeratorDecorator& EnumeratorDecorator::setValue(int value)
{
    if (value != m_implementation->value) {
        // ...Validation here if required...
        m_implementation->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue EnumeratorDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_implementation->value));
}

void EnumeratorDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        setValue(jsonObject.value(key()).toInt());
    } else {
        setValue(0);
    }
}

void EnumeratorDecorator::update(const QJsonValue& jsonValue)
{
    setValue(jsonValue.toInt());
}
