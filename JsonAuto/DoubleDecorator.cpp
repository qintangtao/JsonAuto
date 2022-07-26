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
    implementation.reset(new Implementation(this, value));
}

double DoubleDecorator::value() const
{
    return implementation->value;
}

DoubleDecorator& DoubleDecorator::setValue(double value)
{
    if(value != implementation->value) {
        // ...Validation here if required...
        implementation->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue DoubleDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void DoubleDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        setValue( jsonObject.value(key()).toDouble());
    } else {
        setValue(0.0f);
    }
}
