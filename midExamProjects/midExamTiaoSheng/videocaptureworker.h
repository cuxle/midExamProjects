#ifndef VIDEOCAPTUREWORKER_H
#define VIDEOCAPTUREWORKER_H

#include <QObject>


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

    void setSaved(bool);

private:
//    cv::VideoWriter *m_output = nullptr;
//    cv::Mat *m_frame = nullptr;
    QString m_videoPath = "./abc.avi";
    bool m_bSave = false;
};

#endif // VIDEOCAPTUREWORKER_H
