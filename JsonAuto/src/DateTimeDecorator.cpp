#include "DateTimeDecorator.h"
#include <QVariant>

class DateTimeDecoratorPrivate
{
public:
    DateTimeDecoratorPrivate(DateTimeDecorator* _decorator, const QDateTime& _value)
        : decorator(_decorator)
        , value(_value)
    {
    }
    DateTimeDecorator* decorator{nullptr};
    QDateTime value;
};

DateTimeDecorator::DateTimeDecorator(Entity* parentEntity, const QString& key, const QString& label, const QDateTime& value)
    :  DataDecorator(parentEntity, key, label)
    , m_d(new DateTimeDecoratorPrivate(this, value))
{
}

DateTimeDecorator::~DateTimeDecorator()
{
    if (m_d)
        delete m_d;
}

const QDateTime& DateTimeDecorator::value() const
{
    return m_d->value;
}

DateTimeDecorator& DateTimeDecorator::setValue(const QDateTime& value)
{
    if(value != m_d->value) {
        // ...Validation here if required...
        m_d->value = value;
        emit valueChanged();
    }

    return *this;
}

QString DateTimeDecorator::toIso8601String() const
{
    if (m_d->value.isNull()) {
        return "Not set";
    } else {
        return m_d->value.toString(Qt::ISODate);
    }
}

QString DateTimeDecorator::toPrettyString() const
{
    if (m_d->value.isNull()) {
        return "Not set";
    } else {
        return m_d->value.toString( "ddd d MMM yyyy @ HH:mm:ss" );
    }
}

QString DateTimeDecorator::toPrettyDateString() const
{
    if (m_d->value.isNull()) {
        return "Not set";
    } else {
        return m_d->value.toString( "d MMM yyyy" );
    }
}

QString DateTimeDecorator::toPrettyTimeString() const
{
    if (m_d->value.isNull()) {
        return "Not set";
    } else {
        return m_d->value.toString( "hh:mm ap" );
    }
}

QJsonValue DateTimeDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_d->value.toString(Qt::ISODate)));
}

void DateTimeDecorator::update(const QJsonObject& jsonObject)
{
    if (jsonObject.contains(key())) {
        setValue(QDateTime::fromString( jsonObject.value(key()).toString(), Qt::ISODate));  // yyyy-MM-ddTHH:mm:ss
    } else {
        setValue(QDateTime());
    }
}

void DateTimeDecorator::update(const QJsonValue& jsonValue)
{
    setValue(QDateTime::fromString( jsonValue.toString(), Qt::ISODate));  // yyyy-MM-ddTHH:mm:ss
}
