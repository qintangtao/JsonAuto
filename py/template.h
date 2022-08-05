#ifndef ${DEFHEADER}_H
#define ${DEFHEADER}_H

#include "Entity.h"

${INCLUDEENTITY}

class ${CLASSNAME} : public Entity
{
    Q_OBJECT
public:
    explicit ${CLASSNAME}(QObject* parent = nullptr);
    ${CLASSNAME}(QObject* parent, const QJsonObject& json);

    ${METHOD}

    QString toString() const;

private:
    ${PROPERTY}
};

#endif // ${DEFHEADER}_H
