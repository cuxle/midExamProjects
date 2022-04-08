#pragma execution_character_set("utf-8")

#include "formlogin.h"
#include "ui_formlogin.h"

#include "formfuncchoose.h"
#include <QDebug>
#include <QMessageBox>
#include "singleton.h"
#include "datamanager.h"
#include "datamanagerdb.h"
#include "appconfig.h"

#if defined(YTXS) || defined(TIAOSHENG)
#include <QProcess>
#endif

FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
{
#if defined(YTXS) || defined(TIAOSHENG)
    initRopeSkipWorkerZmq();

    QEventLoop loop;
    connect(m_skipRopeZeroMq, &SkipRopeOnZeroMq::sigContinueRun, &loop, &QEventLoop::quit);
    qDebug() << "waiting.... ";
    loop.exec();
    qDebug() << "waiting....finished! ";
#endif
    ui->setupUi(this);

    NetWorkServer &server = Singleton<NetWorkServer>::GetInstance();

//    connect(&server, &NetWorkServer::sigLoginStateChanged, this, &FormLogin::hanldeLoginStateChanged);
    ui->cmbUserId->lineEdit()->setPlaceholderText("请输入用户名");

    QFont font;
    font.setFamily(QString::fromUtf8("Microsoft YaHei"));
    font.setPixelSize(18);

    ui->cmbUserId->lineEdit()->setFont(font);
    ui->leUserCode->setFont(font);

    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
    for (auto &item : appconfig.m_userNameslist) {
        ui->cmbUserId->addItem(item);
    }
}

FormLogin::~FormLogin()
{
#if  defined(YTXS) || defined(TIAOSHENG)
    m_skipRopeZeroMqThread->quit();
    m_skipRopeZeroMqThread->wait();
#endif
    delete ui;
}

#if defined(YTXS) || defined(TIAOSHENG)
void FormLogin::initRopeSkipWorkerZmq()
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    m_skipRopeZeroMq = new SkipRopeOnZeroMq;
    m_skipRopeZeroMqThread = new QThread;
    m_skipRopeZeroMq->moveToThread(m_skipRopeZeroMqThread);
    connect(m_skipRopeZeroMqThread, &QThread::started, m_skipRopeZeroMq, &SkipRopeOnZeroMq::init);
    connect(m_skipRopeZeroMqThread, &QThread::finished, m_skipRopeZeroMq, &SkipRopeOnZeroMq::handleDestroyObject);
//    connect(m_skipRopeZeroMqThread, &QThread::finished, m_skipRopeZeroMq, &SkipRopeOnZeroMq::deleteLater);

    // move to formFuncChoose start;
//    connect(m_camera, &Camera::sigImageCapture, m_skipRopeZeroMq, &SkipRopeOnZeroMq::handleReceiveImage);
//    connect(this, &FormFuncChoose::sigStartCount, m_skipRopeZeroMq, &SkipRopeOnZeroMq::startCount);
//    connect(this, &FormFuncChoose::sigResetCount, m_skipRopeZeroMq, &SkipRopeOnZeroMq::resetCount);
//    connect(m_skipRopeZeroMq, &SkipRopeOnZeroMq::sigSkipCountChanged, this, &FormFuncChoose::handleSkipCountChanged);
    // move to formFuncChoose end;
    m_skipRopeZeroMqThread->start();
}
#endif

void FormLogin::hanldeLoginStateChanged(bool isLogin)
{
    if (isLogin) {
        on_pbLoginOffline_clicked();
    } else {
        QMessageBox::warning(this, tr("\347\231\273\345\275\225\346\217\220\347\244\272"), tr("\350\264\246\345\217\267\346\210\226\345\257\206\347\240\201\344\270\215\345\257\271\357\274\214\350\257\267\346\240\270\351\252\214\345\220\216\345\206\215\347\231\273\345\275\225"));
    }
}

void FormLogin::initMainFrm(bool online)
{
    if (m_frmFuncChoose == nullptr) {
#if defined(YTXS) || defined(TIAOSHENG)
        m_frmFuncChoose = new FormFuncChoose(online, m_skipRopeZeroMq);
#else
        m_frmFuncChoose = new FormFuncChoose(online);
#endif
    }
    qDebug() << __LINE__;
    emit sigHiddenLoginForm();
    qDebug() << __LINE__;
    m_frmFuncChoose->show();
    qDebug() << __LINE__;

    this->setParent(m_frmFuncChoose);
}

void FormLogin::on_pbLoginOffline_clicked()
{
    // 离线登录，全屏显示，三个按钮
    // 开始测试，数据管理，设置
    qDebug() << __LINE__;
    initMainFrm(false);
}

void FormLogin::on_pbExit_clicked()
{
    // exit all app
    emit sigExitApp();
}


void FormLogin::on_pbLoginOnline_clicked()
{
    QString id = ui->cmbUserId->currentText();
    updateUserNameListInfo(id);

//    QString id = ui->leUserNameLogin->text();
    QString code = ui->leUserCode->text();

    DataManagerDb &dataManager = Singleton<DataManagerDb>::GetInstance();
    dataManager.updateIdCode(id, code);

    initMainFrm(true);
}

void FormLogin::updateUserNameListInfo(const QString &arg1)
{
    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
    if (!appconfig.m_userNameslist.contains(arg1)) {
        appconfig.m_userNameslist.push_front(arg1);
    } else {
        appconfig.m_userNameslist.removeOne(arg1);
        appconfig.m_userNameslist.push_front(arg1);
    }
}
