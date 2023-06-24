#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QDateTime>
#include <algorithm>
#include <limits>

class Student {
public:
    Student();

    void initTimeExam();

    void initCountExam();

    QString getFinalScoreByTime();

    QString getFinalScoreByCount();

    bool isValid;
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
//    const int int_max = (std::numeric_limits<int>::max)();
//    const int int_min = (std::numeric_limits<int>::min)();

    const int int_max = 10;
    const int int_min = 1;


    //
    //
    /*
     * 1. for football basketball
     *      valid score is [0, 199999] ms
     *      invalid score is std::number_limits<int>::max()
     *      final result is min element
     * 2. for count exam
     *      valid score is [0, 199999]
     *      invalid score is std::number_limits<int>::min()
     *      final result is max element

    */
    std::vector<int> scores;

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

    bool operator==(const Student& rhs) const
    {
        return this->zkh == rhs.zkh;
    }

    // Overloaded assignment
    Student& operator= (const Student& fraction);
private:
    int getFinalExamResultByTime();

    int getFinalExamResultByCount();
};

#endif // TMPSTUDENT_H
