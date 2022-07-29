#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "JsonAuto.h"
#include "DataDecorator.h"
#include "IntDecorator.h"
#include "DoubleDecorator.h"
#include "StringDecorator.h"
#include "BoolDecorator.h"
#include "DateTimeDecorator.h"
#include "EntityCollection.h"
#include "DataDecoratorCollection.h"

// add decorator
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

#define ADD_CHILD_COLLECTION(cls, type, key) \
                static_cast<cls<type>*>(addChildCollection(new cls<type>(this, key)));

#define ADD_CHILD_ENTITYCOLLECTION(type, key) \
               ADD_CHILD_COLLECTION(EntityCollection, type, key)

#define ADD_CHILD_DATADECORATORCOLLECTION(type, key) \
               ADD_CHILD_COLLECTION(DataDecoratorCollection, type, key)

// method
#define DECORATOR_SETMETHOD(PROPERTYTYPE, PROPERTYNAME, SETNAME) \
    inline void SETNAME(PROPERTYTYPE value) { PROPERTYNAME->setValue(value); }

#define DECORATOR_GETMETHOD(PROPERTYTYPE, PROPERTYNAME, GETNAME) \
    inline PROPERTYTYPE GETNAME() const {   return PROPERTYNAME->value();  }

// string method
#define STRINGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    DECORATOR_SETMETHOD(const QString&, PROPERTYNAME, SETNAME)

#define STRINGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME) \
    DECORATOR_GETMETHOD(const QString&, PROPERTYNAME, GETNAME)

#define STRINGDECORATOR_METHOD(PROPERTYNAME, SETNAME, GETNAME) \
    STRINGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    STRINGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME)

// int method
#define INTGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    DECORATOR_SETMETHOD(int, PROPERTYNAME, SETNAME)

#define INTGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME) \
    DECORATOR_GETMETHOD(int, PROPERTYNAME, GETNAME)

#define INTGDECORATOR_METHOD(PROPERTYNAME, SETNAME, GETNAME) \
    INTGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    INTGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME)

// double method
#define DOUBLEGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    DECORATOR_SETMETHOD(double, PROPERTYNAME, SETNAME)

#define DOUBLEGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME) \
    DECORATOR_GETMETHOD(double, PROPERTYNAME, GETNAME)

#define DOUBLEGDECORATOR_METHOD(PROPERTYNAME, SETNAME, GETNAME) \
    DOUBLEGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    DOUBLEGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME)

// bool method
#define BOOLGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    DECORATOR_SETMETHOD(bool, PROPERTYNAME, SETNAME)

#define BOOLGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME) \
    DECORATOR_GETMETHOD(bool, PROPERTYNAME, GETNAME)

#define BOOLGDECORATOR_METHOD(PROPERTYNAME, SETNAME, GETNAME) \
    BOOLGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    BOOLGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME)

// DateTime method
#define DATETIMEGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    DECORATOR_SETMETHOD(const QDateTime&, PROPERTYNAME, SETNAME)

#define DATETIMEGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME) \
    DECORATOR_GETMETHOD(const QDateTime&, PROPERTYNAME, GETNAME)

#define DATETIMEGDECORATOR_METHOD(PROPERTYNAME, SETNAME, GETNAME) \
    DATETIMEGDECORATOR_SETMETHOD(PROPERTYNAME, SETNAME) \
    DATETIMEGDECORATOR_GETMETHOD(PROPERTYNAME, GETNAME)


template <class T>
T* JsontoEntity(const QString &json)
{
    QJsonParseError jsonerror;
    QJsonDocument doucment;

    doucment = QJsonDocument::fromJson(json.toLocal8Bit(), &jsonerror);

    if(jsonerror.error != QJsonParseError::NoError) {
        return NULL;
    }

    if( !doucment.isObject() ) {
        return NULL;
    }

    return new T(NULL, doucment.object());
}

QString JSONAUTOSHARED_EXPORT EntitytoJson(Entity *entity);

class EntityPrivate;

class  JSONAUTOSHARED_EXPORT Entity : public QObject
{
    Q_OBJECT

public:
    explicit Entity(QObject* parent = nullptr, const QString& key = "SomeEntityKey");
    explicit Entity(QObject* parent, const QString& key, const QJsonObject& jsonObject);
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
    //基本体集合发生变化
    void childDecoratorCollectionsChanged(const QString& collectionKey);
    //包含的信息体发生变化
    void childEntitiesChanged();
    //包含的属性发生变化
    void dataDecoratorsChanged();

protected:
    //添加包含的信信息体
    Entity* addChild(Entity* entity, const QString& key);
    //添加包含的信息实体列表
    EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);
    // 基本类型列表
    DataDecoratorCollectionBase* addChildCollection(DataDecoratorCollectionBase* dataCollection);
    //添加子属性
    DataDecorator* addDataItem(DataDecorator* dataDecorator);

protected:
    EntityPrivate *m_d;
};

#endif // ENTITY_H
