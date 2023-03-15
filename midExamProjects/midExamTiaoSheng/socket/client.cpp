#include "client.h"
#include "appconfig.h"
#include "singleton.h"
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>

Client::Client(int devId, const QString &ip, QObject *parent)
    : QObject(parent),
      m_id(devId),
      m_serverIp(QHostAddress(ip))
{

}

Client::~Client()
{

}

void Client::destroyClient()
{
    //    m_out.setDevice(m_tcpSocket);
    //    m_out.setVersion(QDataStream::Qt_5_15);

    //    connect(m_tcpSocket, &QIODevice::readyRead, this, &Client::handleReadReady);

    this->deleteLater();
}


void Client::initClient()
{
        m_tcpSocket = QSharedPointer<QTcpSocket>(new QTcpSocket);
        m_connectTimer = QSharedPointer<QTimer>(new QTimer);
        m_connectTimer->setInterval(2000);
        m_feedDogTimer = QSharedPointer<QTimer>(new QTimer);
        m_feedDogTimer->setInterval(1000);

        connect(m_feedDogTimer.data(), &QTimer::timeout, this, &Client::handleFeedWatchDog);

        //    m_out.setDevice(m_tcpSocket);
        //    m_out.setVersion(QDataStream::Qt_5_15);

        //    connect(m_tcpSocket, &QIODevice::readyRead, this, &Client::handleReadReady);
        //! [2] //! [4]
        connect(m_tcpSocket.data(), &QAbstractSocket::errorOccurred,
                //! [3]
                this, &Client::displayError);



        connect(m_connectTimer.data(), &QTimer::timeout, this, &Client::handleConnectServer);

        m_connectTimer->setInterval(1000);
        m_connectTimer->start();

        m_waitAckTimer =QSharedPointer<QTimer>(new QTimer);
        m_waitAckTimer->setInterval(1500);
        connect(m_waitAckTimer.data(), &QTimer::timeout, this, &Client::handleWatchDogAckExceeds);

}

void Client::handleWatchDogAckExceeds()
{
    if (m_curLoseTimes > m_totalAllowedTimes) {
        m_curLoseTimes = 0;
        handleDisconnectFromServer();
        qDebug() << __func__ << __LINE__ << "watchdog Ack timer exceeds!" << QDateTime::currentDateTime();
    }
    m_curLoseTimes++;
    qDebug() << __func__ << __LINE__  << m_curLoseTimes;
}

void Client::handleFeedWatchDog()
{
    sendCmdToServer(ClientWatchDog, m_id);

    // after send feed watchdog, wait for the server response 1.5s exceeds
    if (!m_waitAckTimer->isActive()) {
        m_waitAckTimer->start();
    }

}

void Client::handleConnectServer()
{
    qDebug() << __func__ << __LINE__ << m_tcpSocket->state() << QDateTime::currentDateTime();
    m_connectTimer->stop();
    if (m_tcpSocket->state() != QTcpSocket::ConnectedState) {
        AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
        QString serverAddress = appconfig.m_sendCmdServerIp;
        m_tcpSocket->connectToHost(QHostAddress(serverAddress), 1234);

        if (m_tcpSocket->waitForConnected(3000)) {

//            connect(m_tcpSocket, &QAbstractSocket::disconnected, qobject_cast<QObject*>(m_tcpSocket), &QObject::deleteLater);
            connect(m_tcpSocket.data(), &QAbstractSocket::readyRead, this, &Client::handleSocketReadyRead);
            connect(m_tcpSocket.data(), &QAbstractSocket::disconnected, this, &Client::handleDisconnectFromServer);

            qRegisterMetaType<ClientState>("ClientState");

            setClientState(ClientOnline);

            // after connect to server wait server init client over, send client id
            QTimer::singleShot(500, [&](){
                qDebug() << __func__ << __LINE__ << "connect to server!";
                sendCmdToServer(ClientIdType, m_id);
                QThread::msleep(200);
                sendCmdToServer(ClientStateType, ClientOnline);
                QThread::msleep(200);
                m_feedDogTimer->start();
            });


        } else {
            qDebug() << "sockect tiem out!";
            m_connectTimer->start();
        }
    }
}

