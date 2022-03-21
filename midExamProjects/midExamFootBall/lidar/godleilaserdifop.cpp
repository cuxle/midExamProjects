#include "godleilaserdifop.h"
#include <QNetworkDatagram>
#include <QUdpSocket>
#include <QDebug>
//#include "laserchunkdata.h"
#include <iostream>
#include <QThread>

GodLeiLaserDIFOP::GodLeiLaserDIFOP(QObject *parent)
    : QObject(parent)
{

}


void GodLeiLaserDIFOP::initSocket()
{
    qInfo() << __func__;
    udpSocket = new QUdpSocket;
    udpSocket->bind(QHostAddress::AnyIPv4, 2369);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &GodLeiLaserDIFOP::readPendingDatagrams);
}

void GodLeiLaserDIFOP::handleDestroy()
{
    disconnect(udpSocket, &QUdpSocket::readyRead,
            this, &GodLeiLaserDIFOP::readPendingDatagrams);
    delete udpSocket;
    this->deleteLater();
}

void GodLeiLaserDIFOP::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void GodLeiLaserDIFOP::processTheDatagram(const QNetworkDatagram &datagram)
{
    QByteArray dataByteArray = datagram.data();
    int recvLen = dataByteArray.length();
//        qDebug() << __func__ << __LINE__ << recvLen << dataByteArray.toHex(' ');
//    QByteArray azimuth = data.mid(2, 2);

//    unsigned short angle = 0;
//    angle |= (((quint8)azimuth.at(1)) << 8);
//    angle |= azimuth.at(0);
//    qInfo() << angle*0.01;

    //m_laserChunkData->setRawData(datagram.data());
    // parse raw data to formated data
    // 水平角度
    // 垂直角度
    // chanel i
    // 距离 distance
    // 强度
    // there are 1206 bytes data
    // 12 blocks

    // call dll to fomat graph

//    recvLen = recvfrom(m_sock_difop, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrFrom, &len);
    //���յ�����
    //DIFOP����ʶ��ͷ 0xA5 0xFF 0x00 0x5A
//    qDebug() << int(dataByteArray[0]) << int(dataByteArray[1]) << int(dataByteArray[2]) << int(dataByteArray[3]);
//    qDebug() << quint8(dataByteArray[0]) << quint8(dataByteArray[1]) << quint8(dataByteArray[2]) << quint8(dataByteArray[3]);
    if (recvLen > 0 && (int(dataByteArray[0]) == -91) && int(dataByteArray[1]) == -1 && int(dataByteArray[2]) == 0 && int(dataByteArray[3]) == 90) {
        //�������յ�����
        std::vector<unsigned char> data;
        for (int i = 0; i < 1206; i++)
        {
            data.push_back(dataByteArray[i]);
            tmpDevData[i] = dataByteArray[i];
        }

        //��̫����Ϣ
        std::vector<int> LidarIP;	//�״�IP
        LidarIP.push_back(data[10]);
        LidarIP.push_back(data[11]);
        LidarIP.push_back(data[12]);
        LidarIP.push_back(data[13]);
        std::cout << "LidarIP:" << LidarIP[0] << "." << LidarIP[1] << "." << LidarIP[2] << "." << LidarIP[3] << std::endl;

        std::vector<int> DestIP;	//Ŀ��IP
        DestIP.push_back(data[14]);
        DestIP.push_back(data[15]);
        DestIP.push_back(data[16]);
        DestIP.push_back(data[17]);
        std::cout << "DestIP:" << DestIP[0] << "." << DestIP[1] << "." << DestIP[2] << "." << DestIP[3] << std::endl;

        int Port1 = data[24] * 256 + data[25];	//�˿�1
        int Port2 = data[26] * 256 + data[27];	//�˿�2
        std::cout << "Port1:" << Port1 << "   " << "Port2:" << Port2 << std::endl;

        //GPSʱ��
        std::vector<int> TimeStamp;
        TimeStamp.push_back(data[52]);	//��
        TimeStamp.push_back(data[53]);	//��
        TimeStamp.push_back(data[54]);	//��
        TimeStamp.push_back(data[55]);	//ʱ
        TimeStamp.push_back(data[56]);	//��
        TimeStamp.push_back(data[57]);	//��
//        std::cout << "TimeStamp:" << TimeStamp[0] << "-" << TimeStamp[1] << "-" << TimeStamp[2] << " " << TimeStamp[3] << ":" << TimeStamp[4] << ":" << TimeStamp[5] << std::endl;

    }
    else {
        QThread::msleep(1000);
    }
    emit sigDataReceived();
}
