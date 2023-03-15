#pragma execution_character_set("utf-8")

#include <QStringLiteral>
#include "widget.h"
#include "ui_widget.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QFontDatabase>
#include <QMediaPlayer>
#include <QThread>

#include "client.h"
#include "formbasegroup.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    // init clients box
    initClientsBox();

    // hide label
    ui->lbFinishState->setHidden(true);
    ui->lbCurrentGroupValue->setText(QString::number(m_currentGroup));

    // init common toolbar
    initCommonToolbar();

    initFontDatabase();

    initMediaPlayer();

    initTimers();

    initServer();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initTimers()
{
    m_backCountTimer = new QTimer(this);
    m_backCountTimer->setInterval(m_internal);
    connect(m_backCountTimer, &QTimer::timeout, this, &Widget::updateDisplayTimer);
    m_backCountTimer->setTimerType(Qt::PreciseTimer);

    setLeftTime(m_totalTimeMs);

    m_startDelayTimer = new QTimer(this);
    m_startDelayTimer->setInterval(9000);
    m_startDelayTimer->setTimerType(Qt::PreciseTimer);
    m_startDelayTimer->setSingleShot(true);
    connect(m_startDelayTimer, &QTimer::timeout, this, &Widget::handleStartExam);
}

void Widget::updateDisplayTimer()
{
    m_curTimeLeftMs -= m_internal;

    setLeftTime(m_curTimeLeftMs);

    if (m_curTimeLeftMs <= 0) {

        m_backCountTimer->stop();

        stopExamStuff();

//        // stop count
//        emit sigStartCount(false);

//        // start
//        emit sigStartSaveVideo(false, m_videoFileName);


    }

}

void Widget::stopExamStuff()
{
    // 1. 按钮， 变为enable
    startTestUiStuff(false);

    // 2. ui display time left
    m_curTimeLeftMs = m_totalTimeMs;
    setLeftTime(m_curTimeLeftMs);
}

void Widget::handleStartExam()
{
    // 1. 开始60s 倒计时
    m_curTimeLeftMs = m_totalTimeMs;    

    // 2. after gun fire start cmd
//    for (Client *client : m_clients) {
//        client->startSkipCmd(true);
//    }
    Client::sendCmdToAllDevices();

    m_backCountTimer->start();
}

void Widget::setLeftTime(int leftTimeMs)
{
    int sPart = leftTimeMs / 1000;
    int msPart = leftTimeMs % 1000;
    msPart = msPart / 10;
    QString text = QString("%1:%2").arg(sPart, 2, 10, QLatin1Char('0')).arg(msPart, 2, 10, QLatin1Char('0'));
    ui->lbCurLeftTimes->setText(text);
}

void Widget::initMediaPlayer()
{
    m_mp3Player = new QMediaPlayer(this);

    QString mediapath = "qrc:/resource/sound/skipRope30s.mp3";

    m_mp3Player->setMedia(QUrl(mediapath));

    m_mp3Player->setVolume(100);

    // no need to handle sound stop

//    connect(m_mp3Player, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State newState){
//       if (newState == QMediaPlayer::StoppedState) {
//           if (m_bCameraIsOpen) {
//               emit sigStartSaveVideo(false);
//           }
//       }
//    });
}

