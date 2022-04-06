#ifndef FORMFUNCCHOOSE_H
#define FORMFUNCCHOOSE_H

#include <QDialog>
#include <QDir>
#include "scoremanagemodel.h"
#include <opencv2/opencv.hpp>
#include "camera.h"
//#include "socket/client.h"
#include "schoollisttablemodel.h"
#include "localstudenttablemodel.h"
#include "Student.h"
#include "qcustomplot.h"

#pragma   push_macro("min")
#pragma   push_macro("max")
#undef   min
#undef   max

#include "lidar/godleilaser.h"
#include "lidar/lidarAnalysis.h"

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>


#pragma   pop_macro("min")
#pragma   pop_macro("max")

#include <QMenu>
#include <string>
//#include <qcustomplot.h>
#include <QAction>
#include <QVector>
#include <QTimer>

class QCustomPlot;
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
    explicit FormFuncChoose(bool online, QDialog *parent = 0);
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

    void sigSetReginRect(float xMin, float xMax, float yMin, float yMax);
private slots:
    void handleStudentQiangPao(bool flag);

    void handleStartExamFromRemote(bool start);

    void updateImageDisplay(const QImage &img);

//    void handleSkipCountChanged(int skipCount);

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
	
	void handleSendLoginInCmdRequest();

    void handlePlayDingSound();

    void on_pbLock_toggled(bool checked);

    void on_pbShowExamRegin_clicked();

    void on_pbConnectLeiDa_clicked();

    void handleUpdateStudentPos(const QVector<double> &vx, const QVector<double> &vy);

    void setValueRange(const QCPRange &range);

//    void setKeyRange(const QCPRange &range);

public slots:
    // update point cloud
    void handleUpdateReceivedLeidaData();

    // update normalized football or basketball regin
    void handleUpdateNormalizedData();
    void updateRectPointTopLeft(const QPoint &topLeft);
    void updateRectPointBottomRight(const QPoint &bottomRight);

private slots:
    void handleRestLidarToClose();

    void on_pbRotateLeftLeiDa_pressed();

    void handleUpdateLidarAngle();

    void on_pbRotateLeftLeiDa_released();

    void on_pbRotateRightLeiDa_pressed();

    void on_pbRotateRightLeiDa_released();

private:
    enum ExamAction {
        ExamStart,
        ExamStopFinish,
        ExamMidStop
    };
    void initUi();
//    void initXlsxDcoment();
    void initCameraWorker();
//    void initRopeSkipWorker();
    void initVideoCaptureWorker();
    void initVideoPlayer();
    void initCommonToolbar();
    void initFontDatabase();
    void initTimers();
    void initSocketClient();
    void initVolleyballWorker();
    void mapFromStdFootGroundToWidget(std::vector<PointXYZ> &objs);
    void startExamWhenStuEnterExamRegin();

    void clearAppConfig();

    void recordStudentExamInfo(ExamAction action);

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

    void setLeftTimeSeconds(int leftTimeSeconds);

    void startPrepareExam();

    void initSchoolListInterface();

    void initStudentsListInterface();

    void shiftScoreLabel();

    void resetSkipCounterDisply();

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

//    SitupWorker *m_situpWorker = nullptr;
//    QThread *m_situpThread = nullptr;

//    VolleyballWorker *m_volleyballWorker = nullptr;
//    QThread *m_volleyballThread = nullptr;


    bool m_bStartCapture = true;
    QString m_videoFilePath;

    VideoReplayWorker *m_videoPlayer = nullptr;
    QThread *m_videoPlayerThread = nullptr;

    int m_nWidth = 1280;
    int m_nHeight = 1024;

    int m_curTimeLeftMs = 0;
    const int m_totalTimeMs = 60*1000;
    const int m_internal = 10;


    QString m_videoFileFolder = QDir::homePath();
    QString m_currentUserId;
    QString m_videoFileName;
    QString m_picPathFileName;


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

    GodLeiLaser *m_godlei = nullptr;
    QThread *m_laserThread = nullptr;

    bool m_exminStudentInRegin = false;
    bool m_examFirstRunning = false;


    const double PI = 3.1415926;
    float theta2[16] = { -15, 1, -13, 3, -11, 5, -9, 7, -7, 9, -5, 11, -3, 13, -1, 15 };
    float theta133[16] = { -10, 0.665, -8.665, 2, -7.33, 3.33, -6, 4.665, -4.665, 6, -3.33, 7.33, -2, 8.665, -0.665, 10 };

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;

    QVector<double> vx, vy;
    QPointF m_topLeft;
    QPointF m_bottomRight;
    QMenu contexMenu;


private:
//     QXlsx::Document *m_xlsx = nullptr;
     void saveStudentScore();
     void saveAndUploadStudentScore();
     void clearStudentUiInfo();
     void initGodLeilaser();
     void showCustomPlot();
     void showExamRegion();
     void LidarParsing(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloudData);
     int m_rowsInXlsx = 1;
     QString m_saveVideoFormat = ".mp4";
     QString m_savePictureFormat = ".png";

     QFrame *m_toolBarframe = nullptr;


     SchoolListTableModel *m_schoolListModel;

     Student *m_curTmpStudent = nullptr;

     LocalStudentTableModel *m_studentsModel = nullptr;
     int m_examCount = 1;
     int m_curExamCount = 0;
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

     bool m_startShown = false;

     lidarAnalysis *m_lidaAnalysis = nullptr;
     bool m_lidarIsOpen = false;
     QTimer m_lidarWatchDogTimer;
     std::vector<PointXYZ> m_objs;

     QTimer m_turnLidarTimer;
     float m_currentAngle = 0;
     float m_deltaAngle = 0.5;

     int m_examReginTopLeftX;
     int m_examReginTopLeftY;
     int m_examReginBottomRightX;
     int m_examReginBottomRightY;
     int m_lidarFace = 0;
     int m_lidarType = 0;


     int m_rectReginTopLeftX;
     int m_rectReginTopLeftY;
     int m_rectReginWidth;
     int m_rectReginHight;

//     int m_rectReginTopLeftX;
//     int m_rectReginTopLeftY;
//     int m_rectReginBottomRightX;
//     int m_rectReginBottomRightY;

protected:
     void closeEvent(QCloseEvent *event);
};

#endif // FORMFUNCCHOOSE_H
