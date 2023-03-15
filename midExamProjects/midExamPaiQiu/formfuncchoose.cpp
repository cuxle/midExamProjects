#pragma execution_character_set("utf-8")

#include "formfuncchoose.h"
#include "ui_formfuncchoose.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QFileDialog>
#include <QThread>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QStringLiteral>
#include <QFont>
#include <QToolBar>
#include <QSpacerItem>
#include <QPixmap>
#include <QTextCodec>
#include <QProcess>
#include <QModelIndex>
#include <QDesktopServices>

#include <QFontDatabase>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QDateTime>
#include "mat2qtformatmethod.h"
#include "algorithm/ropeskipworker.h"
#include "videocaptureworker.h"
#include "videowidget.h"
#include "videoreplayworker.h"

#include "settingdialog.h"
#include "networkserver.h"
#include "videowidget.h"
#include "datamanagerdb.h"


#include "singleton.h"
#include "appconfig.h"
#include <QStringLiteral>

#include "datamanager.h"

#include <QLockFile>

#include <QLocale>

FormFuncChoose::FormFuncChoose(bool online, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::FormFuncChoose),
    m_isLogin(online)
{
    ui->setupUi(this);
	
    initUi();

    initCameraWorker();

    initVideoCaptureWorker();

    // init exam time version
    //initExamTimeVersion();

    if (!m_cmdOnline) {
       initMediaPlayer();
    } else {
        ui->horizontalSpacer_31->changeSize(0, 0);
    }

    // do not open until load viddeo file
    // initVideoPlayer();

    // init timers
    initTimers();

    // init socket if online
//    if (m_cmdOnline) {
//        initSocketClient();
//    }
	
	initVolleyballWorker();

    // init school list model
    initSchoolListInterface();
	
    VideoWidget *videoWidget = static_cast<VideoWidget *>(ui->videoWidget);
    if (videoWidget != nullptr) {
        connect(this, &FormFuncChoose::sigOpenCamera, videoWidget, &VideoWidget::handleResetVideoWidgetRatio);
        connect(this, &FormFuncChoose::sigSetPlayVideoName, videoWidget, &VideoWidget::handleResetVideoWidgetRatio);
        connect(videoWidget, &VideoWidget::sigReginPosChanged, m_volleyballWorker, &VolleyballWorker::handleSetRectPos);
        connect(this, &FormFuncChoose::sigVideoWidgetIsLocked, videoWidget, &VideoWidget::handleVideoWidgetIsLocked);
    }
}

FormFuncChoose::~FormFuncChoose()
{

    qDebug() << __func__ << __LINE__;
//    if (m_cmdOnline) {
//        m_clientThread->quit();
//        m_clientThread->wait();
//    }	
//    if (m_enableStartSound) {
//        m_mp3Player->stop();
//        delete m_mp3Player;
//    }

//    disconnect(m_camera, &Camera::sigImageCapture, m_videoCapture, &VideoCaptureWorker::handleReceiveImage);

    m_cameraThread->quit();
    m_cameraThread->wait();


    m_volleyballThread->quit();
    m_volleyballThread->wait();

    m_videoCaptureThread->quit();
    m_videoCaptureThread->wait();

    qDebug() << __func__ << __LINE__;
    if (m_videoPlayerThread != nullptr) {
        m_videoPlayerThread->quit();
        m_videoPlayerThread->wait();
    }

    delete ui;
}

//void FormFuncChoose::initSitupWorker()
//{
//    m_situpWorker = new SitupWorker;
//    m_situpThread = new QThread;
//    connect(m_situpThread, &QThread::started, m_situpWorker, &SitupWorker::initlib);
//    connect(m_situpThread, &QThread::finished, m_situpWorker, &SitupWorker::deleteLater);
//    connect(m_camera, &Camera::sigImageCapture, m_situpWorker, &SitupWorker::handleReceiveImage);
//    connect(m_videoPlayer, &VideoReplayWorker::sigSendImageFromVideoReplay, m_situpWorker, &SitupWorker::handleReceiveImage2);
//    connect(this, &FormFuncChoose::sigStartCount, m_situpWorker, &SitupWorker::startCount);
//    connect(this, &FormFuncChoose::sigResetCount, m_situpWorker, &SitupWorker::resetCount);
//    connect(m_situpWorker, &SitupWorker::sigSitupCountChanged, this, &FormFuncChoose::handleSkipCountChanged);
//    m_situpThread->start();
//}

void FormFuncChoose::initVolleyballWorker()
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
	if (m_camera == nullptr) return;
    m_volleyballWorker = new VolleyballWorker;
    m_volleyballThread = new QThread;
    m_volleyballWorker->moveToThread(m_volleyballThread);
    connect(m_volleyballThread, &QThread::started, m_volleyballWorker, &VolleyballWorker::initlib);
    connect(m_volleyballThread, &QThread::finished, m_volleyballWorker, &VolleyballWorker::destroyWorker);
    if (m_camera->isOpencvCam()) {
        connect(m_camera, &Camera::sigImageCaptureMat, m_volleyballWorker, &VolleyballWorker::handleReceiveMat);
    } else {
        connect(m_camera, &Camera::sigImageCapture, m_volleyballWorker, &VolleyballWorker::handleReceiveImage);
    }
//    connect(this, &FormFuncChoose::sigSendImageFromVideo, m_volleyballWorker, &VolleyballWorker::handleReceiveImage2);
    connect(this, &FormFuncChoose::sigStartCount, m_volleyballWorker, &VolleyballWorker::startCount);
    connect(this, &FormFuncChoose::sigResetCount, m_volleyballWorker, &VolleyballWorker::resetCount);
    connect(m_volleyballWorker, &VolleyballWorker::sigVolCountChanged, this, &FormFuncChoose::handleSkipCountChanged);
    m_volleyballThread->start();
}

void FormFuncChoose::initUi()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);

    initScoreUiDisplay();

    // init common toolbar
    initCommonToolbar();

    this->setStyleSheet(QString::fromUtf8("FormFuncChoose{background-color: rgb(35, 31, 57);}"));
    const QRect rect = QApplication::desktop()->screenGeometry();
    this->setGeometry(rect);

    ui->stackedWidget->setCurrentIndex(0);
    ui->stkVideoHolder->setCurrentIndex(0);

    // no cmd online mode for ytxs
    // read m_online from settings
//    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
//    m_cmdOnline = appconfig.m_appMode == "ONLINE";
//    qDebug() << __func__ << "m_online:" << m_cmdOnline;

    ui->pbStartSkip->setHidden(m_cmdOnline);
    ui->lbClientStatus->setHidden(!m_cmdOnline);
    ui->pbOpenLocalVideoFile->setHidden(m_cmdOnline);

    // init font database
    initFontDatabase();

    connect(this, &FormFuncChoose::sigLocalStudentsDataChanged, ui->scoreManagerWidget, &ScoreManagerForm::handleUpdateScoreModel);
}


