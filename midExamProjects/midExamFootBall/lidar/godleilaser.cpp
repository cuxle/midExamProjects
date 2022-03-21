#include "godleilaser.h"
#include "godleilasermsop.h"
#include "godleilaserdifop.h"

#include <QThread>

std::vector<std::vector<float> > GodLeiLaser::lidar_angle;	//角度
std::vector<std::vector<int> > GodLeiLaser::lidar_dist;		//距离
std::vector<std::vector<int> > GodLeiLaser::lidar_inst;		//强度
std::vector<std::vector<unsigned long long> > GodLeiLaser::lidar_mtimestamp;	//时间戳

GodLeiLaser::GodLeiLaser(QObject *parent)
    : QObject(parent)
{
    m_godLeiMsopClient = new GodLeiLaserMSOP;
    m_msopThread = new QThread;
    m_godLeiMsopClient->moveToThread(m_msopThread);
    connect(m_msopThread, &QThread::started, m_godLeiMsopClient, &GodLeiLaserMSOP::initSocket);
    connect(m_godLeiMsopClient, &GodLeiLaserMSOP::sigDataReceived, this, &GodLeiLaser::sigHandleReceivedData);
    connect(m_msopThread, &QThread::finished, m_godLeiMsopClient, &GodLeiLaserMSOP::handleDestroy);
    m_msopThread->start();

    m_godLeiDifopClient = new GodLeiLaserDIFOP;
    m_difopThread = new QThread;
    m_godLeiDifopClient->moveToThread(m_difopThread);
    connect(m_difopThread, &QThread::started, m_godLeiDifopClient, &GodLeiLaserDIFOP::initSocket);
    connect(m_difopThread, &QThread::finished, m_godLeiDifopClient, &GodLeiLaserDIFOP::handleDestroy);
//    m_difopThread->start();
}

GodLeiLaser::~GodLeiLaser()
{
    m_msopThread->quit();
    m_msopThread->wait();

    m_difopThread->quit();
    m_difopThread->wait();
}

//void GodLeiLaser::sigHandleReceivedData()
//{
//    int i = 0;
//    if (lidar_angle.size() > 0)
//    {
//        i++;
//        pcl::PointCloud<pcl::PointXYZ> cloud;
//        //			PointCloud<PointXYZ>::Ptr cloud(new PointCloud<PointXYZ>);

//        LidarParsing(cloud);
//        cloud.width = 1;
//        cloud.height = cloud.points.size();
//        //���������ݴ洢�ڵ���cloud������Լ��Ӻ����㷨����
//        //			std::cout << lidar_dist[0][0] << std::endl;


//        viewer.showCloud(cloud.makeShared());
//        viewer.runOnVisualizationThreadOnce(viewerOneOff);

//        if (i < 5)
//        {
//            pcl::io::savePCDFileASCII("D:/pcd_test" + std::to_string(i) + ".pcd", cloud);
//            //				pcl::io::savePCDFileBinary("D:/pcd_test" + std::to_string(i) + ".pcd", cloud);
//        }
//        else
//        {
//            i = 5;
//        }

//        //			system("pause");


//        cout << cloud.points.size() << endl;
//        cloud.points.resize(0);



//        lidar_dist.clear();
//        lidar_inst.clear();
//        lidar_angle.clear();
//        lidar_mtimestamp.clear();
//    }
//    else {
//        //usleep(10);
//    }
//}

//���ݽ���
//void GodLeiLaser::LidarParsing(pcl::PointCloud<pcl::PointXYZ> &cloudData)
//{
//    using namespace pcl;
//    //����16���ߵ�������ֵ
//    double cosTheta[16] = { 0 };
//    double sinTheta[16] = { 0 };
//    for (int i = 0; i < 16; i++)
//    {
//        cosTheta[i] = cos(theta[i] * PI / 180);
//        sinTheta[i] = sin(theta[i] * PI / 180);
//    }

//    //����һȦ����ÿ�������������ֵ
//    std::vector<std::vector<double> > sinAngle;
//    std::vector<std::vector<double> > cosAngle;
//    sinAngle.resize(16);
//    cosAngle.resize(16);

//    for (int i = 0; i < 16; i++)
//    {
//        for (int j = 0; j < (int)lidar_angle[i].size(); j++)
//        {
//            sinAngle[i].push_back(sin(lidar_angle[i][j] * PI / 180));
//            cosAngle[i].push_back(cos(lidar_angle[i][j] * PI / 180));
//        }
//    }

//    for (int i = 0; i < 16; i++)
//    {
//        for (int j = 0; j < (int)lidar_angle[i].size(); j++)
//        {
//            float tempX = 0.0, tempY = 0.0, tempZ = 0.0;
//            tempX = ((lidar_dist[i][j] * cosTheta[i] * cos((lidar_angle[i][j]) * PI / 180)) +
//                (4.376 * cos((14.67 - lidar_angle[i][j]) * PI / 180))) / 100.f;
//            tempY = (-((lidar_dist[i][j] * cosTheta[i] * sin(lidar_angle[i][j] * PI / 180))) +
//                (4.376 * sin((14.67 - lidar_angle[i][j]) * PI / 180))) / 100.f;
//            tempZ = ((lidar_dist[i][j] * sinTheta[i]) + 0.426) / 100.f;

//            cloudData.points.push_back(PointXYZ(tempY, -tempX, tempZ));

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
