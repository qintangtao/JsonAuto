#include "XXMUser.h"

XXMUser::XXMUser(QObject* parent)
    : Entity(parent, "XXMUser")
{
    m_id = ADD_INT_DATAITEM("id", QObject::tr("id"))
	m_age = ADD_INT_DATAITEM("age", QObject::tr("age"))
	m_name = ADD_STRING_DATAITEM("name", QObject::tr("name"))
	m_big_size = ADD_BOOL_DATAITEM("big_size", QObject::tr("big_size"))
	m_defaultAddres = ADD_CHILD(XXMAddress, "defaultAddres")
	m_address = ADD_CHILD_ENTITYCOLLECTION(XXMAddress, "address")
	m_sizes = ADD_CHILD_DATADECORATORCOLLECTION(IntDecorator, "sizes")
	
}

XXMUser::XXMUser(QObject* parent, const QJsonObject& json)
    : XXMUser(parent)
{
    update(json);
}


QString XXMUser::toString() const
{
    return QString("%1=%2").arg(m_id->label()).arg(m_id->value()) + ", " +
			QString("%1=%2").arg(m_age->label()).arg(m_age->value()) + ", " +
			QString("%1=%2").arg(m_name->label()).arg(m_name->value()) + ", " +
			QString("%1=%2").arg(m_big_size->label()).arg(m_big_size->value());
}