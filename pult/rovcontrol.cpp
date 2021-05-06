#include "rovcontrol.h"
#include <QDebug>


RovControl::RovControl(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    timer->start(100);
    udp = new Communication();
    RovMov = new RovOrient();
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
}

void RovControl::tick()
{
    //qDebug()<<"Timer tick";
    MoveRov = udp->GetDataFromMatlab();
    emit UpdateRoveWidgents(MoveRov);
    DirectControl();
    BfsDrk();
    udp->send(DrkSignals);
    //RovMov->ResetSpeed();
}

void RovControl::BfsDrk()
{
    DrkSignals.Uvr = static_cast<int>(SpeedError.Depth+SpeedError.Roll);
    DrkSignals.Uvl = static_cast<int>(SpeedError.Depth-SpeedError.Roll);
    DrkSignals.Uhrf = static_cast<int>(SpeedError.March+SpeedError.Yaw);
    DrkSignals.Uhrb = static_cast<int>(SpeedError.March+SpeedError.Yaw);
    DrkSignals.Uhlf = static_cast<int>(SpeedError.March-SpeedError.Yaw);
    DrkSignals.Uhlb = static_cast<int>(SpeedError.March-SpeedError.Yaw);
}

void RovControl::DirectControl()
{
   SpeedError.Depth = RovMov->GetSetMove().DepthSpeed;
   SpeedError.Yaw = RovMov->GetSetMove().YawSpeed;
   SpeedError.March = RovMov->GetSetMove().MarchSpeed;
   SpeedError.Roll = RovMov->GetSetMove().RollSpeed;

}

void RovControl::key(QKeyEvent *ev)
{
    RovMov->KeyGrab(ev);
}
