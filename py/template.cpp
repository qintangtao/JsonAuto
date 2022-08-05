#include "${CLASSNAME}.h"

${CLASSNAME}::${CLASSNAME}(QObject* parent)
    : Entity(parent, "${CLASSNAME}")
{
    ${ADDPROPERTY}
}

${CLASSNAME}::${CLASSNAME}(QObject* parent, const QJsonObject& json)
    : ${CLASSNAME}(parent)
{
    update(json);
}


QString ${CLASSNAME}::toString() const
{
    return ${TOSTRING};
}