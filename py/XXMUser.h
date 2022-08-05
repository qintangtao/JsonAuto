#ifndef XXMUSER_H
#define XXMUSER_H

#include "Entity.h"

#include "XXMAddress.h"
#include "XXMAddress.h"


class XXMUser : public Entity
{
    Q_OBJECT
public:
    explicit XXMUser(QObject* parent = nullptr);
    XXMUser(QObject* parent, const QJsonObject& json);

    INTGDECORATOR_METHOD(m_id,setId,id)
	INTGDECORATOR_METHOD(m_age,setAge,age)
	STRINGDECORATOR_METHOD(m_name,setName,name)
	BOOLGDECORATOR_METHOD(m_big_size,setBigSize,big_size)
	
	inline XXMAddress *defaultAddres() const
	{ return m_defaultAddres; }
	
	inline EntityCollection<XXMAddress> *address() const
	{ return m_address; }
	
	inline DataDecoratorCollection<IntDecorator> *sizes() const
	{ return m_sizes; }
	

    QString toString() const;

private:
    IntDecorator *m_id;
	IntDecorator *m_age;
	StringDecorator *m_name;
	BoolDecorator *m_big_size;
	XXMAddress *m_defaultAddres;
	EntityCollection<XXMAddress> *m_address;
	DataDecoratorCollection<IntDecorator> *m_sizes;
	
};

#endif // XXMUSER_H
