#include "formlogin.h"
#include "logindialog.h"
#include "Logger.h"
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
    // start algorithm server
    QString cmd = QString("cmd /c %1").arg(serverFullName);
    int ret = WinExec(cmd.toLocal8Bit(), SW_HIDE);
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



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!License::verifyLicenseFromFile("./license.lic")) {
        QMessageBox::critical(nullptr, "warning", "请获取license.lic并放入软件执行目录！");
        return -1;
    }

    createDataFolder();

    initDb();
	
//    Logger::init();
	
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

    int ret = a.exec();
    #if defined(TIAOSHENG) || defined(YTXS)
//    killServer(serverName);
    #endif
    if (ret == RETCODE_RESTART) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }
    return ret;
}
