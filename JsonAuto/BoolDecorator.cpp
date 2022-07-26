#include "BoolDecorator.h"
#include <QVariant>

class BoolDecorator::Implementation
{
public:
    Implementation(BoolDecorator* BoolDecorator, bool value)
        : BoolDecorator(BoolDecorator)
        , value(value)
    {
    }

    BoolDecorator* BoolDecorator{nullptr};
    bool value;
};

BoolDecorator::BoolDecorator(Entity* parentEntity, const QString& key, const QString& label, bool value)
    :  DataDecorator(parentEntity, key, label)
{
    implementation.reset(new Implementation(this, value));
}

bool BoolDecorator::value() const
{
    return implementation->value;
}

BoolDecorator& BoolDecorator::setValue(bool value)
{
    if(value != implementation->value) {
        // ...Validation here if required...
        implementation->value = value;
        emit valueChanged();
    }

    return *this;
}

QJsonValue BoolDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void BoolDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        setValue( jsonObject.value(key()).toBool());
    } else {
        setValue(false);
    }
}
