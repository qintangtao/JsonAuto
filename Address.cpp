#include "Address.h"

Address::Address(QObject* parent)
        : Entity(parent, "address")
{
#if 1
    building = ADD_STRING_DATAITEM("building", "Building");
    building = ADD_STRING_DATAITEM("building", "Building");
    street = ADD_STRING_DATAITEM("street", "Street");
    city = ADD_STRING_DATAITEM( "city", "City");
    postcode = ADD_STRING_DATAITEM("postcode", "Post Code");
#else
    building = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "building", "Building")));
    street = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "street", "Street")));
    city = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "city", "City")));
    postcode = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "postcode", "Post Code")));
#endif
}

Address::Address(QObject* parent, const QJsonObject& json)
        : Address(parent)
{
    update(json);
}

QString Address::toString() const
{
    return QString("%1=%2").arg(building->key()).arg(building->value()) + ", " +
               QString("%1=%2").arg(street->key()).arg(street->value()) + ", " +
               QString("%1=%2").arg(city->key()).arg(city->value()) + ", " +
               QString("%1=%2").arg(postcode->key()).arg(postcode->value())  ;
}
