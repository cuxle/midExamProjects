#ifndef VIDEOCAPTUREWORKER_H
#define VIDEOCAPTUREWORKER_H

#include <QObject>
#include <QDir>
#include <QSharedPointer>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/imgproc/types_c.h>

// new lib from chunyan start
#include <videoWriterFFmpeg.h>
#include <time.h>

// new lib from chunyan end


class VideoCaptureWorker : public QObject
{
    Q_OBJECT
public:
    explicit VideoCaptureWorker(QObject *parent = nullptr);

signals:
public slots:
    void initWorker();

    void handleReceiveImage(const QImage &iamge);

    void setVideoSavePath(const QString &fileName);

    void setSaved(bool, const QString &);

    void destroyWorker();

private:
//    QSharedPointer<cv::VideoWriter> m_videoWriter = nullptr;

    QSharedPointer<videoWriterFFmpeg> m_videoWriter = nullptr;

    void openSavedFile(const QString &fileName);

    QString m_videoPath = QDir::homePath();
    QString m_fileName;
    QString m_saveVideoFormat = ".mp4";
    bool m_bSave = false;
    bool m_fileIsOpened = false;

    int m_width = 1280;
    int m_height = 1024;
};

#endif // VIDEOCAPTUREWORKER_H
