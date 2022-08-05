#include "XXMAddress.h"

XXMAddress::XXMAddress(QObject* parent)
    : Entity(parent, "XXMAddress")
{
    m_id = ADD_INT_DATAITEM("id", QObject::tr("id"))
	m_age = ADD_INT_DATAITEM("age", QObject::tr("age"))
	m_name = ADD_STRING_DATAITEM("name", QObject::tr("name"))
	m_big_size = ADD_BOOL_DATAITEM("big_size", QObject::tr("big_size"))
	
}

XXMAddress::XXMAddress(QObject* parent, const QJsonObject& json)
    : XXMAddress(parent)
{
    update(json);
}


QString XXMAddress::toString() const
{
    return QString("%1=%2").arg(m_id->label()).arg(m_id->value()) + ", " +
			QString("%1=%2").arg(m_age->label()).arg(m_age->value()) + ", " +
			QString("%1=%2").arg(m_name->label()).arg(m_name->value()) + ", " +
			QString("%1=%2").arg(m_big_size->label()).arg(m_big_size->value());
}