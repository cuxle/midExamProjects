#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>

class FormBaseGroup;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QTcpServer;
class Client;
class QMediaPlayer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pbBackStep_clicked();
    void handleNewClientConnection();
    void handleClientStateChanged(int id, int State);
    void on_pbStartAll_clicked();
    void handleClientDestroyed();

    void on_pbRefreshStatus_clicked();

    void on_pbTestSound_clicked();

    void updateDisplayTimer();

    void on_pbNextGroup_clicked();

    void on_cmbExamTimeChoose_currentIndexChanged(int index);

private:
    Ui::Widget *ui;

    void initCommonToolbar();
    void initServer();
    void initClientsBox();
    void setItemId(FormBaseGroup *gb, int id);
    void initFontDatabase();
    void initMediaPlayer();
    void initTimers();
    void setLeftTime(int leftTimeMs);
    void handleStartExam();
    void stopExamStuff();

    void startTestUiStuff(bool start);

    QList<FormBaseGroup*> m_uiClientsBox;

    QList<Client*> m_clients;

    QTcpServer *tcpServer = nullptr;

    QMediaPlayer *m_mp3Player = nullptr;
    QTimer *m_backCountTimer = nullptr;
    QTimer *m_startDelayTimer = nullptr;
    QString m_currentMp3File;

    int m_curTimeLeftMs = 0;
    int m_totalTimeMs = 30*1000;
    const int m_internal = 100;

    int m_currentGroup = 1;
//    QMap<int, Client*> m_clients;
};
#endif // WIDGET_H
