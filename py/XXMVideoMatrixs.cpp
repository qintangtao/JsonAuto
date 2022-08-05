#include "XXMVideoMatrixs.h"

XXMVideoMatrixs::XXMVideoMatrixs(QObject* parent)
    : Entity(parent, "XXMVideoMatrixs")
{
    ADD_CHILD_ENTITYCOLLECTION(XXMVideoMatrix, "vmxs")
	
}

XXMVideoMatrixs::XXMVideoMatrixs(QObject* parent, const QJsonObject& json)
    : XXMVideoMatrixs(parent)
{
    update(json);
}


QString XXMVideoMatrixs::toString() const
{
    return QString();
}