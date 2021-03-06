#ifndef ROVORIENT_H
#define ROVORIENT_H

#include <QObject>
#include <QKeyEvent>
#include "datatypes.h"

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
    void ResetSpeed();
    MoveParm GetSetMove()
    {
        return SetMove;
    }
    void SetSens(double sens)
    {
        senstive = sens;
    }

signals:
    void UpdateSetWG(const MoveParm &Move);

public slots:
    void KeyGrab(QKeyEvent *ev);

private:

    MoveParm SetMove;
    double senstive;

};

#endif // ROVORIENT_H
