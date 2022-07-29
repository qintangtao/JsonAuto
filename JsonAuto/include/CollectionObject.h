#ifndef COLLECTIONOBJECT_H
#define COLLECTIONOBJECT_H

#include <QObject>
#include "JsonAuto.h"

//基类声明集合变化的信号
class JSONAUTOSHARED_EXPORT CollectionObject : public QObject
{
    Q_OBJECT

public:
    CollectionObject(QObject* parent = nullptr) ;
    virtual ~CollectionObject();

signals:
    void collectionChanged();
};

#endif // COLLECTIONOBJECT_H
