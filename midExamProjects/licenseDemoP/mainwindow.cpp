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
    QString cmd = QString("wmic %1 get %2").arg(idType).arg(param2);
    QProcess p(0);
    p.start(cmd);
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
    QString biosId = getId("bios");
    QString baseBoard = getId("baseboard");
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


