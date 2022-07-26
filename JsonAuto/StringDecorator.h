#ifndef STRINGDECORATOR_H
#define STRINGDECORATOR_H

#include <QString>
#include "DataDecorator.h"

class StringDecorator : public DataDecorator
{
    Q_OBJECT
    //QML访问的属性
    Q_PROPERTY( QString ui_value READ value WRITE setValue NOTIFY valueChanged )
public:
    StringDecorator(Entity* parentEntity, const QString& key, const QString& label = "", const QString& value = "");

    //修改和获取字符串封装类型中的原始数据
    StringDecorator& setValue(const QString& value);
    const QString& value() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;

signals:
    //数据发生变化的时候发送的信号
    void valueChanged();

private:
    class Implementation;
    QScopedPointer<Implementation, QScopedPointerDeleter2<Implementation>> implementation;
};

#endif // STRINGDECORATOR_H
