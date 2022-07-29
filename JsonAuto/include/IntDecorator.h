#ifndef INTDECORATOR_H
#define INTDECORATOR_H

#include "DataDecorator.h"

class IntDecoratorPrivate;

class JSONAUTOSHARED_EXPORT  IntDecorator : public DataDecorator
{
    Q_OBJECT
    // QML访问的接口
    Q_PROPERTY( int ui_value READ value WRITE setValue NOTIFY valueChanged )
public:
    explicit IntDecorator(Entity* parentEntity, const QString& key, const QString& label = "", int value = 0);
    ~IntDecorator();

    //修改和获取字符串封装类型中的原始数据
    IntDecorator& setValue(int value);
    int value() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;
    void update(const QJsonValue& jsonValue) override;

signals:
    //数据发生变化的时候发送的信号
    void valueChanged();

private:
    IntDecoratorPrivate *m_d;
};

#endif // INTDECORATOR_H
