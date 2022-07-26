#ifndef DOUBLEDECORATOR_H
#define DOUBLEDECORATOR_H

#include "DataDecorator.h"

class DoubleDecoratorPrivate;

class JSONAUTOSHARED_EXPORT DoubleDecorator : public DataDecorator
{
    Q_OBJECT
    // QML访问的接口
    Q_PROPERTY( double ui_value READ value WRITE setValue NOTIFY valueChanged )
public:
    explicit DoubleDecorator(Entity* parentEntity, const QString& key, const QString& label = "", double value = 0.0f);
    ~DoubleDecorator();

    //修改和获取字符串封装类型中的原始数据
    DoubleDecorator& setValue(double value);
    double value() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;
    void update(const QJsonValue& jsonValue) override;

signals:
    //数据发生变化的时候发送的信号
    void valueChanged();

private:
    DoubleDecoratorPrivate *m_d;
};

#endif // DOUBLEDECORATOR_H
