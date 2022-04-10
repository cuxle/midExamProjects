#include "networkserver.h"
#include <QDir>
#include <QTimer>
#include <QLockFile>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QUrlQuery>
#include "singleton.h"
#include "appconfig.h"
#include "datamanagerdb.h"

NetWorkServer::NetWorkServer(QObject *parent)
    : QObject(parent)
{
    m_netWorkManager = new QNetworkAccessManager(this);
    connect(m_netWorkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    AppConfig &appConfig = Singleton<AppConfig>::GetInstance();
    m_base = appConfig.m_platAddress;
//    initLoginTimer();
//    initArbitrationTimer();
//    initHeartBeatTimer();
}

NetWorkServer::~NetWorkServer()
{
}

void NetWorkServer::requestFor(RequestType type)
{
    m_nextRequest = type;
    sendLoginInCmdRequest();
}

void NetWorkServer::handleNextRequest(RequestType type)
{
    switch(type) {
    case RequestLoginIn:
    {
        sendLoginInCmdRequest();
        break;
    }
    case RequestSchoolList:
    {
        sendGetSchoolListRequest();
        break;
    }
    case RequestCheckedSchoolStudents:
    {
        sendGetAllSchoolStudentsList();
//        sendGetCurrentSchoolStudentsRequest();
        break;
    }
    case RequestArbitrationList:
    {
        sendArbitrationListRequest();
        break;
    }
    case RequestUploadArbitrationVideo:
    {
        sendUploadArbitrationInfoRequst();
        break;
    }
    case RequestExamProject:
    {
        sendExamProjectRequest();
        break;
    }
    case RequestUploadAllExamedStudentScore:
    {
        sendUploadAllExamedStudentScore();
        break;
    }
    case RequestUploadStudentScore:
    {
        sendUploadStudentScore();
        break;
    }   
    default:
        break;
    }
}

QNetworkRequest NetWorkServer::makeHeartBeatRequst()
{
    QString requestTail = "/xuetong/business/biz/host/heartBeat";
    QString req = m_base + requestTail;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(QUrl(req));
    return request;
}

QNetworkRequest NetWorkServer::makeExamProjectRequst()
{
    QString requestTail = "/xuetong/business/biz/host/project";
    QString req = m_base + requestTail;
    qDebug() << __func__ << __LINE__ << req;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(m_tokenKey.toUtf8(), m_tokenValue.toUtf8());
    request.setUrl(QUrl(req));
    return request;
}

void NetWorkServer::sendExamProjectRequest()
{
    QNetworkRequest request = makeExamProjectRequst();
    m_currentRequest = RequestExamProject;
    QNetworkReply* reply = m_netWorkManager->get(request);
    qDebug() << __func__ << __LINE__;
    Q_UNUSED(reply);
}

void NetWorkServer::sendHeartBeatRequst()
{
    // TODO not sure what the data of the request till now
    QNetworkRequest request = makeHeartBeatRequst();
    m_currentRequest = RequestHeartBeat;
    QJsonDocument doc;
    QJsonObject obj;

    AppConfig &config = Singleton<AppConfig>::GetInstance();
    obj["devName"] = config.m_deviceId;

    doc.setObject(obj);
    QNetworkReply* reply = m_netWorkManager->post(request, doc.toJson());
    Q_UNUSED(reply);
}

void NetWorkServer::sendLoginInCmdRequest()
{
    DataManagerDb &manager = Singleton<DataManagerDb>::GetInstance();

    QJsonDocument doc;
    QJsonObject obj;

    obj["userName"] = manager.m_curIdCode.id;
    obj["password"] = manager.m_curIdCode.code;
    doc.setObject(obj);

    qDebug() << __func__ << __LINE__ << manager.m_curIdCode.id;
    qDebug() << __func__ << __LINE__ << manager.m_curIdCode.code;

    QNetworkRequest request = makeLoginRequest();
    m_currentRequest = RequestLoginIn;
    QNetworkReply* reply = m_netWorkManager->post(request, doc.toJson());
    Q_UNUSED(reply);
}

void NetWorkServer::sendGetSchoolListRequest()
{
    QNetworkRequest request = makeGetSchoolListRequest();
    m_currentRequest = RequestSchoolList;
    QNetworkReply* reply = m_netWorkManager->get(request);
    qDebug() << __func__ << __LINE__ ;
    Q_UNUSED(reply);
}

void NetWorkServer::sendGetCurrentSchoolStudentsRequest()
{
    if (m_schoolsToDownloadByZxdm.isEmpty()) return;

    QString zxdm = m_schoolsToDownloadByZxdm.front();

    QString requestTail = "/xuetong/business/biz/host/getCandidate";

    QString req = m_base + requestTail;
    QUrl url(req);

    QUrlQuery query;
    query.addQueryItem("zxdm", zxdm);
    url.setQuery(query.query());

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");

    m_currentRequest = RequestCurrentSchoolStudents;
    QNetworkReply* reply = m_netWorkManager->post(request, "");
    Q_UNUSED(reply);
}

void NetWorkServer::sendGetAllSchoolStudentsList()
{
    DataManagerDb::selectSchoolsChecked(m_schoolsToDownloadByZxdm);

    sendGetCurrentSchoolStudentsRequest();
}

QNetworkRequest NetWorkServer::makeUploadStudentScore()
{
    // read from loclStudentScore file of not uploaded students to a queue
    // maybe it can be accomplished by DataManager class
    QString requestTail = "/xuetong/business/biz/host/upload/result";

    QString req = m_base + requestTail;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setUrl(QUrl(req));
    return request;
}

/*
    1. upload unloaded students
    2. then request arbitration list
*/
void NetWorkServer::sendUploadAllExamedStudentScore()
{
    DataManagerDb &dataManager = Singleton<DataManagerDb>::GetInstance();
    dataManager.readUnUploadedStudents();
    sendUploadStudentScore();
}

void NetWorkServer::sendUploadStudentScore()
{
    //TODO 这里有个问题， DataManager中的queue何时更新呢
    // 1. 重新读取本地json文件
    // 2. 一次考试结束时，更新queue内容
    //TODO 何时保存呢
    // 1. queue 为空时，表示文件里的东西上传完了，可以保存一次
    DataManagerDb &dataManager = Singleton<DataManagerDb>::GetInstance();
    if (!dataManager.m_uploadStudentQueue.isEmpty()) {
        // form the current student upload info
        QJsonDocument doc;
        QJsonValue value;
        // get devName from appconfig
        AppConfig &config = Singleton<AppConfig>::GetInstance();

        Student curStudent = dataManager.m_uploadStudentQueue.front();
        QJsonArray array;
        for (int i = 1; i <= curStudent.examCount; i++) {
            QJsonObject obj;
            obj["examId"] = dataManager.m_curExamInfo.value;
            if (i == 1) {
                // 目前跳绳只有一次成绩，只上传firstscore
                obj["result"] = curStudent.firstScore;
                obj["gmtEnded"] = curStudent.examStopFirstTime;
                obj["gmtStarted"] = curStudent.examStartFirstTime;
                // midStop 是不是也应该有三次
                obj["other"] = curStudent.midStopFirst ? 1 : 0;
            } else if (i == 2) {
                // 目前跳绳只有一次成绩，只上传firstscore
                obj["result"] = curStudent.secondScore;
                obj["gmtEnded"] = curStudent.examStopSecondTime;
                obj["gmtStarted"] = curStudent.examStartSecondTime;
                // midStop 是不是也应该有三次
                obj["other"] = curStudent.midStopSecond ? 1 : 0;
            } else if (i == 3) {
                // 目前跳绳只有一次成绩，只上传firstscore
                obj["result"] = curStudent.thirdScore;
                obj["gmtEnded"] = curStudent.examStopThirdTime;
                obj["gmtStarted"] = curStudent.examStartThirdTime;
                // midStop 是不是也应该有三次
                obj["other"] = curStudent.midStopSecond ? 1 : 0;
            }

            obj["ksId"] = curStudent.id;

            //0 人工， 1， 设备， 2， 减考， 3，免考
            obj["resultType"] = 1;

            // 0, 必考项目; 1, 选考项目 TODO
            obj["type"] = 1;

            obj["devName"] = config.m_deviceId.toInt();

            // 0, 必考项目; 1, 选考项目
            obj["type"] = 1;

            qDebug() << "examId" << dataManager.m_curExamInfo.value;
            qDebug() << "gmtEnded" << curStudent.examStopFirstTime;
            qDebug() << "gmtStarted" << curStudent.examStartFirstTime;
            qDebug() << "ksId" << curStudent.id;
            qDebug() << "objKsId:" << obj["ksId"];
            qDebug() << "result" << curStudent.firstScore;
            array.append(obj);
        }

        doc.setArray(array);

//        qDebug() << doc;

        QNetworkRequest request = makeUploadStudentScore();
        m_currentRequest = RequestUploadStudentScore;
        QNetworkReply* reply = m_netWorkManager->post(request, doc.toJson());
        Q_UNUSED(reply);
    }
}

QNetworkRequest NetWorkServer::makeUploadArbititrationVideoRequest()
{
    // TODO not so sure how to add data to post file
    QString requestTail = "/xuetong/business/biz/host/arbitration/upload";

    QString req = m_base + requestTail;
    QNetworkRequest request;
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setRawHeader(m_tokenKey.toUtf8(), m_tokenValue.toUtf8());
    request.setUrl(QUrl(req));
    return request;
}

QNetworkRequest NetWorkServer::makeGetSchoolStudentsRequest(QString schooCode)
{
    QString requestTail = "/xuetong/business/biz/host/getCandidate";

    QString req = m_base + requestTail;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setUrl(QUrl(req));
    return request;
}

void NetWorkServer::sendUploadArbitrationInfoRequst()
{
    // id file name
    // get info from arbitration list
    // TODO not so sure how to add data to post file
    if (m_arbitrationEntityQueue.isEmpty()) {
        m_currentRequest = RequestInvalid;
//        m_heartBeatTimer->start();
        return;
    }

    QNetworkRequest request = makeUploadArbititrationVideoRequest();
    m_currentRequest = RequestUploadArbitrationVideo;

    ArbitrationEntity entity = m_arbitrationEntityQueue.front();

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart filePart;
    QFile m_file(entity.filePath);
    if (m_file.open(QIODevice::ReadOnly)) {
        qDebug() << __func__ << __LINE__ << "open file successfully";
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("video/mp4"));
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\";filename=\""+ m_file.fileName() + "\""));
        filePart.setBody(m_file.readAll());
        multiPart->append(filePart);
    } else {
        qDebug() << __func__ << __LINE__ << "open file failed";
    }

    QHttpPart idPart;
    idPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
    idPart.setBody(entity.id.toLatin1());
    multiPart->append(idPart);

    QHttpPart totalPart;
    totalPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"total\""));
    totalPart.setBody(QString::number(entity.total).toLatin1());
    multiPart->append(totalPart);

    QHttpPart typePart;
    typePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"type\""));
    typePart.setBody(QString::number(entity.type).toLatin1());
    multiPart->append(typePart);

    qDebug() << entity.filePath << entity.id << entity.total << entity.type;

    QNetworkReply* reply = m_netWorkManager->post(request, multiPart);
    multiPart->setParent(reply);
    Q_UNUSED(reply);
}

