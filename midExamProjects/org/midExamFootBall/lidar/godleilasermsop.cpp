#include "godleilasermsop.h"
#include <QNetworkDatagram>
#include <QUdpSocket>
#include <QDebug>
//#include "laserchunkdata.h"
#include "godleilaser.h"

GodLeiLaserMSOP::GodLeiLaserMSOP(QObject *parent)
    : QObject(parent)
{

}


void GodLeiLaserMSOP::initSocket()
{
    qInfo() << __func__;
    udpSocket = new QUdpSocket;
    udpSocket->bind(QHostAddress::AnyIPv4, 2368);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &GodLeiLaserMSOP::readPendingDatagrams);

    tempAngle.clear();
    angle.resize(16);
    distance.resize(16);
    intensity.resize(16);
    mtimestamp.resize(16);
    tempAngle2.clear();
    angle2.resize(16);
    distance2.resize(16);
    intensity2.resize(16);
    mtimestamp2.resize(16);

    tmplidar_dist.clear();
    tmplidar_inst.clear();
    tmplidar_angle.clear();
    tmplidar_mtimestamp.clear();
    tmplidar_dist.resize(16);
    tmplidar_inst.resize(16);
    tmplidar_angle.resize(16);
    tmplidar_mtimestamp.resize(16);

}

void GodLeiLaserMSOP::handleDestroy()
{
    disconnect(udpSocket, &QUdpSocket::readyRead,
            this, &GodLeiLaserMSOP::readPendingDatagrams);
    delete udpSocket;
    this->deleteLater();
}

