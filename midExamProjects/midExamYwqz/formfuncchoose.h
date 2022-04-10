#ifndef FORMFUNCCHOOSE_H
#define FORMFUNCCHOOSE_H

#include <QDialog>
#include <QDir>
#include "scoremanagemodel.h"
//#include "studentmanager.h"
#include <opencv2/opencv.hpp>
#include "camera.h"
//#include "socket/client.h"
//#include "xlsxdocument.h"
#include "algorithm/skipropeonzeromq.h"
#include "schoollisttablemodel.h"
#include "localstudenttablemodel.h"
#include "Student.h"
#include "algorithm/situpworker.h"

class Camera;
class QThread;
class RopeSkipWorker;
class VideoCaptureWorker;
class QMediaPlayer;
class VideoReplayWorker;
class SettingDialog;
class Client;
class QFrame;

namespace Ui {
class FormFuncChoose;
}

static const int RETCODE_RESTART = 773;

class FormFuncChoose : public QDialog
{
    Q_OBJECT

public:
    explicit FormFuncChoose(bool online, SkipRopeOnZeroMq *skipRqopeMq, QDialog *parent = 0);
    ~FormFuncChoose();
    enum PageType {
        PageMenu = 0,
        PageTest,
        PageDataManage,
        PageSetup,
        PageDataDownload,
        PageDataImport,
        PageScoreManage
    };
    void setVideoName(const QString &newVideoName);

signals:
    void sigCloseLoginForm();

    void sigOpenCamera();
    void sigCloseCamera();

    // algorithm skip rope start
    void sigStartCount(bool);
    void sigResetCount();


    // set video signal
    void sigSetVideoPath(const QString &filePath);

    void sigStartSaveVideo(bool, const QString &fileName = nullptr);

    // send video
    void sigSetPlayVideoName(const QString &fileName);

    void sigSendImageFromVideo(const cv::Mat &image);

    void sigStartPlayVideo();

    void sigUpdateCameraSettings();

    void sigLocalStudentsDataChanged();

    void sigVideoWidgetIsLocked(bool);

    void sigStopVideoPlay();
private slots:

    void handleStartExamFromRemote(bool start);

    void updateImageDisplay(const QImage &img);

    void handleSkipCountChanged(int skipCount);

    void on_pbStartTest_clicked();

    void on_pbDataManage_clicked();

    void on_pbSetup_clicked();

//    void on_pbStepBack_clicked();

    void on_pbExit_clicked();

    void on_pbMainForm_clicked();

    void on_pbBackMenu_clicked();

//    void on_pbBackMenu_2_clicked();

    void on_pbDataDownload_clicked();

    void on_pbDataImport_clicked();

    void on_pbScoreManage_clicked();

    void on_pbGoBackDataDownload_clicked();

    void on_pbGoBackFromDataImport_clicked();

    void on_pbGoBackFromScoreManage_clicked();

    void on_pbSearch_clicked();

    void on_pbExport_clicked();

    void on_pbHome_clicked();

    void on_pbPrePage_clicked();

    void on_pbNextPage_clicked();

    void on_pbCancelSetting_clicked();

    void on_pbSaveSetting_clicked();

    void on_pbOpenLocalFile_clicked();

    void on_pbOpenIpc_clicked();

    void on_pbStartSkip_clicked();

    void updateDisplayTimer();

    void on_pbOpenLocalVideoFile_clicked();

    void on_pbDecreaseScore_clicked();

    void on_pbConfimUserIdBtn_clicked();

    void on_leVideoSavePath_editingFinished();

    void handleStartExam();

    void handleCameraStateChanged(CameraState);

//    void handleClientStatusChanged(Client::ClientState state);

    void handleLoadFileFinished(bool loaded);

//    void handleClientConflict();

    void on_tableViewDataDownload_clicked(const QModelIndex &index);

    void on_cbCheckAll_clicked(bool checked);

    void on_pbStartDownload_clicked();

    void on_pbGetSchoolList_clicked();

    void on_pbZhongTing_clicked();

    void on_tblViewStudentData_doubleClicked(const QModelIndex &index);

    void on_leUserId_editingFinished();
	
	void handleUploadExamedStudentsScore();

    void handlePlayDingSound();
	
	    void handleUpdateScoreModel();

    void on_pbLock_toggled(bool checked);

private:
    enum ExamAction {
        ExamStart,
        ExamStopFinish,
        ExamMidStop
    };
    void initUi();
//    void initXlsxDcoment();
    void initCameraWorker();
    void initSkipRopeZeroMq();
//    void initRopeSkipWorker();
    void initVideoCaptureWorker();
    void initVideoPlayer();
    void initCommonToolbar();
    void initFontDatabase();
    void initTimers();
//    void initSocketClient();
    //void initinitRopeSkipWorkerZmq();
   // void initSitupWorker();

