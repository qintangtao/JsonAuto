#include ".h"

::(QObject* parent)
    : Entity(parent, "")
{
    
}

::(QObject* parent, const QJsonObject& json)
    : (parent)
{
    update(json);
}


QString ::toString() const
{
    return QString();
}