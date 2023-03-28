#include "videowidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QTimer>
#include "appconfig.h"
#include "singleton.h"

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent),
      m_triggle(QPolygon(3))
{    
    QTimer::singleShot(50, [&](){
        QRect rect = this->rect();
//        m_rect.setX(rect.x() + rect.width() / 4);
//        m_rect.setY(rect.y() + rect.height() / 4);
//        m_rect.setHeight(rect.height() / 2);
//        m_rect.setWidth(rect.width() / 2);
//        return;
        qDebug() << __func__ << __LINE__;

        AppConfig &config = Singleton<AppConfig>::GetInstance();

        qDebug() << __func__ << __LINE__;
        int p1x = config.m_point1x != -1 ? config.m_point1x : rect.width() / 4;
        int p1y = config.m_point1y != -1 ? config.m_point1y : rect.height() / 2;

        qDebug() << __func__ << __LINE__;
        int p2x = config.m_point2x != -1 ? config.m_point2x : rect.width() / 2;
        int p2y = config.m_point2y != -1 ? config.m_point2y : rect.height() / 2;

        qDebug() << __func__ << __LINE__;
        int p3x = config.m_point3x != -1 ? config.m_point3x : rect.width() * 3 / 4;
        int p3y = config.m_point3y != -1 ? config.m_point3y : rect.height() * 3 / 4;

        qDebug() << __func__ << __LINE__;
        int rectP1x = config.m_rectPoint1x != -1 ? config.m_rectPoint1x : rect.width() * 1 / 2;
        int rectP1y = config.m_rectPoint1y != -1 ? config.m_rectPoint1y : rect.height() * 1 / 2;

        m_rectLeftTop.setX(rectP1x);
        m_rectLeftTop.setY(rectP1y);

        int rectP2x = config.m_rectPoint2x != -1 ? config.m_rectPoint2x : rect.width() * 1 / 2 + 200;
        int rectP2y = config.m_rectPoint2y != -1 ? config.m_rectPoint2y : rect.height() * 1 / 2 + 200;

        m_rectRightBottom.setX(rectP2x);
        m_rectRightBottom.setY(rectP2y);


        int rectHeight = config.m_rectHeight != -1 ? config.m_rectHeight : rect.width() / 4;
        int rectWidth = config.m_rectWidth != -1 ? config.m_rectHeight : rect.width() / 4;
        qDebug() << __func__ << __LINE__;

        m_rectHeight = rectHeight;
        m_rectWidth = rectWidth;

        m_triPoint1.setX(p1x);
        m_triPoint1.setY(p1y);
        qDebug() << __func__ << __LINE__;

        m_triPoint2.setX(p2x);
        m_triPoint2.setY(p2y);
        qDebug() << __func__ << __LINE__;

        m_triPoint3.setX(p3x);
        m_triPoint3.setY(p3y);
        qDebug() << __func__ << __LINE__;


        m_triggle.putPoints(0, 3, m_triPoint1.x(), m_triPoint1.y(),
                            m_triPoint2.x(), m_triPoint2.y(),
                            m_triPoint3.x(), m_triPoint3.y());
//        m_triggle << m_triPoint1 << m_triPoint2 << m_triPoint3;
//        m_triggle.setPoint(1, m_triPoint1.x(), m_triPoint1.y());
//        qDebug() << __func__ << __LINE__;
//        m_triggle.setPoint(2, m_triPoint2.x(), m_triPoint2.y());
//        qDebug() << __func__ << __LINE__;
//        m_triggle.setPoint(3, m_triPoint3.x(), m_triPoint3.y());
//        qDebug() << __func__ << __LINE__;

        qDebug() << __func__ << __LINE__;
        m_rect.setTopLeft(m_rectLeftTop);
        m_rect.setBottomRight(m_rectRightBottom);
        qDebug() << __func__ << __LINE__;
//        m_rect.setHeight(m_rectHeight);
//        m_rect.setWidth(m_rectWidth);
        this->update();
    });
}

VideoWidget::~VideoWidget()
{

}

