#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Entity.h"
#include "EntityCollection.h"

#include "IntDecorator.h"
#include "StringDecorator.h"

#include "Address.h"

class Customer : public Entity
{
    Q_OBJECT
public:
    explicit Customer(QObject* parent = nullptr);
    Customer(QObject* parent, const QJsonObject& json);

    IntDecorator* age{nullptr};       //年龄
    StringDecorator* name{nullptr};   //姓名
    Address* defaultAddr{nullptr};    //默认地址
    EntityCollection<Address>* addresses{nullptr}; //地址列表

    QString toString() const;
};

#endif // CUSTOMER_H
