#ifndef STUDENTINDICATOR_H
#define STUDENTINDICATOR_H

#include <QObject>

class QLabel;

class ClientIndicator : public QObject
{
    Q_OBJECT
public:
    enum ClinetState {
        ClientDisconnect,
        ClientStopped,
        ClientConnected,
        ClientExaming
    };
    explicit ClientIndicator(QObject *parent = nullptr);

    void setLabel(QLabel *newLabel);

    void setId(int newId);

    void setState(ClinetState newState);

signals:
private:
    QLabel *m_label;
    int m_id = -1;
    ClinetState m_state;
};

#endif // STUDENTINDICATOR_H