bool NetWorkServer::isLogin() const
{
    return m_isLogin;
}

QList<School *> &NetWorkServer::schools()
{
    return m_schools;
}

QNetworkRequest NetWorkServer::makeGetArbitrationListRequest()
{
    QString requestTail = "/xuetong/business/biz/host/arbitration/list";

    QString req = m_base + requestTail;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(m_tokenKey.toUtf8(), m_tokenValue.toUtf8());
    request.setUrl(QUrl(req));
    return request;
}

QNetworkRequest NetWorkServer::makeGetSchoolListRequest()
{
    QString requestTail = "/xuetong/business/biz/host/school";
    QString req = m_base + requestTail;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(QUrl(req));
    return request;
}

QNetworkRequest NetWorkServer::makeLoginRequest()
{
    QString url = m_base + "/xuetong/business/biz/host/login";
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    request.setUrl(QUrl(url));

    return request;
}

void NetWorkServer::requestFinished(QNetworkReply* reply)
{
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    } else {
        QStringList propertyNames;
        QStringList propertyKeys;
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        bool success = jsonObject["success"].toBool();
        qDebug() << __func__ << "--------cut line------------" << m_currentRequest;
        qDebug() << "status:" << jsonObject["code"].toInt();
        qDebug() << "success:" << jsonObject["success"].toBool();
        qDebug() << "msg:" << jsonObject["msg"].toString();
        qDebug() << "time:" << jsonObject["time"].toString();
        qDebug() << "json response:" << jsonResponse;
        switch (m_currentRequest) {
        case RequestLoginIn:
        {
            if (success) {
                m_isLogin = success;
                m_loginTime = jsonObject["time"].toString();

                // parse token
                QJsonObject obj = jsonObject["data"].toObject();
                m_tokenValue = obj["token"].toString();

                qDebug() << __func__ << __LINE__ << "m_isLogin:" << m_isLogin;
                qDebug() << __func__ << __LINE__ << "m_loginTime:" << m_loginTime;
                qDebug() << __func__ << __LINE__ << "m_currentToken:" << m_tokenValue;

                m_loginFailTimes = 0;
                handleNextRequest(m_nextRequest);
            } else {
                // no response also resend TODO
                if (m_loginFailTimes < 3) {
                    sendLoginInCmdRequest();
                }
                m_loginFailTimes++;
            }
            break;
        }
        case RequestSchoolList:
        {
            if (success) {
                m_schools.clear();
                while (!m_studentArray.empty()) {
                    m_studentArray.removeLast();
                }
                QJsonArray array = jsonObject["data"].toArray();
                for (int i = 0; i < array.size(); i++) {
                    QJsonObject schoolObj;
                    QJsonValue value = array[i];
                    QJsonObject obj = array[i].toObject();
//                    int id = obj["id"].toInt();
                    QString zxmc = obj["zxmc"].toString();
                    QString zxdm = obj["zxdm"].toString();

                    DataManagerDb::addSchool(0, zxdm, zxmc, 0);



                    emit sigSchoolListDataChanged();
                }

                handleNextRequest(RequestExamProject);
//                sendExamProjectRequest();
            }

            break;
        }
        case RequestCurrentSchoolStudents:
        {
            if (success) {
                // parse one school student
                QString zxdm = m_schoolsToDownloadByZxdm.front();
                DataManagerDb::updateSchoolDownloadStatus(zxdm, 1);
                emit sigSchoolDataDownloaded(true);
                m_schoolsToDownloadByZxdm.pop_front();

                // pasrse all student to joson file
                QJsonArray array = jsonObject["data"].toArray();  // students list
                for (int i = 0; i < array.size(); i++) {
                    QJsonObject obj = array[i].toObject();
                    QString zkh = obj["zkh"].toString();
                    QString name = obj["name"].toString();
                    int gender = obj["gender"].toInt();
                    QString zxdm = obj["zxdm"].toString();
                    QString zxmc = obj["zxmc"].toString();
                    QString id = obj["id"].toString();
//                    qDebug() << __func__ << zkh << name << gender << zxdm << zxmc << id;
                    DataManagerDb::addStudent(zkh, name, gender, zxdm, zxmc, id);
                }
                if (!m_schoolsToDownloadByZxdm.isEmpty()) {
//                    handleNextRequest(RequestCurrentSchoolStudents);
                    sendGetCurrentSchoolStudentsRequest();
                }
                break;
            }

        }
        case RequestArbitrationList:
        {
            if (success) {
                m_requestArbitrationListFailedTimes = 0;
                AppConfig &config = Singleton<AppConfig>::GetInstance();
                QString curDevName = config.m_deviceId;
                // if there is arbitration info request upload the request in a queue, post one by one

                QJsonArray array = jsonObject["data"].toArray();
                for (int i = 0; i < array.size(); i++) {
                    QJsonObject obj = array[i].toObject();
                    ArbitrationResponse response;
                    response.alongtime = obj["alongTime"].toString();
                    // TODO 设备号与本机设备号不一致直接退出
                    response.devName = obj["devName"].toString();

                    // TODO 设备号与本机设备号不一致直接退出
                    if (response.devName.isEmpty() || response.devName != curDevName) {
                        qDebug() << __func__ << __LINE__ << response.devName << curDevName << "devName not be compatible";
                        continue;
                    }

                    response.id = obj["id"].toString();
                    response.pictureReq = obj["picture"].toInt();
                    response.project = obj["project"].toString();
                    response.videoReq = obj["video"].toInt();
                    response.zkh = obj["zkh"].toString();
    //                m_arbitrationResponseQueue.append(response);

                    // arbitration id
                    // zkh -> video nums:total, video path
                    // type : video and picture
                    QString zkh = response.zkh;

                    // type 1 视频 2轨迹图
                    // need upload picture
                    if (response.pictureReq == 1) {
                        QString curStuVideoPath = config.m_videoSavePath + "/video/" + zkh + "/";
                        QDir dir(curStuVideoPath);
                        QStringList filters;
                        filters << "*.png";
                        dir.setNameFilters(filters);
                        // 不存在这个考生视频，直接推出
                        if (!dir.exists()) {
                            qDebug() << __func__ << __LINE__ << "student folder not found , continue;";
                            continue;
                        } else {
                            QStringList pictures = dir.entryList(QDir::Files);
                            ArbitrationEntity entity;
                            entity.total = pictures.size();
                            entity.id = obj["id"].toString();
                            entity.type = 0;
                            for (auto &item : pictures) {
                                entity.filePath = curStuVideoPath + item;
                                qDebug() << __func__ << __LINE__ << entity.filePath;
                                entity.type = 2;
                                m_arbitrationEntityQueue.push_back(entity);
                            }
                        }
                    }
                    // need upload video
                    if (response.videoReq == 1) {
                        QString curStuVideoPath = config.m_videoSavePath + "/video/" + zkh + "/";

                        QDir dir(curStuVideoPath);
                        QStringList filters;
                        filters << "*.mp4";
                        dir.setNameFilters(filters);

                        if (!dir.exists()) {
                            qDebug() << __func__ << __LINE__ << curStuVideoPath << "student folder not found , continue;";
                            continue;
                        } else {
                            qDebug() << __func__ << __LINE__ << "student " << zkh << "found;";

                            QStringList videos = dir.entryList(QDir::Files);
                            ArbitrationEntity entity;
                            entity.total = videos.size();
                            entity.id = obj["id"].toString();
                            entity.type = 0;
                            for (auto &item : videos) {
                                entity.filePath = curStuVideoPath + item;
                                entity.type = 1;
                                m_arbitrationEntityQueue.push_back(entity);
                            }
                        }

                    }

                }
                sendUploadArbitrationInfoRequst();
            }
            else {
                if (m_requestArbitrationListFailedTimes < 3) {
                    sendArbitrationListRequest();
                }
                m_requestArbitrationListFailedTimes++;
            }
            break;
        }
        case RequestUploadArbitrationVideo:
        {
            if (success) {
                qDebug() << __func__ << __LINE__ << "upload success" << "RequestUploadArbitrationVideo";
                m_requestUploadArbitrationVideoFailTimes = 0;
                // post one entity from queue successfully

                m_arbitrationEntityQueue.pop_front();
//                m_arbitrationEntityFailedTimes = 0;

                sendUploadArbitrationInfoRequst();
            } else {
                if (m_requestUploadArbitrationVideoFailTimes < 3) {
                    sendUploadArbitrationInfoRequst();
                }
                m_requestUploadArbitrationVideoFailTimes ++;
            }

            break;
        }
        case RequestExamProject:
        {
            if (success) {
                m_requestExamProjectFailedTimes = 0;
                // parse exam project to DataManager
                DataManagerDb &dataManager = Singleton<DataManagerDb>::GetInstance();
                dataManager.parseExamProjectJsonDoc(jsonResponse);             
            } else {
                // success: false
                // retry 3 times still failed re login                
                if (m_requestExamProjectFailedTimes < 3) {
                    handleNextRequest(RequestExamProject);
//                    sendExamProjectRequest();
                }
                m_requestExamProjectFailedTimes++;
            }
            break;
        }
        case RequestUploadStudentScore:
        {
            // if request queue is not empty, continue to request
            // if request queue is empty, transfer to next request            
            // send request upload based on request info list
            // TODO format to discuss
            DataManagerDb &dataManager = Singleton<DataManagerDb>::GetInstance();
            qDebug() << __func__ << __LINE__ << "upload success:" << success;
            qDebug() << __func__ << __LINE__ << "response:" << jsonResponse;
            if (success) {
                // upload one student score success                
                Student curStudent = dataManager.m_uploadStudentQueue.front();

                QJsonObject dataObj = jsonObject["data"].toObject();
                curStudent.uploadStatus = dataObj["uploadStatus"].toInt(); // upload 1 success 0 failed

                DataManagerDb::updateStudentScoreUploadStatus(curStudent);


                emit sigStudentScoreUploaded();

                dataManager.m_uploadStudentQueue.pop_front();
                m_sendUploadFailedTimes = 0;

                if (!dataManager.m_uploadStudentQueue.isEmpty()) {
                    sendUploadStudentScore();
                } else {
                    // 发送视频仲裁列表请求， 视频过大暂时不发，20220208 TODO
                    handleNextRequest(RequestArbitrationList);
//                    sendArbitrationListRequest();
                }
            } else {
                if (m_sendUploadFailedTimes < 3) {
                    // 失败三次就重新登录了
                    sendUploadStudentScore();
                } else {
                    // pop one element if this student upload failed > 3 times
                    if (!dataManager.m_uploadStudentQueue.isEmpty()) {
                        dataManager.m_uploadStudentQueue.pop_front();
                    }
                    sendUploadStudentScore();
                    m_sendUploadFailedTimes = 0;
                    break;
                }
                m_sendUploadFailedTimes ++;
            }

            break;
        }
        case RequestHeartBeat:
        {
            // 0. what if request failed
            // failed 3 次 启动重新连接接口
            if (success) {
                // 1. stop the heart beat timer
                m_heartBeatTimer->stop();

                // 2. sent the arbiti list request
//                sendArbitrationListRequest();
                // 2. upload local students value  -- 2022/1/25
                sendUploadStudentScore();
            } else {
                m_requestHeartBeatFailTimes++;
                if (m_requestHeartBeatFailTimes > 3) {
                    m_requestHeartBeatFailTimes = 0;
                    sendLoginInCmdRequest();
                } else {
                    QTimer::singleShot(500, [&](){
                        sendHeartBeatRequst();
                    });
                }
            }
            break;

        }
        case RequestInvalid:
        {
            qDebug() << __func__ << "request invalid";
            break;
        }
        default:
            break;
        }
        // 获取返回内容
        reply->deleteLater();
    }
}

void NetWorkServer::sendArbitrationListRequest()
{
    QNetworkRequest request = makeGetArbitrationListRequest();
    m_currentRequest = RequestArbitrationList;
    QNetworkReply* reply = m_netWorkManager->post(request, "");
    Q_UNUSED(reply);
}