//void FormFuncChoose::initExamTimeVersion()
//{
//    AppConfig &config = Singleton<AppConfig>::GetInstance();
//    int examTime = config.m_examTime; // m_examTime 0: 60s; m_examTime 1: 30s

//    m_currentMediaFile = examTime == 0 ? m_mediapath60s : m_mediapath30s;

//    m_totalTimeMs =  examTime == 0 ? 60*1000 : 30*1000;
//}

void FormFuncChoose::initFontDatabase()
{
    int id = QFontDatabase::addApplicationFont(":/resource/font/DS-DIGIB.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    font.setPixelSize(120);
    ui->lbCurLeftTimes->setFont(font);
}

void FormFuncChoose::initTimers()
{
    m_curLocalTimer = new QTimer(this);
    m_curLocalTimer->setInterval(1000);

    connect(m_curLocalTimer, &QTimer::timeout, [&](){
        QString str = QDateTime::currentDateTime().toLocalTime().toString("yyyy-MM-dd hh:mm:ss ddd");
        ui->lbCurrentTime->setText(str);
    });
    m_curLocalTimer->start();

//    setLeftTime(m_totalTimeMs);
    setLeftTimeSeconds(0);

//    m_backCountTimer = new QTimer(this);
//    m_backCountTimer->setInterval(m_internal);
//    connect(m_backCountTimer, &QTimer::timeout, this, &FormFuncChoose::updateDisplayTimer);
//    m_backCountTimer->setTimerType(Qt::PreciseTimer);

    m_forwardCountTimer = new QTimer(this);
    m_forwardCountTimer->setInterval(m_internal);
    connect(m_forwardCountTimer, &QTimer::timeout, this, &FormFuncChoose::updateDisplayTimer);
    m_forwardCountTimer->setTimerType(Qt::PreciseTimer);

    // off line does need delay timer
    if (!m_cmdOnline) {
        m_startDelayTimer = new QTimer(this);
        m_startDelayTimer->setInterval(9000);
        m_startDelayTimer->setTimerType(Qt::PreciseTimer);
        m_startDelayTimer->setSingleShot(true);
        connect(m_startDelayTimer, &QTimer::timeout, this, &FormFuncChoose::handleStartExam);
    }

    m_3minsDelayTimer = new QTimer(this);
    m_3minsDelayTimer->setInterval(3*60*1000);
//    m_3minsDelayTimer->setInterval(20*1000);
//    m_3minsDelayTimer->setInterval(10*1000);
    connect(m_3minsDelayTimer, &QTimer::timeout, this, &FormFuncChoose::handleUploadExamedStudentsScore);
    m_3minsDelayTimer->start();
}


void FormFuncChoose::handleUploadExamedStudentsScore()
{
    NetWorkServer &server = Singleton<NetWorkServer>::GetInstance();
    server.requestFor(NetWorkServer::NetWorkServer::RequestArbitrationList);
}

//void FormFuncChoose::initSocketClient()
//{
//    qRegisterMetaType<Client::ClientState>("Client::ClientState");
//    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
//    int id = appconfig.m_deviceId.toInt();
//    QString ip = appconfig.m_platAddress;
//    m_client = new Client(id, ip);
//    m_clientThread = new QThread;
//    m_client->moveToThread(m_clientThread);
//    connect(m_clientThread, &QThread::started, m_client, &Client::initClient);
//    connect(m_clientThread, &QThread::finished, m_client, &Client::destroyClient);
////    connect(m_clientThread, &QThread::finished, m_client, &Client::deleteLater);
//    connect(m_client, &Client::sigStartTest, this, &FormFuncChoose::handleStartExamFromRemote);
//    connect(m_client, &Client::sigClientStatusChanged, this, &FormFuncChoose::handleClientStatusChanged);
//    connect(m_client, &Client::sigClientConflict, this, &FormFuncChoose::handleClientConflict);
//    m_clientThread->start();
////    m_client->updateState(Client::ClientRunning);
//}

//void FormFuncChoose::handleClientConflict()
//{
//    QMessageBox::warning(nullptr, tr("Warning!"), tr("id 已经被占用，请重新配置id"));
//}

//void FormFuncChoose::handleClientStatusChanged(Client::ClientState state)
//{
//    qDebug() << __func__ << __LINE__ << state;
//    if (state == Client::ClientOnline) {
//        ui->lbClientStatus->setText("Online");
//        ui->lbClientStatus->setStyleSheet("color: rgb(0, 255, 0);");
//    } else if (state == Client::ClientOffline) {
//        ui->lbClientStatus->setText("Offline");
//        ui->lbClientStatus->setStyleSheet("color: rgb(255, 0, 0);");
//    }
//}


void FormFuncChoose::initCommonToolbar()
{
    m_toolBarframe = new QFrame(this);
    m_toolBarframe->setMinimumHeight(60);
    m_toolBarframe->setStyleSheet("background-color: rgb(55, 50, 82);");
//    frame->setMaximumHeight(50);
    QLabel *label = new QLabel(m_toolBarframe);
//    label->setPixmap(QPixmap(":/resource/images/mainform/loginIcon.png"));
    label->setMaximumHeight(36);
    label->setMaximumWidth(36);
    label->setMinimumWidth(36);
    label->setMinimumHeight(36);

    label->setStyleSheet("border-image: url(:/resource/images/mainform/loginIcon.png);");

    QLabel *softTitle = new QLabel(m_toolBarframe);
    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei"));
    font.setPointSize(15);
    softTitle->setFont(font);
    softTitle->setText("中考体育考试软件");
//    softTitle->setText(QCoreApplication::translate("FormFuncChoose", "\345\255\246\351\200\232\344\270\255\350\200\203\344\275\223\350\202\262\350\200\203\350\257\225\350\275\257\344\273\266", nullptr));
    softTitle->setStyleSheet("color:rgb(255,255,255);");
    QPushButton *pbMainForm = new QPushButton(this);
    pbMainForm->setFlat(true);
    pbMainForm->setIcon(QIcon(":/resource/images/examPage/backStep.png"));
    pbMainForm->setStyleSheet("background-color:#373252;");
    connect(pbMainForm, &QPushButton::clicked, this, &FormFuncChoose::on_pbMainForm_clicked);

    QSpacerItem *hSpaceItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(label);
    hlayout->addWidget(softTitle);
    hlayout->addItem(hSpaceItem);
    hlayout->addWidget(pbMainForm);
    m_toolBarframe->setLayout(hlayout);

    QVBoxLayout *vlayout1 = new QVBoxLayout(this);
    vlayout1->addWidget(m_toolBarframe);
    vlayout1->addWidget(ui->stackedWidget);
    vlayout1->setMargin(0);
    this->setLayout(vlayout1);
}

void FormFuncChoose::handleStartExam()
{
    QTimer::singleShot(1000, [&](){
		if (m_dingPlayer == nullptr || m_mp3Player == nullptr) return;
        qDebug() << __func__ << __LINE__ << (m_dingPlayer == nullptr);
        m_dingPlayer->stop();
        m_mp3Player->stop();
    });
    // 0. update state
    m_curExamState = ExamIsRunning;

    // 1. reset 60s
    m_curTimeLeftMs = m_totalTimeMs;  

    // 2. skip rope dll reset count
//    m_skipRopeZeroMq->resetCount();
//    m_skipRopeZeroMq->m_bStartCount = true;
//    m_ropeSkipWorker->resetCount();
//    m_ropeSkipWorker->m_bStartCount = true;
//    emit sigResetCount();
//    m_volleyballWorker->m_bStartCount = true;

    emit sigStartCount(true);

    // 3. start back count 60s倒计时

    // record start time for exam
    recordStudentExamInfo(ExamStart);

    m_forwardCountTimer->start();
}

void FormFuncChoose::recordStudentExamInfo(ExamAction action)
{
    if (m_curExamMode != ExamModeFromCamera) return;
    QDateTime dateTime = QDateTime::currentDateTime();
    QLocale local = QLocale::English;
    QString dataTime = local.toString(dateTime, Utils::strFormat);
//    QDateTime dataTime = QDateTime::currentDateTime().toLocalTime();
    switch (action) {
    case ExamStart:
    {
        // record start time for exam
        if (m_curStudent.isValid) {
            if (m_curExamCount == 1) {
                m_curStudent.examTime = dataTime;
                m_curStudent.examStartFirstTime = dataTime;
            } else if (m_curExamCount == 2) {
                m_curStudent.examStartSecondTime = dataTime;
            } else if (m_curExamCount == 3) {
                m_curStudent.examStartThirdTime = dataTime;
            }
        }
        break;
    }
    case ExamStopFinish:
    {
        // when one exam test stoped
        // save exam score and time
        if (m_curStudent.isValid) {
            if (m_curExamCount == 1) {
                m_curStudent.firstScore = m_curSkipCount;
                qDebug() << __func__ << __LINE__ << m_curStudent.firstScore;
                m_curStudent.examStopFirstTime = dataTime;
            } else if (m_curExamCount == 2) {
                m_curStudent.secondScore = m_curSkipCount;
                qDebug() << __func__ << __LINE__ << m_curStudent.secondScore;
                m_curStudent.examStopSecondTime = dataTime;
            } else if (m_curExamCount == 3) {
                m_curStudent.thirdScore = m_curSkipCount;
                m_curStudent.examStopThirdTime = dataTime;
            }
        }
        break;
    }
    case ExamMidStop:
    {
        if (m_curStudent.isValid) {
            if (m_curExamCount == 1) {
                m_curStudent.midStopFirst = true;
                m_curStudent.firstScore = m_curSkipCount;
                m_curStudent.examStopFirstTime = dataTime;
            } else if (m_curExamCount == 2) {
                m_curStudent.midStopSecond = true;
                m_curStudent.secondScore = m_curSkipCount;
                m_curStudent.examStopSecondTime = dataTime;
            } else if (m_curExamCount == 3) {
                m_curStudent.midStopThird = true;
                m_curStudent.thirdScore = m_curSkipCount;
                m_curStudent.examStopThirdTime = dataTime;
            }
        }
        break;
    }
    default:
        break;
    }
}

void FormFuncChoose::handleStartExamFromRemote(bool start)
{
    on_pbStartSkip_clicked();
}

void FormFuncChoose::handleCameraStateChanged(CameraState state)
{
    switch (state) {
    case CameraOpened:
        m_bCameraIsOpen = true;
        m_curExamMode = ExamModeFromCamera;
        break;
    case CameraNotFound:
        QMessageBox::warning(this, "Camera Info:", "Camera Not Found!");
        ui->stkVideoHolder->setCurrentIndex(0);
        m_curExamMode = ExamModeInvalid;
        break;
    case CameraClosed:
        m_bCameraIsOpen = false;
        m_curExamMode = ExamModeInvalid;
        break;
    default:
        break;

    }
}

void FormFuncChoose::setVideoName(const QString &newVideoName)
{
    m_videoFileName = newVideoName;
}

void FormFuncChoose::setLeftTimeSeconds(int forwardSeconds)
{
    int mPart = forwardSeconds / 60;
    int sPart = forwardSeconds % 60;
    QString text = QString("%1:%2").arg(mPart, 2, 10, QLatin1Char('0')).arg(sPart, 2, 10, QLatin1Char('0'));
    ui->lbCurLeftTimes->setText(text);
}

void FormFuncChoose::setLeftTime(int leftTimeMs)
{
    int sPart = leftTimeMs / 1000;
    int msPart = leftTimeMs % 1000;
    msPart = msPart / 10;
    QString text = QString("%1:%2").arg(sPart, 2, 10, QLatin1Char('0')).arg(msPart, 2, 10, QLatin1Char('0'));
    ui->lbCurLeftTimes->setText(text);
}

void FormFuncChoose::resetAllSkipCounterBeforeExam()
{
    // clear ui
    ui->lbScoreFirst->setText(QString::number(0));
    ui->lbScoreSecond->setText(QString::number(0));
    ui->lbScoreThird->setText(QString::number(0));
    ui->lbScoreFinal->setText(QString::number(0));


    m_skipCountFromDll = 0;

    m_curSkipCount = 0;

    m_skipCountMinus = 0;

//    handleSkipCountChanged(0);
}
void FormFuncChoose::resetSkipCounterBeforeSubExam()
{
    if (m_curScoreLabel == ui->lbScoreFirst) {
        ui->lbScoreFirst->setText(QString::number(0));
        ui->lbScoreSecond->setText(QString::number(0));
        ui->lbScoreThird->setText(QString::number(0));
        ui->lbScoreFinal->setText(QString::number(0));
    }

    m_skipCountFromDll = 0;

    m_curSkipCount = 0;

    m_skipCountMinus = 0;

//    handleSkipCountChanged(0);
}

void FormFuncChoose::startPrepareExam()
{
    // update positon
    VideoWidget *videoWidget = static_cast<VideoWidget *>(ui->videoWidget);
    if (videoWidget != nullptr) {
        videoWidget->updateAlgorithmPos();
    }
    if (m_isLogin) {
        m_3minsDelayTimer->stop();
    }

    // 2.清零计数
    resetSkipCounterBeforeSubExam();

    if (m_cmdOnline) {
        handleStartExam();
    } else {
        // 1."开始" 按钮变为 "停止"
        ui->pbStartSkip->setText("停止");
        ui->pbStartSkip->setStyleSheet("border-image: url(:/resource/images/examPage/stopBtn.png); \
                                       font: 25 21pt \"Microsoft YaHei\";");

        // move to MainCounter start
        // 4. skip rope线程暂时停止工作, 只在60s内计数
        emit sigStartCount(false);

        // 5. delay 9.5s, wait the start gun
        m_startDelayTimer->start(); // 倒计时结束开始倒计时60s backCounter

        if (m_enableStartSound) {
            // 6. play start mp3
            m_mp3Player->stop();
            m_mp3Player->play();
        }
        // move to MainCounter start
    }
}

void FormFuncChoose::initSchoolListInterface()
{
    NetWorkServer &server = Singleton<NetWorkServer>::GetInstance();
    m_schoolListModel = new SchoolListTableModel(this);
    m_schoolListModel->setTable("schools");
//    m_schoolListModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_schoolListModel->select();
    ui->tableViewDataDownload->setModel(m_schoolListModel);
    ui->tableViewDataDownload->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableViewDataDownload->horizontalHeader()->setHidden(true);
    ui->tableViewDataDownload->verticalHeader()->setHidden(true);
    handleUpdateSchoolListView();
    connect(&server, &NetWorkServer::sigSchoolDataDownloaded, this, &FormFuncChoose::handleUpdateSchoolListView);
    connect(&server, &NetWorkServer::sigSchoolListDataChanged, this, &FormFuncChoose::handleUpdateSchoolListView);
//    connect(&server, &NetWorkServer::sigSchoolListDataChanged, m_schoolListModel, &SchoolListTableModel::schoolListDataChanged);

}

void FormFuncChoose::handleUpdateSchoolListView()
{
    m_schoolListModel->updateModel();
    m_schoolListModel->select();
    for (int col = 0; col < 4; col++)
    {
        ui->tableViewDataDownload->setColumnWidth(col, 250);
    }
}

void FormFuncChoose::resetScoreLabel()
 {
     ui->lbScoreFirst->clear();
     ui->lbScoreSecond->clear();
     ui->lbScoreThird->clear();
     ui->lbScoreFinal->clear();

     m_curExamCount = 0;

     shiftScoreLabel();
 }

void FormFuncChoose::shiftScoreLabel()
{
    // 0. shift score label
    m_preScoreLabel = m_curScoreLabel;
    if (m_examCount > m_curExamCount) {
        // cur = 0
        if (m_curExamCount == 0) {            
            m_curScoreLabel = ui->lbScoreFirst;
        } else if (m_curExamCount == 1) {
        // cur = 1
            m_curScoreLabel = ui->lbScoreSecond;
        } else if (m_curExamCount == 2) {
        // cur = 2
            m_curScoreLabel = ui->lbScoreThird;
        }
        m_curExamCount++;
        // 归位的操作放在结束考试的停止地方
//        if (m_curExamCount == m_examCount) {
//            m_curExamCount = 0;
//        }
    }
    if (m_preScoreLabel != nullptr) {
        m_preScoreLabel->setFont(m_notChoosenFont);
        m_preScoreLabel->setStyleSheet(m_notChoosenColor);
    }
    if (m_curScoreLabel != nullptr) {
        m_curScoreLabel->setStyleSheet(m_choosenColor);
        m_curScoreLabel->setFont(m_choosenFont);
        //m_curScoreLabel->setText(QString::number(0));
    }
}

void FormFuncChoose::updateDisplayTimer()
{
    m_curForwardSeconds++;

    setLeftTimeSeconds(m_curForwardSeconds);

    // this paiqiu will not end until the stop button is pushed
    return; 

}

void FormFuncChoose::saveAndUploadStudentScore()
{
    if (m_curExamMode  != ExamModeFromCamera) return;
    // 此时保存考生数据为未上传状态， 等下边与服务器交互完成后，会再次保存
    DataManagerDb &dataManager = Singleton<DataManagerDb>::GetInstance();
    if (m_curStudent.isValid) {
        QSqlError error = DataManagerDb::addScore(m_curStudent);
        dataManager.m_uploadStudentQueue.push_back(m_curStudent);

        NetWorkServer &server = Singleton<NetWorkServer>::GetInstance();
        server.requestFor(NetWorkServer::RequestUploadStudentScore);
    }
    emit sigLocalStudentsDataChanged();

    if (m_isLogin) {
        m_3minsDelayTimer->start();
    }
}

void FormFuncChoose::clearStudentUiInfoWithNoUserId()
{
    //ui->leUserId->clear();
    ui->leUserGender->clear();
    ui->leUserName->clear();
    ui->leUserSchool->clear();
}

void FormFuncChoose::clearStudentUiInfo()
{
    ui->leUserId->clear();
    ui->leUserGender->clear();
    ui->leUserName->clear();
    ui->leUserSchool->clear();
}

void FormFuncChoose::closeEvent(QCloseEvent *event)
{
    qDebug() << __func__ << __LINE__;
//    if (m_curExamState == ExamIsRunning) {
//        stopExamStuff();
//    }
    emit sigStartSaveVideo(false);
    //QThread::msleep(2*1000);
    emit sigCloseCamera();
    //QThread::msleep(2*1000);
    QDialog::closeEvent(event);
}

void FormFuncChoose::initMediaPlayer()
{
    if (m_enableStartSound) {
        m_mp3Player = new QMediaPlayer(this);
	    m_mp3Player->setMedia(QUrl(m_mediapath));
	    m_mp3Player->setVolume(100);

        m_dingPlayer = new QMediaPlayer(this);
        m_dingPlayer->setMedia(QUrl(m_mediaDingPath));
        m_dingPlayer->setVolume(100);

//	    connect(m_mp3Player, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State newState){
//	       if (newState == QMediaPlayer::StoppedState) {
//	           if (m_bCameraIsOpen) {
//	               emit sigStartSaveVideo(false);
//	           }
//	       }
//	        });
    }

}

void FormFuncChoose::initCameraWorker()
{
    qRegisterMetaType<QImage>("QImage");
    qRegisterMetaType<CameraState>("CameraState");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    bool useOpenCvCamera = false;
    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
    if (appconfig.m_camera == 1) {
        useOpenCvCamera = true;
    }
    m_camera = new Camera(useOpenCvCamera);
    m_cameraThread = new QThread;
    m_camera->moveToThread(m_cameraThread);
    connect(m_cameraThread, &QThread::started, m_camera, &Camera::initCamera);
//    connect(m_cameraThread, &QThread::finished, m_camera, &Camera::deleteLater);
    connect(m_cameraThread, &QThread::finished, m_camera, &Camera::destoryCamera);
    connect(this, &FormFuncChoose::sigOpenCamera, m_camera, &Camera::openCamera);
    connect(this, &FormFuncChoose::sigCloseCamera, m_camera, &Camera::closeCamera);
    connect(m_camera, &Camera::sigCameraState, this, &FormFuncChoose::handleCameraStateChanged);
    if (m_camera->isOpencvCam()) {
        connect(m_camera, &Camera::sigImageCaptureMat, this, &FormFuncChoose::updateImageDisplayMat);
    } else {
        connect(m_camera, &Camera::sigImageCapture, this, &FormFuncChoose::updateImageDisplay);
    }
    connect(this, &FormFuncChoose::sigUpdateCameraSettings, m_camera, &Camera::updateCameraSettings);

    m_cameraThread->start();
//    m_cameraThread->setPriority(QThread::TimeCriticalPriority);
}


//void FormFuncChoose::initRopeSkipWorker()
//{
//    qRegisterMetaType<cv::Mat>("cv::Mat");
//    m_ropeSkipWorker = new RopeSkipWorker;
//    m_ropeSkipThread = new QThread;
//    m_ropeSkipWorker->moveToThread(m_ropeSkipThread);
//    connect(m_ropeSkipThread, &QThread::started, m_ropeSkipWorker, &RopeSkipWorker::initSkipRope);
//    connect(m_ropeSkipThread, &QThread::finished, m_ropeSkipWorker, &RopeSkipWorker::deleteLater);
//    connect(m_camera, &Camera::sigImageCapture, m_ropeSkipWorker, &RopeSkipWorker::handleReceiveImage);
//    connect(this, &FormFuncChoose::sigStartCount, m_ropeSkipWorker, &RopeSkipWorker::startCount);
//    connect(this, &FormFuncChoose::sigResetCount, m_ropeSkipWorker, &RopeSkipWorker::resetCount);
//    connect(m_ropeSkipWorker, &RopeSkipWorker::sigSkipCountChanged, this, &FormFuncChoose::handleSkipCountChanged);
//    m_ropeSkipThread->start();
////    m_ropeSkipThread->setPriority(QThread::TimeCriticalPriority);
//}

//void FormFuncChoose::initinitRopeSkipWorkerZmq()
//{
//    qRegisterMetaType<cv::Mat>("cv::Mat");
//    m_skipRopeZeroMq = new SkipRopeOnZeroMq;
//    m_skipRopeZeroMqThread = new QThread;
//    m_skipRopeZeroMq->moveToThread(m_skipRopeZeroMqThread);
//    connect(m_skipRopeZeroMqThread, &QThread::started, m_skipRopeZeroMq, &SkipRopeOnZeroMq::init);
//    connect(m_skipRopeZeroMqThread, &QThread::finished, m_skipRopeZeroMq, &SkipRopeOnZeroMq::deleteLater);
//    connect(m_camera, &Camera::sigImageCapture, m_skipRopeZeroMq, &SkipRopeOnZeroMq::handleReceiveImage);
////    connect(this, &FormFuncChoose::sigSendMatFrame, m_skipRopeZeroMq, &SkipRopeOnZeroMq::handleReceiveImage2);
//    connect(this, &FormFuncChoose::sigStartCount, m_skipRopeZeroMq, &SkipRopeOnZeroMq::startCount);
//    connect(this, &FormFuncChoose::sigResetCount, m_skipRopeZeroMq, &SkipRopeOnZeroMq::resetCount);
//    connect(m_skipRopeZeroMq, &SkipRopeOnZeroMq::sigSkipCountChanged, this, &FormFuncChoose::handleSkipCountChanged);
//    m_skipRopeZeroMqThread->start();

//}

void FormFuncChoose::initVideoCaptureWorker()
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    // init opencv capture worker
    m_videoCapture = new VideoCaptureWorker;
    m_videoCaptureThread = new QThread;
    m_videoCapture->moveToThread(m_videoCaptureThread);
    connect(m_videoCaptureThread, &QThread::started, m_videoCapture, &VideoCaptureWorker::initWorker);
    connect(m_videoCaptureThread, &QThread::finished, m_videoCapture, &VideoCaptureWorker::destroyWorker);
//    connect(m_videoCaptureThread, &QThread::finished, m_videoCapture, &VideoCaptureWorker::deleteLater);
//    connect(m_videoCaptureThread, &QThread::finished, m_videoCaptureThread, &QThread::deleteLater);

    if (m_camera->isOpencvCam()) {
        connect(m_camera, &Camera::sigImageCaptureMat, m_videoCapture, &VideoCaptureWorker::handleReceiveMat);
    } else {
        connect(m_camera, &Camera::sigImageCapture, m_videoCapture, &VideoCaptureWorker::handleReceiveImage);
    }
    connect(this, &FormFuncChoose::sigSetVideoPath, m_videoCapture, &VideoCaptureWorker::setVideoSavePath);
    connect(this, &FormFuncChoose::sigStartSaveVideo, m_videoCapture, &VideoCaptureWorker::setSaved);
    m_videoCaptureThread->start();
//    m_videoCaptureThread->setPriority(QThread::TimeCriticalPriority);
}

