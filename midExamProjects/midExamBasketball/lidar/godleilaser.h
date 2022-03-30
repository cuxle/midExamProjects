#ifndef GODLEILASER_H
#define GODLEILASER_H

#include <QObject>

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/segmentation/sac_segmentation.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/project_inliers.h>

class GodLeiLaserMSOP;
class GodLeiLaserDIFOP;

class GodLeiLaser : public QObject
{
    Q_OBJECT
public:
    explicit GodLeiLaser(QObject *parent = nullptr);
    ~GodLeiLaser();

    static std::vector<std::vector<float> > lidar_angle;	//角度
    static std::vector<std::vector<int> > lidar_dist;		//距离
    static std::vector<std::vector<int> > lidar_inst;		//强度
    static std::vector<std::vector<unsigned long long> > lidar_mtimestamp;	//时间戳

signals:
    void sigHandleReceivedData();
//    void sigStudentInExamReginWhenStarting(bool);
//    void sigStudentOutOfExamReginExamFinished(bool);
//    void sigStudentPositionUpdated(const QVector<double> &vx, const QVector<double> &vy);
//    void sigStudentQiangPao(bool);

public slots:
//    void handleReceivedData();
    void initLaser();
    void destroyLaser();
//    void handleReceivedPointsData();
//    void handleSetTestRegin(float xMin, float xMax, float yMin, float yMax);
//    void handleStartExam(bool);
//    void handleExamMode(int); // 0, start; 1, weigui
private:
//    void LidarParsing(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloudData);

    GodLeiLaserMSOP *m_godLeiMsopClient = nullptr;
    QThread *m_msopThread = nullptr;

    GodLeiLaserDIFOP *m_godLeiDifopClient = nullptr;
    QThread *m_difopThread = nullptr;


//    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;


    // this container contains m_objs first major obj position
//    QVector<double> vx, vy;

//    const double PI = 3.1415926;
//    float const theta[16] = { -15, 1, -13, 3, -11, 5, -9, 7, -7, 9, -5, 11, -3, 13, -1, 15 };

};

#endif // GODLEILASER_H
