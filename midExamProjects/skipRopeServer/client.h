#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QHostAddress>
#include <QDataStream>

#include "formbasegroup.h"
#include <QTcpSocket>

class QTcpSocket;
class FormBaseGroup;


enum ClientDataType {
    ClientIdType,
    ClientStateType,
    ClientActionType,
    ClientWatchDog
};

class Client : public QObject
{
//    enum ClientState {
//        ClientStoped,
//        ClientRunning,
//        ClientInvalid
//    };



    Q_OBJECT
public:
    explicit Client(QList<FormBaseGroup*> *uiClientsBox, QObject *parent = nullptr);
    ~Client();
    void setTcpSocket(QTcpSocket *newTcpSocket);

    int id() const;

    void startSkipCmd(bool);

    void sendCmdToServer(ClientDataType type, int value);

    static unsigned int m_allDeviceFlag;
    
	static QList<Client*> m_clients;
    
	static void sendCmdToAllDevices();
	
    const QHostAddress &ip() const;

    quint16 port() const;

signals:
    void sigStateChanged(int id, int state);
    void toDestroy();

private slots:
    void handleSocketReadyRead();
    void handleWathdogTimeout();

private:    
    void updateIdFlag(int id);
    void releaseIdFlag(int id);
    bool idFlagHasBeenToken(int id);

    int m_id = -1; // 此id为设备自身设置的id
    QHostAddress m_ip;
    QString m_macAddress;
    quint16 m_port = 0;
    QTcpSocket *m_tcpSocket = nullptr;

    ClientState m_state = ClientInvalid;
    QDataStream m_in;
    FormBaseGroup *m_myUi = nullptr;;

    QList<FormBaseGroup*> *m_uiClientsBox;

    QTimer *m_watchDog = nullptr;

    int m_totalAllowedTimes = 3;
    int m_currentLostTimes = 0;

};

#endif // CLIENT_H
