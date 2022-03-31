#ifndef FOOTBALLREGIN_H
#define FOOTBALLREGIN_H

#include <QWidget>
#include <QRect>
#include <QMenu>
#include <QPoint>

#include <vector>
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
#include <pcl/ModelCoefficients.h>

class FootballRegin : public QWidget
{
    Q_OBJECT
public:
    explicit FootballRegin(QWidget *parent = nullptr);
    void updateStudentPointPos(float x, float y);
    void updateStudentPointPosFromStdFootGround(std::vector<pcl::PointXYZ> &objs);
    void startExam(bool);
    float m_deltaX = 0;
    float m_deltaY = 0;
public slots:
    void updateRectPoint(const QPoint &topLeft, const QPoint &bottomRight);

signals:
private:
    void calculateObsStickPosition();
    void showExamRegin();
    void showExamStudentPoints();
    void showExamStudentPath();
    void showExamStickPos();
    QRect m_rect;
    QMenu contexMenu;

    QPoint leftUpPoint;
    QPoint rightBotomPoint;
    QPoint contexPoint;

    QPointF m_studentPos;
    QPoint followPoint;
    QPointF m_origin;

    QVector<QPointF> m_studentsPoints;
    QVector<QPoint> m_pointPath;
    QVector<QPoint> m_stickPos;
    int minY = 10000000;
    bool isLoging;

    float m_per_pixelX = 0;
    float m_per_pixelY = 0;

    bool leftUpOk = false;
    bool rightDownOk = false;

    bool m_examStarted = false;

    QPointF m_rectCenter;
    QPointF m_realCenter;



    // QPaintDevice interface

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // FOOTBALLREGIN_H
