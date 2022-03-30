#ifndef VOLLEYBALLWORKER_H
#define VOLLEYBALLWORKER_H

#include <QObject>
#include "volleyballinterface.h"
#include <QLibrary>
#include <QSharedPointer>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

class VolleyballWorker : public QObject
{
    Q_OBJECT
public:
    explicit VolleyballWorker(QObject *parent = nullptr);
    ~VolleyballWorker();

    bool m_bStartCount = false;
signals:
    void sigVolCountChanged(int);

public slots:
    void startCount(bool);
    void resetCount();
    void initlib();
    void destroylib();
    void handleReceiveImage(const QImage &image);
    void handleReceiveImage2(cv::Mat image);
    void handleSetRectPos(int lefttopx, int lefttopy, int rightdownx, int rightdowny);
    void destroyWorker();


private:
    //    QLibrary lib;
    QSharedPointer<VolleyballLib> m_volcntlib;
    int m_count = 0;
};

#endif // VOLLEYBALLWORKER_H
