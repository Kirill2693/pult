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
    void send(DRK sendData);
    void resivData();
    void ProcessingRawData();
    MoveParm GetDataFromMatlab()
    {
        ProcessingRawData();
        return ResiveData;
    }

private:

    QUdpSocket *m_socket;
    QUdpSocket *m_resiveSocket;
    MoveParm ResiveData;
};

#endif // COMMUNICATION_H
