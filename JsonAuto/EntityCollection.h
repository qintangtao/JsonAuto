#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include <QObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

class Entity;

//基类声明集合变化的信号
class EntityCollectionObject : public QObject
{
    Q_OBJECT

public:
    EntityCollectionObject(QObject* _parent = nullptr) : QObject(_parent) {}
    virtual ~EntityCollectionObject() {}

signals:
    void collectionChanged();
};

//数据信息集合的基类
class EntityCollectionBase : public EntityCollectionObject
{
public:
    EntityCollectionBase(QObject* parent = nullptr, const QString& key = "SomeCollectionKey")
        : EntityCollectionObject(parent)
        , key(key)
    {}

    virtual ~EntityCollectionBase()
    {}

    inline QString getKey() const
    { return key; }

    virtual void clear() = 0;
    //json数组转成数据实体
    virtual void update(const QJsonArray& json) = 0;
    virtual std::vector<Entity*> baseEntities() = 0;

    template <class T>
    QList<T*>& derivedEntities();

    template <class T>
    T* addEntity(T* entity);

private:
    QString key;
};

//数据信息基类
template <typename T>
class EntityCollection : public EntityCollectionBase
{
public:
    EntityCollection(QObject* parent = nullptr, const QString& key = "SomeCollectionKey")
        : EntityCollectionBase(parent, key)
    {}

    ~EntityCollection()
    {}

    //清空列表
      void clear() override
      {
          for(auto entity : collection) {
              entity->deleteLater();
          }
          collection.clear();
      }
      //更新列表
      void update(const QJsonArray& jsonArray) override
      {
          clear();
          for(const QJsonValue& jsonValue : jsonArray) {
              addEntity(new T(this, jsonValue.toObject()));
          }
      }

      //获取列表
      std::vector<Entity*> baseEntities() override
      {
          std::vector<Entity*> returnValue;
          for(T* entity : collection) {
              returnValue.push_back(entity);
          }
          return returnValue;
      }

      //获取列表的引用
      QList<T*>& derivedEntities()
      {
          return collection;
      }

      //添加新的信息实体
      T* addEntity(T* entity)
      {
          if(!collection.contains(entity)) {
              collection.append(entity);
              EntityCollectionObject::collectionChanged();
          }
          return entity;
      }

private:
    QList<T*> collection;
};

template <class T>
QList<T*>& EntityCollectionBase::derivedEntities()
{
    return dynamic_cast<const EntityCollection<T>&>(*this).derivedEntities();
}

template <class T>
T* EntityCollectionBase::addEntity(T* entity)
{
    return dynamic_cast<const EntityCollection<T>&>(*this).addEntity(entity);
}


#endif // ENTITYCOLLECTION_H
