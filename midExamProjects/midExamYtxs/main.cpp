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

void initAlgorithmServer()
{
    // if server is running, kill the process
    QProcess process1(0);
    process1.start("cmd.exe", QStringList()<< "/c" << "taskkill /im server_ytxs.exe /f");
    //process.start("cmd.exe", QStringList()<< "/c" << "skiprope_server_ori.exe");
    process1.waitForStarted();
    process1.waitForFinished();

    // start algorithm server
    QProcess process(0);
    process.start("cmd.exe", QStringList()<< "/c" << "start D://server_ytxs.exe");
    //process.start("cmd.exe", QStringList()<< "/c" << "start ./server20220228.exe");
    process.waitForStarted();
    process.waitForFinished();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    createDataFolder();

    //Logger::init();

    initAlgorithmServer();

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
        // 传入 qApp->applicationFilePath()，启动自己
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }
    return ret;
}
