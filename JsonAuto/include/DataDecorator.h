#ifndef DATADECORATOR_H
#define DATADECORATOR_H

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include "JsonAuto.h"

class Entity;
class DataDecoratorPrivate;

class JSONAUTOSHARED_EXPORT DataDecorator : public QObject
{
    Q_OBJECT
    //导出QML中需要访问属性
    Q_PROPERTY( QString ui_describe READ label CONSTANT )
public:
    explicit DataDecorator(Entity *parent, const QString& key, const QString& label = "");
    ~DataDecorator();

    const QString& key() const;   //key值用来查找该属性
    const QString& label() const; //label用来描述该属性字段
    Entity* parentEntity();       //属性字段属于哪个数据实体(比如用户等)

    //Json和数据类之间的相互转化
    virtual QJsonValue jsonValue() const = 0;
    virtual void update(const QJsonObject& jsonObject) = 0;
    virtual void update(const QJsonValue& jsonValue) = 0;

private:
    DataDecoratorPrivate *m_d;
};

#endif // DATADECORATOR_H
