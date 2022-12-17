#include "lidarcloudwidget.h"

LidarCloudWidget::LidarCloudWidget(QWidget *parent)
    : QCustomPlot(parent)
{

    QAction *actionL = new QAction("设为左上");
    QAction *actionR = new QAction("设为右下");
    connect(actionL, &QAction::triggered, this, &LidarCloudWidget::handleLeftUpPointSet);
    connect(actionR, &QAction::triggered, this, &LidarCloudWidget::handleRightDownPointSet);
    connect(this, &QWidget::customContextMenuRequested, this, &LidarCloudWidget::on_plot_customContextMenuRequested);
    //    ui->plot->addAction(actionL);
    //    ui->plot->addAction(actionR);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    contexMenu.addAction(actionL);
    contexMenu.addAction(actionR);
}

LidarCloudWidget::~LidarCloudWidget()
{

}

//void LidarCloudWidget::contextMenuEvent(QContextMenuEvent *event)
//{
//    qDebug() << __func__ << __LINE__ << event->pos();
//    contexPoint = event->pos();

//    contexMenu.exec(mapFromGlobal(event->pos()));
//    QWidget::contextMenuEvent(event);
//}

void LidarCloudWidget::handleLeftUpPointSet()
{
    m_topLeftPoint = contexPoint;
//    m_rect.setTopLeft(leftUpPoint);
    leftUpOk = true;
    qDebug() << __func__ << __LINE__<< m_topLeftPoint;
    emit sigRectPointTopLeftUpdated(m_topLeftPoint);
}


void LidarCloudWidget::handleRightDownPointSet()
{
    m_bottomRightPoint = contexPoint;
//    m_rect.setBottomRight(rightBotomPoint);
    rightDownOk = true;
    qDebug() << __func__ << __LINE__<< m_bottomRightPoint;
    emit sigRectPointBottomRightUpdated(m_bottomRightPoint);
}

void LidarCloudWidget::on_plot_customContextMenuRequested(const QPoint &pos)
{
    qDebug() << __func__ << __LINE__<< (QPoint(pos.x(), pos.y()));

    contexPoint.setX(pos.x());
    contexPoint.setY(pos.y());

    contexMenu.exec(mapToGlobal(pos));
    qDebug() << __func__ << __LINE__<< (QPoint(mapToGlobal(pos).x(), mapToGlobal(pos).y()));
}
