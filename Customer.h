#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Entity.h"

#include "Address.h"

class Customer : public Entity
{
    Q_OBJECT
public:
    explicit Customer(QObject* parent = nullptr);
    Customer(QObject* parent, const QJsonObject& json);

    BOOLGDECORATOR_METHOD(m_valide, setValide, valide)
    DOUBLEGDECORATOR_METHOD(m_distance, setDistance, distance)
    DATETIMEGDECORATOR_METHOD(m_date, setDate, date)
    INTGDECORATOR_METHOD(m_age, setAge, age)
    STRINGDECORATOR_METHOD(m_name, setName, name)

    inline Address* defaultAddr() const
    { return m_defaultAddr; }

    inline EntityCollection<Address>* addresses() const
    { return m_addresses; }

    inline DataDecoratorCollection<IntDecorator>* orders() const
    { return m_orders; }

    QString toString() const;

private:
    BoolDecorator* m_valide;
    DoubleDecorator* m_distance;
    DateTimeDecorator *m_date;
    IntDecorator* m_age;       //年龄
    StringDecorator* m_name;   //姓名
    Address* m_defaultAddr;    //默认地址
    EntityCollection<Address>* m_addresses; //地址列表
    DataDecoratorCollection<IntDecorator> * m_orders;
};

#endif // CUSTOMER_H