void VideoWidget::updateConfig()
{
     AppConfig &config = Singleton<AppConfig>::GetInstance();

     m_triPoint1 = m_triggle.point(0);
     m_triPoint2 = m_triggle.point(1);
     m_triPoint3 = m_triggle.point(2);

     m_rectLeftTop = m_rect.topLeft();
     m_rectRightBottom = m_rect.bottomRight();

     m_rectHeight = m_rect.height();
     m_rectWidth = m_rect.width();

     config.m_point1x = m_triPoint1.x();
     config.m_point1y = m_triPoint1.y();

     config.m_point2x = m_triPoint2.x();
     config.m_point2y = m_triPoint2.y();

     config.m_point3x = m_triPoint3.x();
     config.m_point3y = m_triPoint3.y();

     config.m_rectPoint1x = m_rectLeftTop.x();
     config.m_rectPoint1y = m_rectLeftTop.y();

     config.m_rectPoint2x = m_rectRightBottom.x();
     config.m_rectPoint2y = m_rectRightBottom.y();
//     emit sigReginPosChanged(m_triPoint1.x()*m_ratioX, m_triPoint1.y()*m_ratioY, m_triPoint2.x()*m_ratioX, m_triPoint2.y()*m_ratioY,
//                             m_triPoint3.x()*m_ratioX, m_triPoint3.y()*m_ratioY, m_rectLeftTop.x()*m_ratioX, m_rectLeftTop.y()*m_ratioY,
//                             m_rectRightBottom.x()*m_ratioX, m_rectRightBottom.y()*m_ratioY);
     emit sigReginRectChanged(m_rectLeftTop.x()*m_ratioX, m_rectLeftTop.y()*m_ratioY,
                              m_rectHeight*m_ratioY, m_rectWidth*m_ratioX);
     //config.writeConfig();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    if (pix.isNull())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QSize pixSize = pix.size();
//    qDebug() << __func__ << __LINE__ << pixSize << "before";
    pixSize.scale(event->rect().size(), Qt::KeepAspectRatioByExpanding);

    QPixmap scaledPix = pix.scaled(pixSize,
                                   Qt::KeepAspectRatio,
                                   Qt::SmoothTransformation
                                   );
//    qDebug() << __func__ << __LINE__ << scaledPix.size() << "after";
    if (!m_ratioCounted) {
        m_ratioX = pix.size().width() * 1.0 / scaledPix.size().width();
        m_ratioY = pix.size().height() * 1.0 / scaledPix.size().height();
        m_ratioCounted = true;
    }
    painter.drawPixmap(QPoint(), scaledPix);


    QPen m_pen;
    m_pen.setColor(QColor("green"));
    m_pen.setWidth(3);
    m_pen.setStyle(Qt::DashDotDotLine);
    QPainter painter1(this);
    painter1.setPen(m_pen);
    painter1.drawRect(m_rect);

//    QPen triPen;
//    triPen.setColor(QColor("red"));
//    triPen.setWidth(3);
//    triPen.setStyle(Qt::DashLine);

//    QPainter triPainter(this);
//    triPainter.setPen(triPen);
//    triPainter.drawPolygon(m_triggle);


    QWidget::paintEvent(event);
}

const QPixmap* VideoWidget::pixmap() const
{
    return &pix;
}

void VideoWidget::setPixmap (const QPixmap &pixmap)
{
    pix = pixmap;
    update();
}

void VideoWidget::updateAlgorithmPos()
{
    updateConfig();
}

void VideoWidget::handleVideoWidgetIsLocked(bool locked)
{
    m_isLocked = locked;
}

void VideoWidget::handleResetVideoWidgetRatio()
{
    m_ratioCounted = false;
}

