#ifndef DATAMANAGERDB_H
#define DATAMANAGERDB_H

#include <QtSql>
#include "Student.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "xlsxdocument.h"
#include "utils.h"

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
    static QSqlError addStudentsFromExecl(const QString &execlName);
    static QSqlError addSchool(int checked, const QString &zxdm, const QString &zxmc, int downloaded);
    static QSqlError addStudent(const QString &zkh, const QString &name, int gender,
                    const QString &zxdm, const QString &zxmc, const QString &id);
    static QSqlError addExamproject(const QString &name, const QString &type, const QString &unit,const QString &value);
//    static QSqlError addScore(const QString &zkh, const QString &name, int gender, const QString &examProject, int firstScore, int secondScore, int thirdScore,
//                       bool midStopFist, bool midStopSecond, bool midStopThird, const QString &examTime, int uploadStatus, bool isOnline, const QString &errorMsg, const QString &onSiteVide);
    static QSqlError addScore(const Student &student);
    static QSqlError updateStudentScoreUploadStatus(const Student &student);
    static QSqlError updateSchoolDownloadStatus(const QString &zxdm, int downloaded);
    static QSqlError updateSchoolCheckedStatus(const QString &zxdm, int checked);
    static void selectSchoolsChecked(QList<QString> &list);
    static void checkedAllSchools(bool checked);
    static Student selectStudentByZkh(const QString &zkh);
    void parseExamProjectJsonDoc(const QJsonDocument &doc);
    void readUnUploadedStudents();
    void updateIdCode(const QString &id, const QString &code);
    static QDateTime getValidDateTimeOfStudent(Student &student);

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
    static void addScorePrivate(QSqlQuery &q, const Student &student);

    QSqlError addIdCode(const QString &id);
//    static void addScorePrivate(QSqlQuery &q,
//                         const QString &zkh,
//                         const QString &name,
//                         int gender,
//                         const QString &examProject,
//                         int firstScore,
//                         int secondScore,
//                         int thirdScore,
//                         bool midStopFist, bool midStopSecond, bool midStopThird,
//                         const QString &examTime,
//                         int uploadStatus,
//                         bool isOnline,
//                         const QString &errorMsg,
//                         const QString &onSiteVide);



//    QHash<QString, ExamProject> m_examProjects;

//    QList<IDCode> m_idCodes;

    QList<IDCode> m_idCodes;

    QString m_curExamName;

    QString m_dataBasePath;

    QDateTime deadlineDateTime = QDateTime::fromString("2023-04-26 23:59:59", Utils::strFormat.chopped(4));
};

#endif // DATAMANAGERDB_H
