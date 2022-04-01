#ifndef DATAMANAGERDB_H
#define DATAMANAGERDB_H

#include <QObject>
#include <QtSql>

class DataManagerDb : public QObject
{
    Q_OBJECT
public:
    explicit DataManagerDb(QObject *parent = nullptr);
    QSqlError addSchool(int checked, const QString &zxdm, const QString &zxmc, int downloaded);
    QSqlError addStudent(const QString &zkh, const QString &name, int gender,
                    const QString &zxmc, const QString &id);
    QSqlError addScore(const QString &zkh,
                  const QString &name,
                  int gender,
                  const QString &examProject,
                  const QString &firstScore,
                  const QString &secondScore,
                  const QString &thirdScore,
                  const QString &examTime,
                  int uploadStatus,
                  const QString &errorMsg,
                  const QString &onSiteVide);


signals:
private:
    QSqlError initDb();


    void addSchoolPrivate(QSqlQuery &q, int checked,
                       const QString &zxdm, const QString &zxmc,
                       int downloaded);
    void addStudentPrivate(QSqlQuery &q, const QString &zkh, const QString &name, int gender,
                    const QString &zxmc, const QString &id);
    void addScorePrivate(QSqlQuery &q, const QString &zkh,
                  const QString &name,
                  int gender,
                  const QString &examProject,
                  const QString &firstScore,
                  const QString &secondScore,
                  const QString &thirdScore,
                  const QString &examTime,
                  int uploadStatus,
                  const QString &errorMsg,
                  const QString &onSiteVide);


    QString m_dataBasePath;
};

#endif // DATAMANAGERDB_H
