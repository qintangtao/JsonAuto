#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include "CollectionObject.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

class Entity;

//数据信息集合的基类
class EntityCollectionBase : public CollectionObject
{
public:
    EntityCollectionBase(QObject* parent = nullptr, const QString& key = "SomeCollectionKey")
        : CollectionObject(parent)
        , m_key(key)
    {}

    virtual ~EntityCollectionBase()
    {}

    inline QString key() const
    { return m_key; }

    virtual void clear() = 0;
    virtual void update(const QJsonArray& json) = 0;
    virtual std::vector<Entity*> baseDatas() = 0;

    template <class T>
    const QList<T*>& datas() const;

    template <class T>
    T* addData(T* data);

    template <class T>
    void removeData(T* data);

private:
    QString m_key;
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
          for(auto data : m_collection) {
              data->deleteLater();
          }
          m_collection.clear();
      }
      //更新列表
      void update(const QJsonArray& jsonArray) override
      {
          clear();
          for(const QJsonValue& jsonValue : jsonArray) {
              addData(new T(this, jsonValue.toObject()));
          }
      }

      //获取列表
      std::vector<Entity*> baseDatas() override
      {
          std::vector<Entity*> returnValue;
          for(T* data : m_collection) {
              returnValue.push_back(data);
          }
          return returnValue;
      }

      //获取列表的引用
      const QList<T*>& datas() const
      {
          return m_collection;
      }

      //添加新的信息实体
      T* addData(T* data)
      {
          if(!m_collection.contains(data)) {
              m_collection.append(data);
              CollectionObject:: collectionChanged();
          }
          return data;
      }

      void removeData(T* data)
      {
          if(m_collection.contains(data)) {
              m_collection.removeOne(data);
          }
      }

private:
    QList<T*> m_collection;
};

template <class T>
const QList<T*>& EntityCollectionBase::datas() const
{
    return dynamic_cast<const EntityCollection<T>&>(*this).datas();
}

template <class T>
T* EntityCollectionBase::addData(T* data)
{
    return dynamic_cast<const EntityCollection<T>&>(*this).addData(data);
}

template <class T>
void EntityCollectionBase::removeData(T* data)
{
    return dynamic_cast<const EntityCollection<T>&>(*this).removeData(data);
}

#endif // ENTITYCOLLECTION_H
