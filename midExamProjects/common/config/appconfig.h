#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>

class AppConfig : public QObject
{
    Q_OBJECT
public:
    explicit AppConfig(QObject *parent = nullptr);
    ~AppConfig();
    QString m_cddFilePath;
    QString m_projectConfigPath;
    QString m_secAccFuncBlockScriptPath;
    QString m_logFilePath;
    QString m_dbcFilePath;
    QString m_ldfFilePath;
    QString m_fibexFilePath;
    QString m_downloadfuncBlockFilePath;

    // network setting
    QString m_platAddress;
    QString m_deviceId;
    QString m_faceIdLastSixNum;
    QString m_sendCmdServerIp;
    QString m_appMode; // online, offline

    // video setting
    QString m_ipcAddress;
    QString m_ipcUserName;
    QString m_ipcCode;

    // exam setting
    QString m_examProject;
    int m_examNums;
    QString m_videoSavePath;
    int m_examTime = 0; // 0 : 60s; 1:30s

    // check setting
    QString m_angleProbe;
    QString m_probeSize;
    QString m_probeSensitive;
    QString m_baseFrameRefreshSensitive;
#if FOOTBALL
    float m_radius = 0.2f;
    float m_clusterTolerance = 0.5;
    int m_minClusterSize = 5;
    int m_maxClusterSize = 200;
    float m_zMin = 0;
    float m_zMax = 0;
    float m_ratio = 1.0f;

    int m_examReginTopLeftX = 0;
    int m_examReginTopLeftY = 0;
    int m_examReginBottomRightX = 0;
    int m_examReginBottomRightY = 0;

    int m_rectReginTopLeftX = 0;
    int m_rectReginTopLeftY = 0;
    int m_rectReginWidth = 0;
    int m_rectReginHeight = 0;

    float m_deltaAngle = 0;
    float m_x_rangeStart = 0;
    float m_x_rangeEnd = 5;
    float m_y_rangeStart = 0;
    float m_y_rangeEnd = 5;
#endif
    int m_point1x;
    int m_point1y;

    int m_point2x;
    int m_point2y;

    int m_point3x;
    int m_point3y;

    int m_rectPoint1x;
    int m_rectPoint1y;

    int m_rectPoint2x;
    int m_rectPoint2y;

    int m_rectHeight;
    int m_rectWidth;

	QStringList m_userNameslist;

signals:

private:
    void writeConfig();
    void readConfig();

    const QString m_company = "100YearSchool";
    const QString m_appName = "MidExam";
};

#endif // APPCONFIG_H
