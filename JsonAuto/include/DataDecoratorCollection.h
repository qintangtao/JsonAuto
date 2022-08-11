#ifndef DECORATORCOLLECTION_H
#define DECORATORCOLLECTION_H

#include "CollectionObject.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

class DataDecorator;

//数据信息集合的基类
class DataDecoratorCollectionBase : public CollectionObject
{
public:
    DataDecoratorCollectionBase(QObject* parent = nullptr, const QString& key = "SomeCollectionKey")
        : CollectionObject(parent)
        , m_key(key)
    {}

    virtual ~DataDecoratorCollectionBase()
    {}

    inline QString key() const
    { return m_key; }

    virtual void clear() = 0;
    virtual void update(const QJsonArray& json) = 0;
    virtual std::vector<DataDecorator*> baseDatas() = 0;

    template <class T>
    const QList<T*>& datas() const;

    template <class T>
    T* addData(T* decorator);

    template <class T>
    void removeData(T* decorator);

private:
    QString m_key;
};

//数据信息基类
template <typename T>
class DataDecoratorCollection : public DataDecoratorCollectionBase
{
public:
    DataDecoratorCollection(QObject* parent = nullptr, const QString& key = "SomeCollectionKey")
        : DataDecoratorCollectionBase(parent, key)
    {}

    ~DataDecoratorCollection()
    {
        clear();
    }

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
              T *data = new T(NULL, "", "");
              data->update(jsonValue);
              addData(data);
          }
      }

      //获取列表
      std::vector<DataDecorator*> baseDatas() override
      {
          std::vector<DataDecorator*> returnValue;
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
              CollectionObject::collectionChanged();
          }
          return data;
      }

      void removeData(T* decorator)
      {
          if(m_collection.contains(decorator)) {
              m_collection.removeOne(decorator);
          }
      }

private:
    QList<T*> m_collection;
};


template <class T>
const QList<T*>& DataDecoratorCollectionBase::datas() const
{
    return dynamic_cast<const DataDecoratorCollection<T>&>(*this).datas();
}

template <class T>
T* DataDecoratorCollectionBase::addData(T* data)
{
    return dynamic_cast<const DataDecoratorCollection<T>&>(*this).addData(data);
}

template <class T>
void DataDecoratorCollectionBase::removeData(T* data)
{
    return dynamic_cast<const DataDecoratorCollection<T>&>(*this).removeData(data);
}

#endif // DECORATORCOLLECTION_H
