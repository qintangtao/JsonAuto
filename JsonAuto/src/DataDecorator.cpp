#include "DataDecorator.h"
#include <QtGlobal>

class DataDecorator::Implementation
{
public:
    Implementation(Entity* _parent, const QString& _key, const QString& _label)
        : parentEntity(_parent)
        , key(_key)
        , label(_label)
    {
    }

    Entity* parentEntity{nullptr};
    QString key;
    QString label;
};

DataDecorator::DataDecorator(Entity*parent, const QString& key, const QString& label) : QObject((QObject*)parent)
{
        m_implementation.reset(new Implementation(parent, key, label));
}

const QString& DataDecorator::key() const
{
    return m_implementation->key;
}

const QString& DataDecorator::label() const
{
    return m_implementation->label;
}

Entity* DataDecorator::parentEntity()
{
    return m_implementation->parentEntity;
}
