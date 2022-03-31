#include "datamanager.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "singleton.h"
#include "appconfig.h"
#include <QLockFile>
#include <QThread>

DataManager::DataManager(QObject *parent)
    : QObject(parent)
{
    // old code
    AppConfig &config = Singleton<AppConfig>::GetInstance();
    m_basePath = config.m_videoSavePath;
    initReadTotalStudents();
    initReadLocalStudents();
    initReadLocalExamProjects();

    // by sql
    initDataBase();

}

void DataManager::initDataBase()
{
    // init database

    // create three table
    // totalStudent
    // local student
    // school list
}

DataManager::~DataManager()
{
    // 1. save local exam students in local folder
    saveLocalIDCodes();
}

void DataManager::initReadTotalStudents()
{
    m_totalStudents.clear();

    // read student information from json file
    QString fileName = m_basePath + "/data/totalStudents.json";

    QJsonDocument jdc = readJsonToJsonDoc(fileName);
    if (jdc.isEmpty()) {
        return;
    }
    QJsonObject obj = jdc.object();
    QJsonArray array = obj["students"].toArray();
    for (int i = 0; i < array.size(); i++) {
        QJsonObject oobj = array[i].toObject();
        QString bctyxm = oobj["bctyxm"].toString();
        QString xctyxm1 = oobj["xctyxm1"].toString();
        QString xctyxm2 = oobj["xctyxm2"].toString();

        TmpStudent *student = new TmpStudent;
        QJsonObject obj = array[i].toObject();
        student->zkh = obj["zkh"].toString();
        student->name = obj["name"].toString();
        student->gender = obj["gender"].toInt();
        student->bctyxm = obj["bctyxm"].toString();
        student->xctyxm1 = obj["xctyxm1"].toString();
        student->xctyxm2 = obj["xctyxm2"].toString();
        student->firstScore = obj["firstScore"].toInt();
        student->secondScore = obj["secondScore"].toInt();
        student->thirdScore = obj["thirdScore"].toInt();
        student->examTime = obj["examTime"].toString();
        student->uploadStatus = obj["uploadStatus"].toInt();
        student->errorMsg = obj["errorMsg"].toString();
        student->videoPath = obj["onSiteVideo"].toString();
        student->zxmc = obj["zxmc"].toString();
        student->id = obj["id"].toString();
//        qDebug() << __func__ << __LINE__ << student->id << obj["id"].toString();
//        student->examProject = examProject;
        m_totalStudents.insert(student->zkh, student);
    }
}

void DataManager::initReadLocalStudents()
{
    m_uploadStudentQueue.clear();
    m_localExamedStudents.clear();
    // read student information from json file
    QString fileName = m_basePath + "/data/localStudents.json";
    QJsonDocument jdc = readJsonToJsonDoc(fileName);
    QJsonObject obj = jdc.object();
    QJsonArray array = obj["students"].toArray();
    qDebug() << __func__ << __LINE__ << array.size();
    for (int i = 0; i < array.size(); i++) {
        QJsonObject oobj = array[i].toObject();
        QString bctyxm = oobj["bctyxm"].toString();
        QString xctyxm1 = oobj["xctyxm1"].toString();
        QString xctyxm2 = oobj["xctyxm2"].toString();

        TmpStudent *student = new TmpStudent;
        QJsonObject obj = array[i].toObject();
        student->zkh = obj["zkh"].toString();
        student->name = obj["name"].toString();
        student->gender = obj["gender"].toInt();
        student->bctyxm = obj["bctyxm"].toString();
        student->xctyxm1 = obj["xctyxm1"].toString();
        student->xctyxm2 = obj["xctyxm2"].toString();
        student->firstScore = obj["firstScore"].toInt();
        student->secondScore = obj["secondScore"].toInt();
        student->thirdScore = obj["thirdScore"].toInt();
        student->examTime = obj["examTime"].toString();
        student->examStartFirstTime = obj["examStartFirstTime"].toString();
        student->examStopFirstTime = obj["examStopFirstTime"].toString();
        student->examStartSecondTime = obj["examStartSecondTime"].toString();
        student->examStopSecondTime = obj["examStopSecondTime"].toString();
        student->examStartThirdTime = obj["examStartThirdTime"].toString();
        student->examStopThirdTime = obj["examStopThirdTime"].toString();
        student->uploadStatus = obj["uploadStatus"].toInt();
        student->errorMsg = obj["errorMsg"].toString();
        student->videoPath = obj["onSiteVideo"].toString();
        student->zxmc = obj["zxmc"].toString();
        student->uploadStatus = obj["uploadStatus"].toInt();
        student->isOnline = obj["isOnline"].toBool();
        student->examProjectName = obj["examProjectName"].toString();
        student->id = obj["id"].toString();
        if (student->uploadStatus == 0 && student->isOnline) {
            m_uploadStudentQueue.push_back(student);
        }
        m_localExamedStudents.push_back(student);
    }
}

void DataManager::initReadLocalExamProjects()
{
    QString fileName = m_basePath + "/data/localExamProjects.json";
    QJsonDocument jdc = readJsonToJsonDoc(fileName);
    parseExamProjectJsonDoc(jdc);
}

