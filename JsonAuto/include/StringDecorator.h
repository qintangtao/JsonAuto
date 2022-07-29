#ifndef STRINGDECORATOR_H
#define STRINGDECORATOR_H

#include <QString>
#include "DataDecorator.h"

class StringDecoratorPrivate;

class JSONAUTOSHARED_EXPORT StringDecorator : public DataDecorator
{
    Q_OBJECT
    //QML访问的属性
    Q_PROPERTY( QString ui_value READ value WRITE setValue NOTIFY valueChanged )
public:
    explicit StringDecorator(Entity* parentEntity, const QString& key, const QString& label = "", const QString& value = "");
    ~StringDecorator();

    //修改和获取字符串封装类型中的原始数据
    StringDecorator& setValue(const QString& value);
    const QString& value() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;
    void update(const QJsonValue& jsonValue) override;

signals:
    //数据发生变化的时候发送的信号
    void valueChanged();

private:
    StringDecoratorPrivate *m_d;
};

#endif // STRINGDECORATOR_H
