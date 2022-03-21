#include "settingdialog.h"
#include "ui_settingdialog.h"

#include "singleton.h"
#include "appconfig.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>


SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    initPushButton();
    initSettingUIValue();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::initSettingUIValue()
{
    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();

    ui->rbOnlineMode->setChecked(appconfig.m_appMode == "ONLINE");
    ui->lePlatAddress->setText(appconfig.m_platAddress);
    ui->leDeviceId->setText(appconfig.m_deviceId);
    ui->leFaceId6Last->setText(appconfig.m_faceIdLastSixNum);
    ui->leSendCmdServerIp->setText(appconfig.m_sendCmdServerIp);

    ui->leIPCAddress->setText(appconfig.m_ipcAddress);
    ui->leIPCUserName->setText(appconfig.m_ipcUserName);
    ui->leIPCCode->setText(appconfig.m_ipcCode);

    qDebug() << __func__ << "m_examProject" << appconfig.m_examProject;
    qDebug() << __func__ << "m_examNums" << appconfig.m_examNums;
    qDebug() << __func__ << "m_videoSavePath" << appconfig.m_videoSavePath;

    ui->leExamProject->setText(appconfig.m_examProject);
    ui->cmbExamTestTimes->setCurrentIndex(appconfig.m_examNums - 1);
    ui->leVideoSavePath->setText(appconfig.m_videoSavePath);
    if (appconfig.m_examTime <= 1 && appconfig.m_examTime >= 0) {
        ui->cmbExamTimeVersion->setCurrentIndex(appconfig.m_examTime);
    } else {
        qDebug() << __func__ << "error m_examTime" << appconfig.m_examTime ;
    }


    ui->leAngleProbe->setText(appconfig.m_angleProbe);
    ui->leProbeSensitive->setText(appconfig.m_probeSensitive);
    ui->leProbeSize->setText(appconfig.m_probeSize);
    ui->leBaseUpdateSensitive->setText(appconfig.m_baseFrameRefreshSensitive);
}

void SettingDialog::initPushButton()
{
    ui->stkWidgetSetting->setCurrentIndex(3);
    ui->pbSetNetwork->setStyleSheet(m_checked); // checked
    ui->pbSetVideo->setStyleSheet(m_unchecked);
    ui->pbSetExam->setStyleSheet(m_unchecked);
    ui->pbSetCheck->setStyleSheet(m_unchecked);
}

void SettingDialog::on_pbSetNetwork_clicked()
{
    // from ui_*.h
    // QString::fromUtf8("font: 25 14pt \"Microsoft YaHei\";\n"
    //"color: rgb(181, 180, 188);")
    // 1. set button color
    // 2. apply the function
    ui->stkWidgetSetting->setCurrentIndex(3);
    ui->pbSetNetwork->setStyleSheet(m_checked); // checked
    ui->pbSetVideo->setStyleSheet(m_unchecked);
    ui->pbSetExam->setStyleSheet(m_unchecked);
    ui->pbSetCheck->setStyleSheet(m_unchecked);
}


void SettingDialog::on_pbSetVideo_clicked()
{
    ui->stkWidgetSetting->setCurrentIndex(0);
    ui->pbSetNetwork->setStyleSheet(m_unchecked); // checked
    ui->pbSetVideo->setStyleSheet(m_checked);
    ui->pbSetExam->setStyleSheet(m_unchecked);
    ui->pbSetCheck->setStyleSheet(m_unchecked);
}


void SettingDialog::on_pbSetExam_clicked()
{
    ui->stkWidgetSetting->setCurrentIndex(1);
    ui->pbSetNetwork->setStyleSheet(m_unchecked); // checked
    ui->pbSetVideo->setStyleSheet(m_unchecked);
    ui->pbSetExam->setStyleSheet(m_checked);
    ui->pbSetCheck->setStyleSheet(m_unchecked);
}


void SettingDialog::on_pbSetCheck_clicked()
{
    ui->stkWidgetSetting->setCurrentIndex(2);
    ui->pbSetNetwork->setStyleSheet(m_unchecked); // checked
    ui->pbSetVideo->setStyleSheet(m_unchecked);
    ui->pbSetExam->setStyleSheet(m_unchecked);
    ui->pbSetCheck->setStyleSheet(m_checked);
}


