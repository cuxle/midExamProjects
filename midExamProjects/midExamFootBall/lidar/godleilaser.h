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

public slots:
    void initLaser();
    void destroyLaser();

private:
    GodLeiLaserMSOP *m_godLeiMsopClient = nullptr;
    QThread *m_msopThread = nullptr;
};

#endif // GODLEILASER_H
