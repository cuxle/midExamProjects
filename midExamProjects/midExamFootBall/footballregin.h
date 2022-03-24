#ifndef FOOTBALLREGIN_H
#define FOOTBALLREGIN_H

#include <QWidget>
#include <QRect>
#include <QMenu>
#include <QPoint>

class FootballRegin : public QWidget
{
    Q_OBJECT
public:
    explicit FootballRegin(QWidget *parent = nullptr);
    void updateStudentPointPos(int x, int y);
public slots:
    void updateRectPoint(const QPoint &topLeft, const QPoint &bottomRight);
//private slots:
//    void handleLeftUpPointSet();
//    void handleRightDownPointSet();
//    void on_plot_customContextMenuRequested(const QPoint &pos);

signals:
private:
    void calculateObsStickPosition();

    QRect m_rect;
    QMenu contexMenu;

    QPoint leftUpPoint;
    QPoint rightBotomPoint;
    QPoint contexPoint;

    QPoint m_studentPos;
    QPoint followPoint;

    QVector<QPoint> m_pointPath;
    QVector<QPoint> m_stickPos;
    int minY = 10000000;
    bool isLoging;

    bool leftUpOk = false;
    bool rightDownOk = false;

    // QPaintDevice interface

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // FOOTBALLREGIN_H
