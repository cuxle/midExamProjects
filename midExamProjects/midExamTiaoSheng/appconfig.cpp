#include "appconfig.h"

#include <QDir>
#include <QSettings>
#include <QDebug>
#include "log/Logger.h"

AppConfig::AppConfig(QObject *parent) : QObject(parent)
{
    readConfig();
}

AppConfig::~AppConfig()
{
    qDebug() << __func__ << __LINE__;
    writeConfig();
    Logger::destroy();
}

void AppConfig::writeConfig()
{
    QSettings settings(m_company, m_appName);
    settings.beginGroup("NETWORK");
    settings.setValue("PLATADDRESS", m_platAddress);
    settings.setValue("DEVICEID", m_deviceId);
    qDebug() << __func__ << __LINE__ << "DEVICEID:" << m_deviceId;
    settings.setValue("FACEIDSIXLAST", m_faceIdLastSixNum);
    settings.setValue("SENDCMDSERVER", m_sendCmdServerIp);
    settings.setValue("APPMODE", m_appMode);
    settings.endGroup();
    qDebug() << __func__ << __LINE__ << "APPMODE:" << m_appMode;

    settings.beginGroup("VIDEO");
    settings.setValue("IPCADDRESS", m_ipcAddress);
    settings.setValue("IPCUSERNAME", m_ipcUserName);
    settings.setValue("IPCCODE", m_ipcCode);
    settings.endGroup();


    settings.beginGroup("EXAM");
    settings.setValue("EXAMPROJECT", m_examProject);
    settings.setValue("EXAMNUMS", m_examNums);
    settings.setValue("VIDEOSAVEPATH", m_videoSavePath);
    settings.setValue("EXAMTIME", m_examTime);
    settings.endGroup();


    settings.beginGroup("CHECK");
    settings.setValue("ANGLE", m_angleProbe);
    settings.setValue("PROBESIZE", m_probeSize);
    settings.setValue("PROBESENSITIVE", m_probeSensitive);
    settings.setValue("BASEFRAMEUPDATESENSITIVE", m_baseFrameRefreshSensitive);
    settings.endGroup();

    settings.beginGroup("UserNames");
    settings.beginWriteArray("UserNameArray", m_userNameslist.size());
    for (int i = 0; i < m_userNameslist.size(); i++) {
        settings.setArrayIndex(i);
        QString key = QString("UserName%1").arg(i);
        settings.setValue(key, m_userNameslist.at(i));
    }
    settings.endArray();
    settings.endGroup();
//    settings.beginGroup("UDS");
//    settings.setValue("CDD_FILE_PATH", m_cddFilePath);
//    settings.setValue("PROJECT_CONFIG_PATH", m_projectConfigPath);
//    settings.setValue("SECACCFUNCBLOCK_SCRIPT_PATH", m_secAccFuncBlockScriptPath);
//    settings.setValue("LOG_FILE_PATH", m_logFilePath);
//    settings.setValue("DBC_FILE_PATH", m_dbcFilePath);
//    settings.setValue("LDF_FILE_PATH", m_ldfFilePath);
//    settings.setValue("FIBEX_FILE_PATH", m_fibexFilePath);
//    settings.setValue("DOWNLOAD_FUNCBLOCK_FILE_PATH", m_downloadfuncBlockFilePath);
//    settings.endGroup();
}

void AppConfig::readConfig()
{
    QSettings settings(m_company, m_appName);
    settings.beginGroup("NETWORK");
    m_platAddress = settings.value("PLATADDRESS", "http://121.227.30.61:8787/").toString();
    m_deviceId = settings.value("DEVICEID", "1").toString();
    m_faceIdLastSixNum = settings.value("FACEIDSIXLAST", "3").toString();
    m_sendCmdServerIp = settings.value("SENDCMDSERVER", "192.168.0.254").toString();
    m_appMode = settings.value("APPMODE", "OFFLINE").toString();
    settings.endGroup();
    qDebug() << __func__ << __LINE__ << "APPMODE:" << m_appMode;

    settings.beginGroup("VIDEO");
    m_ipcAddress = settings.value("IPCADDRESS").toString();
    m_ipcUserName = settings.value("IPCUSERNAME").toString();
    m_ipcCode = settings.value("IPCCODE").toString();
    settings.endGroup();

    settings.beginGroup("EXAM");
    //m_examProject = settings.value("EXAMPROJECT", "跳绳").toString();
	m_examProject = "跳绳";
    m_examNums = settings.value("EXAMNUMS").toInt();
    m_videoSavePath = settings.value("VIDEOSAVEPATH").toString();
    m_examTime = settings.value("EXAMTIME", 0).toInt();
    settings.endGroup();

    settings.beginGroup("CHECK");
    m_angleProbe = settings.value("ANGLE").toString();
    m_probeSize = settings.value("PROBESIZE").toString();
    m_probeSensitive = settings.value("PROBESENSITIVE").toString();
    m_baseFrameRefreshSensitive = settings.value("BASEFRAMEUPDATESENSITIVE").toString();
    settings.endGroup();

    settings.beginGroup("UserNames");
    int size = settings.beginReadArray("UserNameArray");
    for (int i = 0; i < size; i++) {
        settings.setArrayIndex(i);
        QString key = QString("UserName%1").arg(i);
        QString value = settings.value(key).toString();
        if (value.isEmpty()) continue;
        m_userNameslist.append(settings.value(key).toString());
    }
    settings.endArray();
    settings.endGroup();

//    settings.beginGroup("UDS");
//    m_cddFilePath = settings.value("CDD_FILE_PATH", QDir::currentPath()).toString();
//    m_projectConfigPath = settings.value("PROJECT_CONFIG_PATH", QDir::currentPath()).toString();
//    m_secAccFuncBlockScriptPath = settings.value("SECACCFUNCBLOCK_SCRIPT_PATH", QDir::currentPath()).toString();
//    m_logFilePath = settings.value("LOG_FILE_PATH", QDir::homePath()).toString();
//    m_dbcFilePath = settings.value("DBC_FILE_PATH", QDir::currentPath()).toString();
//    m_ldfFilePath = settings.value("LDF_FILE_PATH", QDir::currentPath()).toString();
//    m_fibexFilePath = settings.value("FIBEX_FILE_PATH", QDir::currentPath()).toString();
//    m_downloadfuncBlockFilePath = settings.value("DOWNLOAD_FUNCBLOCK_FILE_PATH", QDir::currentPath()).toString();
//    settings.endGroup();
}
