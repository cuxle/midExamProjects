#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QHostAddress>
#include <QDataStream>

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
        ClientIdType,
        ClientStateType,
        ClientActionType,
        ClientWatchDog
    };

    Q_OBJECT
public:
    explicit Client(int devId, const QString &ip, QObject *parent = nullptr);
    ~Client();
    void setTcpSocket(QTcpSocket *newTcpSocket);

    int id() const;

    void setId(int newId);

    void updateState(ClientState state);

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
    void handleReadReady();
    void handleConnectServer();
    void handleDisconnectFromServer();
    void handleSendWatchDog();


private:
    void sendCmdToServer(ClientDataType type, int value);

    int m_id = 1; // 此id为设备自身设置的id
    QHostAddress m_serverIp;
    QString m_macAddress;
    quint16 m_port = 0;
    QTcpSocket *m_tcpSocket = nullptr;
    ClientState m_state;
    QDataStream m_out;

    QTimer *m_connectTimer = nullptr;
    QTimer *m_watchDogTimer = nullptr;
};

#endif // CLIENT_H
