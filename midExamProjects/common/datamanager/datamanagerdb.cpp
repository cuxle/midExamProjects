#include "datamanagerdb.h"
#include "singleton.h"
#include "appconfig.h"

const auto STUDENTS_SQL =  QLatin1String(R"(
        create table students(zkh varchar(20), name varchar(20),  gender integer, zxdm varchar(20), zxmc varchar(20), id varchar(30)))");

const auto SCHOOLS_SQL =  QLatin1String(R"(
        create table schools(checked integer, zxdm varchar, zxmc varchar, downloaded integer))");


const auto INSERT_STUDENT_SQL = QLatin1String(R"(
        insert into students(zkh, name, gender, zxdm, zxmc, id)
                          values(?, ?, ?, ?, ?,?))");

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


QSqlError DataManagerDb::updateSchoolDownloadStatus(const QString &zxdm, int downloaded)
{
    QSqlQuery query;
    query.prepare("update schools set downloaded=? where zxdm=?");
    query.addBindValue(downloaded);
    query.addBindValue(zxdm);
    query.exec();

    return query.lastError();
}

QSqlError DataManagerDb::updateSchoolCheckedStatus(const QString &zxdm, int checked)
{
    QSqlQuery query;
    query.prepare("update schools set checked=? where zxdm=?");
    query.addBindValue(checked);
    query.addBindValue(zxdm);
    query.exec();
    qDebug() << __func__ << __LINE__ << zxdm << checked << query.lastError().text();
    return query.lastError();
}

void DataManagerDb::selectSchoolsChecked(QList<QString> &list)
{
    list.clear();
    QSqlQuery query;
    QString qstr = QString("SELECT * FROM schools where %1 = %2").arg("checked").arg(QString::number(2));
    query.prepare(qstr);
    query.exec();
    qDebug() << __func__ << __LINE__;
    int fieldNo = query.record().indexOf("zxdm");
    while (query.next()) {
        qDebug() << __func__ << __LINE__ << query.value(fieldNo);
        list.append(query.value(fieldNo).toString());
    }
}

void DataManagerDb::checkedAllSchools(bool checked)
{
    QSqlQuery query;
    query.prepare("update schools set checked=?");
    QString value;
    if (checked) {
        value = QString::number(2);
    } else {
        value = QString::number(0);
    }
    query.addBindValue(value);
    query.exec();
}


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
                const QString &zxdm, const QString &zxmc, const QString &id) {
    q.addBindValue(zkh);
    q.addBindValue(name);
    q.addBindValue(gender);
    q.addBindValue(zxdm);
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

QSqlError DataManagerDb::addSchool(int checked, const QString &zxdm, const QString &zxmc, int downloaded)
{
    qDebug() << __func__ << __LINE__ << zxdm << zxmc;
    QSqlQuery q;
    if (!q.prepare(INSERT_SCHOOL_SQL))
        return q.lastError();
    addSchoolPrivate(q, checked, zxdm, zxmc, downloaded);
    qDebug() << __func__ << __LINE__ << q.lastError().text();
    return QSqlError();
}

QSqlError DataManagerDb::addStudent(const QString &zkh, const QString &name, int gender, const QString &zxdm, const QString &zxmc, const QString &id)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_STUDENT_SQL))
        return q.lastError();
    addStudentPrivate(q, zkh, name, gender, zxdm, zxmc, id);
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

//QSqlError DataManagerDb::initDb()
//{
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(m_dataBasePath);

//    if (!db.open())
//        return db.lastError();

//    QStringList tables = db.tables();
//    if (tables.contains("studetns", Qt::CaseInsensitive)
//            && tables.contains("schools", Qt::CaseInsensitive)
//            && tables.contains("scores", Qt::CaseInsensitive))
//        return QSqlError();

//    QSqlQuery q;
//    if (!q.exec(SCHOOLS_SQL))
//        return q.lastError();
//    if (!q.exec(STUDENTS_SQL))
//        return q.lastError();
//    if (!q.exec(SCORES_SQL))
//        return q.lastError();

//    //        if (!q.prepare(INSERT_AUTHOR_SQL))
//    //            return q.lastError();
//    //        QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"), QDate(1920, 2, 1));
//    //        if (!q.prepare(INSERT_GENRE_SQL))
//    //            return q.lastError();
//    //        QVariant fantasy = addGenre(q, QLatin1String("Fantasy"));

//    //        if (!q.prepare(INSERT_BOOK_SQL))
//    //            return q.lastError();
//    //        addBook(q, QLatin1String("Foundation"), 1951, asimovId, sfiction, 3);
//    return QSqlError();
//}
