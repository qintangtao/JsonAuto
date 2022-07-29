#ifndef BOOLDECORATOR_H
#define BOOLDECORATOR_H

#include "DataDecorator.h"

class BoolDecoratorPrivate;

class JSONAUTOSHARED_EXPORT BoolDecorator : public DataDecorator
{
    Q_OBJECT
    // QML访问的接口
    Q_PROPERTY( bool ui_value READ value WRITE setValue NOTIFY valueChanged )
public:
    explicit BoolDecorator(Entity* parentEntity, const QString& key, const QString& label = "", bool value = false);
    ~BoolDecorator();

    //修改和获取字符串封装类型中的原始数据
    BoolDecorator& setValue(bool value);
    bool value() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;
    void update(const QJsonValue& jsonValue) override;

signals:
    //数据发生变化的时候发送的信号
    void valueChanged();

private:
    BoolDecoratorPrivate *m_d;
};

#endif // BOOLDECORATOR_H