void FormFuncChoose::initVideoPlayer()
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    m_videoPlayer = new VideoReplayWorker;
    m_videoPlayerThread = new QThread;
    m_videoPlayer->moveToThread(m_videoPlayerThread);
    connect(m_videoPlayerThread, &QThread::started, m_videoPlayer, &VideoReplayWorker::init);
    connect(m_videoPlayerThread, &QThread::finished, m_videoPlayer, &VideoReplayWorker::deleteLater);

    connect(this, &FormFuncChoose::sigStartPlayVideo, m_videoPlayer, &VideoReplayWorker::startPlayVideo);
    connect(m_videoPlayer, &VideoReplayWorker::sigSendMatFromVideoReplay, this, &FormFuncChoose::updateImageDisplayMat);

    connect(this, &FormFuncChoose::sigStopVideoPlay, m_videoPlayer, &VideoReplayWorker::handleStopPlayVideo);
    // load frame direcetly from videoreplayworker
//    connect(m_videoPlayer, &VideoReplayWorker::sigSendImageFromVideoReplay, m_skipRopeZeroMq, &SkipRopeOnZeroMq::handleReceiveImage2);
//    connect(m_videoPlayer, &VideoReplayWorker::sigResetCount, m_skipRopeZeroMq, &SkipRopeOnZeroMq::resetCount);

    connect(m_videoPlayer, &VideoReplayWorker::sigSendMatFromVideoReplay, m_volleyballWorker, &VolleyballWorker::handleReceiveMat);
    connect(m_videoPlayer, &VideoReplayWorker::sigResetCount, m_volleyballWorker, &VolleyballWorker::resetCount);


    connect(m_videoPlayer, &VideoReplayWorker::sigVideoFileLoaded, this, &FormFuncChoose::handleLoadFileFinished);
    connect(this, &FormFuncChoose::sigSetPlayVideoName, m_videoPlayer, &VideoReplayWorker::gotPlayVideoName);
    m_videoPlayerThread->start();
    m_videoPlayerThread->setPriority(QThread::TimeCriticalPriority);
}

