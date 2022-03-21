#include "maincounter.h"
#include <QMediaPlayer>
#include <QTimer>
#include <QLabel>

MainCounter::MainCounter(QLabel *label, QObject *parent)
    : QObject(parent),
      m_display(label)
{
    initMediaPlayer();
    initTimers();
}

void MainCounter::start()
{
//    emit sigStartCount(false);

    // 5. delay 9.5s, wait the start gun
    m_startDelayTimer->start(); // 倒计时结束开始倒计时60s backCounter

    // 6. play start mp3
    m_mp3Player->play();



//    if (!m_bVideoFileLoaded && !m_bCameraIsOpen) {
//        QMessageBox::warning(this, "Warning", tr("Please open camera or load a video file"));
//        return;
//    }

//    if (m_bVideoFileLoaded || m_bCameraIsOpen) {
//        // real start
//        // start
//        // if video is from camera start save video
//        if (m_bCameraIsOpen) {
//            // 如果是摄像头读入数据，需要输入学生ID
//            QString idText = ui->leUserId->text();
//            if (idText.isEmpty()) {
//                QMessageBox::warning(this, "Warning", "请输入考生ID");
//                return;
//            } else {
//                // 保存视频名称
//                m_videoFileName = ui->leUserId->text() + ".avi";
//            }
//            // open this at last
////            emit sigStartSaveVideo(true, m_videoFileName);
//        } else if (m_bVideoFileLoaded) {
//            // if video is from video, start play video
//            emit sigStartPlayVideo();
//        }

//        // state = 未开始  -> start = 准备阶段 --> 进入准备阶段
//        // state  = 准备阶段 or 考试阶段 -> 停止考试
//        switch (m_curState) {
//        case ExamNotStart:
//        {
//            m_curState = ExamPreparing;
//            startPrepareExam();
//            emit sigUpdateCameraSettings();
//            break;
//        }
//        case ExamPreparing:
//        case ExamIsRunning:
//        {
//            stopExamStuff();
//            break;
//        }
//        default:
//            break;

//        }
//    }
}

// stop from outer space
void MainCounter::stop()
{
    m_curState = ExamNotStart;

//    emit sigStartCount(false);
    emit sigCountFinished();

    //    m_ropeSkipWorker->m_bStartCount = false;


    if (m_backCountTimer->isActive()) {
        m_backCountTimer->stop();
    }

    if (m_startDelayTimer->isActive()) {
        m_startDelayTimer->stop();
    }

    m_curTimeLeftMs = m_totalTimeMs;
    setLeftTime(m_curTimeLeftMs);
    m_mp3Player->blockSignals(true);
    m_mp3Player->stop();
    m_mp3Player->blockSignals(false);
}

void MainCounter::initTimers()
{
    m_startDelayTimer = new QTimer(this);
    m_startDelayTimer->setInterval(9500);
    m_startDelayTimer->setTimerType(Qt::PreciseTimer);
    m_startDelayTimer->setSingleShot(true);
    connect(m_startDelayTimer, &QTimer::timeout, this, &MainCounter::handleStartExam);

    m_backCountTimer = new QTimer(this);
    m_backCountTimer->setInterval(m_internal);
    connect(m_backCountTimer, &QTimer::timeout, this, &MainCounter::updateDisplayTimer);
    m_backCountTimer->setTimerType(Qt::PreciseTimer);


}



void MainCounter::setLeftTime(int leftTimeMs)
{
    int sPart = leftTimeMs / 1000;
    int msPart = leftTimeMs % 1000;
    msPart = msPart / 10;
    QString text = QString("%1:%2").arg(sPart, 2, 10, QLatin1Char('0')).arg(msPart, 2, 10, QLatin1Char('0'));
    if (m_display == nullptr) return;
    m_display->setText(text);
}

void MainCounter::updateDisplayTimer()
{
    m_curTimeLeftMs -= m_internal;

    setLeftTime(m_curTimeLeftMs);

    if (m_curTimeLeftMs <= 0) {

        m_backCountTimer->stop();

        stop();

//        // start
//        emit sigStartSaveVideo(false, m_videoFileName);


    }

}

void MainCounter::handleStartExam()
{
    // 0. update state
    m_curState = ExamIsRunning;

    // 1. reset 60s
    m_curTimeLeftMs = m_totalTimeMs;

    // 2. skip rope dll reset count
    emit sigStartCount(true);
//    m_ropeSkipWorker->resetCount();


    // 3. start back count 60s倒计时
    m_backCountTimer->start();


}

void MainCounter::stopExamStuff()
{
    // 1. 考试结束了
//    m_curState = ExamNotStart; // ExamFinished

    // 2. 这是设置"开始" XXX
//    ui->pbStartSkip->setText(QCoreApplication::translate("FormFuncChoose", "\345\274\200\345\247\213", nullptr));

    // stop count in skip rope
//    emit sigStartCount(false);
//    m_ropeSkipWorker->m_bStartCount = false;

//    emit sigStartSaveVideo(false, m_videoFileName); // TODO when to stop save video
//    if (m_bCameraIsOpen) {
////        emit sigStartSaveVideo(false, m_videoFileName); // 摄像头没必要关吧， 暂时不关
//    }

//    if (m_bVideoFileLoaded) {
//        m_bVideoFileLoaded = false;
//        ui->stkVideoHolder->setCurrentIndex(0);
//        // TODO 如果视频没有播放完，60s结束了怎么处理呢？我们暂时假定肯定播放完
//    }

    if (m_backCountTimer->isActive()) {
        m_backCountTimer->stop();
    }

    if (m_startDelayTimer->isActive()) {
        m_startDelayTimer->stop();
    }

    m_curTimeLeftMs = m_totalTimeMs;
    setLeftTime(m_curTimeLeftMs);
    m_mp3Player->blockSignals(true);
    m_mp3Player->stop();
    m_mp3Player->blockSignals(false);
}


void MainCounter::initMediaPlayer()
{
    m_mp3Player = new QMediaPlayer(this);

    QString mediapath = "qrc:/resource/sound/skipRopeStart.mp3";

    m_mp3Player->setMedia(QUrl(mediapath));

    m_mp3Player->setVolume(100);

    // not use mediaplayer to count
//    connect(m_mp3Player, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State newState){
//       if (newState == QMediaPlayer::StoppedState) {
//           if (m_bCameraIsOpen) {
//               emit sigStartSaveVideo(false);
//           }
//       }
//    });
}
