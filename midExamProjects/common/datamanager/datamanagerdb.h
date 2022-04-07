#ifndef DATAMANAGERDB_H
#define DATAMANAGERDB_H

#include <QtSql>
#include "Student.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ExamProject {
public:
    ExamProject():valid(false){

    }
    QString name;
    QString value;
    QString unit;
    QString type;
    bool valid = false;
};

struct IDCode {
    QString id;
    QString code;
    bool operator == (const IDCode &idcode) {
        return id == idcode.id && code == idcode.code;
    }
};

class DataManagerDb
{
public:
    explicit DataManagerDb();
    static QSqlError addSchool(int checked, const QString &zxdm, const QString &zxmc, int downloaded);
    static QSqlError addStudent(const QString &zkh, const QString &name, int gender,
                    const QString &zxdm, const QString &zxmc, const QString &id);
    static QSqlError addExamproject(const QString &name, const QString &type, const QString &unit,const QString &value);
    static QSqlError addScore(const QString &zkh, const QString &name, int gender, const QString &examProject, int firstScore, int secondScore, int thirdScore,
                       bool midStopFist, bool midStopSecond, bool midStopThird, const QString &examTime, int uploadStatus, const QString &errorMsg, const QString &onSiteVide);

    static QSqlError updateSchoolDownloadStatus(const QString &zxdm, int downloaded);
    static QSqlError updateSchoolCheckedStatus(const QString &zxdm, int checked);
    static void selectSchoolsChecked(QList<QString> &list);
    static void checkedAllSchools(bool checked);
    static Student selectStudentByZkh(const QString &zkh);
    void parseExamProjectJsonDoc(const QJsonDocument &doc);

    void updateIdCode(const QString &id, const QString &code);

    IDCode m_curIdCode;
    ExamProject m_curExamInfo;
    QQueue<Student> m_uploadStudentQueue;
signals:
private:
//    QSqlError initDb();
    void initCurExamProject();

    ExamProject selectExamProjectByName(const QString &projectName);

    static void addSchoolPrivate(QSqlQuery &q, int checked,
                       const QString &zxdm, const QString &zxmc,
                       int downloaded);
    static void addStudentPrivate(QSqlQuery &q, const QString &zkh, const QString &name, int gender,
                    const QString &zxdm, const QString &zxmc, const QString &id);
    static void addScorePrivate(QSqlQuery &q,
                         const QString &zkh,
                         const QString &name,
                         int gender,
                         const QString &examProject,
                         int firstScore,
                         int secondScore,
                         int thirdScore,
                         bool midStopFist, bool midStopSecond, bool midStopThird,
                         const QString &examTime,
                         int uploadStatus,
                         const QString &errorMsg,
                         const QString &onSiteVide);



//    QHash<QString, ExamProject> m_examProjects;

//    QList<IDCode> m_idCodes;

    QList<IDCode> m_idCodes;

    QString m_curExamName;

    QString m_dataBasePath;
};

#endif // DATAMANAGERDB_H