void FormFuncChoose::handleLoadFileFinished(bool loaded)
{
    m_bVideoFileLoaded = loaded;
    if (!m_bVideoFileLoaded) {
        QMessageBox::warning(this, "Warning", tr("打开视频失败"));
        ui->stkVideoHolder->setCurrentIndex(0);

    }
    qDebug() << "m_bVideoFileLoaded:" << m_bVideoFileLoaded;
}

void FormFuncChoose::updateImageDisplay(const QImage &img)
{    
    QImage image = img.rgbSwapped();
    QPixmap pix = QPixmap::fromImage(image);

    VideoWidget *video = (VideoWidget*)ui->videoWidget;
    if (video != nullptr) {
        video->setPixmap(pix);
    }
}

void FormFuncChoose::updateImageDisplayMat(const cv::Mat &mat)
{
    QPixmap pix = CV2QTFORMAT::cvMatToQPixmap(mat);
    VideoWidget *videoWidget = (VideoWidget*)ui->videoWidget;
    videoWidget->setPixmap(pix);
}

void FormFuncChoose::handleSkipCountChanged(int skipCount)
{    
    if (skipCount != m_skipCountFromDll) {
        m_skipCountFromDll = skipCount;
        if (m_curScoreLabel == nullptr) {
            qDebug() << "m_curScoreLabel == nullptr";
            return;
        }

        m_curSkipCount = skipCount - m_skipCountMinus;

        m_curScoreLabel->setText(QString::number(m_curSkipCount));

        handlePlayDingSound();
    }
}