void Client::handleDisconnectFromServer()
{
    if (!m_feedDogTimer.isNull()) {
        m_feedDogTimer->stop();
    };    
    if (!m_waitAckTimer.isNull()) {
        m_waitAckTimer->stop();
    }

    if (!m_connectTimer.isNull()) {
        m_connectTimer->start();
    }

    disconnect(m_tcpSocket.data(), &QAbstractSocket::readyRead, this, &Client::handleSocketReadyRead);
    disconnect(m_tcpSocket.data(), &QAbstractSocket::disconnected, this, &Client::handleDisconnectFromServer);

    m_tcpSocket->disconnectFromHost();

    // send signal to UI
    setClientState(ClientOffline);
}

void Client::setClientState(ClientState state)
{
    m_curState = state;
    emit sigClientStatusChanged(state);
}

void Client::sendCmdToServer(ClientDataType type, int value)
{
    if (m_tcpSocket.isNull()) return;
    if (m_tcpSocket->state() == QTcpSocket::ConnectedState) {
        if (m_tcpSocket->isWritable()) {
            QByteArray data;
            QDataStream out(&data, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_15);
            qDebug() << __func__ << __LINE__ << type << value;
            out << type << value;
            m_tcpSocket->write(data);
//            qDebug() << __func__ << __LINE__ << m_tcpSocket->waitForBytesWritten(1000);
        } else {
            qDebug() << __func__ << __LINE__ << "m_tcpSocket->isWritable():" << m_tcpSocket->isWritable();
        }
    } else {
        qDebug() << __func__ << __LINE__ << m_tcpSocket->state();
    }
}

void Client::displayError(QAbstractSocket::SocketError error)
{
    if (m_tcpSocket.isNull()) return;
    if (error == QAbstractSocket::RemoteHostClosedError) {
        m_tcpSocket->disconnectFromHost();
        if (!m_connectTimer.isNull()) {
            m_connectTimer->start();
        }
    }
    qDebug() << __func__ << __LINE__ << error;
}

//void Client::setTcpSocket(QTcpSocket *newTcpSocket)
//{
//    m_tcpSocket = newTcpSocket;
//    m_in.setDevice(m_tcpSocket);
//    m_in.setVersion(QDataStream::Qt_5_15);
//    QObject::connect(newTcpSocket, &QAbstractSocket::disconnected, qobject_cast<QObject*>(m_tcpSocket), &QObject::deleteLater);
//    m_ip = m_tcpSocket->localAddress();
//    m_port = m_tcpSocket->localPort();
//    connect(m_tcpSocket, &QAbstractSocket::readyRead, this, &Client::handleSocketReadyRead);
//}

int Client::id() const
{
    return m_id;
}

void Client::handleSocketReadyRead()
{
    if (m_tcpSocket == nullptr) return;
    QByteArray in = m_tcpSocket->readAll();;
    QDataStream stream(&in, QIODevice::ReadOnly);
//    stream.startTransaction();

    int dataType;
    stream >> dataType;
    qDebug() << __func__ << __LINE__ << dataType ;
    switch (dataType) {
    case ClientIdType:
    {
        stream >> m_id;
        break;
    }
    case ClientWatchDogAck:
    {
        int id = 0;
        stream >> id;
        qDebug() << __func__ << __LINE__ << "got feedDog Ack from Server" <<  QDateTime::currentDateTime();
        m_waitAckTimer->stop();
        m_feedDogTimer->start();
        m_curLoseTimes = 0;
        break;
    }
    case ClientActionType:
    {
        bool start = false;
        stream >> start;
        emit sigStartTest(start);
        qDebug() << __func__ << __LINE__ << dataType;
        break;
    }

    default:
        break;
    }

//    if (!stream.commitTransaction())
//        return;
    // if it is state change update state change
}

void Client::setId(int newId)
{
    m_id = newId;
}
