#include "DataDecorator.h"
#include <QtGlobal>

class DataDecoratorPrivate
{
public:
    DataDecoratorPrivate(Entity* _parent, const QString& _key, const QString& _label)
        : parentEntity(_parent)
        , key(_key)
        , label(_label)
    {
    }

    Entity* parentEntity{nullptr};
    QString key;
    QString label;
};

DataDecorator::DataDecorator(Entity*parent, const QString& key, const QString& label)
    : QObject((QObject*)parent)
    , m_d(new DataDecoratorPrivate(parent, key, label))
{
}

DataDecorator::~DataDecorator()
{
    if (m_d)
        delete m_d;
}

const QString& DataDecorator::key() const
{
    return m_d->key;
}

const QString& DataDecorator::label() const
{
    return m_d->label;
}

Entity* DataDecorator::parentEntity()
{
    return m_d->parentEntity;
}
