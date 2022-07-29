#include "DateTimeDecorator.h"
#include <QVariant>

class DateTimeDecorator::Implementation
{
public:
    Implementation(DateTimeDecorator* dateTimeDecorator, const QDateTime& value)
        : dateTimeDecorator(dateTimeDecorator)
        , value(value)
    {
    }
    DateTimeDecorator* dateTimeDecorator{nullptr};
    QDateTime value;
};

DateTimeDecorator::DateTimeDecorator(Entity* parentEntity, const QString& key, const QString& label, const QDateTime& value)
    :  DataDecorator(parentEntity, key, label)
{
    m_implementation.reset(new Implementation(this, value));
}

const QDateTime& DateTimeDecorator::value() const
{
    return m_implementation->value;
}

DateTimeDecorator& DateTimeDecorator::setValue(const QDateTime& value)
{
    if(value != m_implementation->value) {
        // ...Validation here if required...
        m_implementation->value = value;
        emit valueChanged();
    }

    return *this;
}

QString DateTimeDecorator::toIso8601String() const
{
    if (m_implementation->value.isNull()) {
        return "Not set";
    } else {
        return m_implementation->value.toString(Qt::ISODate);
    }
}

QString DateTimeDecorator::toPrettyString() const
{
    if (m_implementation->value.isNull()) {
        return "Not set";
    } else {
        return m_implementation->value.toString( "ddd d MMM yyyy @ HH:mm:ss" );
    }
}

QString DateTimeDecorator::toPrettyDateString() const
{
    if (m_implementation->value.isNull()) {
        return "Not set";
    } else {
        return m_implementation->value.toString( "d MMM yyyy" );
    }
}

QString DateTimeDecorator::toPrettyTimeString() const
{
    if (m_implementation->value.isNull()) {
        return "Not set";
    } else {
        return m_implementation->value.toString( "hh:mm ap" );
    }
}

QJsonValue DateTimeDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(m_implementation->value.toString(Qt::ISODate)));
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
