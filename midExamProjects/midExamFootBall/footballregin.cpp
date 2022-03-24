#include "footballregin.h"
#include <QPen>
#include <QPainter>
#include <QAction>
#include <QDebug>
#include <QContextMenuEvent>
#include <QPixmap>
#include <QPalette>

FootballRegin::FootballRegin(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet("background-color: rgb(55, 50, 82);");
    this->setAttribute(Qt::WA_StyledBackground);

//    QAction *actionL = new QAction("设为左上");
//    QAction *actionR = new QAction("设为右下");
//    connect(actionL, &QAction::triggered, this, &FootballRegin::handleLeftUpPointSet);
//    connect(actionR, &QAction::triggered, this, &FootballRegin::handleRightDownPointSet);
//    connect(this, &QWidget::customContextMenuRequested, this, &FootballRegin::on_plot_customContextMenuRequested);
//    //    ui->plot->addAction(actionL);
//    //    ui->plot->addAction(actionR);
//    this->setContextMenuPolicy(Qt::CustomContextMenu);
//    contexMenu.addAction(actionL);
//    contexMenu.addAction(actionR);

}

void FootballRegin::updateStudentPointPos(int x, int y)
{
    m_studentPos.setX(x);
    m_studentPos.setY(y);
//    this->update();
}

//void FootballRegin::handleLeftUpPointSet()
//{
//    leftUpPoint = contexPoint;
//    m_rect.setTopLeft(leftUpPoint);
//    leftUpOk = true;
//    this->update();
//    qDebug() << __func__ << __LINE__ << leftUpPoint;
//}

void FootballRegin::calculateObsStickPosition()
{
    // calculate five pionts of stick value
    // x is the same
    int x = (leftUpPoint.x() + rightBotomPoint.x()) / 2;
    int y0 = leftUpPoint.y();
    int ylast = rightBotomPoint.y();
    int diff = (ylast - y0) / 6;
    int y1 = y0 + diff;
    int y2 = y1 + diff;
    int y3 = y2 + diff;
    int y4 = y3 + diff;
    int y5 = y4 + diff;

    m_stickPos.clear();
    m_stickPos.push_back(QPoint(x, y1));
    m_stickPos.push_back(QPoint(x, y2));
    m_stickPos.push_back(QPoint(x, y3));
    m_stickPos.push_back(QPoint(x, y4));
    m_stickPos.push_back(QPoint(x, y5));
}

//void FootballRegin::handleRightDownPointSet()
//{
//    rightBotomPoint = contexPoint;
//    m_rect.setBottomRight(rightBotomPoint);
//    rightDownOk = true;

//    calculateObsStickPosition();

//    this->update();


//    qDebug() << __func__ << __LINE__ << rightBotomPoint;
//}

//void FootballRegin::on_plot_customContextMenuRequested(const QPoint &pos)
//{
//    contexPoint = (pos);
////    QCPAxis *keyAxis = ui->plot->graph(0)->keyAxis();
////    QCPAxis *valueAxis = ui->plot->graph(0)->valueAxis();
////    qDebug() << __func__ << __LINE__<< keyAxis->pixelToCoord(pos.x());
////    qDebug() << __func__ << __LINE__<< valueAxis->pixelToCoord(pos.y());
////    contexPoint = QPointF(keyAxis->pixelToCoord(pos.x()), valueAxis->pixelToCoord(pos.y()));
////    qDebug() << __func__ << __LINE__<< contexPoint;
//    contexMenu.exec(mapToGlobal(pos));
////    qDebug() << contexMenu.x() << contexMenu.y();
//    qDebug() << mapFromGlobal(QPoint(contexMenu.x(), contexMenu.y()));
////    QCPAxis *keyAxis = ui->plot->graph(0)->keyAxis();
////    QCPAxis *valueAxis = ui->plot->graph(0)->valueAxis();
////    qDebug() << __func__ << __LINE__<< keyAxis->pixelToCoord(pos.x());
////    qDebug() << __func__ << __LINE__<< valueAxis->pixelToCoord(pos.y());

