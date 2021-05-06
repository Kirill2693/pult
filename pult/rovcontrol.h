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
signals:
    void UpdateRoveWidgents(const MoveParm& Rov);

public slots:
    void tick();
    void key(QKeyEvent *ev);

private:
    QTimer *timer;
    Communication *udp;
    RovOrient *RovMov;
    DRK DrkSignals;
    ContourSignals SpeedError;
    ContourSignals PosError;
    MoveParm MoveRov;
};

#endif // ROVCONTROL_H
