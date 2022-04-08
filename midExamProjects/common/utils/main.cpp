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

#if TIAOSHENG
const QString serverName = "server_tiaosheng.exe";
#elif YTXS
const QString serverName = "server_ytxs.exe";
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
#if defined(TIAOSHENG) || defined(YTXS)
void initAlgorithmServer()
{
    // if server is running, kill the process
    QProcess process1(0);
    QString killCmd = QString("taskkill /im %1 /f").arg(serverName);
    process1.start("cmd.exe", QStringList()<< "/c" << killCmd);
    process1.waitForStarted();
    process1.waitForFinished();

    // start algorithm server
    QProcess process(0);
    QString startCmd = QString("start D://%1").arg(serverName);
    process.start("cmd.exe", QStringList()<< "/c" << startCmd);
    process.waitForStarted();
    process.waitForFinished();
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

	
    Logger::init();


	
#if defined(TIAOSHENG) || defined(YTXS)
    initAlgorithmServer();
#endif

    initQss();

    LoginDialog logDialog;
    logDialog.showNormal();

    int ret = a.exec();
    if (ret == RETCODE_RESTART) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }
    return ret;
}