void FormFuncChoose::on_pbStartTest_clicked()
{
    // 显示 学生信息， 登录， 视频采集，成绩互动   
    ui->stackedWidget->setCurrentIndex(PageTest);

    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
    // if appconfig m_videoPath isEmpty or dir not exists pop up messagebox
    QString videoPath = appconfig.m_videoSavePath;
    QDir dir(videoPath);
    if (videoPath.isEmpty() || !dir.exists()) {
        QMessageBox::warning(this, "Warning!", "请设置有效的视频保存路径");
    }
}

void FormFuncChoose::on_pbDataManage_clicked()
{
    // 数据管理
    ui->stackedWidget->setCurrentIndex(PageDataManage);
}

void FormFuncChoose::on_pbSetup_clicked()
{
    // 设置 配置信息
    // show setting dialog
    if (m_settingDialog.isNull()) {
        m_settingDialog = QSharedPointer<SettingDialog>(new SettingDialog());
        m_settingDialog->setWindowModality(Qt::ApplicationModal);
        connect(m_settingDialog.data(), &SettingDialog::sigReStartApp, [&](){
            AppConfig &config = Singleton<AppConfig>::GetInstance();
            config.deleteLater();
            this->close();
            qApp->exit(RETCODE_RESTART);
//            this->close();
        });
    }
    m_settingDialog->exec();
}

