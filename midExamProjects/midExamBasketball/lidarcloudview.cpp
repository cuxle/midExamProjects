#include "lidarcloudview.h"

LidarCloudView::LidarCloudView(QWidget *parent)
    : QCustomPlot(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    m_actionL = new QAction("设为左上");
    m_actionR = new QAction("设为右下");
    m_actionL->setEnabled(true);
    m_actionR->setDisabled(true);

    connect(m_actionL, &QAction::triggered, this, &LidarCloudView::handleLeftUpPointSet);
    connect(m_actionR, &QAction::triggered, this, &LidarCloudView::handleRightDownPointSet);
    connect(this, &QWidget::customContextMenuRequested, this, &LidarCloudView::on_plot_customContextMenuRequested);
    //    ui->plot->addAction(actionL);
    //    ui->plot->addAction(actionR);

    contexMenu.addAction(m_actionL);
    contexMenu.addAction(m_actionR);
}

LidarCloudView::~LidarCloudView()
{

}

//void LidarCloudView::contextMenuEvent(QContextMenuEvent *event)
//{
//    qDebug() << __func__ << __LINE__ << event->pos();
//    contexPoint = event->pos();

//    contexMenu.exec(mapFromGlobal(event->pos()));
//    QWidget::contextMenuEvent(event);
//}

void LidarCloudView::handleLeftUpPointSet()
{
    m_topLeftPoint = contexPoint;
    leftUpOk = true;
    qDebug() << __func__ << __LINE__<< m_topLeftPoint;
    emit sigRectPointTopLeftUpdated(m_topLeftPoint);
    m_actionL->setDisabled(true);
    m_actionR->setEnabled(true);
}


void LidarCloudView::handleRightDownPointSet()
{
    m_bottomRightPoint = contexPoint;
    rightDownOk = true;
    emit sigRectPointBottomRightUpdated(m_bottomRightPoint);
    m_actionL->setEnabled(true);
    m_actionR->setDisabled(true);
}

void LidarCloudView::on_plot_customContextMenuRequested(const QPoint &pos)
{
    qDebug() << __func__ << __LINE__<<" local pos" << (QPoint(pos.x(), pos.y()));

    contexPoint.setX(pos.x());
    contexPoint.setY(pos.y());

    contexMenu.exec(mapToGlobal(pos));
}
