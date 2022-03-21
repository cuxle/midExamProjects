#include "situpworker.h"
#include <QImage>
#include <iostream>
#include <QDebug>

SitupWorker::SitupWorker(QObject *parent)
    : QObject(parent)
{
//    initlib();
}

SitupWorker::~SitupWorker()
{

}

void SitupWorker::startCount(bool start)
{
    m_bStartCount = start;
}

void SitupWorker::resetCount()
{
    m_situpcntlib->ResetDetector();
    m_count = 0;
}

void SitupWorker::initlib()
{
    qDebug() << "SitupLib!";
    m_situpcntlib = QSharedPointer<SitupLib>(new SitupLib("./situp_bg.dll"));

}

void SitupWorker::destroylib()
{
//    delete m_situpcntlib;
}

void SitupWorker::handleReceiveImage(const QImage &image)
{
    if (m_bStartCount) {
        QImage img = image;
        bool bUp;
        bool bDown;
        m_count = m_situpcntlib->CountSitup(img.height(), img.width(), img.bits(), &bUp, &bDown);
        if (m_lastDown == false && bDown == true) {
            // this is one laydown, emit a signal to mainform to "ding"
            emit sigPlayDingSound();
        }
        m_lastDown = bDown;
        if (m_lastUp == false && bUp == true) {
            // this is one situp, emit a signal to mainform to "ding"
            emit sigPlayDingSound();
        }

        m_lastUp = bUp;
        qDebug() << __func__ << __LINE__ << "bUp:" << bUp << "bDown:" << bDown;
//        std::cout << "skip count:" << m_count << std::endl;
        emit sigSitupCountChanged(m_count);
    }
}

void SitupWorker::handleReceiveImage2(const cv::Mat &image)
{
    if (m_bStartCount) {
//        QImage img = image;
        cv::Mat mat;
        image.copyTo(mat);
//        qDebug() << __LINE__ << __func__;
//        qDebug() << mat.rows << mat.cols;
        bool bUp;
        bool bDown;
        std::cout << "skip count:" << m_count << std::endl;
        m_count = m_situpcntlib->CountSitup(mat.rows, mat.cols, mat.data, &bUp, &bDown);
        if (m_lastDown == false && bDown == true) {
            // this is one laydown, emit a signal to mainform to "ding"
            emit sigPlayDingSound();
//            qDebug() << "down ding";
        }
        m_lastDown = bDown;
        if (m_lastUp == false && bUp == true) {
            // this is one situp, emit a signal to mainform to "ding"
            emit sigPlayDingSound();
//            qDebug() << "down ding";
        }
        m_lastUp = bUp;
        qDebug() << __func__ << __LINE__ << "bUp:" << bUp << "bDown:" << bDown;
//        std::cout << "skip count:" << m_count << std::endl;
        emit sigSitupCountChanged(m_count);
    }

}

void SitupWorker::handleSetRectPos(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int lefttopx, int lefttopy, int rightdownx, int rightdowny)
{
    qDebug() << __func__ << __LINE__;
    m_situpcntlib->SetRect(p1x, p1y, p2x, p2y, p3x, p3y, lefttopx, lefttopy, rightdownx, rightdowny);
}

