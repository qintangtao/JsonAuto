#ifndef DATETIMEDECORATOR_H
#define DATETIMEDECORATOR_H

#include <QDateTime>
#include "DataDecorator.h"

class DateTimeDecorator : public DataDecorator
{
     Q_OBJECT
    //QML中访问各种日期的格式
    Q_PROPERTY( QString ui_iso8601String READ toIso8601String NOTIFY valueChanged )
    Q_PROPERTY( QString ui_prettyDateString READ toPrettyDateString NOTIFY valueChanged )
    Q_PROPERTY( QString ui_prettyTimeString READ toPrettyTimeString NOTIFY valueChanged )
    Q_PROPERTY( QString ui_prettyString READ toPrettyString NOTIFY valueChanged )
    Q_PROPERTY( QDateTime ui_value READ value WRITE setValue NOTIFY valueChanged )
public:
    DateTimeDecorator(Entity* parentEntity, const QString& key, const QString& label = "", const QDateTime& value = QDateTime());

    const QDateTime& value() const;
    DateTimeDecorator& setValue(const QDateTime& value);

    //获取各种显示格式
    QString toIso8601String() const;
    QString toPrettyDateString() const;
    QString toPrettyTimeString() const;
    QString toPrettyString() const;

    QJsonValue jsonValue() const override;
    void update(const QJsonObject& jsonObject) override;
    void update(const QJsonValue& jsonValue) override;

signals:
    void valueChanged();

private:
    class Implementation;
    QScopedPointer<Implementation, QScopedPointerDeleter2<Implementation>> m_implementation;
};

#endif // DATETIMEDECORATOR_H
