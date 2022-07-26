#include <QCoreApplication>
#include <QTextCodec>
#include <QJsonDocument>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "Address.h"
#include "Customer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //将json结构转换成一个数据类
#if  1
    QString json = "{\"date\":\"2022-07-26T21:50:49\", \"distance\":128.5,\"valide\":true, \"address\":[{\"building\":\"6号楼\",\"city\":\"西河市\",\"postcode\":\"56789\",\"street\":\"细节街道\"}],\"age\":23,\"defaultAddress\":{\"building\":\"6号楼\",\"city\":\"北京市\",\"postcode\":\"56788\",\"street\":\"光明街道\"},\"name\":\"小明\"}";
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(json.toLocal8Bit(), &json_error);
    if(json_error.error != QJsonParseError::NoError) {
        qDebug() << json_error.errorString();
        return 0;
    }

    if( !parse_doucment.isObject() )
        return 0;

    QJsonObject customer_json = parse_doucment.object();
#else
    QJsonObject customer_json;
#endif
    Customer* customer = new Customer(NULL, customer_json);

    qDebug() << customer->toString() ;
    qDebug() << customer->defaultAddr->toString() ;
    QList<Address*>& lstAddress = customer->addresses->derivedEntities();
    foreach(Address* address, lstAddress)
    {
        qDebug() << customer->defaultAddr->toString() ;
    }

    //修改数据
    customer->valide->setValue(false);
    customer->distance->setValue(22.9);
    customer->date->setValue(QDateTime::currentDateTime());
    customer->name->setValue("小明");
    customer->age->setValue(23);
    customer->defaultAddr->city->setValue("北京市");
    customer->defaultAddr->street->setValue("光明街道");
    customer->defaultAddr->building->setValue("6号楼");
    customer->defaultAddr->postcode->setValue("56788");

    //添加新地址
    Address* new_addr = new Address();
    new_addr->city->setValue("西河市");
    new_addr->street->setValue("细节街道");
    new_addr->building->setValue("6号楼");
    new_addr->postcode->setValue("56789");
    customer->addresses->addEntity(new_addr);

    //将数据类型转换成json数据结构
    QJsonObject json_object = customer->toJson();

    QJsonDocument document;
    document.setObject(json_object);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);

   QString json2= QString::fromLocal8Bit( byte_array );

   qDebug() << json2 ;

   {
       QFile file( "JsonAuto.txt" );
       QTextStream stream( &file);
       if ( file.open(QFile::ReadWrite) ) {
           stream << json2;
           file.close();
       }
   }
    return a.exec();
}
