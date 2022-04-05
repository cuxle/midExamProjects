#ifndef DATAMANAGERDB_H
#define DATAMANAGERDB_H

#include <QtSql>

class DataManagerDb
{
public:
    static QSqlError addSchool(int checked, const QString &zxdm, const QString &zxmc, int downloaded);
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

    static QSqlError updateSchoolDownloadStatus(const QString &zxdm, int downloaded);
    static QSqlError updateSchoolCheckedStatus(const QString &zxdm, int checked);
    static void selectSchoolsChecked(QList<QString> &list);
    static void checkedAllSchools(bool checked);

signals:
private:
//    QSqlError initDb();


    static void addSchoolPrivate(QSqlQuery &q, int checked,
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
