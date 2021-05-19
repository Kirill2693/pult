#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QUdpSocket>
#include "datatypes.h"

class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = nullptr);

signals:

public slots:
    void send(DRK sendData); // передача в модель структуры с сигналами двигателей
    void resivData();        // прием данных из матлаба
    DataFromMatlab GetDataFromMatlab() // доступ к принятым данным
    {
        return ResiveData;
    }

private:

    QUdpSocket *m_socket;
    QUdpSocket *m_resiveSocket;
    DataFromMatlab ResiveData;
};

#endif // COMMUNICATION_H
