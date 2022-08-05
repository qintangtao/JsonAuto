#ifndef _H
#define _H

#include "Entity.h"

class  : public Entity
{
    Q_OBJECT
public:
    explicit (QObject* parent = nullptr);
    (QObject* parent, const QJsonObject& json);

    

    QString toString() const;

private:
    
};

#endif // _H
