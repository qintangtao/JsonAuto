#ifndef ENUMERATORDECORATOR_H
#define ENUMERATORDECORATOR_H

#include <map>
#include "DataDecorator.h"

class EnumeratorDecorator : public DataDecorator
{
     Q_OBJECT
    //枚举属性值
    Q_PROPERTY( int ui_value READ value WRITE setValue NOTIFY valueChanged )
    //枚举属性对应的字符串描述
    Q_PROPERTY( QString ui_valueDescription READ valueDescription NOTIFY valueChanged )

public:
    EnumeratorDecorator(Entity* parentEntity, const QString& key, const QString& label = "", int value = 0, const std::map<int, QString>& descriptionMapper = std::map<int, QString>());

    //获取属性对应的值和描述
    EnumeratorDecorator& setValue(int value);
    int value() const;
    QString valueDescription() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;

signals:
    void valueChanged();

private:
    class Implementation;
    QScopedPointer<Implementation, QScopedPointerDeleter2<Implementation>> implementation;
};

#endif // ENUMERATORDECORATOR_H
