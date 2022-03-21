#ifndef ROPESKIPWORKER_H
#define ROPESKIPWORKER_H

#include <QObject>
#include "ropeskippinginterface.h"
#include <QLibrary>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <QDateTime>
#include <QSharedPointer>
#include <QMutex>
#include <QQueue>

class RopeSkipWorker : public QObject
{
    Q_OBJECT
public:
    explicit RopeSkipWorker(QObject *parent = nullptr);
    ~RopeSkipWorker();
    bool m_bStartCount = false;
signals:
    void sigSkipCountChanged(int);

public slots:
    void startCount(bool);
    void resetCount();
    void initSkipRope();
    void destroylib();
    void handleReceiveImage(const QImage &image);
    void handleReceiveImage2(const cv::Mat &image);

private:
    //    QLibrary lib;
    QSharedPointer<RopeSkippingLib> m_ropeSkiplib;
//    RopeSkippingLib *m_ropeSkiplib = nullptr;

    int m_count = 0;
    int m_lastCount = 0;
    bool m_isRunning = true; // false to quit
    QDateTime m_baseTime;

};

#endif // ROPESKIPWORKER_H