//}

void FootballRegin::updateRectPoint(const QPoint &topLeft, const QPoint &bottomRight)
{
     leftUpPoint = topLeft;
     rightBotomPoint = bottomRight;
     m_rect.setTopLeft(topLeft);
     m_rect.setBottomRight(bottomRight);
     leftUpOk = true;
     rightDownOk = true;
     calculateObsStickPosition();
     this->update();
}


void FootballRegin::paintEvent(QPaintEvent *event)
{
//    qDebug() << __func__ << __LINE__ << leftUpOk << rightDownOk;
    if (leftUpOk && rightDownOk) {
        QPen m_pen;
        m_pen.setColor(QColor(107, 223, 255));
        m_pen.setWidth(2);
        m_pen.setStyle(Qt::SolidLine);
        QPainter painter1(this);
        painter1.setPen(m_pen);
        painter1.drawRect(m_rect);
    }

    QPen m_pen2;
    m_pen2.setColor(QColor("green"));
    m_pen2.setWidth(3);
    m_pen2.setStyle(Qt::SolidLine);
    QPainter painterline(this);
    painterline.setPen(m_pen2);
    painterline.drawLines(m_pointPath);

    QPen m_pen3;
    m_pen3.setColor(QColor("green"));
    m_pen3.setWidth(5);
    m_pen3.setStyle(Qt::SolidLine);



    QPainter painterPoint(this);
    painterPoint.setPen(m_pen3);
    for (int i = 0; i < 5; i++) {
        if (minY < m_stickPos[i].y()) {
            m_pen3.setColor(QColor("red"));
            painterPoint.setPen(m_pen3);
        } else {
            m_pen3.setColor(QColor("green"));
            painterPoint.setPen(m_pen3);
        }
        painterPoint.drawPoint(m_stickPos[i]);

    }

    QPen m_pen4;
    m_pen4.setColor(QColor("yellow"));
    m_pen4.setWidth(5);
    m_pen4.setStyle(Qt::SolidLine);
    QPainter studentPoint(this);
    studentPoint.setPen(m_pen4);
    studentPoint.drawPoint(m_studentPos);

    QWidget::paintEvent(event);
}

//void FootballRegin::contextMenuEvent(QContextMenuEvent *event)
//{
//    qDebug() << __func__ << __LINE__ << event->pos();
//    contexPoint = event->pos();
////    QCPAxis *keyAxis = ui->plot->graph(0)->keyAxis();
////    QCPAxis *valueAxis = ui->plot->graph(0)->valueAxis();
////    qDebug() << __func__ << __LINE__<< keyAxis->pixelToCoord(pos.x());
////    qDebug() << __func__ << __LINE__<< valueAxis->pixelToCoord(pos.y());
////    contexPoint = QPointF(keyAxis->pixelToCoord(pos.x()), valueAxis->pixelToCoord(pos.y()));
////    qDebug() << __func__ << __LINE__<< contexPoint;
//    contexMenu.exec(mapFromGlobal(event->pos()));
//    QWidget::contextMenuEvent(event);
//}

void FootballRegin::mousePressEvent(QMouseEvent *event)
{
    m_pointPath.clear();
    isLoging = true;
    QWidget::mousePressEvent(event);
}

void FootballRegin::mouseReleaseEvent(QMouseEvent *event)
{
    if (isLoging) {
        QPixmap pix(this->size());
        this->render(&pix);
        pix.save("test.png");
    }
    isLoging = false;

    QWidget::mouseReleaseEvent(event);
}

void FootballRegin::mouseMoveEvent(QMouseEvent *event)
{
    if (isLoging) {
        m_pointPath.push_back(event->pos());
        if (event->pos().y() < minY) {
            minY = event->pos().y();
        }
        this->update();
    }
    QWidget::mouseMoveEvent(event);
}