void VideoWidget::mouseMoveEvent(QMouseEvent *event)
{

    qDebug() << "active shape:" << (int)m_activeShape;
    // moving
//    if (m_isDragging) {
    if (!m_isLocked) {
        QPoint currentPos = event->globalPos();
        if (m_activeShape == ActiveRect) {
            QPoint bottomRight = m_rect.bottomRight();
            QPoint leftTop = m_rect.topLeft();
            switch (m_rectMoveType) {
            case RectMoveFromTop:
                leftTop.setY(leftTop.y() + currentPos.y() - lastPos.y());
//                m_rect.setY(m_rect.y() + currentPos.y() - lastPos.y());
                break;
            case RectMoveFromDown:
                bottomRight.setY(bottomRight.y() + currentPos.y() - lastPos.y());
//                m_rect.setHeight(m_rect.height() + currentPos.y() - lastPos.y());
                break;
            case RectMoveFromLeft:
                leftTop.setX(leftTop.x() + currentPos.x() - lastPos.x());
//                m_rect.setX(m_rect.x() + currentPos.x() - lastPos.x());
                break;
            case RectMoveFromRight:
                bottomRight.setX(bottomRight.x() + currentPos.x() - lastPos.x());
//                m_rect.setWidth(m_rect.width() + currentPos.x() - lastPos.x());
                break;
            case RectMoveFromTopLeft:
                leftTop.setX(leftTop.x() + currentPos.x() - lastPos.x());
                leftTop.setY(leftTop.y() + currentPos.y() - lastPos.y());
                break;
            case RectMoveFromBottomLeft:
                // x chagne
                // y not change
                // height change
                // width not change
                leftTop.setX(leftTop.x() + currentPos.x() - lastPos.x());
                bottomRight.setY(bottomRight.y() + currentPos.y() - lastPos.y());
                break;
            case RectMoveFromTopRight:
                // x not change
                // y change
                // height not chagne
                // width change
                leftTop.setY(leftTop.y() + currentPos.y() - lastPos.y());
                bottomRight.setX(bottomRight.x() + currentPos.x() - lastPos.x());
                break;
            case RectMoveFromBottomRight:
                // x not change
                // y not change
                // height chagne
                // width change
                bottomRight.setX(bottomRight.x() + currentPos.x() - lastPos.x());
                bottomRight.setY(bottomRight.y() + currentPos.y() - lastPos.y());
                break;
            default:
                break;
            }
            if (bottomRight.x() - leftTop.x() <= 50 || bottomRight.y() - leftTop.y() <= 50) {
                return;
            }


            switch (m_rectMoveType) {
            case RectMoveFromTop:
                m_rect.setY(m_rect.y() + currentPos.y() - lastPos.y());
                break;
            case RectMoveFromDown:
                m_rect.setHeight(m_rect.height() + currentPos.y() - lastPos.y());
                break;
            case RectMoveFromLeft:
                m_rect.setX(m_rect.x() + currentPos.x() - lastPos.x());
                break;
            case RectMoveFromRight:
                m_rect.setWidth(m_rect.width() + currentPos.x() - lastPos.x());
                break;
            case RectMoveFromTopLeft:
                m_rect.setX(m_rect.x() + currentPos.x() - lastPos.x());
                m_rect.setY(m_rect.y() + currentPos.y() - lastPos.y());
                break;
            case RectMoveFromBottomLeft:
                // x chagne
                // y not change
                // height change
                // width not change
                m_rect.setX(m_rect.x() + currentPos.x() - lastPos.x());
                m_rect.setHeight(m_rect.height() + currentPos.y() - lastPos.y());
                break;
            case RectMoveFromTopRight:
                // x not change
                // y change
                // height not chagne
                // width change
                m_rect.setY(m_rect.y() + currentPos.y() - lastPos.y());
                m_rect.setWidth(m_rect.width() + currentPos.x() - lastPos.x());
                break;
            case RectMoveFromBottomRight:
                // x not change
                // y not change
                // height chagne
                // width change
                m_rect.setHeight(m_rect.height() + currentPos.y() - lastPos.y());
                m_rect.setWidth(m_rect.width() + currentPos.x() - lastPos.x());
                break;
            default:
                int height = m_rect.height();
                int width = m_rect.width();
                m_rect.setX(m_rect.x() + currentPos.x() - lastPos.x());
                m_rect.setY(m_rect.y() + currentPos.y() - lastPos.y());
                m_rect.setHeight(height);
                m_rect.setWidth(width);
            }
            lastPos = currentPos;
            updateConfig();
        } else {
            switch (m_triMoveType) {
                case TriMovePoint1:
                {
                    m_triPoint1.setX(m_triPoint1.x() + currentPos.x() - lastPos.x());
                    m_triPoint1.setY(m_triPoint1.y() + currentPos.y() - lastPos.y());
                    break;
                }
                case TriMovePoint2:
                {
                    m_triPoint2.setX(m_triPoint2.x() + currentPos.x() - lastPos.x());
                    m_triPoint2.setY(m_triPoint2.y() + currentPos.y() - lastPos.y());
                    break;
                }
                case TriMovePoint3:
                {
                    m_triPoint3.setX(m_triPoint3.x() + currentPos.x() - lastPos.x());
                    m_triPoint3.setY(m_triPoint3.y() + currentPos.y() - lastPos.y());
                    break;
                }
                case TriMoveAll:
                {
                    m_triPoint1 = m_triggle.point(0);
                    m_triPoint2 = m_triggle.point(1);
                    m_triPoint3 = m_triggle.point(2);

                    m_triPoint1.setX(m_triPoint1.x() + currentPos.x() - lastPos.x());
                    m_triPoint1.setY(m_triPoint1.y() + currentPos.y() - lastPos.y());

                    m_triPoint2.setX(m_triPoint2.x() + currentPos.x() - lastPos.x());
                    m_triPoint2.setY(m_triPoint2.y() + currentPos.y() - lastPos.y());

                    m_triPoint3.setX(m_triPoint3.x() + currentPos.x() - lastPos.x());
                    m_triPoint3.setY(m_triPoint3.y() + currentPos.y() - lastPos.y());
                    break;
                }

                default:
                {
                    break;
                }
            }
            m_triggle.setPoint(0, m_triPoint1);
            m_triggle.setPoint(1, m_triPoint2);
            m_triggle.setPoint(2, m_triPoint3);

            lastPos = currentPos;
            updateConfig();
        }

    }

    QWidget::mouseMoveEvent(event);
    QWidget::update();
}

