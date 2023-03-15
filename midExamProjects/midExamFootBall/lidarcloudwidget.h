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
    void sigRectPointTopLeftUpdated(const QPointF &topLeft);
    void sigRectPointBottomRightUpdated(const QPointF &bottomRight);
private slots:
    void handleLeftUpPointSet();
    void handleRightDownPointSet();
    void on_plot_customContextMenuRequested(const QPoint &pos);
private:

    QMenu contexMenu;

    QPointF m_topLeftPoint;
    QPointF m_bottomRightPoint;
    QPointF contexPoint;

    QPointF m_cordPointTopLefts;
    QPointF m_cordPointBottomRight;

    bool leftUpOk = false;
    bool rightDownOk = false;

    QAction *m_actionL = nullptr;
    QAction *m_actionR = nullptr;

//protected:
//    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // LIDARCLOUDWIDGET_H
