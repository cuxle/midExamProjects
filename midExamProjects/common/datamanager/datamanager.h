#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QHash>
#include <QQueue>
#include <TmpStudent.h>

struct ExampProject {
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

    // zkh, student
    QHash<QString, TmpStudent*> m_totalStudents;  // read from total students json file
    QList<TmpStudent*> m_localExamedStudents;
    TmpStudent *m_curStudent;

    QHash<QString, ExampProject> m_examProjects;
    QQueue<TmpStudent*> m_uploadStudentQueue;
    ExampProject m_curExamInfo;

    QList<IDCode> m_idCodes;
    IDCode m_curIdCode;

    QString m_basePath;
};

#endif // DATAMANAGER_H
