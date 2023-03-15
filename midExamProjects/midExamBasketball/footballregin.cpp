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
#include "lidar/lidarBasketballAnalysis.h"
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

 //       qDebug() << __func__ << __LINE__ <<"convert before" << i << objs[i]._PointXYZ::x << objs[i]._PointXYZ::y;

        // tranform meters to pixels
        float x_pixel = objs[i]._PointXYZ::x * m_XpixelPerMeter;
        float y_pixel = objs[i]._PointXYZ::y * m_YpixelPerMeter;

        // tranform coordinate system to qt's
        x_pixel = fx * (x_pixel + deltaX);
        y_pixel = fy * (y_pixel + deltaY);

        QPointF fpoint = QPointF(x_pixel, y_pixel);
        m_studentsPoints.push_back(fpoint);
        if (m_examStarted) {
            m_stuPointsPath.push_back(fpoint);

            if (m_eanbleLastPointFill) {
                // mainten the last points, this part of code should not exist
                if (m_lastTwoPoints.size() >= 2) {
                    m_lastTwoPoints.push_back(fpoint);
                    m_lastTwoPoints.pop_front();
                } else {
                    m_lastTwoPoints.push_back(fpoint);
                }
                // mainten the last points, this part of code should not exist
            }

        } else {
            qDebug() << "display path";
        }
        qDebug() << __func__ << __LINE__ << "students in exam region";
    }

    if (m_eanbleLastPointFill) {
        // mainten the last points, this part of code should not exist
        if (m_lastStudentPointSize == m_studentsPoints.size() && !m_examStarted) {
            if (m_lastTwoPoints.size() == 2) {
                QPointF calculatePoint = calculatNextPoint(m_lastTwoPoints.at(0), m_lastTwoPoints.at(1)) ;
                m_lastTwoPoints.clear();
                m_stuPointsPath.push_back(calculatePoint);
            } else {
                return;
            }
        }

        m_lastStudentPointSize = m_studentsPoints.size();
        // mainten the last points, this part of code should not exist
    }
}

QPointF FootballRegin::calculatNextPoint(const QPointF &p1, const QPointF &p2)
{
    float x = 2 * p2.x() - p1.x();
    float y = 2 * p2.y() - p1.y();
    return std::move(QPointF(x,y));
}

void FootballRegin::startExam(bool started)
{
    m_examStarted = started;

    // 开始考试， 清除上次考生路径, 20221128 cxl
    if (started) {
        m_stuPointsPath.clear();
    }
    // 停止考试了， 要保存考生路径为图片
//    if (!m_examStarted) {
//        m_stuPointsPath.clear();
//        QPixmap pix(this->size());
//        this->render(&pix);
//        pix.save(m_stuMovePathFileName);
//    }
}

void FootballRegin::savePath(const QString &zkh, const QString &time)
{
     // 停止考试了， 要保存考生路径为图片
    //if (!m_examStarted) { comment this line in 20230303
        // 没必要清除，开始后再清除  20221128
        //m_stuPointsPath.clear();
        QPixmap pix(this->size());
        this->render(&pix);
        pix.save(m_stuMovePathFileName);

        // write zkh and socre on the picture
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
    //}
}

void FootballRegin::updateStudentPointPos(float x, float y)
{
    m_studentPos.setX(x);
    m_studentPos.setY(y);
//    this->update();
}

void FootballRegin::calculateObsStickPosition()
{
    qDebug() <<__func__ << m_topLeft << m_bottomRight;
    // calculate five pionts of stick value
    float width = m_bottomRight.x() - m_topLeft.x();
    float height =  m_bottomRight.y() - m_topLeft.y();
    float y0 = m_topLeft.y() + (5.8 / 28) * height;
    float y1 = m_topLeft.y() + height * 0.5;
    float y2 = m_topLeft.y() + (28 - 5.8) / 28 * height;
    float x0 = m_topLeft.x() + (15 - 3.6) / 2 / 15 * width;
    float x1 = x0 + (3.6) / 15 * width;


    m_stickPos.clear();
    m_stickPos.push_back(QPoint(x0, y2));
    m_stickPos.push_back(QPoint(x1, y2));

    m_stickPos.push_back(QPoint(x0, y1));
    m_stickPos.push_back(QPoint(x1, y1));


    m_stickPos.push_back(QPoint(x0, y0));
    m_stickPos.push_back(QPoint(x1, y0));
}

