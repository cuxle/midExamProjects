#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QHash>
#include <QQueue>
#include <Student.h>
#include "datamanagerdb.h"

//struct ExamProject {
//    QString name;
//    QString value;
//    QString unit;
//    QString type;
//    bool valid = false;
//};

//struct IDCode {
//    QString id;
//    QString code;
//    bool operator == (const IDCode &idcode) {
//        return id == idcode.id && code == idcode.code;
//    }
//};

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);
    ~DataManager();
    void initReadTotalStudents();
    void initReadLocalStudents();
    void initReadLocalExamProjects();
    void initReadLocalIDCodes();
    void saveLocalIDCodes();
    void saveLocalStudents();
    void parseExamProjectJsonDoc(const QJsonDocument &doc);
    static void saveJsonToFile(const QByteArray &data, const QString &fileName);
    QJsonDocument readJsonToJsonDoc(const QString &fileName);
    void updateIdCode(const QString &id, const QString &code);
    void initDataBase();
    // zkh, student
    QHash<QString, Student*> m_totalStudents;  // read from total students json file
    QList<Student*> m_localExamedStudents;
    Student *m_curStudent;

    QHash<QString, ExamProject> m_examProjects;
    QQueue<Student*> m_uploadStudentQueue;
    ExamProject m_curExamInfo;

    IDCode m_curIdCode;

    QList<IDCode> m_idCodes;
    QString m_basePath;
};

#endif // DATAMANAGER_H
