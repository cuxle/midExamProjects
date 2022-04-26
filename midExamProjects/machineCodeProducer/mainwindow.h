#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pbGetMachineCode_clicked();

private:
    Ui::MainWindow *ui;
    QString getId(QString idType);
    QString getMachineCode();
};
#endif // MAINWINDOW_H
