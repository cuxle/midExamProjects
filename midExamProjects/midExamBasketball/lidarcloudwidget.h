#ifndef LIDARCLOUDWIDGET_H
#define LIDARCLOUDWIDGET_H

#include <QWidget>
#include <qcustomplot.h>
#include <QMenu>
#include <QPoint>
#include <QPointF>

class LidarCloudWidget : public QCustomPlot
{
    Q_OBJECT
public:
    explicit LidarCloudWidget(QWidget *parent = nullptr);
    ~LidarCloudWidget();
signals:
    void sigRectPointTopLeftUpdated(const QPoint &topLeft);
    void sigRectPointBottomRightUpdated(const QPoint &bottomRight);
private slots:
    void handleLeftUpPointSet();
    void handleRightDownPointSet();
    void on_plot_customContextMenuRequested(const QPoint &pos);
private:

    QMenu contexMenu;

    QPoint m_topLeftPoint;
    QPoint m_bottomRightPoint;
    QPoint contexPoint;

    QPointF m_cordPointTopLefts;
    QPointF m_cordPointBottomRight;

    bool leftUpOk = false;
    bool rightDownOk = false;

//protected:
//    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // LIDARCLOUDWIDGET_H
