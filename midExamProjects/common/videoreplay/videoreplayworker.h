#ifndef VIDEOREPLAYWORKER_H
#define VIDEOREPLAYWORKER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QSharedPointer>
#include <algorithm/ropeskipworker.h>

class QImage;

class VideoReplayWorker : public QObject
{
    Q_OBJECT
public:
    explicit VideoReplayWorker(QObject *parent = nullptr);
    ~VideoReplayWorker();
    bool m_isRunning = true;

signals:
    void sigResetCount(bool);
    void sigSendImageFromVideoReplay(const cv::Mat &image);
    void sigVideoFileLoaded(bool);
public slots:
    void init();
    void destroy();
    void startPlayVideo();
    void handleStopPlayVideo();
    void gotPlayVideoName(const QString &fileName);

private:
    QSharedPointer<cv::VideoCapture> m_capture = nullptr;
    QString m_videoName;

    double m_fps = 0;
    const quint64 m_msInOneSecond = 1000;    
};

#endif // VIDEOREPLAYWORKER_H
