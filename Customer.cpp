#include "Customer.h"
#include "EntityCollection.h"

Customer::Customer(QObject* parent)
    : Entity(parent, "Customer")
{
#if 1
    age = ADD_INT_DATAITEM("age", "年龄");
    name = ADD_STRING_DATAITEM("name", "姓名");
    defaultAddr = ADD_CHILD(Address, "defaultAddress");
    addresses = ADD_CHILD_COLLECTION(Address, "address");
#else
    age = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "age", "年龄")));
    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "姓名")));
    defaultAddr = static_cast<Address*>(addChild(new Address(this), "defaultAddress"));
    addresses = static_cast<EntityCollection<Address>*>(addChildCollection(new EntityCollection<Address>(this, "address")));
#endif
}

Customer::Customer(QObject* parent, const QJsonObject& json)
    : Customer(parent)
{
    update(json);
}


QString Customer::toString() const
{
    return QString("%1=%2").arg(age->key()).arg(age->value()) + ", " +
               QString("%1=%2").arg(name->key()).arg(name->value()) ;
}