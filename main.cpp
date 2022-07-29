#include <QCoreApplication>
#include <QTextCodec>
#include <QJsonDocument>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "Entity.h"
#include "Address.h"
#include "Customer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //将json结构转换成一个数据类
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
    Customer* customer = JsontoEntity<Customer>(json);
    if (customer == NULL)
        return 0;

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

    customer->defaultAddr()->setCity("北京市");
    customer->defaultAddr()->setStreet("光明街道");
    customer->defaultAddr()->setBuilding("6号楼");
    customer->defaultAddr()->setPostcode("56788");

    //添加新地址
    Address* new_addr = new Address();
    new_addr->setCity("北京市");
    new_addr->setStreet("光明街道");
    new_addr->setBuilding("6号楼");
    new_addr->setPostcode("56788");
    customer->addresses()->addData(new_addr);

    //将数据类型转换成json数据结构
   QString json2= EntitytoJson(customer);
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
