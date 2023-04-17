#include "videoreplayworker.h"
#include "Logger.h"
#include "mat2qtformatmethod.h"
#include <QImage>
#include <QDateTime>
#include <QCoreApplication>
#include <QThread>

VideoReplayWorker::VideoReplayWorker(QObject *parent)
    : QObject(parent)
{

}

VideoReplayWorker::~VideoReplayWorker()
{
    qDebug() << __func__;
}

void VideoReplayWorker::init()
{
    m_capture = QSharedPointer<cv::VideoCapture>(new cv::VideoCapture);
}

void VideoReplayWorker::destroy()
{
    m_isRunning = false;
}

void VideoReplayWorker::startPlayVideo()
{
    m_isRunning = true;

    cv::Mat frame;
    cv::Mat img;

    frame = m_capture->open(m_videoName.toStdString());
    if (!m_capture->isOpened()) {
        qDebug() << "open video failed";
        return;
    } else {
        qDebug() << "open video successfully";
    }
    quint64 i = 0;

    emit sigResetCount(true);
    cv::waitKey(10); // wait skipRopeWork start
    QDateTime baseTime = QDateTime::currentDateTime();
    int waitTime = round(m_msInOneSecond / m_fps);
    while (m_capture->read(frame)) {
//        if (count++ % 2 == 0) {
//            continue;
//        }

        cv::Mat mat;

        frame.copyTo(mat);

        emit sigSendMatFromVideoReplay(mat);

        int waitDiff = waitTime + QDateTime::currentDateTime().msecsTo(baseTime);
        if (waitDiff > 0) {
            cv::waitKey(waitDiff);
        }
//        if (cv::waitKey(waitTime) >= 0) {
//            break;
//        }

        if (i++ % 20 == 0) {
            QCoreApplication::processEvents();
        }
        if (!m_isRunning) {
            qDebug() << __func__ << __LINE__;
            m_capture->release();
            return;
        }
        baseTime = QDateTime::currentDateTime();
    }
    qDebug() << __func__ << -QDateTime::currentDateTime().msecsTo(baseTime);
    m_capture->release();
}

void VideoReplayWorker::handleStopPlayVideo()
{
    m_isRunning = false;
}

void VideoReplayWorker::gotPlayVideoName(const QString &fileName)
{
    m_videoName = fileName;

    cv::Mat frame;
    cv::Mat img;
    qDebug() << __func__ << __LINE__ << QThread::currentThreadId();

    frame = m_capture->open(fileName.toStdString());
    if (!m_capture->isOpened()) {
        qDebug() << "open video failed";
        emit sigVideoFileLoaded(false);
        return;
    } else {
        qDebug() << __func__ << __LINE__ << "open video successfully";
    }

    m_capture->read(frame);

    m_fps = m_capture->get(cv::CAP_PROP_FPS);

    emit sigSendMatFromVideoReplay(frame);

    m_capture->release();

    emit sigVideoFileLoaded(true);
}