void Widget::initFontDatabase()
{
    int id = QFontDatabase::addApplicationFont(":/resource/font/DS-DIGIB.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    font.setPixelSize(120);
    ui->lbCurLeftTimes->setFont(font);
}

void Widget::initClientsBox()
{
    QString gbBoxStyle = "QGroupBox{background-color: rgb(42, 38, 66);\
            border:0px;\
            border-radius: 10px;}";
    ui->gbBox1->setStyleSheet(gbBoxStyle);

    FormBaseGroup *gb1 = (FormBaseGroup *)ui->gbBox1;
    setItemId(gb1, 1);
    gb1->setItemState(ClientOffline);

    m_uiClientsBox.append(gb1);

    FormBaseGroup *gb2 = (FormBaseGroup *)ui->gbBox2;
    setItemId(gb2, 2);
    gb1->setItemState(ClientOffline);
    m_uiClientsBox.append(gb2);

    FormBaseGroup *gb3 = (FormBaseGroup *)ui->gbBox3;
    setItemId(gb3, 3);
    m_uiClientsBox.append(gb3);

    FormBaseGroup *gb4 = (FormBaseGroup *)ui->gbBox4;
    setItemId(gb4, 4);
    m_uiClientsBox.append(gb4);

    FormBaseGroup *gb5 = (FormBaseGroup *)ui->gbBox5;
    setItemId(gb5, 5);
    m_uiClientsBox.append(gb5);

    FormBaseGroup *gb6 = (FormBaseGroup *)ui->gbBox6;
    setItemId(gb6, 6);
    m_uiClientsBox.append(gb6);

    FormBaseGroup *gb7 = (FormBaseGroup *)ui->gbBox7;
    setItemId(gb7, 7);
    m_uiClientsBox.append(gb7);

    FormBaseGroup *gb8 = (FormBaseGroup *)ui->gbBox8;
    setItemId(gb8, 8);
    m_uiClientsBox.append(gb8);

    FormBaseGroup *gb9 = (FormBaseGroup *)ui->gbBox9;
    setItemId(gb9, 9);
    m_uiClientsBox.append(gb9);

    FormBaseGroup *gb10 = (FormBaseGroup *)ui->gbBox10;
    setItemId(gb10, 10);
    m_uiClientsBox.append(gb10);

    FormBaseGroup *gb11 = (FormBaseGroup *)ui->gbBox11;
    setItemId(gb11, 11);
    m_uiClientsBox.append(gb11);

    FormBaseGroup *gb12 = (FormBaseGroup *)ui->gbBox12;
    setItemId(gb12, 12);
    m_uiClientsBox.append(gb12);

    FormBaseGroup *gb13 = (FormBaseGroup *)ui->gbBox13;
    setItemId(gb13, 13);
    m_uiClientsBox.append(gb13);

    FormBaseGroup *gb14 = (FormBaseGroup *)ui->gbBox14;
    setItemId(gb14, 14);
    m_uiClientsBox.append(gb14);

    FormBaseGroup *gb15 = (FormBaseGroup *)ui->gbBox15;
    setItemId(gb15, 15);
    m_uiClientsBox.append(gb15);

    FormBaseGroup *gb16 = (FormBaseGroup *)ui->gbBox16;
    setItemId(gb16, 16);
    m_uiClientsBox.append(gb16);

    FormBaseGroup *gb17 = (FormBaseGroup *)ui->gbBox17;
    setItemId(gb17, 17);
    m_uiClientsBox.append(gb17);

    FormBaseGroup *gb18 = (FormBaseGroup *)ui->gbBox18;
    setItemId(gb18, 18);
    m_uiClientsBox.append(gb18);

    FormBaseGroup *gb19 = (FormBaseGroup *)ui->gbBox19;
    setItemId(gb19, 19);
    m_uiClientsBox.append(gb19);

    FormBaseGroup *gb20 = (FormBaseGroup *)ui->gbBox20;
    setItemId(gb20, 20);
    m_uiClientsBox.append(gb20);

    FormBaseGroup *gb21 = (FormBaseGroup *)ui->gbBox21;
    setItemId(gb21, 21);
    m_uiClientsBox.append(gb21);

    FormBaseGroup *gb22 = (FormBaseGroup *)ui->gbBox22;
    setItemId(gb22, 22);
    m_uiClientsBox.append(gb22);

    FormBaseGroup *gb23 = (FormBaseGroup *)ui->gbBox23;
    setItemId(gb23, 23);
    m_uiClientsBox.append(gb23);

    FormBaseGroup *gb24 = (FormBaseGroup *)ui->gbBox24;
    setItemId(gb24, 24);
    m_uiClientsBox.append(gb24);

    FormBaseGroup *gb25 = (FormBaseGroup *)ui->gbBox25;
    setItemId(gb25, 25);
    m_uiClientsBox.append(gb25);

    for (FormBaseGroup *item : m_uiClientsBox) {
        item->setItemState(ClientOffline);
    }
}

void Widget::setItemId(FormBaseGroup *gb, int id)
{
    if (gb != nullptr) {
        gb->setItemId(id);
    }
}

void Widget::initServer()
{
//! [0] //! [1]
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, 1234)) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();

        m_appInitFailureType = AppInitServerFailed;
        return;
    }
