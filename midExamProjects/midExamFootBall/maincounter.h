#ifndef MAINCOUNTER_H
#define MAINCOUNTER_H

#include <QObject>


class QLabel;
class QMediaPlayer;

class MainCounter : public QObject
{
    Q_OBJECT
public:
    explicit MainCounter(QLabel *label, QObject *parent = nullptr);
    void start();
    void stop();

    enum ExamState {
        ExamNotStart,
        ExamPreparing,
        ExamIsRunning,
    };

signals:
    void sigStartCount(bool);
    void sigCountFinished();


private slots:
    void updateDisplayTimer();
    void handleStartExam();

private:
    void initMediaPlayer();
    void initTimers();
    void setLeftTime(int leftTimeMs);
    void stopExamStuff();

    QLabel *m_display = nullptr;

    QMediaPlayer *m_mp3Player = nullptr;
    QTimer *m_backCountTimer = nullptr;
    QTimer *m_startDelayTimer = nullptr;

    int m_curTimeLeftMs = 0;
    const int m_totalTimeMs = 60*1000;
    const int m_internal = 100;

     ExamState m_curState = ExamNotStart;

};

#endif // MAINCOUNTER_H
