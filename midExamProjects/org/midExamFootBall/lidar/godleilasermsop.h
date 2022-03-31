#ifndef GODLEILASERMSOP_H
#define GODLEILASERMSOP_H

#include <QObject>

class QUdpSocket;
class QNetworkDatagram;
class LaserChunkData;

class GodLeiLaserMSOP : public QObject
{
    Q_OBJECT
public:
    explicit GodLeiLaserMSOP(QObject *parent = nullptr);

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

    char recvBuf[1206] = { 0 };
    int recvLen;
    std::vector<float> tempAngle, tempAngle2;	//ԭʼ�Ƕ�
    std::vector<std::vector<float> > angle, angle2;
    std::vector<std::vector<int> > distance, distance2;
    std::vector<std::vector<int> > intensity, intensity2;
    std::vector<std::vector<unsigned long long> > mtimestamp, mtimestamp2;


    std::vector<std::vector<float> > tmplidar_angle;	//�Ƕ�
    std::vector<std::vector<int> > tmplidar_dist;		//����
    std::vector<std::vector<int> > tmplidar_inst;		//ǿ��
    std::vector<std::vector<unsigned long long> > tmplidar_mtimestamp;	//ʱ���


    //�����Ƕ�
    std::vector<std::vector<float> > tmpangle, tmpangle2;
    std::vector<std::vector<int> > tmpdistance, tmpdistance2;
    std::vector<std::vector<int> > tmpintensity, tmpintensity2;
    std::vector<std::vector<unsigned long long> > tmpmtimestamp, tmpmtimestamp2;
};

#endif // GODLEILASERMSOP_H
