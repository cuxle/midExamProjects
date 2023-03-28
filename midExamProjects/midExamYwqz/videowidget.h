#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QPixmap>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget();
    const QPixmap* pixmap() const;
    void setPixmap (const QPixmap &pixmap);
    void updateAlgorithmPos();
    enum ActiveShape {
        ActiveTriggle,
        ActiveRect,
        ActiveInvalid
    };

    enum TriggleMoveType {
        TriMovePoint1,
        TriMovePoint2,
        TriMovePoint3,
        TriMoveAll,
        TriMovePointInvalid
    };
public slots:
    void handleVideoWidgetIsLocked(bool);
    void handleResetVideoWidgetRatio();
signals:
    void sigReginPosChanged(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int lefttopx, int lefttopy, int rightdownx, int rightdowny);
    void sigReginRectChanged(int p1x, int p1y, int height, int width);
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap pix;

//    enum RectMoveType {
//        RectMoveX = 1,
//        RectMoveY = 2,
//        RectMoveXAndY = 3,
//        RectMoveHight = 4,
//        RectMoveWidth,
//        RectMoveHightAndWidth
//    };

    Qt::CursorShape getCurrentCursorShape(QMouseEvent *event);
    ActiveShape getCurrentActiveShape(const QPoint &point);

    void updateConfig();

    QRect m_rect;
    QPolygon m_triggle;

    QPoint m_triPoint1;
    QPoint m_triPoint2;
    QPoint m_triPoint3;

    QPoint m_rectLeftTop;
    QPoint m_rectRightBottom;
    int m_rectHeight;
    int m_rectWidth;

    bool m_isDragging = false;
    QPoint lastPos;
    bool m_isLocked = false;

    double m_ratioX = 0;
    double m_ratioY = 0;
    bool m_ratioCounted = false;

    ActiveShape m_activeShape = ActiveInvalid;
    TriggleMoveType m_triMoveType = TriMovePointInvalid;
    enum RectMoveType
    {
        RectMoveFromTop,
        RectMoveFromDown,
        RectMoveFromLeft,
        RectMoveFromRight,
        RectMoveFromTopLeft,
        RectMoveFromTopRight,
        RectMoveFromBottomLeft,
        RectMoveFromBottomRight,
        RectMoveAll,
        RectMoveInvalid
    } m_rectMoveType;
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // VIDEOWIDGET_H
