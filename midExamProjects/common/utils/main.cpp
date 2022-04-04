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

#if TIAOSHENG
const QString serverName = "server_tiaosheng.exe";
#elif YTXS
const QString serverName = "server_ytxs.exe";
#else

#endif

void createDataFolder()
{
    QDir data("data");
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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    createDataFolder();
	
    Logger::init();
	
#if defined(TIAOSHENG) || defined(YTXS)
    initAlgorithmServer();
#endif

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
//    MainWindow w;
//    FormLogin loginfrm;
//    loginfrm.show();
//    w.show();
    LoginDialog logDialog;
    logDialog.showNormal();

    int ret = a.exec();
    if (ret == RETCODE_RESTART) {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }
    return ret;
}