//void VideoLabel::rectMove(MoveType type)
//{

//}

Qt::CursorShape VideoWidget::getCurrentCursorShape(QMouseEvent *event)
{

    // if left right QCursor type 2 her
    // if top left cornor, top left type 3
    // if down left coror, down left type 4
    // if top right cornor, top right type 5
    // if down right cornor, down right type 6
    Qt::CursorShape shape = Qt::WaitCursor;
//    if (m_triggle.containsPoint(event->pos(), Qt::OddEvenFill)) {
//        m_triMoveType = TriMoveWhole;
//        return Qt::SizeAllCursor;
//    } else if (m_rect.contains(event->pos())) {
//        m_rectMoveType = RectMoveAll;
//        return Qt::SizeAllCursor;
//    }
    m_triMoveType = TriMovePointInvalid;
    m_rectMoveType = RectMoveInvalid;
    m_activeShape = ActiveInvalid;
    int diff = 15;
    if ((abs((event->y() - m_rect.topLeft().y())) <= diff) &&
            (abs(event->x() - m_rect.topLeft().x()) <= diff)) {
        // top left
        shape = Qt::SizeFDiagCursor;
        m_rectMoveType = RectMoveFromTopLeft;
        m_triMoveType = TriMovePointInvalid;
        m_activeShape = ActiveRect;
    } else if ((abs((event->y() - m_rect.topRight().y())) <= diff) &&
               (abs(event->x() - m_rect.topRight().x()) <= diff)) {
        // top right
        shape = Qt::SizeBDiagCursor;
        m_rectMoveType = RectMoveFromTopRight;
        m_triMoveType = TriMovePointInvalid;
        m_activeShape = ActiveRect;
    } else if ((abs((event->x() - m_rect.bottomLeft().x())) <= diff) &&
               (abs(event->y() - m_rect.bottomLeft().y()) <= diff)) {
        // bottom left
        shape = Qt::SizeBDiagCursor;
        m_rectMoveType = RectMoveFromBottomLeft;
        m_triMoveType = TriMovePointInvalid;
        m_activeShape = ActiveRect;
    } else if ((abs((event->y() - m_rect.bottomRight().y())) <= diff) &&
               (abs(event->x() - m_rect.bottomRight().x()) <= diff)) {
        // bottom right
        shape = Qt::SizeFDiagCursor;
        m_rectMoveType = RectMoveFromBottomRight;
        m_triMoveType = TriMovePointInvalid;
        m_activeShape = ActiveRect;
    } else if ((abs((event->y() - m_rect.topLeft().y())) <= diff)) {
        shape = Qt::SizeVerCursor;
        m_rectMoveType = RectMoveFromTop;
        m_triMoveType = TriMovePointInvalid;
        m_activeShape = ActiveRect;
    } else if ((abs((event->x() - m_rect.topLeft().x())) <= diff)) {
        shape = Qt::SizeHorCursor;
        m_rectMoveType = RectMoveFromLeft;
        m_triMoveType = TriMovePointInvalid;
        m_activeShape = ActiveRect;
    } else if ((abs(event->y() - m_rect.bottomRight().y()) <= diff)) {
        shape = Qt::SizeVerCursor;
        m_rectMoveType = RectMoveFromDown;
        m_triMoveType = TriMovePointInvalid;
        m_activeShape = ActiveRect;
    } else if ((abs(event->x() - m_rect.bottomRight().x()) <= diff)) {
        shape = Qt::SizeHorCursor;
        m_rectMoveType = RectMoveFromRight;
        m_triMoveType = TriMovePointInvalid;
        m_activeShape = ActiveRect;
    } else if ((abs((event->y() - m_triPoint1.y())) <= diff) &&
             (abs(event->x() - m_triPoint1.x()) <= diff)) {
        // top left
        shape = Qt::SizeAllCursor;
        m_triMoveType = TriMovePoint1;
        m_rectMoveType = RectMoveInvalid;
        m_activeShape = ActiveTriggle;
    } else if ((abs((event->y() - m_triPoint2.y())) <= diff) &&
               (abs(event->x() - m_triPoint2.x()) <= diff)){
        shape = Qt::SizeAllCursor;
        m_triMoveType = TriMovePoint2;
        m_rectMoveType = RectMoveInvalid;
        m_activeShape = ActiveTriggle;
    } else if ((abs((event->y() - m_triPoint3.y())) <= diff) &&
               (abs(event->x() - m_triPoint3.x()) <= diff)){
        shape = Qt::SizeAllCursor;
        m_triMoveType = TriMovePoint3;
        m_rectMoveType = RectMoveInvalid;
        m_activeShape = ActiveTriggle;
    }


    if (m_activeShape == ActiveInvalid) {
        // get active from event pos
        m_activeShape = getCurrentActiveShape(event->pos());
        if (m_activeShape != ActiveInvalid) {
            m_isDragging = true;
        } else {
            m_isDragging = false;
        }
    }


    if (m_triMoveType == TriMovePointInvalid && m_rectMoveType == RectMoveInvalid) {
        if (m_activeShape == ActiveRect) {
            m_rectMoveType = RectMoveAll;
            shape = Qt::SizeAllCursor;
        } else if (m_activeShape == ActiveTriggle) {
            m_triMoveType = TriMoveAll;
            shape = Qt::SizeAllCursor;
        }
    }

    qDebug() <<__func__ << __LINE__  << "shape:" << shape;
    qDebug() <<__func__ << __LINE__  << "m_triMoveType:" << m_triMoveType;
    qDebug() <<__func__ << __LINE__  << "m_rectMoveType:" << m_rectMoveType;

    return shape;
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    if (!m_isLocked) {
        // set start position
        lastPos = event->globalPos();
        this->setCursor(getCurrentCursorShape(event));
    }

    QWidget::mousePressEvent(event);
}

VideoWidget::ActiveShape VideoWidget::getCurrentActiveShape(const QPoint &point)
{
    if (m_triggle.containsPoint(point, Qt::OddEvenFill)) {
        qDebug() << __func__ << __LINE__ << "Triggle type";
        return ActiveTriggle;
    } else if (m_rect.contains(point, true)) {
        qDebug() << __func__ << __LINE__ << "ActiveRect type";
        return ActiveRect;
    } else {
        qDebug() << __func__ << __LINE__ << "invalid type";
        return ActiveInvalid;
    }
}

void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_isLocked) {
        // set end position
        m_isDragging = false;
        m_activeShape = ActiveInvalid;
        m_triMoveType = TriMovePointInvalid;
        m_rectMoveType = RectMoveInvalid;
        this->setCursor(Qt::ArrowCursor);
    }

    QWidget::mouseReleaseEvent(event);
}
