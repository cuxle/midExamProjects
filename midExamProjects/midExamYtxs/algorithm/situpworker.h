#ifndef SITUPWORKER_H
#define SITUPWORKER_H

#include <QObject>
#include "situpinterface.h"
#include <QLibrary>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

class SitupWorker : public QObject
{
    Q_OBJECT
public:
    explicit SitupWorker(QObject *parent = nullptr);
    ~SitupWorker();
    bool m_bStartCount = true;

signals:
    void sigSitupCountChanged(int);

public slots:
    void startCount(bool);
    void resetCount();
    void initlib();
    void destroylib();
    void handleReceiveImage(const QImage &image);
    void handleReceiveImage2(cv::Mat image);
    void handleSetRectPos(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int lefttopx, int lefttopy, int rightdownx, int rightdowny);

private:
    //    QLibrary lib;
    SitupLib *m_situpcntlib = nullptr;    
    int m_count = 0;

    bool m_lastUp = false;
    bool m_lastDown = false;
};

#endif // SITUPWORKER_H
