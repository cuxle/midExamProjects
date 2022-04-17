#include "godleilaser.h"
#include "godleilasermsop.h"
#include <QDebug>

#include <QThread>

std::vector<std::vector<float> > GodLeiLaser::lidar_angle;	//角度
std::vector<std::vector<int> > GodLeiLaser::lidar_dist;		//距离
std::vector<std::vector<int> > GodLeiLaser::lidar_inst;		//强度
std::vector<std::vector<unsigned long long> > GodLeiLaser::lidar_mtimestamp;	//时间戳

GodLeiLaser::GodLeiLaser(QObject *parent)
    : QObject(parent)
{

}

GodLeiLaser::~GodLeiLaser()
{

}

void GodLeiLaser::initLaser()
{
    m_godLeiMsopClient = new GodLeiLaserMSOP;
    m_msopThread = new QThread;
    m_godLeiMsopClient->moveToThread(m_msopThread);
    connect(m_msopThread, &QThread::started, m_godLeiMsopClient, &GodLeiLaserMSOP::initSocket);
    connect(m_godLeiMsopClient, &GodLeiLaserMSOP::sigDataReceived, this, &GodLeiLaser::sigHandleReceivedData);
//    connect(m_godLeiMsopClient, &GodLeiLaserMSOP::sigDataReceived, this, &GodLeiLaser::handleReceivedPointsData);
    connect(m_msopThread, &QThread::finished, m_godLeiMsopClient, &GodLeiLaserMSOP::handleDestroy);
    m_msopThread->start();
}

void GodLeiLaser::destroyLaser()
{
    m_msopThread->quit();
    m_msopThread->wait();
}
