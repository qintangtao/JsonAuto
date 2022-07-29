#ifndef COLLECTIONOBJECT_H
#define COLLECTIONOBJECT_H

#include <QObject>

//基类声明集合变化的信号
class CollectionObject : public QObject
{
    Q_OBJECT

public:
    CollectionObject(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~CollectionObject() {}

signals:
    void collectionChanged();
};

#endif // COLLECTIONOBJECT_H
