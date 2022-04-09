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
        /*
        // 1. 判断文件有没有打开
        if (!m_videoWriter->isOpened()) {
            AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
            m_videoPath = appconfig.m_videoSavePath;

            QString fullVideoFolder = m_videoPath + "/"+ m_fileName.split("_").first();
            QDir dir(fullVideoFolder);
            if (!dir.exists()) {
                dir.mkpath(fullVideoFolder);
            }
            int fourcc = cv::VideoWriter::fourcc('X','2','6','4');
//            qDebug() << __func__ << __LINE__ << fourcc;
            QString fullVideoName = fullVideoFolder + "/"+ m_fileName;
//            qDebug() << m_videoWriter->set(cv::VIDEOWRITER_PROP_QUALITY, 50);
            if (m_videoWriter->open(fullVideoName.toStdString(),
//                                    cv::VideoWriter::fourcc('F', 'M', 'P', '4'),
//                                    cv::CAP_MSMF,
                                    cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
//                                    cv::VideoWriter::fourcc('X', 'V', 'I', 'D'),
//                                    cv::VideoWriter::fourcc('H', '2', '6', '4'),
//                                    cv::CAP_OPENCV_MJPEG,
                                    //                                    CV_FOURCC('M', 'P', '4', '2'),
                                    25,
                                    cv::Size(1280, 1024))) {
//                qDebug() << "get " <<m_videoWriter->get(cv::VIDEOWRITER_PROP_QUALITY);
//                qDebug() << m_videoWriter->getBackendName().c_str();
//                qDebug() << "open save video " << fullVideoName << " successfully";
            } else {
                qDebug() << "open save video " << fullVideoName << " failed";
                return;
            }
        }
*/
//        if (!m_fileIsOpened) {
//            AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
//            m_videoPath = appconfig.m_videoSavePath + "/video";

//            QString fullVideoFolder = m_videoPath + "/"+ m_fileName.split("_").first();
//            QDir dir(fullVideoFolder);
//            if (!dir.exists()) {
//                dir.mkpath(fullVideoFolder);
//            }
////            int fourcc = cv::VideoWriter::fourcc('X','2','6','4');
////            qDebug() << __func__ << __LINE__ << fourcc;
//            QString fullVideoName = fullVideoFolder + "/"+ m_fileName;
////            qDebug() << m_videoWriter->set(cv::VIDEOWRITER_PROP_QUALITY, 50);

//            // 设置码率：根据所需的视频大小调整，如果(w * h / 2)得到的视频过大可以改为(w * h / 4)
//            int bitrate = (int)(m_width * m_height / 2);
//            // 帧率
//            int fps = 25;

//            if (!m_videoWriter.isNull() && m_videoWriter->open((char*)fullVideoName.toLatin1().data(), bitrate, fps, m_width, m_height) != 0) {
//                qDebug() << "open file failed";
//                return;
//            }

//            m_fileIsOpened = true;
//        }

        // 2. 确保文件打开后，保存图像
//        QImage img = image;

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


void VideoCaptureWorker::setVideoSavePath(const QString &fileName)
{
    m_videoPath = fileName;    
}

void VideoCaptureWorker::openSavedFile(const QString &fileName)
{
    if (!m_fileIsOpened) {
        AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
        m_videoPath = appconfig.m_videoSavePath + "/video";

        m_videoWriter = QSharedPointer<videoWriterFFmpeg>(new videoWriterFFmpeg);
        m_videoWriter->setCameraId(appconfig.m_deviceId.toInt());
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
