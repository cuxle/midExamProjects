#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QFile>
#include <QQueue>
#include <QHttpMultiPart>

#include "Student.h"

// TODO 1. add login function
// TODO 2. add download school catgray function
// TODO 3. add download students from one school function
// TODO 4. add upload students score info function
struct School {
    bool checked;
    int id;
    QString schoolName;
    QString qxdm; // 区县代码
    QString qxmc; // 区县名称
    QString zxdm; // 中学代码
    QString zxmc; // 中学名称
    QString createdTime;
    QString updatedTime;
    int status;
//    QList<Student> studentList;
};

struct ArbitrationResponse {
    QString alongtime;
    QString devName;
    QString id;
    int pictureReq;
    QString project;
    int videoReq;
    QString zkh;
};

struct ArbitrationEntity {
    QString id;
    QString filePath;
    int total;
    int type;
};


class NetWorkServer : public QObject
{

    Q_OBJECT
public:
    enum RequestType{
        RequestLoginIn,
        RequestSchoolList,
        RequestCheckedSchoolStudents,
        RequestCurrentSchoolStudents,
        RequestArbitrationList,
        RequestUploadArbitrationVideo,
        RequestHeartBeat,
        RequestExamProject,
        RequestUploadAllExamedStudentScore,
        RequestUploadStudentScore,
        RequestInvalid
    };

    explicit NetWorkServer(QObject *parent = nullptr);
    ~NetWorkServer();
    void requestFor(RequestType type);
    void sendLoginInCmdRequest();
    void sendGetSchoolListRequest();
    void sendGetCurrentSchoolStudentsRequest();
//    void sendGetCurrentSchoolStudentsRequest(QString schoolCode);
    void sendGetAllSchoolStudentsList();
    void sendUploadStudentScore();
    void sendUploadAllExamedStudentScore();

    QQueue<School *> m_schoolsToDownload;
    QQueue<QString> m_schoolsToDownloadByZxdm;
    QList<School *> &schools();

    bool isLogin() const;

    bool m_isNotUploading = true;
    bool m_isOnlyLogin = true;

private slots:
    void requestFinished(QNetworkReply* reply);
    void sendArbitrationListRequest();
    void sendHeartBeatRequst();

signals:
    void sigLoginStateChanged(bool loginSucess);
    void sigSchoolListDataChanged();
    void sigSchoolDataDownloaded(bool);

private:
    QNetworkRequest makeLoginRequest();
    QNetworkRequest makeGetSchoolListRequest();
    QNetworkRequest makeGetArbitrationListRequest();
    QNetworkRequest makeGetSchoolStudentsRequest(QString schooCode);
    QNetworkRequest makeUploadArbititrationVideoRequest();
    QNetworkRequest makeHeartBeatRequst();
    QNetworkRequest makeExamProjectRequst();
    QNetworkRequest makeUploadStudentScore();

    void handleNextRequest(RequestType type);

    void sendExamProjectRequest();
    void sendUploadArbitrationInfoRequst();
    void initLoginTimer();
    void initArbitrationTimer();
    void initHeartBeatTimer();

    QNetworkAccessManager* m_netWorkManager = nullptr;

    const QString m_base = "http://xunlian.55555.io:8030";

    QMap<QString, School*> m_schoolMap; // zxdm 中学代码
    QList<School*> m_schools;

    // login information
    QString m_currentId;
    QString m_currentCode;
    //QString m_currenttoken;
    RequestType m_currentRequest = RequestInvalid;
    bool m_isLogin = false;
    QString m_loginTime;

    QJsonDocument m_schooldoc;
    QJsonArray m_schoolArray;
    QJsonObject m_schoolObj;

//    QJsonDocument m_studentDoc;
    QJsonArray m_studentArray;
//    QJsonObject m_studentObj;

    QFile m_schoolsFile;
    QFile m_studentsFile;

    QTimer *m_loginTimer = nullptr;
    QTimer *m_arbitrationTimer = nullptr;
    QQueue<ArbitrationResponse*> m_arbitrationResponseQueue;
    QQueue<ArbitrationEntity> m_arbitrationEntityQueue;
    QTimer *m_heartBeatTimer = nullptr;

    QString m_tokenKey = "Authorization";
    QString m_tokenValue;
    int m_arbitratonInternals = 30*1000;
    int m_heartBeatInternals = 60*1000;
    int m_loginInternals = 10*1000;

    int m_sendUploadFailedTimes = 0;
    int m_arbitrationEntityFailedTimes = 0;
    int m_requestExamProjectFailedTimes = 0;
    int m_requestArbitrationListFailedTimes = 0;
    int m_requestUploadArbitrationVideoFailTimes = 0;
    int m_requestHeartBeatFailTimes = 0;
    int m_loginFailTimes = 0;

    RequestType m_nextRequest = RequestInvalid;
};

#endif // NETWORKSERVER_H
