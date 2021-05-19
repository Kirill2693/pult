#include "rovcontrol.h"
#include <QDebug>


RovControl::RovControl(QObject *parent) : QObject(parent)
{
    K1 = {0,0,0,0};
    K2 = {0,0,0,0};
    KosPos = {0,0,0,0};
    Ksp = {0,0,0,0};

    CurentRovSpeed = {0,0,0,0};
    CurentRovPos = {0,0,0,0};
    SetRovSpeed = {0,0,0,0};
    SetRovPos = {0,0,0,0};

    WorkMode = {DirectMode,DirectMode,DirectMode,DirectMode};
    timer = new QTimer();
    timer->start(Ts);
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

/*void RovControl::BfsDrk(const ContourSignals &OutContour)
{
    DrkSignals.Uvr = OutContour.Depth+OutContour.Roll;
    DrkSignals.Uvl = OutContour.Depth-OutContour.Roll;
    DrkSignals.Uhrf = OutContour.March+OutContour.Yaw;
    DrkSignals.Uhrb = OutContour.March+OutContour.Yaw;
    DrkSignals.Uhlf = OutContour.March-OutContour.Yaw;
    DrkSignals.Uhlb = OutContour.March-OutContour.Yaw;
}*/

void RovControl::BfsDrk(const QVector<double> &OutContour)
{
     DrkSignals.Uvr = OutContour[Depth]+OutContour[Roll];   //вертикальный правый
     DrkSignals.Uvr = Saturation( DrkSignals.Uvr, ThrusterUp, ThrusterDown);
     DrkSignals.Uvl = Saturation(OutContour[Depth]-OutContour[Roll],ThrusterUp,ThrusterDown);   //вертикальный левый
     DrkSignals.Uhrf = Saturation(OutContour[March]+OutContour[Yaw],ThrusterUp,ThrusterDown);   // горизонтальный правый передний
     DrkSignals.Uhrb = Saturation(OutContour[March]+OutContour[Yaw],ThrusterUp,ThrusterDown);   // горизонтальный правый задний
     DrkSignals.Uhlf = Saturation(OutContour[March]-OutContour[Yaw],ThrusterUp,ThrusterDown);   // горизонтальный левый передний
     DrkSignals.Uhlb = Saturation(OutContour[March]-OutContour[Yaw],ThrusterUp,ThrusterDown);   // горизонтальный левый задний

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

double RovControl::CalcContour(const int Contour)
{
    double out=0;
    double  PosError, PosSignal, SpeedError;
    if((WorkMode[Contour] == StabMode)||(WorkMode[Contour] == SettingsMode))      // режим настройки или стабилизации
    {
    PosError =  SetRovPos[Contour]-CurentRovPos[Contour]*KosPos[Contour]; //ошибка по позиции
    PosSignal =  PosError*K1[Contour];  //усиленная ошибка
    SpeedError = PosSignal - CurentRovSpeed[Contour]*K2[Contour];  // ошибка в контуре скорости
    out = SpeedError + SetRovSpeed[Contour] * Ksp[Contour];  // суммируем ошибку в контуре скорости с заданной скоростью
    }
    if(WorkMode[Contour] == DirectMode)  // режим ручного управления
    {
        out = SetRovSpeed[Contour];   // выходное значение равно скорости
    }
    return out;
}

double RovControl::Saturation(const double In,const double Up, const double Down)
{
    double out = In;
    if (In <= Down)
    {
        out = Down;
    }
    if(In >= Up)
    {
        out = Up;
    }
    return out;
}

void RovControl::SetK1(const int Contour, double value)
{
    K1[Contour]= value;
}

void RovControl::SetK2(const int Contour, double value)
{
    K2[Contour] = value;
}

void RovControl::SetKosPos(const int Contour, double value)
{
    KosPos[Contour] = value;
}

void RovControl::SetKsp(const int Contour, double value)
{
    Ksp[Contour] = value;
}

QVector<double>& RovControl::GetK1()
{
    return K1;
}

QVector<double>& RovControl::GetK2()
{
    return  K2;
}
QVector<double>& RovControl::GetKosPos()
{
    return KosPos;
}
QVector<double>& RovControl::GetKsp()
{
    return Ksp;
}

void RovControl::SetMode(const int Contour, int Value)
{
    WorkMode[Contour] = Value;
}

void RovControl::IntegrRovSpeed()
{
    CurentRovPos[Yaw]+=CurentRovSpeed[Yaw]*(Ts/1000.0);  // интегрируем угловую скорость, переводим мс в с
    if(CurentRovPos[Yaw]>360)
    {
        CurentRovPos[Yaw]-=360;
    }
    if(CurentRovPos[Yaw]<0)
    {
        CurentRovPos[Yaw]+=360;
    }

    CurentRovPos[Roll]+=CurentRovSpeed[Roll]*(Ts/1000.0);
    if(CurentRovPos[Roll]>60)
    {
       CurentRovPos[Roll] = 60;
    }
    if(CurentRovPos[Roll]<-60)
    {
       CurentRovPos[Roll] = -60;
    }
}
