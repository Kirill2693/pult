#ifndef ROVCONTROL_H
#define ROVCONTROL_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QVector>
#include <QKeyEvent>
#include "communication.h"
#include "rovorient.h"
#include "datatypes.h"


class RovControl : public QObject
{
    Q_OBJECT
public:
    enum Modes
    {
      DirectMode,
      StabMode,
      SettingsMode
    };
    explicit RovControl(QObject *parent = nullptr);
    void BfsDrk();
    void DirectControl();
    void BfsDrk(const QVector<double> &OutContour); // Вычисление сигналов на двигатели
    void SetYaw(const MoveParm& Move)
    {
        SetRovOrient = Move;
    }
    void ResetSetSpeed();

    double CalcContour(const int Contour); //расчитываем значение на выходе каждого контура
    double Saturation(const double In,const double Up, const double Down); // функция насыщения

    void SetK1(const int Contour, double value);    //установка значений коэффициентов
    void SetK2(const int Contour, double value);
    void SetKosPos(const int Contour, double value);
    void SetKsp(const int Contour, double value);
    QVector<double>& GetK1();
    QVector<double>& GetK2();
    QVector<double>& GetKosPos();
    QVector<double>& GetKsp();

    void SetMode(const int Contour,const int Value);
    void IntegrRovSpeed();

signals:
    void UpdateRoveWidgents(const MoveParm& Rov);

public slots:
    void tick();

private:
    enum Contour
    {
        Yaw,
        Roll,
        Depth,
        March
    };

    QTimer *timer;
    int Ts = 100; // период замыкания системы управления
    Communication *udp;
    QVector<int> WorkMode; // Режимы работы каждого контура
    DRK DrkSignals;  // структура с сигналами на движки

    QVector<double> K1;
    QVector<double> K2;
    QVector<double> KosPos;  //коэфиициент обратной связи по позиции
    QVector<double> Ksp;    //коэффициент обратной связи по установленной скорости

    QVector<double> CurentRovSpeed; //Текущая скорость аппратата
    QVector<double> CurentRovPos; // Текущая ориентация аппарата
    QVector<double> SetRovSpeed;  // Заданная скорость аппарата
    QVector<double> SetRovPos;   //Заданная ориентация аппарата

    double ThrusterUp = 400; //Ограничение входного сигнала движителей
    double ThrusterDown = -400;

    ContourSignals SpeedError;
    ContourSignals PosError;
    MoveParm MoveRov;
    MoveParm SetRovOrient;

};

#endif // ROVCONTROL_H