void SettingDialog::on_pbCloseSetting_clicked()
{
    this->close();
}


void SettingDialog::on_pbChangeVideoPath_clicked()
{
    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();

    QString filePath = appconfig.m_videoSavePath.isEmpty() ? QDir::currentPath() : appconfig.m_videoSavePath;
    QString path = QFileDialog::getExistingDirectory(this,  QString("设置保存路径:"), filePath);
    if (path.isEmpty()) {
        return;
    }
    appconfig.m_videoSavePath = path;

    ui->leVideoSavePath->setText(appconfig.m_videoSavePath);
}


void SettingDialog::on_buttonBox_accepted()
{
    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();

    appconfig.m_platAddress = ui->lePlatAddress->text();
    appconfig.m_deviceId = ui->leDeviceId->text();
    appconfig.m_faceIdLastSixNum = ui->leFaceId6Last->text();
    appconfig.m_sendCmdServerIp = ui->leSendCmdServerIp->text();
    appconfig.m_appMode = ui->rbOnlineMode->isChecked() ? "ONLINE" : "OFFLINE";



    appconfig.m_ipcAddress = ui->leIPCAddress->text();
    appconfig.m_ipcUserName = ui->leIPCUserName->text();
    appconfig.m_ipcCode = ui->leIPCCode->text();

    appconfig.m_examProject = ui->leExamProject->text();
    appconfig.m_examNums = ui->cmbExamTestTimes->currentIndex() + 1;
    appconfig.m_videoSavePath = ui->leVideoSavePath->text();

    qDebug() << "exam project:" << ui->leExamProject->text();
    qDebug() << "m_examNums:" << ui->cmbExamTestTimes->currentIndex() + 1;
    qDebug() << "m_videoSavePath:" << ui->leVideoSavePath->text();

    appconfig.m_angleProbe = ui->leAngleProbe->text();
    appconfig.m_probeSensitive = ui->leProbeSensitive->text();
    appconfig.m_probeSize = ui->leProbeSize->text();
    appconfig.m_baseFrameRefreshSensitive = ui->leBaseUpdateSensitive->text();
    appconfig.m_examTime = ui->cmbExamTimeVersion->currentIndex(); // 0: 60s; 1 : 30s;

    QMessageBox::StandardButton btn = QMessageBox::warning(this,
                                                           tr("AppMode"),
//                                                           tr("Software has been changing to Online mode, Press Yes to restart the Software!"),
                                                           tr("\350\213\245\350\256\276\347\275\256\345\267\262\346\233\264\346\226\260\357\274\214\350\257\267\347\202\271\345\207\273Yes\351\207\215\345\220\257\350\275\257\344\273\266"),
                                                           QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {
        // reboot the software
        emit sigReStartApp();
    } else {
        // reboot later
    }

}


//void SettingDialog::on_rbOnlineMode_toggled(bool checked)
//{
//    if (checked) {
//        AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
//        appconfig.m_appMode = "ONLINE";
//        // save config
//        // ask reboot the app or not , Yes quit , no still run
//        QMessageBox::StandardButton btn = QMessageBox::warning(this,
//                                                               tr("AppMode"),
//                                                               tr("Software has been changing to Online mode, Press Yes to restart the Software!"),
//                                                               QMessageBox::Yes|QMessageBox::No);
//        if (btn == QMessageBox::Yes) {
//            // reboot the software
//            emit sigReStartApp();
//        } else {
//            // reboot later
//        }
//    }

//}


//void SettingDialog::on_rbOfflineMode_toggled(bool checked)
//{
//    if (checked) {
//        AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
//        appconfig.m_appMode = "OFFLINE";
//        // save config
//        // ask reboot the app or not , Yes quit , no still run
//        QMessageBox::StandardButton btn = QMessageBox::warning(this,
//                                                               tr("AppMode"),
//                                                               tr("Software has been changing to Offline mode, Press Yes to restart the Software!"),
//                                                               QMessageBox::Yes|QMessageBox::No);
//        if (btn == QMessageBox::Yes) {
//            // reboot the software
//            emit sigReStartApp();
//        } else {
//            // reboot later
//        }
//    }

//}