void FootballRegin::updateRectPointTopLeft(const QPointF &topLeft)
{
    m_topLeft = topLeft;
    qDebug() << __func__ << __LINE__ << topLeft;
    leftUpOk = true;
//    rightDownOk = true;
//    if (leftUpOk && rightDownOk) {
//        updateRectPoint(m_topLeft, m_bottomRight);
//    }
}

void FootballRegin::updateRectPointBottomRight(const QPointF &bottomRight)
{
    m_bottomRight = bottomRight;
    qDebug() << __func__ << __LINE__ << m_topLeft<< m_bottomRight;
    rightDownOk = true;
    if (leftUpOk && rightDownOk) {
        updateRectPoint(m_topLeft, m_bottomRight);
    }
}

void FootballRegin::updateRectPoint(const QPointF &topLeft, const QPointF &bottomRight)
{
    qDebug() << __func__ << __LINE__ << topLeft << bottomRight;
     m_newCenter.setX((this->rect().topLeft().x() + this->rect().bottomRight().x()) / 2);
     m_newCenter.setY((this->rect().topLeft().y() + this->rect().bottomRight().y()) / 2);

     m_originCenter.setX((topLeft.x() + bottomRight.x())/2);
     m_originCenter.setY((topLeft.y() + bottomRight.y())/2);

     m_deltaX =  m_newCenter.x() - m_originCenter.x();
     m_deltaY =  m_newCenter.y() - m_originCenter.y();


     m_topLeft.setX(topLeft.x());
     m_topLeft.setY(topLeft.y());
     m_bottomRight.setX(bottomRight.x());
     m_bottomRight.setY(bottomRight.y());

     zoomToRect(m_topLeft, m_bottomRight);

     // calculate origin point
//     m_origin.setX((m_topLeft.x() + m_bottomRight.x()) / 2.0);
//     m_origin.setY(m_bottomRight.y());

     m_rect.setTopLeft(m_topLeft);
     m_rect.setBottomRight(m_bottomRight);

     m_XpixelPerMeter =  (m_bottomRight.x() - m_topLeft.x()) / m_realWidth;
     m_YpixelPerMeter =  (m_bottomRight.y() - m_topLeft.y()) / m_realHeight;


     calculateObsStickPosition();
     this->update();
}

// resize to a perfem_ct frame
void FootballRegin::zoomToRect(QPointF &topLeft, QPointF &bottomRight)
{
    int margin = 50;

    qDebug() << __func__ << __LINE__ << topLeft << bottomRight;
    float width = abs(bottomRight.x() - topLeft.x());
    float height = abs(bottomRight.y() - topLeft.y());
    float ratio = 1.0 * width / height;

    float newHeight = 0;
    float newWidth = 0;
    if (height >= width) {
        // pick the direct max slab based on the height or with - 100
        qDebug() << __func__ << __LINE__ << this->rect().height();
        newHeight = this->rect().height() - margin*2;
        newWidth = newHeight * ratio;
    } else {
        qDebug() << __func__ << __LINE__ << this->rect().width();
        newWidth = this->rect().width() - margin*2;
        newHeight = newWidth / ratio;
    }
    m_ratioX = 1.0 * newWidth / width;
    m_ratioY = 1.0 * newHeight / height;

    qDebug() << __func__ << __LINE__ <<"old height:"<< height << "old width:" << width << " new height:"<< newHeight<< " new width:" << newWidth<< m_ratioX << m_ratioY;

    bottomRight.setX(m_newCenter.x() + newWidth / 2);
    bottomRight.setY(m_newCenter.y() + newHeight / 2);

    topLeft.setX(m_newCenter.x() - newWidth / 2);
    topLeft.setY(m_newCenter.y() - newHeight / 2);

    m_origin.setX(m_newCenter.x());
    m_origin.setY(m_bottomRight.y());

    deltaX = m_newCenter.x();
    deltaY = -m_bottomRight.y();

    m_realWidth = m_realHeight * newWidth / newHeight;

//    topLeft = getNewPoint(topLeft);
//    bottomRight = getNewPoint(bottomRight);
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

void FootballRegin::setLidarAnalysis(lidarBasketballAnalysis *newLidarAnalysis)
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
