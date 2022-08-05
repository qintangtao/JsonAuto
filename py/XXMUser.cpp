#include "XXMUser.h"

XXMUser::XXMUser(QObject* parent)
    : Entity(parent, "XXMUser")
{
    ADD_INT_DATAITEM("id", QObject::tr("id"))
	ADD_INT_DATAITEM("age", QObject::tr("age"))
	ADD_STRING_DATAITEM("name", QObject::tr("name"))
	ADD_BOOL_DATAITEM("big_size", QObject::tr("big_size"))
	ADD_CHILD(XXMAddress, "defaultAddres")
	ADD_CHILD_ENTITYCOLLECTION(XXMAddress, "address")
	ADD_CHILD_DATADECORATORCOLLECTION(IntDecorator, "sizes")
	
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