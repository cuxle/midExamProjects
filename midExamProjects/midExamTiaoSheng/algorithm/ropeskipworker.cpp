#include "ropeskipworker.h"
#include <QImage>
#include <iostream>
#include <QDebug>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <QDateTime>
#include <QThread>
#include <QCoreApplication>

RopeSkipWorker::RopeSkipWorker(QObject *parent)
    : QObject(parent)
{

}

RopeSkipWorker::~RopeSkipWorker()
{
    qDebug() << __func__;
}

void RopeSkipWorker::startCount(bool bIsCounting)
{
    m_ropeSkiplib->ResetDetector();
    m_bStartCount = bIsCounting;
}

void RopeSkipWorker::resetCount()
{
    m_ropeSkiplib->ResetDetector();
    m_count = 0;
    m_lastCount = 0;
}

void RopeSkipWorker::initSkipRope()
{
    m_ropeSkiplib = QSharedPointer<RopeSkippingLib>(new RopeSkippingLib("./pose_tracking.dll"));
}

void RopeSkipWorker::destroylib()
{
    m_isRunning = false;
}

void RopeSkipWorker::handleReceiveImage(const QImage &image)
{
    if (m_bStartCount) {
//        QImage img = image;

        cv::Mat frame(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());

        QDateTime baseTime = QDateTime::currentDateTime();
        m_count = m_ropeSkiplib->CountSkipRope(frame.rows, frame.cols, std::move(frame.data));
        qDebug() << "skip rope cost time in ms:" << -QDateTime::currentDateTime().msecsTo(baseTime);

        qDebug() << "lastcout " << m_lastCount << "count:" << m_count;
        if (m_count - m_lastCount >= 10) {
            m_lastCount = m_count;
            emit sigSkipCountChanged(m_count);
        }
    }
}

// handle image from video
void RopeSkipWorker::handleReceiveImage2(const cv::Mat &image)
{
    if (m_bStartCount) {
        cv::Mat mat;
        image.copyTo(mat);

        QDateTime baseTime = QDateTime::currentDateTime();
//        m_count = m_ropeSkiplib->CountSkipRope(mat.rows, mat.cols, mat.data);
        qDebug() << "skip rope cost time in ms:" << -QDateTime::currentDateTime().msecsTo(baseTime);

        qDebug() << "lastcout " << m_lastCount << "count:" << m_count;
        if (m_count - m_lastCount >= 10) {
            emit sigSkipCountChanged(m_count);
            m_lastCount = m_count;
        }
    }


}
