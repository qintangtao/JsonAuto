#include "Address.h"

Address::Address(QObject* parent)
        : Entity(parent, "address")
{
    m_building = ADD_STRING_DATAITEM("building", QObject::tr("楼栋"));
    m_street = ADD_STRING_DATAITEM("street", QObject::tr("街道"));
    m_city = ADD_STRING_DATAITEM( "city", QObject::tr("城市"));
    m_postcode = ADD_STRING_DATAITEM("postcode", QObject::tr("编码"));
}

Address::Address(QObject* parent, const QJsonObject& json)
        :  Address(parent)
{
    update(json);
}

QString Address::toString() const
{
    return QString("%1=%2").arg(m_building->label()).arg(m_building->value()) + ", " +
               QString("%1=%2").arg(m_street->label()).arg(m_street->value()) + ", " +
               QString("%1=%2").arg(m_city->label()).arg(m_city->value()) + ", " +
               QString("%1=%2").arg(m_postcode->label()).arg(m_postcode->value())  ;
}
