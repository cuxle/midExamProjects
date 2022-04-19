#include "widget.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include "log/Logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger::init();

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

    Widget w;
    w.show();

    return a.exec();
}
