#include "videocaptureworker.h"
#include <QImage>
#include <QDebug>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

VideoCaptureWorker::VideoCaptureWorker(QObject *parent)
    : QObject(parent)
{


}

void VideoCaptureWorker::initWorker()
{
//    m_frame = new cv::Mat;
}

void VideoCaptureWorker::handleReceiveImage(const QImage &image)
{
    // 1. convert QImage to cv::Mat

    // 2. init video write
    if (m_bSave) {
//        QImage *img = new QImage(image);
//        cv::Mat mat;
//        cv::Mat mat(img->height(), img->width(), CV_8UC3);
//        cv::Mat mat;
//        m_frame = new cv::Mat(img->height(), img->width(), CV_8UC3, (void*)img->constBits(), img->bytesPerLine());
////        cv::Mat frame(img.height(), img.width(), CV_8UC3, img.bits());
//        if (m_output == nullptr) {
//            m_output = new cv::VideoWriter(m_videoPath.toStdString(), cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(img.width(), img.height()));
//        }
//        m_output->write(m_frame);
        qDebug() << "save frame" << __func__;
    } else {
//        if (m_output != nullptr) {
//            m_output->release();
//            m_output = nullptr;
//        }
    }
    // 3.
}

void VideoCaptureWorker::setVideoSavePath(const QString &fileName)
{
    m_videoPath = fileName;
}

void VideoCaptureWorker::setSaved(bool save)
{
    m_bSave = save;
}
