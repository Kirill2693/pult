#include "rovorient.h"
#include <QDebug>

RovOrient::RovOrient(QObject *parent) : QObject(parent)
{

SetMove.Depth =0;
SetMove.DepthSpeed = 0;
SetMove.MarchSpeed = 0;
SetMove.Roll = 0;
SetMove.RollSpeed = 0;
SetMove.Yaw = 0;
SetMove.YawSpeed = 0;

}

void RovOrient::SetRollSpeed(int dir)
{
    if(dir == FORWARD_DIR)
    {
        SetMove.RollSpeed = 10;
    }
    else if(dir == REVERS_DIR)
    {
         SetMove.RollSpeed = -10;
    }

    SetMove.Roll += SetMove.RollSpeed;
    if(SetMove.Roll > 60)
    {
        SetMove.Roll = 60;
    }
    if(SetMove.Roll < -60)
    {
        SetMove.Roll = -60;
    }
    emit UpdateSetWG(SetMove);
}

void RovOrient::SetYawSpeed(int dir)
{
    if(dir == FORWARD_DIR)
    {
        SetMove.YawSpeed = 10;
    }
    else if(dir == REVERS_DIR)
    {
         SetMove.YawSpeed = -10;
    }

    SetMove.Yaw += SetMove.YawSpeed;
    if(SetMove.Yaw > 360)
    {
        SetMove.Yaw = SetMove.Yaw-360;
    }
    if(SetMove.Yaw < 0)
    {
        SetMove.Yaw =SetMove.Yaw+360 ;
    }

    emit UpdateSetWG(SetMove);
}

void RovOrient::SetDepthSpeed(int dir)
{
    if(dir == FORWARD_DIR)
    {
        SetMove.DepthSpeed = 10;
    }
    else if(dir == REVERS_DIR)
    {
         SetMove.DepthSpeed = -10;
    }

    SetMove.Depth += SetMove.DepthSpeed;
    if(SetMove.Depth<0)
    {
        SetMove.Depth = 0;
    }
    if(SetMove.Depth>100)
    {
        SetMove.Depth = 100;
    }
    emit UpdateSetWG(SetMove);
}

void RovOrient::SetMarchSpeed(int dir)
{
    if(dir == FORWARD_DIR)
    {
        SetMove.MarchSpeed = 10;
    }
    else if(dir == REVERS_DIR)
    {
         SetMove.MarchSpeed = -10;
    }
    emit UpdateSetWG(SetMove);
}
