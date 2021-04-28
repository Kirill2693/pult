#ifndef ROVORIENT_H
#define ROVORIENT_H

#include <QObject>

struct MoveParm
{
    MoveParm() {}
    double Yaw;
    double YawSpeed;
    double Roll;
    double RollSpeed;
    double Depth;
    double DepthSpeed;
    double MarchSpeed;
};

enum Direct
{
   REVERS_DIR,
   FORWARD_DIR
};

class RovOrient : public QObject
{
    Q_OBJECT
public:
    explicit RovOrient(QObject *parent = nullptr);

    void SetRollSpeed(int dir);
    void SetYawSpeed(int dir);
    void SetDepthSpeed(int dir);
    void SetMarchSpeed(int dir);

    void UpdateSetMove();
signals:
    void UpdateSetWG(MoveParm &Move);

public slots:

private:

    MoveParm SetMove;
    MoveParm RovMove;

};

#endif // ROVORIENT_H