//void FormFuncChoose::on_pbStepBack_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(PageMenu);
//}

void FormFuncChoose::on_pbExit_clicked()
{
    this->close();
}

void FormFuncChoose::on_pbMainForm_clicked()
{

    // 1. page = 0 Menu, exit;
    // 2. page = 1 Test, go to Menu
    // 3. page = PageDataManage, go to Menu
    // 4. page = PageSetup, go to Menu
    // 5. page = PageDataDownload, go to PageDataManage
    // 6. page = PageDataImport, go to PageDataManage
    // 7. page = PageScoreManage, go to PageDataManage

    int index = ui->stackedWidget->currentIndex();
    int gotoIndex = -1;
    switch (index) {
    case PageMenu:
        gotoIndex = -1;
        break;
    case PageTest:

        /* comment this code because slib back video widget will stuck
         * and have to reset the app
        stopExamStuff();
//        qDebug() << __func__ << __LINE__ << m_bCameraIsOpen;
        if (m_bCameraIsOpen) {
            emit sigCloseCamera();
            ui->stkVideoHolder->setCurrentIndex(1);
            m_curExamMode = ExamModeInvalid;
        }
        */
    case PageDataManage:
    case PageSetup:
        gotoIndex = PageMenu;
        break;
    case PageDataDownload:
    case PageDataImport:
    case PageScoreManage:
        gotoIndex = PageDataManage;
        break;
    default:
        return;
    }
    if (gotoIndex == -1) {

        this->close();
        return;
    }

    if (gotoIndex >= ui->stackedWidget->count()) {
        return;
    }

    ui->stackedWidget->setCurrentIndex(gotoIndex);
}

void FormFuncChoose::on_pbBackMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(PageMenu);
}

//void FormFuncChoose::on_pbBackMenu_2_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(PageMenu);
//}

void FormFuncChoose::on_pbDataDownload_clicked()
{
    ui->stackedWidget->setCurrentIndex(PageDataDownload);   
}

void FormFuncChoose::on_pbDataImport_clicked()
{
    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
    QString execl = QFileDialog::getOpenFileName(this, "Open Execl", appconfig.m_videoSavePath, tr("Xlsx Files (*.xlsx)"));
    DataManagerDb::addStudentsFromExecl(execl);
}

void FormFuncChoose::on_pbScoreManage_clicked()
{
    // parse students json file into this qtable widget
    // qtable widget is enougth
    qDebug() << __func__ << __LINE__;    
    ui->stackedWidget->setCurrentIndex(PageScoreManage);
    m_toolBarframe->setHidden(true);
}

void FormFuncChoose::on_pbGoBackDataDownload_clicked()
{
    ui->stackedWidget->setCurrentIndex(PageDataManage);
}

void FormFuncChoose::on_pbGoBackFromDataImport_clicked()
{
    ui->stackedWidget->setCurrentIndex(PageDataManage);
}

void FormFuncChoose::on_pbGoBackFromScoreManage_clicked()
{
    ui->stackedWidget->setCurrentIndex(PageDataManage);
    m_toolBarframe->setHidden(false);
}

void FormFuncChoose::on_pbExport_clicked()
{
    // export data from model to a dictionary

}

void FormFuncChoose::on_pbHome_clicked()
{
    // tabel view go to home
}

void FormFuncChoose::on_pbPrePage_clicked()
{
    // tabel view go to previous page
}

void FormFuncChoose::on_pbNextPage_clicked()
{
    // tabel view go to next page
}

void FormFuncChoose::on_pbCancelSetting_clicked()
{
    ui->stackedWidget->setCurrentIndex(PageMenu);
}

void FormFuncChoose::on_pbSaveSetting_clicked()
{
    // save settings in ini file
}

void FormFuncChoose::on_pbOpenLocalFile_clicked()
{
    // 1. get video file
    // 2. open video file
    // 3. start playing
}


void FormFuncChoose::on_pbOpenIpc_clicked()
{
    // 1. open camera
    // success ?
        // 2. switch tabwidget to index 1
    ui->stkVideoHolder->setCurrentIndex(1);
    emit sigOpenCamera();
}

