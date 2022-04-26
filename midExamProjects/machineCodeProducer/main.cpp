#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QString str = "edcrfvpl<2017";

//    QString md5;
//    QByteArray code;
//    code = QCryptographicHash::hash(machineId.toLatin1(), QCryptographicHash::Md5);
//    md5.append(code.toHex());
//    qDebug() << "encryped code:" << md5;
    MainWindow w;
    w.show();
    return a.exec();
}
