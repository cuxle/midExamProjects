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
}


void LidarCloudWidget::handleRightDownPointSet()
{
    m_bottomRightPoint = contexPoint;
//    m_rect.setBottomRight(rightBotomPoint);
    rightDownOk = true;

//    QCPAxis *keyAxis = this->graph(0)->keyAxis();
//    QCPAxis *valueAxis = this->graph(0)->valueAxis();
//    m_cordPointTopLefts = QPointF(keyAxis->pixelToCoord((m_topLeftPoint).x()), valueAxis->pixelToCoord((m_topLeftPoint).y()));
//    m_cordPointBottomRight = QPointF(keyAxis->pixelToCoord((m_bottomRightPoint).x()), valueAxis->pixelToCoord((m_bottomRightPoint).y()));
//    qDebug() << __func__ << __LINE__<< m_cordPointTopLefts << m_cordPointBottomRight;
    emit sigRectPointUpdated(m_topLeftPoint, m_bottomRightPoint);
}

void LidarCloudWidget::on_plot_customContextMenuRequested(const QPoint &pos)
{
//    qDebug() << __func__ << __LINE__<< (QPoint(contexMenu.x(), contexMenu.y()));

    contexPoint = (pos);

    contexMenu.exec(mapToGlobal(pos));

}