//! [0]
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost) {
            bool ok = false;
            quint32 ipv4 = ipAddressesList.at(i).toIPv4Address(&ok);
            Q_UNUSED(ipv4);
            if (ok) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    connect(tcpServer, &QTcpServer::newConnection, this, &Widget::handleNewClientConnection);

//! [1]
}

void Widget::handleNewClientConnection()
{
    // new connection come in
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    if (clientConnection == nullptr) {
        qDebug() << __func__ << __LINE__ << "incoming new pending connection is nullptr";
        return;
    }

    QHostAddress address = clientConnection->peerAddress();
    quint16 port = clientConnection->peerPort();


    qDebug() << __func__ << __LINE__ << clientConnection->peerAddress();
    qDebug() << __func__ << __LINE__ << clientConnection->peerPort();

    Client *toDelete = nullptr;
    for (auto &item : Client::m_clients) {
        if ((item->ip() == address) && (port == item->port())) {
//            delete item;
            toDelete = item;
            break;
            qDebug() << __func__ << __LINE__;
        }
    }
    if (toDelete != nullptr) {
        if (Client::m_clients.contains(toDelete)) {
            Client::m_clients.removeOne(toDelete);
        }
        delete toDelete;
    }

    Client *newClient = new Client(&m_uiClientsBox);
    newClient->setTcpSocket(clientConnection);
//    m_clients.append(newClient);
    connect(newClient, &Client::toDestroy, this, &Widget::handleClientDestroyed);

//    m_clients.insert(newClient->id(), newClient);

    // insert into map after get client id
//    m_clients.insert(newClient->id(), newClient);

    // create an new client
    /*
     * client id
     * client ip
     * client mac
     * client state stopped, running,examing
     * client connected
     * client lost
     */
}

void Widget::handleClientDestroyed()
{
    qDebug() << __func__ << __LINE__;
    Client *object = qobject_cast<Client *>(sender());
    if (object == nullptr) {
        qDebug() << __func__ << __LINE__ << "sender is nullptr;";
        return;
    }
    qDebug() << __func__ << __LINE__;
    if (Client::m_clients.contains(object)) {
        Client::m_clients.removeOne(object);
    }
    delete object;

    //Client::m_clients.removeOne(object);
}

void Widget::handleClientStateChanged(int id, int State)
{
    qDebug() << __func__ << __LINE__ << id << State;
}

void Widget::initCommonToolbar()
{
    QFrame *frame = new QFrame(this);
    frame->setMinimumHeight(60);
    frame->setStyleSheet("background-color: rgb(55, 50, 82);");
//    frame->setMaximumHeight(50);
    QLabel *label = new QLabel(frame);
//    label->setPixmap(QPixmap(":/resource/images/mainform/loginIcon.png"));
    label->setMaximumHeight(36);
    label->setMaximumWidth(36);
    label->setMinimumWidth(36);
    label->setMinimumHeight(36);

    label->setStyleSheet("border-image: url(:/resource/loginIcon.png);");

    QLabel *softTitle = new QLabel(frame);

    softTitle->setText(QCoreApplication::translate("FormFuncChoose", "\345\255\246\351\200\232\344\270\255\350\200\203\344\275\223\350\202\262\350\200\203\350\257\225\350\275\257\344\273\266", nullptr));
    //softTitle->setText(QStringLiteral("学通中考体育考试软件"));
    softTitle->setStyleSheet("color:rgb(255,255,255);");
    QPushButton *pbBackStep = new QPushButton(this);
    pbBackStep->setFlat(true);
    pbBackStep->setIcon(QIcon(":/resource/backStep.png"));
    pbBackStep->setStyleSheet("background-color:#373252;");
    connect(pbBackStep, &QPushButton::clicked, this, &Widget::on_pbBackStep_clicked);

    QSpacerItem *hSpaceItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label);
    hlayout->addWidget(softTitle);
    hlayout->addItem(hSpaceItem);
    hlayout->addWidget(pbBackStep);
    frame->setLayout(hlayout);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(frame);
    vlayout->addWidget(ui->gbMainForm);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    this->setLayout(vlayout);
}

