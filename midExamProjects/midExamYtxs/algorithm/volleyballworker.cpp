#include "volleyballworker.h"
#include <QImage>
#include <iostream>
#include <QDebug>

VolleyballWorker::VolleyballWorker(QObject *parent)
    : QObject(parent)
{
//    initlib();
}

VolleyballWorker::~VolleyballWorker()
{
}

void VolleyballWorker::startCount(bool start)
{
    m_bStartCount = start;
    m_volcntlib->ResetDetector();
    m_count = 0;
}

void VolleyballWorker::resetCount()
{
    m_volcntlib->ResetDetector();
    m_count = 0;
}

void VolleyballWorker::initlib()
{
    m_volcntlib = QSharedPointer<VolleyballLib>(new VolleyballLib("./volleyball.dll"));
//    m_volcntlib = new VolleyballLib("./volleyball.dll");
}

void VolleyballWorker::destroylib()
{

}

void VolleyballWorker::handleReceiveImage(const QImage &image)
{
    if (m_bStartCount) {
        QImage img = image;
        m_count = m_volcntlib->CountVolleyball(img.height(), img.width(), img.bits());
        std::cout << "skip count:" << m_count << std::endl;
        emit sigVolCountChanged(m_count);
    }
}

void VolleyballWorker::handleReceiveImage2(cv::Mat image)
{
    if (m_bStartCount) {
//        QImage img = image;
        cv::Mat mat;
        image.copyTo(mat);
        qDebug() << __LINE__ << __func__;
        qDebug() << mat.rows << mat.cols;
        m_count = m_volcntlib->CountVolleyball(mat.rows, mat.cols, mat.data);
        std::cout << "skip count:" << m_count << std::endl;
        emit sigVolCountChanged(m_count);
//        emit sigSkipCountChanged(m_count);

    }

}

void VolleyballWorker::handleSetRectPos(int lefttopx, int lefttopy, int rightdownx, int rightdowny)
{
    m_volcntlib->SetRect(lefttopx, lefttopy, rightdownx, rightdowny);
}

