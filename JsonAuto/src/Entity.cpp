#include "Entity.h"
#include <map>
#include <QJsonDocument>
#include <QJsonArray>



QString EntitytoJson(Entity *entity)
{
    QJsonDocument document;
    QJsonObject jsonobject;

    jsonobject = entity->toJson();
    document.setObject(jsonobject);

    return QString::fromLocal8Bit( document.toJson(QJsonDocument::Compact) );
}

class Entity::Implementation
{
public:
    Implementation(Entity* _entity, const QString& _key)
        : entity(_entity)
        , key(_key)
    {
    }
    Entity* entity{nullptr};
    QString key;
    std::map<QString, EntityCollectionBase*> childEntityCollections;
    std::map<QString, DataDecoratorCollectionBase*> childDecoratorCollections;
    std::map<QString, Entity*> childEntities;
    std::map<QString, DataDecorator*> dataDecorators;
};

Entity::Entity(QObject* parent, const QString& key)
    : QObject(parent)
{
    m_implementation.reset(new Implementation(this, key));
}

Entity::Entity(QObject* parent, const QString& key, const QJsonObject& jsonObject)
    : Entity(parent, key)
{
    update(jsonObject);
}

Entity::~Entity()
{
}
const QString& Entity::key() const
{
    return m_implementation->key;
}

Entity* Entity::addChild(Entity* entity, const QString& key)
{
    if(m_implementation->childEntities.find(key) == std::end(m_implementation->childEntities)) {
        m_implementation->childEntities[key] = entity;
        emit childEntitiesChanged();
    }

    return entity;
}

EntityCollectionBase* Entity::addChildCollection(EntityCollectionBase* entityCollection)
{
    if(m_implementation->childEntityCollections.find(entityCollection->key()) == std::end(m_implementation->childEntityCollections)) {
        m_implementation->childEntityCollections[entityCollection->key()] = entityCollection;
        emit childCollectionsChanged(entityCollection->key());
    }

    return entityCollection;
}

DataDecoratorCollectionBase* Entity::addChildCollection(DataDecoratorCollectionBase* decoratorCollection)
{
    if(m_implementation->childDecoratorCollections.find(decoratorCollection->key()) == std::end(m_implementation->childDecoratorCollections)) {
        m_implementation->childDecoratorCollections[decoratorCollection->key()] = decoratorCollection;
        emit childDecoratorCollectionsChanged(decoratorCollection->key());
    }

    return decoratorCollection;
}

DataDecorator* Entity::addDataItem(DataDecorator* dataDecorator)
{
    if(m_implementation->dataDecorators.find(dataDecorator->key()) == std::end(m_implementation->dataDecorators)) {
        m_implementation->dataDecorators[dataDecorator->key()] = dataDecorator;
        emit dataDecoratorsChanged();
    }
    return dataDecorator;
}

void Entity::update(const QJsonObject& jsonObject)
{
    // Update data decorators
    for (std::pair<QString, DataDecorator*> dataDecoratorPair : m_implementation->dataDecorators) {
        dataDecoratorPair.second->update(jsonObject);
    }

    // Update child entities
    for (std::pair<QString, Entity*> childEntityPair : m_implementation->childEntities) {
        childEntityPair.second->update(jsonObject.value(childEntityPair.first).toObject());
    }

    // Update child decorator collections
    for (std::pair<QString, DataDecoratorCollectionBase*> childCollectionPair : m_implementation->childDecoratorCollections) {
        childCollectionPair.second->update(jsonObject.value(childCollectionPair.first).toArray());
    }

    // Update child entity collections
    for (std::pair<QString, EntityCollectionBase*> childCollectionPair : m_implementation->childEntityCollections) {
        childCollectionPair.second->update(jsonObject.value(childCollectionPair.first).toArray());
    }
}

QJsonObject Entity::toJson() const
{
    QJsonObject returnValue;

    // Add data decorators
    for (std::pair<QString, DataDecorator*> dataDecoratorPair : m_implementation->dataDecorators) {
        returnValue.insert( dataDecoratorPair.first, dataDecoratorPair.second->jsonValue() );
    }

    // Add child entities
    for (std::pair<QString, Entity*> childEntityPair : m_implementation->childEntities) {
        returnValue.insert( childEntityPair.first, childEntityPair.second->toJson() );
    }

    // Add child decorator collections
    for (std::pair<QString, DataDecoratorCollectionBase*> childCollectionPair : m_implementation->childDecoratorCollections) {
        QJsonArray entityArray;
        for (DataDecorator* decorator : childCollectionPair.second->baseDatas()) {
            entityArray.append( decorator->jsonValue() );
        }
        returnValue.insert( childCollectionPair.first, entityArray );
    }

    // Add child entity collections
    for (std::pair<QString, EntityCollectionBase*> childCollectionPair : m_implementation->childEntityCollections) {
        QJsonArray entityArray;
        for (Entity* entity : childCollectionPair.second->baseDatas()) {
            entityArray.append( entity->toJson() );
        }
        returnValue.insert( childCollectionPair.first, entityArray );
    }

    return returnValue;
}
