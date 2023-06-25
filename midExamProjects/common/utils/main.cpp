#include "formlogin.h"
#include "logindialog.h"
#include "formfuncchoose.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include "license.h"
#include "initdb.h"
#include "appconfig.h"
#include "singleton.h"
#include <QStandardPaths>
#include <WinBase.h>
#include "Logger.h"

QString serverLocation;
#if TIAOSHENG
const QString serverName = "server_database01.exe";
QString serverFullName;
#elif YTXS
const QString serverName = "server_ytxs.exe";
QString serverFullName;
#elif YWQZ
const QString serverName = "server_ywqz.exe";
QString serverFullName;
#else
#endif

void createDataFolder()
{
    // create video data folder
    AppConfig &m_config = Singleton<AppConfig>::GetInstance();
    QString dataFolder = m_config.m_videoSavePath + "/data/";
    QDir data(dataFolder);
    qDebug() << data.absolutePath();
    if (!data.exists()) {
        if (data.mkdir(".")) {
            qDebug() << "create dir successfully";
        } else {
            qDebug() << "create dir failed";
        }
    } else {
        qDebug() << "data dir exists";
    }

    QString videoFolder = m_config.m_videoSavePath + "/video/";
    QDir video(videoFolder);
    qDebug() << video.absolutePath();
    if (!video.exists()) {
        if (video.mkdir(".")) {
            qDebug() << "create video dir successfully";
        } else {
            qDebug() << "create video dir failed";
        }
    } else {
        qDebug() << "video dir exists";
    }
}

#if defined(TIAOSHENG) || defined(YTXS)  || defined(YWQZ)
bool startServer(const QString &serverFullName)
{
    qDebug() << __func__ << __LINE__  << serverFullName;
    // start algorithm server
    QString cmd = QString("cmd /c %1").arg(serverFullName);
    int ret = WinExec(cmd.toLocal8Bit(), SW_NORMAL);
    qDebug() << __func__ << __LINE__ << ret << serverFullName;
    if ( ret <= 31) {
        QMessageBox::critical(nullptr, "Critical", "启动Server失败");
        return false;
    } else {
        return true;
    }

    //    QProcess process(0);
    //    QString startCmd = QString("start /b %1").arg(serverFullName);
    //    process.start("cmd.exe", QStringList()<< "/c" << startCmd);
    //    process.waitForStarted();
    //    process.waitForFinished();
}

void killServer(const QString &serverName)
{
    QString killServerCmd = QString("taskkill /im %1 /f").arg(serverName);
    QProcess process(0);
    process.start("cmd.exe", QStringList()<< "/c" << killServerCmd);
    process.waitForStarted();
    process.waitForFinished();
}

bool initAlgorithmServer()
{
    // if server is running, kill the process
    killServer(serverName);

    // start algorithm server
    return startServer(serverFullName);
}
#endif

void initQss()
{
    QFile file("://resource/exam.qss");
    bool bOpened = file.open(QFile::ReadOnly);
    //assert (bOpened == true);
    if (bOpened) {
        QString styleSheet = file.readAll();
        qDebug() << styleSheet;
        qApp->setStyleSheet (styleSheet);
        file.close();
    } else {
        qDebug() << "open file failed";
    }
}

void testCaseForStudentScoreSmaller() {
    Student student;
    student.examCount = 1;
    student.midStopFirst = true;
    int value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 1; -1:" << value;

    student.examCount = 1;
    student.midStopFirst = false;
    student.firstScore = 10;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 1; 10:" << value;

    student.examCount = 2;
    student.midStopFirst = true;
    student.midStopSecond = true;
    student.firstScore = 10;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 2; -1:" << value;

    student.examCount = 2;
    student.midStopFirst = true;
    student.midStopSecond = false;
    student.firstScore = 10;
    student.secondScore = 5;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 2; 5:" << value;

    student.examCount = 2;
    student.midStopFirst = false;
    student.midStopSecond = true;
    student.firstScore = 10;
    student.secondScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 2; 10:" << value;

    student.examCount = 2;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.firstScore = 30;
    student.secondScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 2; 20:" << value;

    student.examCount = 2;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.firstScore = 30;
    student.secondScore = 40;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 2; 30:" << value;


    student.examCount = 3;
    student.midStopFirst = true;
    student.midStopSecond = true;
    student.midStopThird = true;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; -1:" << value;


    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = true;
    student.midStopThird = true;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 30:" << value;


    student.examCount = 3;
    student.midStopFirst = true;
    student.midStopSecond = false;
    student.midStopThird = true;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 40:" << value;

    student.examCount = 3;
    student.midStopFirst = true;
    student.midStopSecond = true;
    student.midStopThird = false;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 20:" << value;

    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.midStopThird = true;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 30:" << value;

    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = true;
    student.midStopThird = false;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 20:" << value;

    student.examCount = 3;
    student.midStopFirst = true;
    student.midStopSecond = false;
    student.midStopThird = false;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 20:" << value;


    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.midStopThird = false;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 20:" << value;

    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.midStopThird = false;
    student.firstScore = 50;
    student.secondScore = 10;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 10:" << value;

    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.midStopThird = false;
    student.firstScore = 50;
    student.secondScore = 40;
    student.thirdScore = 60;
    value = Utils::calculateFinalScoreBySmallerCount(student);
    qDebug() << "exam count = 3; 40:" << value;



    student.midStopSecond = true;
    student.midStopThird = true;
}

