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

class lidarBasketballAnalysis;

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
    void setStuMovePathFileName(const QString &newStuPathFileName);

    void setLidarAnalysis(lidarBasketballAnalysis *newLidarAnalysis);

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

    lidarBasketballAnalysis *m_lidarAnalysis = nullptr;

    QVector<QPointF> m_studentsPoints;
    QVector<QPointF> m_stuPointsPath;
    QVector<QPointF> m_stickPos;

    bool isLoging;

    float m_per_pixelX = 0;
    float m_per_pixelY = 0;

    bool leftUpOk = false;
    bool rightDownOk = false;

    bool m_examStarted = false;
    bool m_exmineStudentInRegin = false;

    QPointF m_rectCenter;
    QPointF m_realCenter;

    QString m_stuMovePathFileName;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // FOOTBALLREGIN_H
