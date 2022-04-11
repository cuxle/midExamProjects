#ifndef SKIPROPEONZEROMQ_H
#define SKIPROPEONZEROMQ_H

#include <QObject>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <QDateTime>
#include "ShareMemory.h"

class SkipRopeOnZeroMq : public QObject
{
    Q_OBJECT
public:
    explicit SkipRopeOnZeroMq(QObject *parent = nullptr);
    ~SkipRopeOnZeroMq();
    bool m_bStartCount = false;

signals:
    void sigSkipCountChanged(int);
    void sigContinueRun();

public slots:
    void init();
    void handleDestroyObject();
    void setOff(int ydown);
private:
    void registerClient();
    void unregisterClient();
    void *contex = nullptr;
    void *responder = nullptr;

    void *contex1 = nullptr;
    void *responder1 = nullptr;

public slots:
    void startCount(bool);
    void resetCount();
//    void initlib();
//    void destroylib();
    void handleReceiveImage(const QImage &image);
    void handleReceiveMat(cv::Mat image);


private:
    SHAREDMEMORY sharedmem;
    std::string Model = "0";
    char get_data[10] = { 0 };
    int m_count = 0;
    bool m_isRunning = true; // false to quit
    int m_lastCount = 0;
    QDateTime m_dateTime;
};

#endif // SKIPROPEONZEROMQ_H