void testCaseForStudentScoreBigger() {
    Student student;
    student.examCount = 1;
    student.midStopFirst = true;
    int value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 1; 犯规:" << value;

    student.examCount = 1;
    student.midStopFirst = false;
    student.firstScore = 10;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 1; 10:" << value;

    student.examCount = 2;
    student.midStopFirst = true;
    student.midStopSecond = true;
    student.firstScore = 10;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 2; 犯规:" << value;

    student.examCount = 2;
    student.midStopFirst = true;
    student.midStopSecond = false;
    student.firstScore = 10;
    student.secondScore = 5;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 2; 5:" << value;

    student.examCount = 2;
    student.midStopFirst = false;
    student.midStopSecond = true;
    student.firstScore = 10;
    student.secondScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 2; 10:" << value;

    student.examCount = 2;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.firstScore = 30;
    student.secondScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 2; 30:" << value;

    student.examCount = 2;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.firstScore = 30;
    student.secondScore = 40;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 2; 40:" << value;


    student.examCount = 3;
    student.midStopFirst = true;
    student.midStopSecond = true;
    student.midStopThird = true;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; -1:" << value;


    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = true;
    student.midStopThird = true;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 30:" << value;


    student.examCount = 3;
    student.midStopFirst = true;
    student.midStopSecond = false;
    student.midStopThird = true;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 40:" << value;

    student.examCount = 3;
    student.midStopFirst = true;
    student.midStopSecond = true;
    student.midStopThird = false;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 20:" << value;

    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.midStopThird = true;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 40:" << value;

    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = true;
    student.midStopThird = false;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 30:" << value;

    student.examCount = 3;
    student.midStopFirst = true;
    student.midStopSecond = false;
    student.midStopThird = false;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 40:" << value;


    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.midStopThird = false;
    student.firstScore = 30;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 40:" << value;

    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.midStopThird = false;
    student.firstScore = 50;
    student.secondScore = 40;
    student.thirdScore = 20;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 50:" << value;

    student.examCount = 3;
    student.midStopFirst = false;
    student.midStopSecond = false;
    student.midStopThird = false;
    student.firstScore = 50;
    student.secondScore = 40;
    student.thirdScore = 60;
    value = Utils::calculateFinalScoreByBiggerCount(student);
    qDebug() << "exam count = 3; 60:" << value;



    student.midStopSecond = true;
    student.midStopThird = true;
}

void testCplus17ByTime() {
    Student student;
    student.initTimeExam();
    qDebug() << "犯规" << student.getFinalScoreByTime() ;

    student.initTimeExam();
    student.scores[0] = 1;
    student.scores[1] = 2;
    student.scores[2] = 5;
    qDebug() << "0.01" << student.getFinalScoreByTime() ;

    student.initTimeExam();
    student.scores[0] = 1000;
    student.scores[1] = 2000;
    student.scores[2] = 5000;
    qDebug() << "1" << student.getFinalScoreByTime() ;

    student.initTimeExam();
    // student.scores[0] = 1000;
    //student.scores[1] = 2000;
    student.scores[2] = 5000;
    qDebug() << "5" << student.getFinalScoreByTime() ;

    student.initTimeExam();
    student.scores[0] = 10000;
    student.scores[1] = 20000;
    student.scores[2] = 6000;
    qDebug() << "6" << student.getFinalScoreByTime() ;

    student.initCountExam();
    student.scores[0] = 0;
    student.scores[1] = 2;
    student.scores[2] = 5;
    qDebug() << "5" << student.getFinalScoreByCount() ;

    student.initCountExam();
    student.scores[0] = 5;
    student.scores[1] = 2;
    //student.scores[2] = 5;
    qDebug() << "5" << student.getFinalScoreByCount() ;

    student.initCountExam();
    student.scores[0] = 5;
    student.scores[1] = 10;
    //student.scores[2] = 5;
    qDebug() << "10" << student.getFinalScoreByCount() ;

    student.initCountExam();
    //    student.scores[0] = 0;
    //    student.scores[1] = 2;
    //    student.scores[2] = 5;
    qDebug() << "犯规" << student.getFinalScoreByCount() ;


}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    Logger::init();

    if (!License::verifyLicenseFromFile("./license.lic")) {
        QMessageBox::critical(nullptr, "warning", "请获取license.lic并放入软件执行目录！");
        return -1;
    }

    createDataFolder();

    initDb();

#if defined(TIAOSHENG) || defined(YTXS) || defined(YWQZ)
    serverLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/server/";
    serverFullName = serverLocation + serverName;
    if (!initAlgorithmServer()) {
        return 0;
    }
#endif

    initQss();

    LoginDialog logDialog;
    logDialog.showNormal();

    // init log stop
    int ret = application.exec();

#if defined(TIAOSHENG) || defined(YTXS)
    //    killServer(serverName);
#endif
    if (ret == RETCODE_RESTART) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }
    return ret;
}
