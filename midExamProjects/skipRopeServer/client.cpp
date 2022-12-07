#include "client.h"


#include <QAbstractSocket>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>

unsigned int Client::m_allDeviceFlag = 0;
QList<Client*> Client::m_clients;

Client::Client(QList<FormBaseGroup*> *uiClientsBox, QObject *parent)
    : QObject(parent),
      m_uiClientsBox(uiClientsBox)
{
    m_clients.append(this);
   // QTimer::singleShot(1000, [&](){
    m_watchDog = new QTimer(this);
    connect(m_watchDog, &QTimer::timeout, this, &Client::handleWathdogTimeout);
    m_watchDog->setInterval(1000);
    m_watchDog->start();
   // });

}

Client::~Client()
{
//    releaseIdFlag(m_id);
    if (m_myUi != nullptr) {
        m_myUi->setItemState(ClientOffline);
    }

    // comment this because may cause crash
//    if (m_tcpSocket != nullptr && m_tcpSocket->state() == QTcpSocket::ConnectedState) {
//        m_tcpSocket->disconnectFromHost();
//    }
//     move to line before delete client; suspect this code may cause crash
//    if (m_clients.contains(this)) {
//        m_clients.removeOne(this);
//    }

}

void Client::handleWathdogTimeout()
{
    // client is lost
    if (m_currentLostTimes >= m_totalAllowedTimes) {
        if (m_myUi != nullptr) {
            m_myUi->setItemState(ClientOffline);
        } else {
            qDebug() <<__func__ << __LINE__;
        }
        emit toDestroy();
    } else {
        m_currentLostTimes++;
    }
}

void Client::setTcpSocket(QTcpSocket *newTcpSocket)
{
    if (newTcpSocket == nullptr) {
        return;
    }
    m_tcpSocket = newTcpSocket;
    m_in.setDevice(m_tcpSocket);
    m_in.setVersion(QDataStream::Qt_5_15);
    //QObject::connect(newTcpSocket, &QAbstractSocket::disconnected, qobject_cast<QObject*>(m_tcpSocket), &QObject::deleteLater);
    m_ip = m_tcpSocket->peerAddress();
    m_port = m_tcpSocket->peerPort();
    connect(m_tcpSocket, &QAbstractSocket::readyRead, this, &Client::handleSocketReadyRead);

//    connect(newClient, &Client::sigStateChanged, this, &Widget::handleClientStateChanged);
}

int Client::id() const
{
    return m_id;
}

void Client::sendCmdToServer(ClientDataType type, int value)
{
    if (m_tcpSocket == nullptr) return;
    if (m_tcpSocket->state() == QTcpSocket::ConnectedState) {
        if (m_tcpSocket->isWritable()) {
            QByteArray data;
            QDataStream out(&data, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_15);
            out << type << value;
            m_tcpSocket->write(data);
            qDebug() << __func__ << __LINE__ << "type:" << type << "value:" << value << m_tcpSocket->waitForBytesWritten(1000);
        } else {
            qDebug() << __func__ << __LINE__ << "m_tcpSocket->isWritable():" << m_tcpSocket->isWritable();
        }
    } else {
        qDebug() << __func__ << __LINE__ << m_tcpSocket->state();
    }
}

void Client::sendCmdToAllDevices()
{
    for (Client* client: m_clients) {
        if (client != nullptr) {
            client->startSkipCmd(true);
        }
    }
}

void Client::startSkipCmd(bool start)
{
    if (start) {
        sendCmdToServer(ClientActionType, ClientStartTest);
    } else {
        sendCmdToServer(ClientActionType, ClientStopTest);
    }
}

bool Client::idFlagHasBeenToken(int id)
{
    return m_allDeviceFlag & (1 << id);
}

quint16 Client::port() const
{
    return m_port;
}

const QHostAddress &Client::ip() const
{
    return m_ip;
}

void Client::updateIdFlag(int id)
{
    m_allDeviceFlag |= (1 << id);
}

void Client::releaseIdFlag(int id)
{
    m_allDeviceFlag &= (~(1 << id));
}

void Client::handleSocketReadyRead()
{
    m_in.startTransaction();

    int dataType;
    m_in >> dataType;

    switch (dataType) {
    // client should give an id to me to identify it
    case ClientIdType:
        m_in >> m_id;
        qDebug() << __func__ << __LINE__ << dataType << m_id;

        // add in next version
//        // id has been tooken, destroy and send cmd
//        if (idFlagHasBeenToken(m_id)) {
//            m_in.commitTransaction();
//            sendCmdToServer(ClientConflict, 0);
//            emit toDestroy();
////            QThread::msleep(5000);
////            deleteLater();
//            qDebug() << __func__ << __LINE__ << "ID is conflicted!";
//            return;
//        }

        if (m_id <= 0 || m_id > m_uiClientsBox->size()) {
            m_id = -1;
            qDebug() << __func__ << __LINE__ << "id is too small or to big" << m_id;
            return;
        }
//        updateIdFlag(m_id);
        m_myUi = m_uiClientsBox->at(m_id - 1);
        // update ui interface
        break;
    case ClientStateType:
        m_in >> m_state;
        qDebug() << __func__ << __LINE__ << dataType << m_state;
        // change ui state
        if (m_myUi == nullptr)
            return;

        m_myUi->setItemState(m_state);

//        emit sigStateChanged(m_id, m_state);
        break;


    case ClientWatchDog:
    {
        int dog = -1;
        m_in >> dog;
        if (m_watchDog != nullptr) {
            m_watchDog->start();
        }
        m_currentLostTimes = 0;
        break;
    }

    default:
        break;
    }
    bool commit = m_in.commitTransaction();
    if (!commit)
        return;
    // if it is state change update state change
}
