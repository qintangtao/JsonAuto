#ifndef XXMADDRESS_H
#define XXMADDRESS_H

#include "Entity.h"



class XXMAddress : public Entity
{
    Q_OBJECT
public:
    explicit XXMAddress(QObject* parent = nullptr);
    XXMAddress(QObject* parent, const QJsonObject& json);

    INTGDECORATOR_METHOD(m_id,setId,id)
	INTGDECORATOR_METHOD(m_age,setAge,age)
	STRINGDECORATOR_METHOD(m_name,setName,name)
	BOOLGDECORATOR_METHOD(m_big_size,setBigSize,big_size)
	

    QString toString() const;

private:
    IntDecorator *m_id;
	IntDecorator *m_age;
	StringDecorator *m_name;
	BoolDecorator *m_big_size;
	
};

#endif // XXMADDRESS_H
