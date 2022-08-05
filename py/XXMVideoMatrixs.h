#ifndef XXMVIDEOMATRIXS_H
#define XXMVIDEOMATRIXS_H

#include "Entity.h"

#include "XXMVideoMatrix.h"


class XXMVideoMatrixs : public Entity
{
    Q_OBJECT
public:
    explicit XXMVideoMatrixs(QObject* parent = nullptr);
    XXMVideoMatrixs(QObject* parent, const QJsonObject& json);

    
	inline EntityCollection<XXMVideoMatrix> *vmxs() const
	{ return m_vmxs; }
	

    QString toString() const;

private:
    EntityCollection<XXMVideoMatrix> *m_vmxs;
	
};

#endif // XXMVIDEOMATRIXS_H
