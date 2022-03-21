#ifndef VIDEOREPLAYWORKER_H
#define VIDEOREPLAYWORKER_H

#include <QObject>

class VideoReplayWorker : public QObject
{
    Q_OBJECT
public:
    explicit VideoReplayWorker(QObject *parent = nullptr);

signals:

};

#endif // VIDEOREPLAYWORKER_H
