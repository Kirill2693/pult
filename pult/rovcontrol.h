#ifndef ROVCONTROL_H
#define ROVCONTROL_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include "communication.h"
#include "rovorient.h"
#include "datatypes.h"
#include <QKeyEvent>

class RovControl : public QObject
{
    Q_OBJECT
public:
    explicit RovControl(QObject *parent = nullptr);
    void BfsDrk();
    void DirectControl();
    void BfsDrk(const ContourSignals &OutContour);
    void SetYaw(const MoveParm& Move)
    {
        SetRovOrient = Move;
    }
    void ResetSetSpeed();

signals:
    void UpdateRoveWidgents(const MoveParm& Rov);

public slots:
    void tick();

private:
    QTimer *timer;
    Communication *udp;
    DRK DrkSignals;
    ContourSignals SpeedError;
    ContourSignals PosError;
    MoveParm MoveRov;
    MoveParm SetRovOrient;
};

#endif // ROVCONTROL_H
