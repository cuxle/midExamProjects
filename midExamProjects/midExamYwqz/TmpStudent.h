﻿#ifndef TMPSTUDENT_H
#define TMPSTUDENT_H

#include <QString>

struct TmpStudent {
    bool isOnline = false;
    int bcjszt;
    QString bctyxm;
    QString bctyxmcj;
    QString bjdm;
    int gender;
    QString id;
    QString jdh;
    QString name;
    QString picture;
    bool pictureFlag;
    int printTimes;
    QString qy;
    QString serialNum;
    QString sfzPicture;
    QString sfzZp;
    QString sfzh;
    int usualResults;
    unsigned long long version;
    int xcjszt1;
    int xcjszt2;
    QString xctyxm1;
    QString xctyxm2;
    QString xctyxmcj1;
    QString xctyxmcj2;
    QString zkh;
    QString zp;
    QString zpStr;
    QString zt;
    QString zxdm;
    QString zxmc;

    int firstScore = 0;
    int secondScore = 0;
    int thirdScore = 0;

    bool midStopFirst = false;
    bool midStopSecond = false;
    bool midStopThird = false;

    QString examTime;

    QString examStartFirstTime;
    QString examStopFirstTime;

    QString examStartSecondTime;
    QString examStopSecondTime;

    QString examStartThirdTime;
    QString examStopThirdTime;

    int examCount = 1;

    int uploadStatus;
    QString errorMsg;
    QString videoPath;
    QString examProjectName;
};

#endif // TMPSTUDENT_H
