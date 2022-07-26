#ifndef BOOLDECORATOR_H
#define BOOLDECORATOR_H

#include "DataDecorator.h"

class BoolDecorator : public DataDecorator
{
    Q_OBJECT
    // QML访问的接口
    Q_PROPERTY( bool ui_value READ value WRITE setValue NOTIFY valueChanged )
public:
    BoolDecorator(Entity* parentEntity, const QString& key, const QString& label = "", bool value = false);

    //修改和获取字符串封装类型中的原始数据
    BoolDecorator& setValue(bool value);
    bool value() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;

signals:
    //数据发生变化的时候发送的信号
    void valueChanged();

private:
    class Implementation;
    QScopedPointer<Implementation, QScopedPointerDeleter2<Implementation>> implementation;
};

#endif // BOOLDECORATOR_H
