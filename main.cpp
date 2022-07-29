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
    QString json = "{\"date\":\"2022-07-26T21:50:49\",\
                              \"distance\":128.5,\
                              \"valide\":true, \
                             \"age\":23, \
                             \"name\":\"小明\", \
                            \"orders\":[2,4,1,8,5,9,6],\
                             \"address\":[\
                                    {\"building\":\"5号楼\",\
                                    \"city\":\"西河市\",\
                                    \"postcode\":\"56789\",\
                                    \"street\":\"细节街道\"}\
                            ],\
                            \"defaultAddress\":{ \
                                    \"building\":\"6号楼\",\
                                    \"city\":\"北京市\",\
                                    \"postcode\":\"56788\",\
                                    \"street\":\"光明街道\"}\
                        }";
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
    qDebug() << customer->defaultAddr()->toString() ;

    qDebug() << "=========address=========";
    const QList<Address*>& lstAddress = customer->addresses()->datas();
    for(Address* address: lstAddress)
    {
        qDebug() << address->toString() ;
    }

    qDebug() << "=========orders=========";
    const QList<IntDecorator*>& lstOrders = customer->orders()->datas();
     foreach(IntDecorator* order, lstOrders)
     {
         qDebug() << order->value();
     }

    //修改数据
    customer->setValide(false);
    customer->setDistance(22.9);
    customer->setDate(QDateTime::currentDateTime());
    customer->setName("小明");
    customer->setAge(23);

#if 1
    customer->defaultAddr()->setCity("北京市");
    customer->defaultAddr()->setStreet("光明街道");
    customer->defaultAddr()->setBuilding("6号楼");
    customer->defaultAddr()->setPostcode("56788");
#else
    customer->defaultAddr->city->setValue("北京市");
    customer->defaultAddr->street->setValue("光明街道");
    customer->defaultAddr->building->setValue("6号楼");
    customer->defaultAddr->postcode->setValue("56788");
#endif

    //添加新地址
    Address* new_addr = new Address();
#if 1
    new_addr->setCity("北京市");
    new_addr->setStreet("光明街道");
    new_addr->setBuilding("6号楼");
    new_addr->setPostcode("56788");
#else
    new_addr->city->setValue("西河市");
    new_addr->street->setValue("细节街道");
    new_addr->building->setValue("6号楼");
    new_addr->postcode->setValue("56789");
#endif
    customer->addresses()->addData(new_addr);

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

    delete customer;

    return a.exec();
}