void DataManager::initReadLocalIDCodes()
{
    QString fileName = m_basePath + "/data/localIDCodes.json";
    QJsonDocument jdc = readJsonToJsonDoc(fileName);
    QJsonObject obj = jdc.object();
    QJsonArray array = obj["data"].toArray();
    for (int i = 0; i < array.size(); i++) {
        QJsonObject localObj = array[i].toObject();
        IDCode idCode;
        idCode.id = localObj["ID"].toString();
        idCode.code = localObj["Code"].toString();
        m_idCodes.append(idCode);
    }
}

void DataManager::saveLocalIDCodes()
{
    QJsonArray array;
    for (int i = 0; i < m_idCodes.size(); i++) {
        QJsonObject localObj;
        localObj["CODE"] = m_idCodes.at(i).code;
        localObj["ID"] = m_idCodes.at(i).id;
        array.append(localObj);
    }

    QJsonObject obj;
    obj["students"] = array;

    QJsonDocument jsondoc;
    jsondoc.setObject(obj);
    QString fileName = m_basePath + "/data/localIDCodes.json";
    saveJsonToFile(jsondoc.toJson(), fileName);
}

void DataManager::parseExamProjectJsonDoc(const QJsonDocument &doc)
{
    if (doc.isEmpty()) return;
    QJsonObject obj = doc.object();
    QJsonArray array = obj["data"].toArray();
    for (int i = 0; i < array.size(); i++) {
        QJsonObject oobj = array[i].toObject();
        ExampProject localExamProject;
        localExamProject.name = oobj["name"].toString();
        localExamProject.type = oobj["type"].toString();
        localExamProject.unit = oobj["unit"].toString();
        localExamProject.value = oobj["value"].toString();
        m_examProjects.insert(localExamProject.name, localExamProject);
    }
    AppConfig &config = Singleton<AppConfig>::GetInstance();
    QString currentExamName = config.m_examProject;
    if (m_examProjects.contains(currentExamName)) {
        m_curExamInfo = m_examProjects[currentExamName];
        m_curExamInfo.valid = true;
    }
}

void DataManager::saveLocalStudents()
{
    QJsonArray array;
    for (int i = 0; i < m_localExamedStudents.size(); i++) {
        QJsonObject localObj;
        TmpStudent *student = m_localExamedStudents.at(i);
        localObj["zkh"] = student->zkh;
        localObj["name"] = student->name;
        localObj["gender"] = student->gender;
        localObj["bctyxm"] = student->bctyxm;
        localObj["xctyxm1"] = student->xctyxm1;
        localObj["xctyxm2"] = student->xctyxm2;
        localObj["firstScore"] = student->firstScore;
        localObj["secondScore"] = student->secondScore;
        localObj["thirdScore"] = student->thirdScore;
        localObj["examTime"] = student->examTime;
        localObj["uploadStatus"] = student->uploadStatus;
        localObj["errorMsg"] = student->errorMsg;
        localObj["onSiteVideo"] = student->videoPath;
        localObj["zxmc"] = student->zxmc;
        localObj["examStartFirstTime"] = student->examStartFirstTime;
        localObj["examStopFirstTime"] = student->examStopFirstTime;
        localObj["examStartSecondTime"] = student->examStartSecondTime;
        localObj["examStopSecondTime"] = student->examStopSecondTime;
        localObj["examStartThirdTime"] = student->examStartThirdTime;
        localObj["examStopThirdTime"] = student->examStopThirdTime;
        localObj["isOnline"] = student->isOnline;
        localObj["examProjectName"] = student->examProjectName;
        localObj["id"] = student->id;
        array.append(localObj);
    }

    QJsonObject obj;
    obj["students"] = array;

    QJsonDocument jsondoc;
    jsondoc.setObject(obj);

    QString fileName = m_basePath + "/data/localStudents.json";
    saveJsonToFile(jsondoc.toJson(), fileName);
}

void DataManager::saveJsonToFile(const QByteArray &data, const QString &fileName)
{
//    QString m_lockFilePath = QDir::currentPath() + "/data/lockfile";

//    QLockFile lockFile(m_lockFilePath);
//    while (lockFile.isLocked()) {
//        QThread::msleep(20);
//    }

    QFile file(fileName);
    // file not exists, create new file
    QFileInfo fileInfo(fileName);

    QDir dir(fileInfo.absolutePath());
    if (!dir.exists()) {
        dir.mkdir(fileInfo.absolutePath());
    }

    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }
    file.write(data);
    file.close();
}

QJsonDocument DataManager::readJsonToJsonDoc(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open failed!";
        return QJsonDocument();
    } else {
        qDebug() <<"File open successfully!";
    }
    QJsonParseError error;
    QJsonDocument jdc = QJsonDocument::fromJson(file.readAll(), &error);
    qDebug() << __func__ << __LINE__ <<error.errorString();
    return jdc;
}

void DataManager::updateIdCode(const QString &id, const QString &code)
{
    m_curIdCode.id = id;
    m_curIdCode.code = code;
    if (!m_idCodes.contains(m_curIdCode)) {
        m_idCodes.append(m_curIdCode);
        qDebug() << "id code append m_idCodes";
    } else {
        qDebug() << "m_idCodes contains id code";
    }
}