void FormFuncChoose::startSkipStuff()
{
    // 1."开始" 按钮变为 "停止"
    ui->pbStartSkip->setText("停止");
    ui->pbStartSkip->setStyleSheet("border-image: url(:/resource/images/examPage/stopBtn.png); \
                                   font: 25 21pt \"Microsoft YaHei\";");

    // 2.清零计数
    m_skipCountMinus = 0;

    handleSkipCountChanged(0);

    // 4. skip rope线程暂时停止工作, 只在60s内计数
    emit sigStartCount(false);

    // 5. delay 9.5s, wait the start gun
    m_startDelayTimer->start(); // 倒计时结束开始倒计时60s backCounter

    if (m_enableStartSound) {
        // 6. play start mp3
        m_mp3Player->play();
    }
}

// 排球的停止必须手动停止，手动停止分为两种情况
// 1. 记录第一次成绩
// 2. 记录第二次成绩，并且保存成绩，若在线，发送成绩给服务器
void FormFuncChoose::stopExamStuff()
{
    // 0. exam count count count
    // 这是一个考生的最后一次，记录本地成绩，上传考生成绩到服务器
    if (m_curExamCount == m_examCount) {
        if (m_curExamMode == ExamModeFromCamera) {
            saveAndUploadStudentScore();
        }
        ui->lbScoreFinal->setText(Utils::calculateFinalScoreForCount(m_curStudent));

        m_curExamCount = 0;
        clearStudentUiInfo();
    }

    // 1. 考试结束了
    m_curExamState = ExamNotStart; // ExamFinished

    // 2. 这是设置"开始" XXX
    ui->pbStartSkip->setText("开始");
    ui->pbStartSkip->setStyleSheet("border-image: url(:/resource/images/examPage/startBtn.png); \
                                   font: 25 21pt \"Microsoft YaHei\";");
//    ui->pbStartSkip->setText(QCoreApplication::translate("FormFuncChoose", "\345\274\200\345\247\213", nullptr));

    // stop count in skip rope
    emit sigStartCount(false);    
//    m_skipRopeZeroMq->m_bStartCount = false;m_vol
//    m_ropeSkipWorker->m_bStartCount = false;
//    m_situpWorker->m_bStartCount = false;
    m_volleyballWorker->m_bStartCount = false;
    if (m_curExamMode == ExamModeFromCamera) {
        emit sigStartSaveVideo(false, m_videoFileName); // TODO when to stop save video
    } else if (m_curExamMode == ExamModeFromVideo) {
        m_curExamMode = ExamModeInvalid;
        m_bVideoFileLoaded = false;
        ui->stkVideoHolder->setCurrentIndex(0);
        emit sigStopVideoPlay();
        // TODO 如果视频没有播放完，60s结束了怎么处理呢？我们暂时假定肯定播放完
    }

//    if (m_backCountTimer->isActive()) {
//        m_backCountTimer->stop();
//    }

    if (m_forwardCountTimer->isActive()) {
        m_forwardCountTimer->stop();
    }

    shiftScoreLabel();

//        m_curTimeLeftMs = m_totalTimeMs;
		m_curForwardSeconds = 0;
        setLeftTimeSeconds(0);
    if (!m_cmdOnline) {
        if (m_startDelayTimer->isActive()) {
            m_startDelayTimer->stop();
        }

        if (m_enableStartSound) {
            m_mp3Player->blockSignals(true);
            // this will cause bug when click start and stop diff two little time
           // QTimer::singleShot(500, [&](){
                m_mp3Player->stop();
           // });
    //        m_mp3Player->stop();
            m_mp3Player->blockSignals(false);
        }
    }
}

void FormFuncChoose::on_pbStartSkip_clicked()
{
    // 1. 前提条件 camera is open or video file is loaded
    if (m_curExamMode != ExamModeFromCamera && m_curExamMode != ExamModeFromVideo) {
        QMessageBox::warning(this, "Warning", tr("Please open camera or load a video file"));
        return;
    }

    // state = 未开始  -> start = 准备阶段 --> 进入准备阶段
    // state  = 准备阶段 or 考试阶段 -> 停止考试
    switch (m_curExamState) {
    case ExamNotStart:
    {
        m_curExamState = ExamPreparing;
//        if (m_bCameraIsOpen) {
//            emit sigUpdateCameraSettings();
//        }
        switch (m_curExamMode) {
        case ExamModeFromCamera:
        {
            // 如果是摄像头读入数据，需要输入学生ID
            QString idText = ui->leUserId->text();
            if (idText.isEmpty()) {
                QMessageBox::warning(this, "Warning", "请输入考生ID");
                return;
            } else {
                // 保存视频名称
                m_videoFileName = ui->leUserId->text();
                m_videoFileName = m_videoFileName + "_" + QDateTime::currentDateTime().toLocalTime().toString("yyyy-MM-dd-hh-m-ss") + m_saveVideoFormat;
                AppConfig &config = Singleton<AppConfig>::GetInstance();
                if (m_curStudent.isValid) {
                    m_curStudent.videoPath = config.m_videoSavePath + "/video/" + m_videoFileName.split("_").first() + "/" + m_videoFileName;
                }
            }
            // open this at last, this will cause crash now
           emit sigStartSaveVideo(true, m_videoFileName);

    //        emit sigUpdateCameraSettings();
            break;
        }

        case ExamModeFromVideo:
        {
            // if video is from video, start play video
            emit sigStartPlayVideo();

            break;
        }

        default:
            break;
        }

        // shiftScoreLabel();
        startPrepareExam();
        break;
    }
    case ExamPreparing:
    case ExamIsRunning:
    {
        recordStudentExamInfo(ExamStopFinish);
        stopExamStuff();
        break;
    }
    default:
        break;

    }
}


void FormFuncChoose::on_pbOpenLocalVideoFile_clicked()
{
    if (m_videoPlayer == nullptr) {
        initVideoPlayer();
    }
    QString filePath = QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open Video File", filePath);

    if (fileName.isEmpty()) {
        return;
    }
    qDebug() << __func__ << __LINE__ << QThread::currentThreadId();
    // set video file name and show first frame to displayer;
    emit sigSetPlayVideoName(fileName);

    ui->stkVideoHolder->setCurrentIndex(1);

    m_curExamMode = ExamModeFromVideo;
}