    void clearAppConfig();

    void recordStudentExamInfo(ExamAction action);

    void handleResizeSchoolListView();

    Ui::FormFuncChoose *ui;

    enum ExamState {
        ExamNotStart,
        ExamPreparing,
        ExamIsRunning
    };

    enum ExamMode {
        ExamModeFromCamera,
        ExamModeFromVideo,
        ExamModeInvalid
    };

//    void initExamTimeVersion();
	
	void initScoreUiDisplay();
	
    void initMediaPlayer();

    void initTimer();

    void startSkipStuff();

    void stopExamStuff();

    void setLeftTime(int leftTimeMs);

    void startPrepareExam();

    void initSchoolListInterface();

    void initScoreModel();

    void shiftScoreLabel();

    void resetSkipCounterBeforeSubExam();

    void resetAllSkipCounterBeforeExam();

    void resetScoreLabel();

//    ScoreManageModel *m_model = nullptr;
//    QList<QSharedPointer<StudentItem>> m_students;
//    StudentManager *m_studentsManager = nullptr;
//    QSharedPointer<StudentItem>  m_curStudent;


    Camera *m_camera = nullptr;
    QThread *m_cameraThread = nullptr;

//    RopeSkipWorker *m_ropeSkipWorker = nullptr;
//    QThread *m_ropeSkipThread = nullptr;


    VideoCaptureWorker *m_videoCapture = nullptr;
    QThread *m_videoCaptureThread = nullptr;

    SkipRopeOnZeroMq *m_skipRopeZeroMq = nullptr;
//    QThread *m_skipRopeZeroMqThread = nullptr;


    bool m_bStartCapture = true;
    QString m_videoFilePath;

    VideoReplayWorker *m_videoPlayer = nullptr;
    QThread *m_videoPlayerThread = nullptr;

    int m_nWidth = 1280;
    int m_nHeight = 1024;

    int m_curTimeLeftMs = 0;
    const int m_totalTimeMs = 60*1000;
    const int m_internal = 100;


    QString m_videoFileFolder = QDir::homePath();
    QString m_currentUserId;
    QString m_videoFileName;


    QTimer *m_backCountTimer = nullptr;

    int m_curForwardSeconds = 0;

    QTimer *m_forwardCountTimer = nullptr;

    QTimer *m_curLocalTimer = nullptr;

    QTimer *m_startDelayTimer = nullptr;

    QTimer *m_3minsDelayTimer = nullptr;

    int m_curSkipCount = 0;
    int m_skipCountMinus = 0;
    int m_skipCountFromDll = 0;

    bool m_isExaming = false;

    bool m_bVideoFileLoaded = false;

    bool m_bCameraIsOpen = false;

    SettingDialog *m_settingDialog = nullptr;

    ExamState m_curExamState = ExamNotStart;
    ExamMode m_curExamMode = ExamModeInvalid;

    const bool m_cmdOnline = false;

//    Client *m_client = nullptr;

//    QThread *m_clientThread = nullptr;

private:
//     QXlsx::Document *m_xlsx = nullptr;
     void saveStudentScore();
     void saveAndUploadStudentScore();
     void clearStudentUiInfo();
     int m_rowsInXlsx = 1;
     QString m_saveVideoFormat = ".mp4";

     QFrame *m_toolBarframe = nullptr;


     SchoolListTableModel *m_schoolListModel;

     Student m_curStudent;

     LocalStudentTableModel *m_scoreModel = nullptr;
     int m_examCount = 1;
     int m_curExamCount = 0;
     QString m_examProjectName;
     QLabel *m_curScoreLabel = nullptr;
     QLabel *m_preScoreLabel = nullptr;
     QFont m_choosenFont;
     QFont m_notChoosenFont;

     bool m_isOnline = false;
     bool m_isLogin = false;
     bool m_isLocked = false;

     QString m_mediapath = "qrc:/resource/sound/skipRopeStart.mp3";
     QString m_mediaDingPath = "qrc:/resource/sound/ding.wav";
     QMediaPlayer *m_dingPlayer = nullptr;
     QMediaPlayer *m_mp3Player = nullptr;
     bool m_enableStartSound = true;
protected:
     void closeEvent(QCloseEvent *event);
};

#endif // FORMFUNCCHOOSE_H
