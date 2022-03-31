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
}

// convert point from std footground meters to widget pixel
void FootballRegin::updateStudentPointPosFromStdFootGround(std::vector<pcl::PointXYZ> &objs)
{
    // x, y
    m_studentsPoints.clear();
    int showPoints = objs.size();
    // in examing state, only show one point
    if (m_examStarted) {
        showPoints = 1;
    }
    for (int i = 0; i < showPoints; i++) {
        qDebug() << __func__ << __LINE__ << i << objs[i]._PointXYZ::x << objs[i]._PointXYZ::y;
        float x_pixel = objs[i]._PointXYZ::x / m_per_pixelX + m_origin.x();
        float y_pixel = m_origin.y() - objs[i]._PointXYZ::y / m_per_pixelY;
        m_studentsPoints.push_back(QPointF(x_pixel, y_pixel));
    }
}

void FootballRegin::startExam(bool started)
{
    m_examStarted = started;
}

void FootballRegin::updateStudentPointPos(float x, float y)
{
    m_studentPos.setX(x);
    m_studentPos.setY(y);
//    this->update();
}

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

void FootballRegin::updateRectPoint(const QPoint &topLeft, const QPoint &bottomRight)
{


     // no trastration
//     qDebug() << __func__ << __LINE__ << leftUpPoint;
//     qDebug() << __func__ << __LINE__ << rightBotomPoint;
//     qDebug() << __func__ << __LINE__ << this->geometry().topLeft();
//     qDebug() << __func__ << __LINE__ << this->geometry().bottomRight();
//     qDebug() << __func__ << __LINE__ << this->width();
//     qDebug() << __func__ << __LINE__ << this->height();



     m_realCenter.setX((this->geometry().topLeft().x() + this->geometry().bottomRight().x()) / 2);
     m_realCenter.setY((this->geometry().topLeft().y() + this->geometry().bottomRight().y()) / 2);

     m_rectCenter.setX((topLeft.x() + bottomRight.x())/2);
     m_rectCenter.setY((topLeft.y() + bottomRight.y())/2);

     m_deltaX =  m_realCenter.x() - m_rectCenter.x();
     m_deltaY =  m_realCenter.y() - m_rectCenter.y();

     // calculate origin point
     m_origin.setX((topLeft.x() + bottomRight.x()) / 2.0 + m_deltaX);
     m_origin.setY(bottomRight.y() + m_deltaY);

     leftUpPoint.setX(topLeft.x() + m_deltaX);
     leftUpPoint.setY(topLeft.y() + m_deltaY);
     rightBotomPoint.setX(bottomRight.x() + m_deltaX);
     rightBotomPoint.setY(bottomRight.y() + m_deltaY);

     m_rect.setTopLeft(leftUpPoint);
     m_rect.setBottomRight(rightBotomPoint);

     m_per_pixelX = 10.0 / (bottomRight.x() - topLeft.x());
     m_per_pixelY = 30.0 / (bottomRight.y() - topLeft.y());

     leftUpOk = true;
     rightDownOk = true;
     calculateObsStickPosition();
     this->update();
}


void FootballRegin::paintEvent(QPaintEvent *event)
{
//    qDebug() << __func__ << __LINE__ << leftUpOk << rightDownOk;
    showExamRegin();

    showExamStudentPath();

    showExamStickPos();

    showExamStudentPoints();

    QWidget::paintEvent(event);
}

void FootballRegin::showExamStickPos()
{
    QPen m_pen3;
    m_pen3.setWidth(3);
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
}

void FootballRegin::showExamStudentPath()
{
    QPen m_pen2;
    m_pen2.setColor(QColor("green"));
    m_pen2.setWidth(3);
    m_pen2.setStyle(Qt::SolidLine);
    QPainter painterline(this);
    painterline.setPen(m_pen2);
    painterline.drawLines(m_pointPath);

}

void FootballRegin::showExamRegin()
{
    if (leftUpOk && rightDownOk) {
        QPen m_pen;
        m_pen.setColor(QColor(107, 223, 255));
        m_pen.setWidth(2);
        m_pen.setStyle(Qt::SolidLine);
        QPainter painter1(this);
        painter1.setPen(m_pen);
        painter1.drawRect(m_rect);
    }

}

void FootballRegin::showExamStudentPoints()
{
    QPen m_pen;
    m_pen.setColor(QColor("yellow"));
    m_pen.setWidth(6);
    m_pen.setStyle(Qt::SolidLine);
    QPainter studentPoint(this);
    studentPoint.setPen(m_pen);
    for (int i = 0; i < m_studentsPoints.size(); i++) {
        studentPoint.drawPoint(m_studentsPoints.at(i));
    }

}


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
