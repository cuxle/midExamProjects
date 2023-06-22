#ifndef EXAMREGIN_H
#define EXAMREGIN_H

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
#include <QQueue>

#include "utils.h"

class lidarAnalysis;

class ExamRegin : public QWidget
{
    Q_OBJECT
public:
    explicit ExamRegin(QWidget *parent = nullptr);
    void updateStudentPointPos(float x, float y);
    void updateStudentPointPosFromStdFootGround(std::vector<pcl::PointXYZ> &objs);
    void startExam(bool);
    void savePath(const QString &zkh, const QString &time);
    float m_deltaX = 0;
    float m_deltaY = 0;
    float m_ratioX = 1.0;
    float m_ratioY = 1.0;
    void setStuMovePathFileName(const QString &newStuPathFileName);

    void setLidarAnalysis(lidarAnalysis *newLidarAnalysis);

public slots:
    void updateRectPointTopLeft(const QPointF &topLeft);
    void updateRectPointBottomRight(const QPointF &bottomRight);

signals:
private:
    QPointF calculatNextPoint(const QPointF &p1, const QPointF &p2);
    void calculateObsStickPosition();
    void showExamRegin();
    void showExamStudentPoints();
    void showExamStudentPath();
    void showExamStickPos();
    void updateRectPoint(const QPointF &topLeft, const QPointF &bottomRight);
    void zoomToRect(QPointF &topLeft, QPointF &bottomRight);

    QRectF m_rect;
    QMenu contexMenu;

    QPointF m_topLeft;
    QPointF m_bottomRight;
    QPoint contexPoint;

    QPointF m_studentPos;
    QPoint followPoint;
    QPointF m_origin;

    QVector<QPointF> m_studentsPoints;
    QVector<QPointF> m_stuPointsPath;
    QVector<QPointF> m_stickPos;

    bool m_enableFillLastPoint = false;
    QQueue<QPointF> m_lastTwoPoints;
    int m_lastStudentPointSize = 0;

    float fx = 1;
    float deltaX = 0;
    float fy = -1;
    float deltaY = 0;

    float m_realHeight = 30; // meters
    float m_realWidth = 0; // according to ratio

    bool isLoging;

    float m_XpixelPerMeter = 0;
    float m_YpixelPerMeter = 0;

    bool leftUpOk = false;
    bool rightDownOk = false;

    bool m_examStarted = false;
    bool m_exmineStudentInRegin = false;

    QPointF m_originCenter;
    QPointF m_newCenter;

    QString m_stuMovePathFileName;

    lidarAnalysis *m_lidarAnalysis = nullptr;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
#ifdef TEST
    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);


    void mouseMoveEvent(QMouseEvent *event);

#endif
};

#endif // EXAMREGIN_H
