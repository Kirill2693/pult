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
/*
void RovOrient::CalcRoll(int dir)
{
    if(dir == FORWARD_DIR)
    {
        SetMove.Roll += SetMove.RollSpeed;
    }
    else if(dir == REVERS_DIR)
    {
         SetMove.Roll -= SetMove.RollSpeed;
    }
    if(SetMove.Roll > 60)
    {
        SetMove.Roll = 60;
    }
    if(SetMove.Roll < -60)
    {
        SetMove.Roll = -60;
    }
} */
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
    UpdateSetMove();
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
    UpdateSetMove();
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
    UpdateSetMove();
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
    UpdateSetMove();
}

void RovOrient::UpdateSetMove()
{
    SetMove.Yaw += SetMove.YawSpeed;
    SetMove.Roll += SetMove.RollSpeed;
    SetMove.Depth += SetMove.DepthSpeed;

    if(SetMove.Yaw > 360)
    {
        SetMove.Yaw = 0;
    }
    if(SetMove.Yaw < 0)
    {
        SetMove.Yaw = 360;
    }

    if(SetMove.Roll > 60)
    {
        SetMove.Roll = 60;
    }
    if(SetMove.Roll < -60)
    {
        SetMove.Roll = -60;
    }

    if(SetMove.Depth<0)
    {
        SetMove.Depth = 0;
    }
    if(SetMove.Depth>100)
    {
        SetMove.Depth = 100;
    }

    SetMove.YawSpeed = 0;
    SetMove.RollSpeed = 0;
    SetMove.DepthSpeed = 0;
    SetMove.MarchSpeed = 0;

    qDebug()<<"Set Yaw: "<<SetMove.Yaw;
    qDebug()<<"Set Roll: "<<SetMove.Roll;
    qDebug()<<"Set Depth: "<<SetMove.Depth;
    qDebug()<<"Set March Seed: "<<SetMove.MarchSpeed;
}