void FormFuncChoose::on_pbDecreaseScore_clicked()
{
    // 更改“核减”功能为“终止” 20211208
    // 只有在运行中可以核减？
    // decrease one skip by one click
//    if (m_curState == ExamIsRunning || m_curState == ExamPreparing) {
//        ui->pbDecreaseScore->setEnabled(false);
//        stopExamStuff();
//        QTimer::singleShot(500, [&](){
//            ui->pbDecreaseScore->setEnabled(true);
//        });
//    }
//    if (m_curState == ExamIsRunning) {
//        handleSkipCountChanged(m_curSkipCount - 1);
//    }
    m_skipCountMinus++;
    if (m_curScoreLabel == nullptr) {
        qDebug() << "m_curScoreLabel == nullptr" << __LINE__;
        return;
    }
    m_curSkipCount = m_skipCountFromDll - m_skipCountMinus;
    m_curScoreLabel->setText(QString::number(m_curSkipCount));
//    ui->lbScore->setText(QString::number(m_skipCountFromDll - m_skipCountMinus));
}


void FormFuncChoose::on_pbConfimUserIdBtn_clicked()
{
    ui->pbConfimUserIdBtn->setStyleSheet("background-color: rgb(61, 127, 255);\ncolor: rgb(255, 255, 255);");
    QTimer::singleShot(300, [&](){
        ui->pbConfimUserIdBtn->setStyleSheet("background-color: rgb(61, 127, 255);\ncolor: rgb(0, 0, 0);");
    });

    resetAllSkipCounterBeforeExam();

    // 只有用摄像头才需要输入考生id
    if (m_curExamMode != ExamModeFromCamera) return;

    // total aim: create an exam student
    m_currentUserId = ui->leUserId->text();
    if (m_currentUserId.isEmpty()) {
        QMessageBox::warning(nullptr, "警告:", "请输入考生考号！");
        return;
    }

    if (m_curStudent.zkh == m_currentUserId) {
        return;
    }
    m_curStudent.zkh = m_currentUserId;
    Student student = DataManagerDb::selectStudentByZkh(m_currentUserId);
    if (student.isValid) {
        m_curStudent.isValid = true;
        m_curStudent.name = student.name;
        m_curStudent.gender = student.gender;
        m_curStudent.zxdm = student.zxdm;
        m_curStudent.zxmc = student.zxmc;
        m_curStudent.id = student.id;

        ui->leUserName->setText(m_curStudent.name);
        ui->leUserGender->setText(m_curStudent.gender == 1 ? "男" : "女");
        ui->leUserSchool->setText(m_curStudent.zxmc);
    } else {
        clearStudentUiInfoWithNoUserId();
    }
    m_curStudent.uploadStatus = 0;
    m_curStudent.isOnline = m_isLogin;
    DataManagerDb manager = Singleton<DataManagerDb>::GetInstance();
    m_curStudent.examProjectName = manager.m_curExamInfo.name;
    m_curStudent.examCount = m_examCount;
    m_curStudent.isValid = true;

    m_curStudent.midStopFirst = false;
    m_curStudent.midStopSecond = false;
    m_curStudent.midStopThird = false;

    resetScoreLabel();
}


void FormFuncChoose::on_leVideoSavePath_editingFinished()
{
    m_videoFilePath = ui->leVideoSavePath->text();
    emit sigSetVideoPath(m_videoFilePath);
}

void FormFuncChoose::clearAppConfig()
{
    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
    appconfig.deleteLater();
}

void FormFuncChoose::initScoreUiDisplay()
{
    AppConfig &config = Singleton<AppConfig>::GetInstance();
    m_examCount = config.m_examNums;
    qDebug() << __func__ << __LINE__ << m_examCount;
    if (m_examCount == 1) {
        ui->gbScore2->setHidden(true);
        ui->gbScore3->setHidden(true);
    } else if (m_examCount == 2){
        ui->gbScore3->setHidden(true);
    }

    // 默认指向第一个score label
    m_curScoreLabel = ui->lbScoreFirst;

    m_choosenFont.setFamily(QString::fromUtf8("Microsoft YaHei"));
    m_choosenFont.setPixelSize(60);

    m_notChoosenFont.setFamily(QString::fromUtf8("Microsoft YaHei"));
    m_notChoosenFont.setPointSize(28);

    // bold the exam before click start
    shiftScoreLabel();
}


void FormFuncChoose::on_tableViewDataDownload_clicked(const QModelIndex &index)
{
    qDebug() << __func__ << __LINE__;
}


void FormFuncChoose::on_cbCheckAll_clicked(bool checked)
{
    DataManagerDb::checkedAllSchools(checked);
    m_schoolListModel->select();
}


void FormFuncChoose::on_pbStartDownload_clicked()
{
    // put all students to download in queue
    if (m_isLogin) {
        NetWorkServer &server = Singleton<NetWorkServer>::GetInstance();
        server.requestFor(NetWorkServer::RequestCheckedSchoolStudents);
    }
}


void FormFuncChoose::on_pbGetSchoolList_clicked()
{
    if (m_isLogin) {
        // send to server get list of all schools
        NetWorkServer &server = Singleton<NetWorkServer>::GetInstance();
        server.requestFor(NetWorkServer::RequestSchoolList);
    }
}

void FormFuncChoose::on_pbZhongTing_clicked()
{
    // 更改“核减”功能为“终止” 20211208
    // 只有在运行中可以核减？
    // decrease one skip by one click
    if (m_curExamState == ExamIsRunning) {
        if (m_curScoreLabel == nullptr) {
            qDebug() << "m_curScoreLabel == nullptr" << __LINE__;
            return;
        }
        m_curScoreLabel->setText("中停");

        recordStudentExamInfo(ExamMidStop);

        // TODO update student score info
        ui->pbZhongTing->setEnabled(false);

        QTimer::singleShot(500, [&](){
            ui->pbZhongTing->setEnabled(true);
        });
        stopExamStuff();
    }
}


//void FormFuncChoose::on_tblViewStudentData_doubleClicked(const QModelIndex &index)
//{
//    qDebug() << __func__ << __LINE__ << index.row() << index.column() << index.data();
//    if (index.column() == VideoPath) {
//        QString file = index.data().toString();
//        QFileInfo fileInfo(file);
//        QDir dir(fileInfo.absolutePath());
//        if (!dir.exists()) {
//            QMessageBox::warning(this, "警告", "文件夹不存在");
//            return;
//        }
//        QDesktopServices::openUrl(fileInfo.absolutePath());
//    }
//}

void FormFuncChoose::on_leUserId_editingFinished()
{
    qDebug() << __func__ << __LINE__ << ui->leUserId->text();
    on_pbConfimUserIdBtn_clicked();
}


void FormFuncChoose::on_pbLock_toggled(bool checked)
{
    if (checked) {
        ui->pbLock->setStyleSheet("border-image: url(:/resource/images/mainform/cbLock.png);");
    } else {
        ui->pbLock->setStyleSheet("border-image: url(:/resource/images/mainform/cbUnLock.png);");
    }
    m_isLocked = checked;
    // send signal
    emit sigVideoWidgetIsLocked(m_isLocked);
}

void FormFuncChoose::handlePlayDingSound()
{
    if (m_dingPlayer == nullptr) return;
    m_dingPlayer->stop();
    m_dingPlayer->play();
}

