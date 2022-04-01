#include "datamanagerdb.h"
#include "singleton.h"
#include "appconfig.h"

const auto STUDENTS_SQL =  QLatin1String(R"(
    create table students(id integer primary key, zkh varchar, name varchar,  gender int, zxdm vchar, zxmc vchar))");

const auto SCHOOLS_SQL =  QLatin1String(R"(
    create table schools(id integer primary key, checked integer, zxdm varchar, zxmc varchar, downloaded integer))");


const auto INSERT_STUDENT_SQL = QLatin1String(R"(
    insert into students(zkh, year, name, gender, zxdm, zxmc)
                      values(?, ?, ?, ?, ?, ?))");

const auto INSERT_SCHOOL_SQL = QLatin1String(R"(
    insert into schools(checked, zxdm, zxmc, downloaded)
                      values(?, ?, ?, ?))");

const auto SCORES_SQL = QLatin1String(R"(
    create table scores(id integer primary key,
    zkh varchar,
    name varchar,
    gender interger,
    project varchar
    firstScore varchar,
    secondScore varchar,
    thirdScore varchar,
    examTime varchar,
    uploadStatus int,
    errorMsg varchar,
    onSiteVideo varchar))");

const auto INSERT_SCORE_SQL = QLatin1String(R"(
    insert into scores(zkh, name, gender, project, firstScore, secondScore, thirdScore,
                       examTime, uploadStatus, errorMsg, onSiteVide)
                       values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?))");

void DataManagerDb::addSchoolPrivate(QSqlQuery &q, int checked,
                   const QString &zxdm, const QString &zxmc,
                   int downloaded)
{
    q.addBindValue(checked);
    q.addBindValue(zxdm);
    q.addBindValue(zxmc);
    q.addBindValue(downloaded);
    q.exec();
}

void DataManagerDb::addStudentPrivate(QSqlQuery &q, const QString &zkh, const QString &name, int gender,
                const QString &zxmc, const QString &id) {
    q.addBindValue(zkh);
    q.addBindValue(name);
    q.addBindValue(gender);
    q.addBindValue(zxmc);
    q.addBindValue(id);
    q.exec();
}


void DataManagerDb::addScorePrivate(QSqlQuery &q, const QString &zkh,
              const QString &name,
              int gender,
              const QString &examProject,
              const QString &firstScore,
              const QString &secondScore,
              const QString &thirdScore,
              const QString &examTime,
              int uploadStatus,
              const QString &errorMsg,
              const QString &onSiteVide)
{
    q.addBindValue(zkh);
    q.addBindValue(name);
    q.addBindValue(gender);
    q.addBindValue(examProject);
    q.addBindValue(firstScore);
    q.addBindValue(secondScore);
    q.addBindValue(thirdScore);
    q.addBindValue(examTime);
    q.addBindValue(uploadStatus);
    q.addBindValue(errorMsg);
    q.addBindValue(onSiteVide);
    q.exec();
}

DataManagerDb::DataManagerDb(QObject *parent) : QObject(parent)
{
    AppConfig &m_config = Singleton<AppConfig>::GetInstance();
    m_dataBasePath = m_config.m_videoSavePath + "/data/database.db";
}

QSqlError DataManagerDb::addSchool(int checked, const QString &zxdm, const QString &zxmc, int downloaded)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_SCHOOL_SQL))
        return q.lastError();
    addSchoolPrivate(q, 0, zxdm, zxmc, downloaded);
    return QSqlError();
}

QSqlError DataManagerDb::addStudent(const QString &zkh, const QString &name, int gender, const QString &zxmc, const QString &id)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_STUDENT_SQL))
        return q.lastError();
    addStudentPrivate(q, zkh, name, gender, zxmc, id);
    return QSqlError();
}

QSqlError DataManagerDb::addScore(const QString &zkh, const QString &name, int gender, const QString &examProject, const QString &firstScore, const QString &secondScore, const QString &thirdScore,
                                  const QString &examTime, int uploadStatus, const QString &errorMsg, const QString &onSiteVide)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_SCORE_SQL))
        return q.lastError();
    addScorePrivate(q, zkh, name, gender, examProject, firstScore, secondScore, thirdScore, examTime, uploadStatus, errorMsg, onSiteVide);
    return QSqlError();
}

QSqlError DataManagerDb::initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(m_dataBasePath);

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("studetns", Qt::CaseInsensitive)
            && tables.contains("schools", Qt::CaseInsensitive)
            && tables.contains("scores", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if (!q.exec(SCHOOLS_SQL))
        return q.lastError();
    if (!q.exec(STUDENTS_SQL))
        return q.lastError();
    if (!q.exec(SCORES_SQL))
        return q.lastError();

    //        if (!q.prepare(INSERT_AUTHOR_SQL))
    //            return q.lastError();
    //        QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"), QDate(1920, 2, 1));
    //        if (!q.prepare(INSERT_GENRE_SQL))
    //            return q.lastError();
    //        QVariant fantasy = addGenre(q, QLatin1String("Fantasy"));

    //        if (!q.prepare(INSERT_BOOK_SQL))
    //            return q.lastError();
    //        addBook(q, QLatin1String("Foundation"), 1951, asimovId, sfiction, 3);
    return QSqlError();
}