void Widget::on_pbBackStep_clicked()
{
    this->close();
}

void Widget::startTestUiStuff(bool start)
{
    ui->pbStartAll->setDisabled(start);
    ui->pbNextGroup->setDisabled(start);
    ui->pbRefreshStatus->setDisabled(start);
    ui->pbTestSound->setDisabled(start);
    ui->cmbExamTimeChoose->setDisabled(start);
    if (start) {
//        ui->lbTestingState->setText("测试中");
        ui->lbTestingState->setText(QCoreApplication::translate("Widget", "\346\265\213\350\257\225\350\277\233\350\241\214\344\270\255", nullptr));
    } else {
//        ui->lbTestingState->setText("等待开始测试");
        ui->lbTestingState->setText(QCoreApplication::translate("Widget", "\347\255\211\345\276\205\345\274\200\345\247\213\346\265\213\350\257\225", nullptr));
    }
}

void Widget::on_pbStartAll_clicked()
{
    // 1. disable button startAll
    startTestUiStuff(true);


    // 2. start play media
    m_mp3Player->stop();
    m_mp3Player->play();

    // 3. delay 9.5s, wait the start gun
    m_startDelayTimer->start(); // 倒计时结束开始倒计时60s backCounter


    // 4.
    on_pbNextGroup_clicked();
}


void Widget::on_pbRefreshStatus_clicked()
{
    ui->pbRefreshStatus->setEnabled(false);
    ui->pbRefreshStatus->setStyleSheet("background-color: rgb(61, 127, 255);\ncolor: rgb(133, 133, 255);\nfont: 25 13.5pt \"Microsoft YaHei\";\nborder-radius: 15px;");

    // recover
    QTimer::singleShot(300, [&](){
        ui->pbRefreshStatus->setStyleSheet("background-color: rgb(61, 127, 255);\ncolor: rgb(255, 255, 255);\nfont: 25 13.5pt \"Microsoft YaHei\";\nborder-radius: 15px;");
        ui->pbRefreshStatus->setEnabled(true);
    });

    qDeleteAll(Client::m_clients);
    Client::m_clients.clear();
}


void Widget::on_pbTestSound_clicked()
{
    static bool testing = false;
    testing = !testing;
    if (testing) {
//        ui->pbTestSound->setText("停止");
        startTestUiStuff(true);
        m_mp3Player->stop();
        m_mp3Player->play();
        QTimer::singleShot(9500, [&](){
            //if (m_mp3Player->state() == QMediaPlayer::PlayingState) { // no need to judge just stop
                m_mp3Player->stop();
                startTestUiStuff(false);
                testing = false;
            //}
        });
    } else {
        qDebug() << "will not execute forever";
//        ui->pbTestSound->setText("测试");
//        startTestUiStuff(false);
//        m_mp3Player->stop();
//        testing = false;
    }
}


void Widget::on_pbNextGroup_clicked()
{
    // 1. update current group
    ui->lbCurrentGroupValue->setText(QString::number(++m_currentGroup));
}


void Widget::on_cmbExamTimeChoose_currentIndexChanged(int index)
{
    // index 0: 30s version
    // index 1: 60s version
    if (index == 0) {
        m_totalTimeMs = 30*1000;
        m_currentMp3File = "qrc:/resource/sound/skipRope30s.mp3";
    } else if (index == 1) {
        m_totalTimeMs = 60*1000;
        m_currentMp3File = "qrc:/resource/sound/skipRope60s.mp3";
    }
    m_mp3Player->setMedia(QUrl(m_currentMp3File));
    setLeftTime(m_totalTimeMs);
}

