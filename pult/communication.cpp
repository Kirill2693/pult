#include "communication.h"
#include <QDebug>

Communication::Communication(QObject *parent) : QObject(parent)
{
    m_socket = new QUdpSocket(this);
    m_resiveSocket = new QUdpSocket(this);

    qDebug()<<m_socket->bind(QHostAddress::LocalHost,13041);
    qDebug()<<m_socket->errorString();

    qDebug()<<m_resiveSocket->bind(QHostAddress::LocalHost,13044);
    qDebug()<<m_resiveSocket->errorString();

    connect(m_resiveSocket,SIGNAL(readyRead()),this,SLOT(resivData()));
}

void Communication::send(DRK sendData)
{
    qDebug()<<"Uhlb"<<sendData.Uhlb;
    qDebug()<<"Uhlf"<<sendData.Uhlf;
    qDebug()<<"Uhrb"<<sendData.Uhrb;
    qDebug()<<"Uhrf"<<sendData.Uhrf;
    qDebug()<<"Uvl"<<sendData.Uvl;
    qDebug()<<"Uvr"<<sendData.Uvr;
    qDebug()<<m_socket->writeDatagram((char*)&sendData,sizeof(sendData),QHostAddress::LocalHost,13042);
}

void Communication::resivData()
{
    while(m_resiveSocket->hasPendingDatagrams())
    {
        m_resiveSocket->readDatagram((char*)&ResiveData,sizeof(ResiveData));
        qDebug()<<"Resive Yaw"<<ResiveData.Yaw;
        qDebug()<<"Resive YawSpeed"<<ResiveData.YawSpeed;
    }
}

/*void Communication::ProcessingRawData()
{
    if(ResiveData.Yaw > 360)
    {
        ResiveData.Yaw = ResiveData.Yaw-360;
    }
    if(ResiveData.Yaw < 0)
    {
        ResiveData.Yaw =ResiveData.Yaw+360 ;
    }

    if(ResiveData.Depth<0)
    {
        ResiveData.Depth = 0;
    }
    if(ResiveData.Depth>100)
    {
        ResiveData.Depth = 100;
    }

    if(ResiveData.Roll > 60)
    {
        ResiveData.Roll = 60;
    }
    if(ResiveData.Roll < -60)
    {
        ResiveData.Roll = -60;
    }
}
*/
