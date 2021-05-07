#include "rovcontrol.h"
#include <QDebug>


RovControl::RovControl(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    timer->start(5000);
    udp = new Communication();
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
    ResetSetSpeed();
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

void RovControl::BfsDrk(const ContourSignals &OutContour)
{
    DrkSignals.Uvr = static_cast<int>(OutContour.Depth+OutContour.Roll);
    DrkSignals.Uvl = static_cast<int>(OutContour.Depth-OutContour.Roll);
    DrkSignals.Uhrf = static_cast<int>(OutContour.March+OutContour.Yaw);
    DrkSignals.Uhrb = static_cast<int>(OutContour.March+OutContour.Yaw);
    DrkSignals.Uhlf = static_cast<int>(OutContour.March-OutContour.Yaw);
    DrkSignals.Uhlb = static_cast<int>(OutContour.March-OutContour.Yaw);
}

void RovControl::DirectControl()
{
   SpeedError.Depth = SetRovOrient.DepthSpeed;
   SpeedError.Yaw = SetRovOrient.YawSpeed;
   SpeedError.March = SetRovOrient.MarchSpeed;
   SpeedError.Roll = SetRovOrient.RollSpeed;

}

void RovControl::ResetSetSpeed()
{
    SetRovOrient.YawSpeed=0;
    SetRovOrient.MarchSpeed =0;
    SetRovOrient.RollSpeed = 0;
}
