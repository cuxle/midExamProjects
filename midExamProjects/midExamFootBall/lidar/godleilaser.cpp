#include "godleilaser.h"
#include "godleilasermsop.h"
#include "godleilaserdifop.h"
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
//    m_msopThread->quit();
//    m_msopThread->wait();

//    m_difopThread->quit();
//    m_difopThread->wait();
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

    m_godLeiDifopClient = new GodLeiLaserDIFOP;
    m_difopThread = new QThread;
    m_godLeiDifopClient->moveToThread(m_difopThread);
    connect(m_difopThread, &QThread::started, m_godLeiDifopClient, &GodLeiLaserDIFOP::initSocket);
    connect(m_difopThread, &QThread::finished, m_godLeiDifopClient, &GodLeiLaserDIFOP::handleDestroy);
//    m_difopThread->start();

//    m_lidaAnalysis = new lidarAnalysis;
//    cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);
//    m_lidaAnalysis->setTestRegion(-2.4f, 2.8f, 0.3f, 16.3f, -1.2f, 1.0f);
}

void GodLeiLaser::destroyLaser()
{
    m_msopThread->quit();
    m_msopThread->wait();

    m_difopThread->quit();
    m_difopThread->wait();
}



//void GodLeiLaser::LidarParsing(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloudData)
//{
////    vx.clear();
////    vy.clear();
//    using namespace pcl;
//    //����16���ߵ�������ֵ
//    double cosTheta[16] = { 0 };
//    double sinTheta[16] = { 0 };
//    for (int i = 0; i < 16; i++)
//    {
//        cosTheta[i] = cos(theta[i] * PI / 180);
//        sinTheta[i] = sin(theta[i] * PI / 180);
//    }

//    //
//    std::vector<std::vector<double>> sinAngle;
//    std::vector<std::vector<double>> cosAngle;
//    sinAngle.resize(16);
//    cosAngle.resize(16);

//    for (int i = 0; i < 16; i++)
//    {
//        for (int j = 0; j < (int)GodLeiLaser::lidar_angle[i].size(); j++)
//        {
//            sinAngle[i].push_back(sin(GodLeiLaser::lidar_angle[i][j] * PI / 180));
//            cosAngle[i].push_back(cos(GodLeiLaser::lidar_angle[i][j] * PI / 180));
//        }
//    }

//    for (int i = 0; i < 16; i++)
//    {
//        for (int j = 0; j < (int)GodLeiLaser::lidar_angle[i].size(); j++)
//        {
//            float tempX = 0.0, tempY = 0.0, tempZ = 0.0;
//            tempX = ((GodLeiLaser::lidar_dist[i][j] * cosTheta[i] * cos((GodLeiLaser::lidar_angle[i][j]) * PI / 180)) +
//                (4.376 * cos((14.67 - GodLeiLaser::lidar_angle[i][j]) * PI / 180))) / 100.f;
//            tempY = (-((GodLeiLaser::lidar_dist[i][j] * cosTheta[i] * sin(GodLeiLaser::lidar_angle[i][j] * PI / 180))) +
//                (4.376 * sin((14.67 - GodLeiLaser::lidar_angle[i][j]) * PI / 180))) / 100.f;
//            tempZ = ((GodLeiLaser::lidar_dist[i][j] * sinTheta[i]) + 0.426) / 100.f;
////            vx.push_back(tempX+2);
////            vy.push_back(tempY+4);
////            tempZ = 1;
////            tempZ = 0;
//            cloudData->points.push_back(PointXYZ(tempY, -tempX, tempZ));
////            qDebug() << __func__ << __LINE__ << cloudData->points.size();
//#ifdef _DEBUG
//            outfileDeubg << tempX << ","
//                << tempY << ","
//                << tempZ << ","
//                << lidar_inst[i][j] << ","
//                << i << ","
//                << lidar_angle[i][j] << ","
//                << lidar_dist[i][j] / 100.000 << ","
//                << lidar_mtimestamp[i][j] << std::endl;

//            std::cout << "lidar_dist:  " << lidar_dist[i][j] / 100.f << "  point.x:  " << tempX << "  : " << "  point.y:  " << tempY << " : " << "  point.z:  " << tempZ << std::endl;
//#endif
//        }
//    }
//}

//void GodLeiLaser::handleReceivedPointsData()
//{
//    int i = 0;
//    if (GodLeiLaser::lidar_angle.size() > 0)
//    {
//        qDebug() << __func__ << __LINE__ << GodLeiLaser::lidar_angle.size();
//        i++;
//        //			PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);

//        LidarParsing(cloud);


//        if (cloud->points.size() == 0) {
//            return;
//        }

//        qDebug() << __func__ << __LINE__ << cloud->points.size();
//        m_lidaAnalysis->normalizeData(cloud);


//        qDebug() << __func__ << __LINE__ << cloud->points.size();
//        m_objs = m_lidaAnalysis->objectDetection(cloud);

//        return;
//        qDebug() << __func__ << __LINE__ << m_objs.size() << m_objs[0]._PointXYZ::x << m_objs[0]._PointXYZ::y;
//////        for (int i = 0; i < m_objs.size(); i++)
//////        {
//////            std::cout << "core:" << m_objs[i] << endl;
//////        }
//        vx.clear();
//        vy.clear();
//        vx.push_back(m_objs[0]._PointXYZ::x);
//        vy.push_back(m_objs[0]._PointXYZ::y);
//        emit sigStudentPositionUpdated(vx, vy);

////        showCustomPlot();

//        cloud->points.resize(0); // waste resource

//        GodLeiLaser::lidar_dist.clear();
//        GodLeiLaser::lidar_inst.clear();
//        GodLeiLaser::lidar_angle.clear();
//        GodLeiLaser::lidar_mtimestamp.clear();
//    }
//}

//void GodLeiLaser::handleSetTestRegin(float xMin, float xMax, float yMin, float yMax)
//{
//    float zMin = -1.2f;
//    float zMax = 1.0f;
//    if (m_lidaAnalysis->setTestRegion(xMin, xMax, yMin, yMax, zMin, zMax)) {
//        qDebug() << __func__ << __LINE__ << "successfully";
//    } else {
//        qDebug() << __func__ << __LINE__ << "failed!";
//    }
//}

//void GodLeiLaser::handleStartExam(bool start)
//{
//    // 1. start Exam button pressed, check now student is in the ExamRegin or not
//    // 1.1 Yes: return weigui info to main thread
//    // 1.2 No: nothing happen, continue examing
//    if (start) {
//        int result = m_lidaAnalysis->setExamStart(m_objs[0].x, m_objs[0].y);
//        if (!result) {
//            emit sigStudentQiangPao(true);
//        } else {
//            qDebug() << __func__ << __LINE__ << "student not qiangpao continue to exam";
//        }
//    } else {
//        // stop the exam
//    }

//}
