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

    //Тест
  /*  ResiveData.Depth = 10;
    ResiveData.DepthSpeed = 2;
    ResiveData.MarchSpeed = 1;
    ResiveData.RollSpeed = 0.9;
    ResiveData.YawSpeed = 6;*/
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
        qDebug()<<"Resive YawSpeed"<<ResiveData.YawSpeed;
        qDebug()<<"Resive RollSpeed"<<ResiveData.RollSpeed;
        qDebug()<<"Resive DepthSpeed"<<ResiveData.DepthSpeed;
    }
}


