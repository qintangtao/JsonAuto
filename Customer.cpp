#include "Customer.h"
#include "EntityCollection.h"

Customer::Customer(QObject* parent)
    : Entity(parent, "Customer")
{
#if 1
    m_valide = ADD_BOOL_DATAITEM("valide", QObject::tr("有效"));
    m_distance = ADD_DOUBLE_DATAITEM("distance", QObject::tr("距离"));
    m_date = ADD_DATETIME_DATAITEM("date", QObject::tr("日期"));
    m_age = ADD_INT_DATAITEM("age", QObject::tr("年龄"));
    m_name = ADD_STRING_DATAITEM("name", QObject::tr("姓名"));
    m_defaultAddr = ADD_CHILD(Address, "defaultAddress");
    m_addresses = ADD_CHILD_COLLECTION(Address, "address");
#else
    m_age = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "age", "年龄")));
    m_name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "姓名")));
    m_defaultAddr = static_cast<Address*>(addChild(new Address(this), "defaultAddress"));
    m_addresses = static_cast<EntityCollection<Address>*>(addChildCollection(new EntityCollection<Address>(this, "address")));
#endif
}

Customer::Customer(QObject* parent, const QJsonObject& json)
    : Customer(parent)
{
    update(json);
}


QString Customer::toString() const
{
    return QString("%1=%2").arg(m_valide->label()).arg(m_valide->value() ? "true" : "false") + ", " +
               QString("%1=%2").arg(m_distance->label()).arg(m_distance->value()) + ", " +
               QString("%1=%2").arg(m_date->label()).arg(m_date->toIso8601String()) + ", " +
               QString("%1=%2").arg(m_age->label()).arg(m_age->value()) + ", " +
               QString("%1=%2").arg(m_name->label()).arg(m_name->value()) ;
}
