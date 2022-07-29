#include "EnumeratorDecorator.h"
#include <QVariant>

class EnumeratorDecoratorPrivate
{
public:
    EnumeratorDecoratorPrivate(EnumeratorDecorator* _decorator, int _value, const std::map<int, QString>& _descriptionMapper)
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
    , m_d(new EnumeratorDecoratorPrivate(this, value, descriptionMapper))
{

}

EnumeratorDecorator::~EnumeratorDecorator()
{
    if (m_d)
        delete m_d;
}

int EnumeratorDecorator::value() const
{
    return m_d->value;
}

QString EnumeratorDecorator::valueDescription() const
{
    if (m_d->descriptionMapper.find(m_d->value) != m_d->descriptionMapper.end()) {
        return m_d->descriptionMapper.at(m_d->value);
    } else {
        return {};
    }
}

EnumeratorDecorator& EnumeratorDecorator::setValue(int value)
{
    if (value != m_d->value) {
        // ...Validation here if required...
        m_d->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue EnumeratorDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_d->value));
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
