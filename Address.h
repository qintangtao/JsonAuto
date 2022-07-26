#ifndef ADDRESS_H
#define ADDRESS_H

#include "Entity.h"
#include "StringDecorator.h"

class Address : public Entity
{
    Q_OBJECT
    Q_PROPERTY(StringDecorator* ui_building MEMBER building CONSTANT)
    Q_PROPERTY(StringDecorator* ui_street MEMBER street CONSTANT)
    Q_PROPERTY(StringDecorator* ui_city MEMBER city CONSTANT)
    Q_PROPERTY(StringDecorator* ui_postcode MEMBER postcode CONSTANT)

public:
    explicit Address(QObject* parent = nullptr);
    Address(QObject* parent, const QJsonObject& json);

    StringDecorator* building{nullptr}; //建筑
    StringDecorator* street{nullptr};   //街道
    StringDecorator* city{nullptr};     //城市
    StringDecorator* postcode{nullptr}; //邮政编码

     QString toString() const;
};

#endif // ADDRESS_H
