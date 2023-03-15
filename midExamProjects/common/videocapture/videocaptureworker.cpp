#include "videocaptureworker.h"
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QThread>
#include <QDateTime>
#include <QDir>

#include "appconfig.h"
#include "singleton.h"


VideoCaptureWorker::VideoCaptureWorker(QObject *parent)
    : QObject(parent)
{


}

void VideoCaptureWorker::initWorker()
{
//    m_videoWriter = QSharedPointer<cv::VideoWriter>(new cv::VideoWriter);
//    m_videoWriter = QSharedPointer<videoWriterFFmpeg>(new videoWriterFFmpeg);
    //    m_output = new cv::VideoWriter(m_videoPath.toStdString(), cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(1248, 1024));
}

void VideoCaptureWorker::destroyWorker()
{
    if (m_fileIsOpened && !m_videoWriter.isNull()) {
        m_videoWriter->close();
        m_videoWriter.clear();
    }
    this->deleteLater();
}

#if TIAOSHENG
void VideoCaptureWorker::handleReceiveImage(const QImage &image, int time)
#else
void VideoCaptureWorker::handleReceiveImage(const QImage &image)
#endif
{
    if (m_bSave) {
        cv::Mat frame(image.height(), image.width(), CV_8UC3, (uchar * *)image.bits());

        if (!m_videoWriter.isNull()) {
//            m_videoWriter->write(std::move(frame));
#if TIAOSHENG
          m_videoWriter->setDownCount(time);
#endif
            m_videoWriter->write(frame);
        }

    } else {
        if (m_fileIsOpened && !m_videoWriter.isNull()) {
            m_fileIsOpened = false;
            m_videoWriter->close();
            m_videoWriter.clear();
        }
    }
}

#if TIAOSHENG
void VideoCaptureWorker::handleReceiveMat(const cv::Mat &mat, int time)
#else
void VideoCaptureWorker::handleReceiveMat(const cv::Mat &mat)
#endif
{
    if (m_bSave) {
        if (!m_videoWriter.isNull()) {
//            m_videoWriter->write(std::move(frame));
#if TIAOSHENG
          m_videoWriter->setDownCount(time);
#endif
         // qDebug() << __func__ << __LINE__ << mat.cols << mat.rows;
            m_videoWriter->write(mat);
        }

    } else {
        if (m_fileIsOpened && !m_videoWriter.isNull()) {
            m_fileIsOpened = false;
            m_videoWriter->close();
            m_videoWriter.clear();
        }
    }
}


void VideoCaptureWorker::setVideoSavePath(const QString &fileName)
{
    m_videoPath = fileName;    
}

void VideoCaptureWorker::openSavedFile(const QString &fileName)
{

    if (!m_fileIsOpened) {
        AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
#if defined (YWQZ)
        m_width = appconfig.m_cameraWidth / 2;
        m_height = appconfig.m_cameraHeight / 2;
#else
        m_width = appconfig.m_cameraWidth;
        m_height = appconfig.m_cameraHeight;
#endif
        m_videoPath = appconfig.m_videoSavePath + "/video";

        m_videoWriter = QSharedPointer<videoWriterFFmpeg>(new videoWriterFFmpeg);

        m_videoWriter->setCameraId(appconfig.m_deviceId.toInt());

        qDebug() << __func__ << __LINE__ << fileName;

        m_videoWriter->setTimeFlag(true);



        QString fullVideoFolder = m_videoPath + "/"+ m_fileName.split("_").first();
        QDir dir(fullVideoFolder);
        if (!dir.exists()) {
            dir.mkpath(fullVideoFolder);
        }
//            int fourcc = cv::VideoWriter::fourcc('X','2','6','4');
//            qDebug() << __func__ << __LINE__ << fourcc;
        QString fullVideoName = fullVideoFolder + "/"+ m_fileName;
//            qDebug() << m_videoWriter->set(cv::VIDEOWRITER_PROP_QUALITY, 50);

        // 设置码率：根据所需的视频大小调整，如果(w * h / 2)得到的视频过大可以改为(w * h / 4)
        int bitrate = (int)(m_width * m_height / 2);
        // 帧率
        int fps = 25;

        if (!m_videoWriter.isNull() && m_videoWriter->open((char*)fullVideoName.toLatin1().data(), bitrate, fps, m_width, m_height) != 0) {
            qDebug() << "open file failed";
            return;
        }
        qDebug() << "open file successfully";
        m_fileIsOpened = true;
    }
}

void VideoCaptureWorker::setSaved(bool save, const QString &fileName)
{
    m_bSave = save;
    m_fileName = fileName;
    if (m_bSave) {
        openSavedFile(fileName);
    }
}
