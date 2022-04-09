#include "footballregin.h"
#include <QPen>
#include <QPainter>
#include <QAction>
#include <QDebug>
#include <QContextMenuEvent>
#include <QPixmap>
#include <QPalette>
#include <QPainter>
#include <QPen>
#include "appconfig.h"
#include "singleton.h"
#include "lidar/lidarAnalysis.h"
#include <QPainterPath>

bool floatEqual(float a, float b)
{
    return fabs(a - b) <= std::numeric_limits<float>::epsilon();
}

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
        // do not show (0, -1) point

        if (floatEqual(objs[i]._PointXYZ::y, -1) \
                && floatEqual(objs[i]._PointXYZ::x, 0)) {
            continue;
        }

//        qDebug() << __func__ << __LINE__ <<"convert before" << i << objs[i]._PointXYZ::x << objs[i]._PointXYZ::y;
        float x_pixel = objs[i]._PointXYZ::x / m_per_pixelX + m_origin.x();
        float y_pixel = m_origin.y() - objs[i]._PointXYZ::y / m_per_pixelY;
        m_studentsPoints.push_back(QPointF(x_pixel, y_pixel));
        if (m_examStarted) {
            m_stuPointsPath.push_back(QPointF(x_pixel, y_pixel));
        }
    }
}

void FootballRegin::startExam(bool started)
{
    m_examStarted = started;

    // 停止考试了， 要保存考生路径为图片
    if (!m_examStarted) {
        m_stuPointsPath.clear();
        QPixmap pix(this->size());
        this->render(&pix);
        pix.save(m_stuMovePathFileName);
    }
}

void FootballRegin::savePath(const QString &zkh, const QString &time)
{
     // 停止考试了， 要保存考生路径为图片
    if (!m_examStarted) {
        m_stuPointsPath.clear();
        QPixmap pix(this->size());
        this->render(&pix);
        pix.save(m_stuMovePathFileName);

        QPixmap pixmap(m_stuMovePathFileName);
        QPainter painter(&pixmap);
        painter.begin(&pixmap);
        painter.setPen(Qt::red);
        QFont font;
        font.setPixelSize(30);
        font.setFamily("Microsoft YaHei");
        painter.setFont(font);
        painter.drawText(QPoint(50, 50), zkh);
        painter.drawText(QPoint(50, 100), time);
        painter.end();
        pixmap.save(m_stuMovePathFileName);
        qDebug() << __func__ << __LINE__ << m_stuMovePathFileName;
    }
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
    int x = (m_topLeft.x() + m_bottomRight.x()) / 2;
    int y0 = m_topLeft.y();
    int ylast = m_bottomRight.y();
    int diff = (ylast - y0) / 6;
    int y1 = y0 + diff;
    int y2 = y1 + diff;
    int y3 = y2 + diff;
    int y4 = y3 + diff;
    int y5 = y4 + diff;

    m_stickPos.clear();
    m_stickPos.push_back(QPoint(x, y5));
    m_stickPos.push_back(QPoint(x, y4));
    m_stickPos.push_back(QPoint(x, y3));
    m_stickPos.push_back(QPoint(x, y2));
    m_stickPos.push_back(QPoint(x, y1));
}

void FootballRegin::updateRectPointTopLeft(const QPoint &topLeft)
{
    m_topLeft = topLeft;
    qDebug() << __func__ << __LINE__ << topLeft;
    leftUpOk = true;
    if (leftUpOk && rightDownOk) {
        updateRectPoint(m_topLeft, m_bottomRight);
    }
}

void FootballRegin::updateRectPointBottomRight(const QPoint &bottomRight)
{
    m_bottomRight = bottomRight;
    qDebug() << __func__ << __LINE__ << m_bottomRight;
    rightDownOk = true;
    if (leftUpOk && rightDownOk) {
        updateRectPoint(m_topLeft, m_bottomRight);
    }
}

void FootballRegin::updateRectPoint(const QPoint &topLeft, const QPoint &bottomRight)
{
    qDebug() << __func__ << __LINE__ << topLeft << bottomRight;
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

     m_topLeft.setX(topLeft.x() + m_deltaX);
     m_topLeft.setY(topLeft.y() + m_deltaY);
     m_bottomRight.setX(bottomRight.x() + m_deltaX);
     m_bottomRight.setY(bottomRight.y() + m_deltaY);

     m_rect.setTopLeft(m_topLeft);
     m_rect.setBottomRight(m_bottomRight);

     m_per_pixelX = 10.0 / (bottomRight.x() - topLeft.x());
     m_per_pixelY = 30.0 / (bottomRight.y() - topLeft.y());


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
    QPen m_pen;
    m_pen.setWidth(3);
    QPainter painterPoint(this);
    painterPoint.setPen(m_pen);
    for (int i = 0; i < m_stickPos.size(); i++) {
        QColor color = QColor("red");
        if (m_lidarAnalysis != nullptr && m_lidarAnalysis->m_flagStatus[i]) {
            color = QColor("green");
        }
        m_pen.setColor(color);
        painterPoint.setPen(m_pen);
        painterPoint.drawPoint(m_stickPos[i]);
    }
}

void FootballRegin::setLidarAnalysis(lidarAnalysis *newLidarAnalysis)
{
    m_lidarAnalysis = newLidarAnalysis;
}

void FootballRegin::setStuMovePathFileName(const QString &newStuPathFileName)
{
    m_stuMovePathFileName = newStuPathFileName;
}

void FootballRegin::showExamStudentPath()
{
    QPen m_pen2;
    m_pen2.setColor(QColor("green"));
    m_pen2.setWidth(3);
    m_pen2.setStyle(Qt::SolidLine);
    QPainterPath path;
    if (m_stuPointsPath.size() > 0) {
        path.moveTo(m_stuPointsPath.at(0));
        for (int i = 1; i < m_stuPointsPath.size(); i++) {
            path.lineTo(m_stuPointsPath.at(i));
        }
    }
    QPainter painterline(this);
    painterline.setPen(m_pen2);
    painterline.drawPath(path);
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


//void FootballRegin::mousePressEvent(QMouseEvent *event)
//{
//    m_stuPointsPath.clear();
//    isLoging = true;
//    QWidget::mousePressEvent(event);
//}

//void FootballRegin::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (isLoging) {
//        QPixmap pix(this->size());
//        this->render(&pix);
//        pix.save("test.png");
//    }
//    isLoging = false;

//    QWidget::mouseReleaseEvent(event);
//}

//void FootballRegin::mouseMoveEvent(QMouseEvent *event)
//{
//    if (isLoging) {
//        m_stuPointsPath.push_back(event->pos());
//        if (event->pos().y() < minY) {
//            minY = event->pos().y();
//        }
//        this->update();
//    }
//    QWidget::mouseMoveEvent(event);
//}
