#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QHostAddress>
#include <QDataStream>
#include <QSharedPointer>

class QTcpSocket;


class Client : public QObject
{
public:
//    enum ClientState {
//        ClientStoped,
//        ClientRunning,
//        ClientInvalid
//    };

    enum ClientState{
        ClientOnline,
        ClientOffline,
        ClientHasStudent,
        ClientNoStudent,
        ClientInvalid
    };

    enum ClientDataType {
        ClientIdType = 0,
        ClientStateType,
        ClientActionType,
        ClientWatchDog,
        ClientWatchDogAck,
        ClientExamFinished
    };

    Q_OBJECT
public:
    explicit Client(int devId, const QString &ip, QObject *parent = nullptr);
    ~Client();

    int id() const;

    void setId(int newId);

signals:
    void sigStateChanged(int id, int state);
    void sigStartTest(bool start);
    void sigClientStatusChanged(ClientState state);
    void sigClientConflict();

public slots:
    void initClient();
    void destroyClient();

private slots:
    void handleSocketReadyRead();
    void displayError(QAbstractSocket::SocketError error);
    void handleConnectServer();
    void handleDisconnectFromServer();
    void handleFeedWatchDog();
    void handleWatchDogAckExceeds();
    void setClientState(ClientState state);


private:
    void sendCmdToServer(ClientDataType type, int value);

    int m_id = 1; // 此id为设备自身设置的id
    QHostAddress m_serverIp;
    QString m_macAddress;
    quint16 m_port = 0;

    ClientState m_curState;
    QDataStream m_out;

    QSharedPointer<QTcpSocket> m_tcpSocket;
    QSharedPointer<QTimer> m_connectTimer;
    QSharedPointer<QTimer> m_feedDogTimer;
    QSharedPointer<QTimer> m_waitAckTimer;
    const int m_totalAllowedTimes = 3;
    int m_curLoseTimes = 0;
};

#endif // CLIENT_H
