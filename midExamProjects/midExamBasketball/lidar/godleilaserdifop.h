#ifndef GODLEILASERDIFOP_H
#define GODLEILASERDIFOP_H

#include <QObject>

class QUdpSocket;
class QNetworkDatagram;
class LaserChunkData;

class GodLeiLaserDIFOP : public QObject
{
    Q_OBJECT
public:
    explicit GodLeiLaserDIFOP(QObject *parent = nullptr);

signals:
    void sigDataReceived();
public slots:
    void initSocket();
    void handleDestroy();
private:
    void readPendingDatagrams();
    void processTheDatagram(const QNetworkDatagram &datagram);

    //LaserChunkData *m_laserChunkData = nullptr;
    QUdpSocket *udpSocket = nullptr;

    char tmpDevData[1206] = { 0 };
};

#endif // GODLEILASERMSOP_H
