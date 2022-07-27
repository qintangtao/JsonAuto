#include "Address.h"

Address::Address(QObject* parent)
        : Entity(parent, "address")
{
#if 1
    m_building = ADD_STRING_DATAITEM("building", "Building");
    m_building = ADD_STRING_DATAITEM("building", "Building");
    m_street = ADD_STRING_DATAITEM("street", "Street");
    m_city = ADD_STRING_DATAITEM( "city", "City");
    m_postcode = ADD_STRING_DATAITEM("postcode", "Post Code");
#else
    building = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "building", "Building")));
    street = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "street", "Street")));
    city = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "city", "City")));
    postcode = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "postcode", "Post Code")));
#endif
}

Address::Address(QObject* parent, const QJsonObject& json)
        :  Address(parent)
{
    update(json);
}

QString Address::toString() const
{
    return QString("%1=%2").arg(m_building->key()).arg(m_building->value()) + ", " +
               QString("%1=%2").arg(m_street->key()).arg(m_street->value()) + ", " +
               QString("%1=%2").arg(m_city->key()).arg(m_city->value()) + ", " +
               QString("%1=%2").arg(m_postcode->key()).arg(m_postcode->value())  ;
}
