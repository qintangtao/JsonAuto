#ifndef ADDRESS_H
#define ADDRESS_H

#include "Entity.h"
#include "StringDecorator.h"

class Address : public Entity
{
    Q_OBJECT
    Q_PROPERTY(StringDecorator* ui_building MEMBER m_building CONSTANT)
    Q_PROPERTY(StringDecorator* ui_street MEMBER m_street CONSTANT)
    Q_PROPERTY(StringDecorator* ui_city MEMBER m_city CONSTANT)
    Q_PROPERTY(StringDecorator* ui_postcode MEMBER m_postcode CONSTANT)

public:
    explicit Address(QObject* parent = nullptr);
    Address(QObject* parent, const QJsonObject& json);

    STRINGDECORATOR_METHOD(m_building, setBuilding, building)
    STRINGDECORATOR_METHOD(m_street, setStreet, street)
    STRINGDECORATOR_METHOD(m_city, setCity, city)
    STRINGDECORATOR_METHOD(m_postcode, setPostcode, postcode)

    QString toString() const;

private:
    StringDecorator* m_building; //建筑
    StringDecorator* m_street;   //街道
    StringDecorator* m_city;     //城市
    StringDecorator* m_postcode; //邮政编码
};

#endif // ADDRESS_H
