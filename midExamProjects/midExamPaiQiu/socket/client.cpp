#include "client.h"
#include "appconfig.h"
#include "singleton.h"
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include <QTimer>
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
    disconnect(this, &Client::destroyed, m_connectTimer, &QTimer::deleteLater);
    disconnect(this, &Client::destroyed, m_watchDogTimer, &QTimer::deleteLater);
    disconnect(this, &Client::destroyed, m_tcpSocket, &QTcpSocket::deleteLater);

    disconnect(m_watchDogTimer, &QTimer::timeout, this, &Client::handleSendWatchDog);

    //    m_out.setDevice(m_tcpSocket);
    //    m_out.setVersion(QDataStream::Qt_5_15);

    //    connect(m_tcpSocket, &QIODevice::readyRead, this, &Client::handleReadReady);
    //! [2] //! [4]
    disconnect(m_tcpSocket, &QAbstractSocket::errorOccurred,
            //! [3]
            this, &Client::displayError);



    disconnect(m_connectTimer, &QTimer::timeout, this, &Client::handleConnectServer);

    delete m_tcpSocket;
    delete m_watchDogTimer;
    delete m_connectTimer;
    m_tcpSocket = nullptr;
    m_watchDogTimer = nullptr;
    m_connectTimer = nullptr;
    this->deleteLater();
}


void Client::initClient()
{
        m_tcpSocket = (new QTcpSocket);
        m_connectTimer = (new QTimer);
        m_connectTimer->setInterval(2000);
        m_watchDogTimer = new QTimer;
        m_watchDogTimer->setInterval(1000);

        connect(this, &Client::destroyed, m_connectTimer, &QTimer::deleteLater);
        connect(this, &Client::destroyed, m_watchDogTimer, &QTimer::deleteLater);
        connect(this, &Client::destroyed, m_tcpSocket, &QTcpSocket::deleteLater);

        connect(m_watchDogTimer, &QTimer::timeout, this, &Client::handleSendWatchDog);

        //    m_out.setDevice(m_tcpSocket);
        //    m_out.setVersion(QDataStream::Qt_5_15);

        //    connect(m_tcpSocket, &QIODevice::readyRead, this, &Client::handleReadReady);
        //! [2] //! [4]
        connect(m_tcpSocket, &QAbstractSocket::errorOccurred,
                //! [3]
                this, &Client::displayError);



        connect(m_connectTimer, &QTimer::timeout, this, &Client::handleConnectServer);
        m_connectTimer->setInterval(1000);
        m_connectTimer->start();

}

void Client::handleSendWatchDog()
{
    sendCmdToServer(ClientWatchDog, 1);
}

void Client::handleConnectServer()
{
    m_connectTimer->stop();
    if (m_tcpSocket->state() != QTcpSocket::ConnectedState) {
        AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
        QString serverAddress = appconfig.m_sendCmdServerIp;
        m_tcpSocket->connectToHost(QHostAddress(serverAddress), 1234);

        if (m_tcpSocket->waitForConnected(3000)) {

//            connect(m_tcpSocket, &QAbstractSocket::disconnected, qobject_cast<QObject*>(m_tcpSocket), &QObject::deleteLater);
            connect(m_tcpSocket, &QAbstractSocket::readyRead, this, &Client::handleSocketReadyRead);
            connect(m_tcpSocket, &QAbstractSocket::disconnected, this, &Client::handleDisconnectFromServer);


            qRegisterMetaType<ClientState>("ClientState");
            emit sigClientStatusChanged(ClientOnline);
            // after connect to server wait server init client over, send client id
            QTimer::singleShot(500, [&](){
                sendCmdToServer(ClientIdType, m_id);
                QThread::msleep(200);
                sendCmdToServer(ClientStateType, ClientOnline);
                QThread::msleep(200);
                m_watchDogTimer->start();
                qDebug() << __func__ << __LINE__ << "connect to server!";
            });


        } else {
            qDebug() << "sockect tiem out!";
             m_connectTimer->start();
        }
    }
}

void Client::handleDisconnectFromServer()
{
    if (m_watchDogTimer != nullptr) {
        m_watchDogTimer->stop();
    };

    emit sigClientStatusChanged(ClientOffline);

    if (m_connectTimer != nullptr) {
        m_connectTimer->start();
    }

    disconnect(m_tcpSocket, &QAbstractSocket::readyRead, this, &Client::handleSocketReadyRead);
    disconnect(m_tcpSocket, &QAbstractSocket::disconnected, this, &Client::handleDisconnectFromServer);
}

void Client::sendCmdToServer(ClientDataType type, int value)
{
    if (m_tcpSocket == nullptr) return;
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
    if (m_tcpSocket == nullptr) return;
    if (error == QAbstractSocket::RemoteHostClosedError) {
        m_tcpSocket->disconnectFromHost();
        if (m_connectTimer != nullptr) {
            m_connectTimer->start();
        }
    }
    qDebug() << __func__ << __LINE__ << error;
}

void Client::handleReadReady()
{
    qDebug() << __func__ << __LINE__;
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
    qDebug() << __func__ << __LINE__ << dataType;
    switch (dataType) {
    case ClientIdType:
    {
        stream >> m_id;
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

void Client::updateState(ClientState state)
{
    return;
    //! [5]

        m_out.setVersion(QDataStream::Qt_5_15);

        m_out << m_id << (int)state;

    //! [4] //! [7]

}
