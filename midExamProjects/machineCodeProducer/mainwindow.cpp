#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <QCryptographicHash>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getId(QString idType)
{
    /*
     * idType can be
     * 1. cpu
     * 2. bios
     * 3. baseboard
    */
    QString param2 = "serialnumber";
    if (idType == "cpu") {
        param2 = "processorid";
    }
    QString cmd = QString("wmic");
    QProcess p(0);
    QStringList args;
    args << "cpu" << "get" << "processorid";
    p.start(cmd, args);
    p.waitForFinished();
    QString ret = QString::fromLocal8Bit(p.readAllStandardOutput());
    ret = ret.remove(param2, Qt::CaseInsensitive).trimmed();
    return ret;
}

QByteArray encodeByString(QByteArray code, const QByteArray &by)
{
    qDebug() << __LINE__ << code.toHex(' ');
    qDebug() << __LINE__ << by.toHex(' ');
    QByteArray ret;
    for (auto item : by) {
        for (auto &mc : code) {
            mc = mc ^ item;
           // qDebug() << mc;
            ret.append(mc);
            //qDebug() << __LINE__ << ret.size();
        }
    }
    return ret;
}

QString MainWindow::getMachineCode()
{
    QString cpuId = getId("cpu");
    qDebug() << "cpuId id" << cpuId;
    QString biosId = getId("bios");
    qDebug() << "biosId id" << biosId;
    QString baseBoard = getId("baseboard");
    qDebug() << "baseBoard id" << biosId;
    QString machineId = cpuId + biosId + baseBoard;
    qDebug() << "machine id" << machineId;
    QString str = "redDog";
    QByteArray ret = encodeByString(machineId.toLatin1(), str.toLatin1());
    QString retStr;
    retStr.append(ret.toHex());
    return retStr;
}

void MainWindow::on_pbGetMachineCode_clicked()
{
    QString str = getMachineCode();
    ui->lineEdit->setText(str);

}


