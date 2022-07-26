#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include "DataDecorator.h"
#include "IntDecorator.h"
#include "DoubleDecorator.h"
#include "StringDecorator.h"
#include "BoolDecorator.h"
#include "DateTimeDecorator.h"
#include "EntityCollection.h"

#define ADD_DATAITEM(decorator, key, label) \
                static_cast<decorator*>(addDataItem(new decorator(this, key, label)));

#define ADD_STRING_DATAITEM( key, label) \
                ADD_DATAITEM(StringDecorator, key, label)

#define ADD_INT_DATAITEM( key, label) \
                ADD_DATAITEM(IntDecorator, key, label)

#define ADD_DOUBLE_DATAITEM( key, label) \
                ADD_DATAITEM(DoubleDecorator, key, label)

#define ADD_BOOL_DATAITEM( key, label) \
                ADD_DATAITEM(BoolDecorator, key, label)

#define ADD_DATETIME_DATAITEM( key, label) \
                ADD_DATAITEM(DateTimeDecorator, key, label)

#define ADD_CHILD(cls, key) \
                static_cast<cls*>(addChild(new cls(this), key));

#define ADD_CHILD_COLLECTION(cls, key) \
                static_cast<EntityCollection<cls>*>(addChildCollection(new EntityCollection<cls>(this, key)));

class Entity : public QObject
{
    Q_OBJECT

public:
    Entity(QObject* parent = nullptr, const QString& key = "SomeEntityKey");
    Entity(QObject* parent, const QString& key, const QJsonObject& jsonObject);
    virtual ~Entity();

public:
    //数据信息体对应的key值
    const QString& key() const;

    //数据信息类和Json结构之间的相互转换
    void update(const QJsonObject& jsonObject);
    QJsonObject toJson() const;

signals:
    //信息体集合发生变化
    void childCollectionsChanged(const QString& collectionKey);
    //包含的信息体发生变化
    void childEntitiesChanged();
    //包含的属性发生变化
    void dataDecoratorsChanged();

protected:
    //添加包含的信信息体
    Entity* addChild(Entity* entity, const QString& key);
    //添加包含的信息实体列表
    EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);
    //添加子属性
    DataDecorator* addDataItem(DataDecorator* dataDecorator);
protected:
    class Implementation;
    QScopedPointer<Implementation, QScopedPointerDeleter2<Implementation>> implementation;
};

#endif // ENTITY_H
