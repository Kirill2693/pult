#ifndef DATATYPES_H
#define DATATYPES_H
struct DRK
{
    DRK() {Uvl = 0; Uvr = 0; Uvr = 0; Uhlf = 0; Uhrf = 0; Uhlb = 0; Uhrb = 0;}
    int Uvl;
    int Uvr;
    int Uhlf;
    int Uhrf;
    int Uhlb;
    int Uhrb;
};

struct ContourSignals
{
    ContourSignals() {Yaw = 0; Roll = 0; Depth = 0; March=0;}
    double Yaw;
    double Roll;
    double Depth;
    double March;
};

struct MoveParm
{
    MoveParm() {Yaw =0; YawSpeed = 0; Roll = 0; RollSpeed = 0; Depth = 0; DepthSpeed = 0; MarchSpeed = 0;}
    double Yaw;
    double YawSpeed;
    double Roll;
    double RollSpeed;
    double Depth;
    double DepthSpeed;
    double MarchSpeed;
};

#endif // DATATYPES_H