void GodLeiLaserMSOP::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void GodLeiLaserMSOP::processTheDatagram(const QNetworkDatagram &datagram)
{
    QByteArray dataByteArray = datagram.data();
    recvLen = dataByteArray.length();
    //qDebug() << __func__ << __LINE__ << recvLen << dataByteArray.toHex(' ');
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

//    qDebug() << recvLen << int(dataByteArray[0]) << int(dataByteArray[1]) << "dest port:" << datagram.destinationPort()
//             << "send port:" << datagram.senderPort();
//    recvLen = recvfrom(m_sock, recvBuf, sizeof(recvBuf), 0, (struct sockaddr *)&addrFrom, &len);
    if (recvLen > 0 && int(dataByteArray[0]) == -1 && int(dataByteArray[1]) == -18) //���յ�����
    {
        //�������յ�����
        std::vector<unsigned char> data;
        for (int i = 0; i < 1206; i++)
        {
            data.push_back(dataByteArray[i]);
        }
        //ʱ���
        unsigned long long mtimestamp_ = 16777216 * data[1203] + 65536 * data[1202] + 256 * data[1201] + data[1200];

        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                mtimestamp[j].push_back(mtimestamp_ + (16 * i + j)*3.125 - 596.875);
                mtimestamp[j].push_back(mtimestamp_ + (16 * i + (j + 16))*3.125 - 596.875);

                mtimestamp2[j].push_back(mtimestamp_ + (16 * i + j)*3.125 - 596.875);
                mtimestamp2[j].push_back(mtimestamp_ + (16 * i + (j + 16))*3.125 - 596.875);
            }
            if (i % 2 == 0)
            {
                if ((data[3 + 100 * i] * 256 + data[2 + 100 * i]) / 100.f >= 360.0)
                {
                    tempAngle.push_back(0);
                }
                else
                {
                    tempAngle.push_back((data[3 + 100 * i] * 256 + data[2 + 100 * i]) / 100.f);   //��ȡ��һȦ�еķ�λ�Ƕ�ֵ
                }
                for (int j = 0; j < 16; j++)
                {
                    distance[j].push_back((data[5 + 3 * j + 100 * i] * 256 + data[4 + 3 * j + 100 * i]) / 4.0);
                    intensity[j].push_back(data[6 + 3 * j + 100 * i]);

                    distance[j].push_back((data[5 + 3 * (j + 16) + 100 * i] * 256 + data[4 + 3 * (j + 16) + 100 * i]) / 4.0);
                    intensity[j].push_back(data[6 + 3 * (j + 16) + 100 * i]);
                }
                if (tempAngle.size() >= 2)
                {
                    for (int j = 0; j < 16; j++)
                    {
                        float mdiff = (tempAngle.back() - tempAngle[tempAngle.size() - 2]);
                        mdiff = mdiff >= 0 ? mdiff : mdiff + 360;
                        if ((tempAngle[tempAngle.size() - 2] + (mdiff / 32) * j) < 360.0)
                            angle[j].push_back(tempAngle[tempAngle.size() - 2] + (mdiff / 32) * j);
                        else
                            angle[j].push_back(tempAngle[tempAngle.size() - 2] + (mdiff / 32) * j - 360.0);
                        if ((tempAngle[tempAngle.size() - 2] + (mdiff / 32) * (j + 16)) < 360.0)
                            angle[j].push_back(tempAngle[tempAngle.size() - 2] + (mdiff / 32) * (j + 16));
                        else
                            angle[j].push_back(tempAngle[tempAngle.size() - 2] + (mdiff / 32) * (j + 16) - 360.0);
                    }
                }
            }
            if (i % 2 == 1)
            {
                if ((data[3 + 100 * i] * 256 + data[2 + 100 * i]) / 100.f >= 360.0)
                {
                    tempAngle2.push_back(0);
                }
                else
                {
                    tempAngle2.push_back((data[3 + 100 * i] * 256 + data[2 + 100 * i]) / 100.f);   //��ȡ��һȦ�еķ�λ�Ƕ�ֵ
                }
                for (int j = 0; j < 16; j++)
                {
                    distance2[j].push_back((data[5 + 3 * j + 100 * i] * 256 + data[4 + 3 * j + 100 * i]) / 4.0);
                    intensity2[j].push_back(data[6 + 3 * j + 100 * i]);

                    distance2[j].push_back((data[5 + 3 * (j + 16) + 100 * i] * 256 + data[4 + 3 * (j + 16) + 100 * i]) / 4.0);
                    intensity2[j].push_back(data[6 + 3 * (j + 16) + 100 * i]);
                }
                if (tempAngle2.size() >= 2)
                {
                    for (int j = 0; j < 16; j++)
                    {
                        float mdiff = (tempAngle2.back() - tempAngle2[tempAngle2.size() - 2]);
                        mdiff = mdiff >= 0 ? mdiff : mdiff + 360;
                        if ((tempAngle2[tempAngle2.size() - 2] + (mdiff / 32) * j) < 360.0)
                            angle2[j].push_back(tempAngle2[tempAngle2.size() - 2] + (mdiff / 32) * j);
                        else
                            angle2[j].push_back(tempAngle2[tempAngle2.size() - 2] + (mdiff / 32) * j - 360.0);
                        if ((tempAngle2[tempAngle2.size() - 2] + (mdiff / 32) * (j + 16)) < 360.0)
                            angle2[j].push_back(tempAngle2[tempAngle2.size() - 2] + (mdiff / 32) * (j + 16));
                        else
                            angle2[j].push_back(tempAngle2[tempAngle2.size() - 2] + (mdiff / 32) * (j + 16) - 360.0);
                    }
                }
            }

            if (tempAngle.size() >= 2 && abs(tempAngle.back() - tempAngle[tempAngle.size() - 2]) > 180)
            {
                float mdiff = (tempAngle.back() - tempAngle[tempAngle.size() - 2]);
                mdiff = mdiff >= 0 ? mdiff : mdiff + 360;
                for (int j = 0; j < 16; j++)
                {
                    if ((tempAngle.back() + (mdiff / 32) * j) < 360.0)
                        angle[j].push_back(tempAngle.back() + (mdiff / 32) * j);
                    else
                        angle[j].push_back(tempAngle.back() + (mdiff / 32) * j - 360.0);
                    if ((tempAngle.back() + (mdiff / 32) * (j + 16)) < 360.0)
                        angle[j].push_back(tempAngle.back() + (mdiff / 32) * (j + 16));
                    else
                        angle[j].push_back(tempAngle.back() + (mdiff / 32) * (j + 16) - 360.0);
                }

                mdiff = (tempAngle2.back() - tempAngle2[tempAngle2.size() - 2]);
                mdiff = mdiff >= 0 ? mdiff : mdiff + 360;
                for (int j = 0; j < 16; j++)
                {
                    if ((tempAngle2.back() + (mdiff / 32) * j) < 360.0)
                        angle2[j].push_back(tempAngle2.back() + (mdiff / 32) * j);
                    else
                        angle2[j].push_back(tempAngle2.back() + (mdiff / 32) * j - 360.0);
                    if ((tempAngle2.back() + (mdiff / 32) * (j + 16)) < 360.0)
                        angle2[j].push_back(tempAngle2.back() + (mdiff / 32) * (j + 16));
                    else
                        angle2[j].push_back(tempAngle2.back() + (mdiff / 32) * (j + 16) - 360.0);
                }

                tmpangle.clear();
                tmpdistance.clear();
                tmpintensity.clear();
                tmpmtimestamp.clear();
                tmpangle.resize(16);
                tmpdistance.resize(16);
                tmpintensity.resize(16);
                tmpmtimestamp.resize(16);
                for (size_t h = 0; h < 16; h++)
                {
                    for (size_t k = angle[h].size() - 10; k < angle[h].size(); k++)
                    {
                        if (angle[h][k]  < 5)
                        {
                            tmpangle[h].push_back(angle[h][k]);
                            tmpdistance[h].push_back(distance[h][k]);
                            tmpintensity[h].push_back(intensity[h][k]);
                            tmpmtimestamp[h].push_back(mtimestamp[h][k]);
                            angle[h][k] = 0;
                            distance[h][k] = 0;
                            intensity[h][k] = 0;
                            mtimestamp[h][k] = 0;
                        }
                    }
                }

                tmpangle2.clear();
                tmpdistance2.clear();
                tmpintensity2.clear();
                tmpmtimestamp2.clear();
                tmpangle2.resize(16);
                tmpdistance2.resize(16);
                tmpintensity2.resize(16);
                tmpmtimestamp2.resize(16);
                for (size_t h = 0; h < 16; h++)
                {
                    for (size_t k = angle2[h].size() - 10; k < angle2[h].size(); k++)
                    {
                        if (angle2[h][k]  < 5)
                        {
                            tmpangle2[h].push_back(angle2[h][k]);
                            tmpdistance2[h].push_back(distance2[h][k]);
                            tmpintensity2[h].push_back(intensity2[h][k]);
                            tmpmtimestamp2[h].push_back(mtimestamp2[h][k]);
                            angle2[h][k] = 0;
                            distance2[h][k] = 0;
                            intensity2[h][k] = 0;
                            mtimestamp2[h][k] = 0;
                        }
                    }
                }

                if (GodLeiLaser::lidar_angle.empty())
                {
                    tmplidar_dist.clear();
                    tmplidar_inst.clear();
                    tmplidar_angle.clear();
                    tmplidar_mtimestamp.clear();
                    tmplidar_dist.resize(16);
                    tmplidar_inst.resize(16);
                    tmplidar_angle.resize(16);
                    tmplidar_mtimestamp.resize(16);

                    for (int j = 0; j < 16; j++)
                    {
                        tmplidar_dist[j].insert(tmplidar_dist[j].end(), distance[j].begin(), distance[j].end());
                        tmplidar_inst[j].insert(tmplidar_inst[j].end(), intensity[j].begin(), intensity[j].end());
                        tmplidar_angle[j].insert(tmplidar_angle[j].end(), angle[j].begin(), angle[j].end());
                        tmplidar_mtimestamp[j].insert(tmplidar_mtimestamp[j].end(), mtimestamp[j].begin(), mtimestamp[j].end());
                    }
                    for (int j = 0; j < 16; j++)
                    {
                        tmplidar_dist[j].insert(tmplidar_dist[j].end(), distance2[j].begin(), distance2[j].end());
                        tmplidar_inst[j].insert(tmplidar_inst[j].end(), intensity2[j].begin(), intensity2[j].end());
                        tmplidar_angle[j].insert(tmplidar_angle[j].end(), angle2[j].begin(), angle2[j].end());
                        tmplidar_mtimestamp[j].insert(tmplidar_mtimestamp[j].end(), mtimestamp2[j].begin(), mtimestamp2[j].end());
                    }

                    GodLeiLaser::lidar_dist = tmplidar_dist;
                    GodLeiLaser::lidar_inst = tmplidar_inst;
                    GodLeiLaser::lidar_angle = tmplidar_angle;
                    GodLeiLaser::lidar_mtimestamp = tmplidar_mtimestamp;

//                    qDebug() << __func__ << __LINE__ << GodLeiLaser::lidar_angle.size();
                }

                tempAngle.clear();
                angle.clear();
                angle.resize(16);
                distance.clear();
                distance.resize(16);
                intensity.clear();
                intensity.resize(16);
                mtimestamp.clear();
                mtimestamp.resize(16);
                for (size_t h = 0; h < 16; h++)
                {
                    for (size_t k = 0; k < tmpangle[h].size(); k++)
                    {
                        angle[h].push_back(tmpangle[h][k]);
                        distance[h].push_back(tmpdistance[h][k]);
                        intensity[h].push_back(tmpintensity[h][k]);
                        mtimestamp[h].push_back(tmpmtimestamp[h][k]);
                    }
                }

                tempAngle2.clear();
                angle2.clear();
                angle2.resize(16);
                distance2.clear();
                distance2.resize(16);
                intensity2.clear();
                intensity2.resize(16);
                mtimestamp2.clear();
                mtimestamp2.resize(16);
                for (size_t h = 0; h < 16; h++)
                {
                    for (size_t k = 0; k < tmpangle2[h].size(); k++)
                    {
                        angle2[h].push_back(tmpangle2[h][k]);
                        distance2[h].push_back(tmpdistance2[h][k]);
                        intensity2[h].push_back(tmpintensity2[h][k]);
                        mtimestamp2[h].push_back(tmpmtimestamp2[h][k]);
                    }
                }
            }
        }
    }
    emit sigDataReceived();
//    qDebug() << __func__ << __LINE__;
}
