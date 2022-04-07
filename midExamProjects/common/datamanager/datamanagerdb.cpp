#include "datamanagerdb.h"
#include "singleton.h"
#include "appconfig.h"

const auto STUDENTS_SQL =  QLatin1String(R"(
        create table students(zkh varchar(20), name varchar(20),  gender integer, zxdm varchar(20), zxmc varchar(20), id varchar(30)))");

const auto SCHOOLS_SQL =  QLatin1String(R"(
        create table schools(checked integer, zxdm varchar unique, zxmc varchar unique, downloaded integer))");

const auto INSERT_STUDENT_SQL = QLatin1String(R"(
        insert into students(zkh, name, gender, zxdm, zxmc, id)
                          values(?, ?, ?, ?, ?, ?))");

const auto INSERT_SCHOOL_SQL = QLatin1String(R"(
        insert into schools(checked, zxdm, zxmc, downloaded)
                          values(?, ?, ?, ?))");

const auto EXAMPROJECTS_SQL =  QString::fromLocal8Bit(R"(
        create table examprojects(name varchar(15), type varchar(15), unit varchar(15), value varchar(20))");

const auto INSERT_EXAMPROJECT_SQL = QString::fromLocal8Bit(R"(
        insert into examprojects(name, type, unit, value)
                          values(?, ?, ?, ?))");

const auto SCORES_SQL = QLatin1String(R"(
        create table scores(zkh varchar(20),
        name varchar(10),
        gender interger,
        project varchar(10),
        firstScore integer,
        secondScore integer,
        thirdScore integer,
        midStopFirst integer,
        midStopSecond integer,
        midStopThird integer,
        examTime varchar(40),
        uploadStatus integer,
        isOnline integer,
        errorMsg varchar(40),
        onSiteVideo varchar(40)))");

const auto INSERT_SCORE_SQL = QLatin1String(R"(
        insert into scores(zkh, name, gender, project, firstScore, secondScore, thirdScore,
                           midStopFirst, midStopSecond, midStopThird, examTime, uploadStatus, isOnline, errorMsg, onSiteVideo)
                           values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?))");


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


void DataManagerDb::addScorePrivate(QSqlQuery &q,
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
                                    bool isOnline,
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
    q.addBindValue(midStopFist);
    q.addBindValue(midStopSecond);
    q.addBindValue(midStopThird);
    q.addBindValue(examTime);
    q.addBindValue(uploadStatus);
    q.addBindValue(isOnline);
    q.addBindValue(errorMsg);
    q.addBindValue(onSiteVide);
    q.exec();
    qDebug() << __func__ << __LINE__ << q.lastError().text();
}

DataManagerDb::DataManagerDb()
{
    AppConfig &config = Singleton<AppConfig>::GetInstance();
    m_dataBasePath = config.m_videoSavePath + "/data/";
    m_curExamName = config.m_examProject;

    qDebug() << __func__ << __LINE__ << m_curExamName;

    ExamProject project = selectExamProjectByName(m_curExamName);
    if (project.valid) {
        m_curExamInfo.name = project.name;
        m_curExamInfo.type = project.type;
        m_curExamInfo.value = project.value;
        m_curExamInfo.unit = project.unit;
        m_curExamInfo.valid = true;
    }
}

ExamProject DataManagerDb::selectExamProjectByName(const QString &projectName)
{
    ExamProject project;
    QSqlQuery query;
    // not working
    // QString qstr = QString::fromLocal8Bit("SELECT * FROM examprojects where name = %1").arg(projectName);

    QString qstr = QString::fromLocal8Bit("SELECT * FROM examprojects");

    query.prepare(qstr);
    query.exec();
    qDebug() << __func__ << __LINE__ <<query.lastError().text();
    int filedNoPType = query.record().indexOf("type");
    int filedNoName = query.record().indexOf("name");
    int filedNoUnit = query.record().indexOf("unit");
    int filedNoValue = query.record().indexOf("value");
    while (query.next()) {
        QString name = query.value(filedNoName).toString();
        if (name == projectName) {
            project.name = query.value(filedNoName).toString();
            project.type = query.value(filedNoPType).toString();
            project.unit = query.value(filedNoUnit).toString();
            project.value = query.value(filedNoValue).toString();
            project.valid = true;
            qDebug() << __func__ << __LINE__ << project.name << projectName << (project.name == projectName);
            break;
        }
    }
    return project;
}

QSqlError DataManagerDb::addSchool(int checked, const QString &zxdm, const QString &zxmc, int downloaded)
{
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

QSqlError DataManagerDb::addExamproject(const QString &name, const QString &type, const QString &unit, const QString &value)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_EXAMPROJECT_SQL))
        return q.lastError();
    q.addBindValue(name);
    q.addBindValue(type);
    q.addBindValue(unit);
    q.addBindValue(value);
    q.exec();
    qDebug() << __func__ << __LINE__ << q.lastError().text();
    return QSqlError();
}

QSqlError DataManagerDb::addScore(const QString &zkh, const QString &name, int gender, const QString &examProject, int firstScore, int secondScore, int thirdScore,
                                  bool midStopFist, bool midStopSecond, bool midStopThird,const QString &examTime, int uploadStatus, bool isOnline, const QString &errorMsg, const QString &onSiteVide)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_SCORE_SQL))
        return q.lastError();
    addScorePrivate(q, zkh, name, gender, examProject, firstScore, secondScore, thirdScore, midStopFist, midStopSecond, midStopThird, examTime, uploadStatus, isOnline, errorMsg, onSiteVide);
    return QSqlError();
}

Student DataManagerDb::selectStudentByZkh(const QString &zkh)
{
    Student student;
    QSqlQuery query;
    QString qstr = QString("SELECT * FROM students where zkh = %1").arg(zkh);
    query.prepare(qstr);
    query.exec();

    int filedNoZkh = query.record().indexOf("zkh");
    int filedNoId = query.record().indexOf("id");
    int filedNoName = query.record().indexOf("name");
    int filedNoZxdm = query.record().indexOf("zxdm");
    int filedNoZxmc = query.record().indexOf("zxmc");
    int filedNoGender = query.record().indexOf("gender");
    while (query.next()) {
        student.zkh = query.value(filedNoZkh).toString();
        student.gender = query.value(filedNoGender).toInt();
        student.name = query.value(filedNoName).toString();
        student.zxdm = query.value(filedNoZxdm).toString();
        student.zxmc = query.value(filedNoZxmc).toString();
        student.id = query.value(filedNoId).toString();
        student.isValid = true;

        qDebug() << __func__ << "name" << student.name;
        qDebug() << __func__ << "gender" << student.gender;
        qDebug() << __func__ << "zkh" << student.zkh;
        qDebug() << __func__ << "zxdm" << student.zxdm;
        qDebug() << __func__ << "zxmc" << student.zxmc;
        qDebug() << __func__ << "id" << student.id;
    }
    return student;
}


void DataManagerDb::updateIdCode(const QString &id, const QString &code)
{
    m_curIdCode.id = id;
    m_curIdCode.code = code;
    if (!m_idCodes.contains(m_curIdCode)) {
        m_idCodes.append(m_curIdCode);
        qDebug() << "id code append m_idCodes";
    } else {
        qDebug() << "m_idCodes contains id code";
    }
}

void DataManagerDb::initCurExamProject()
{

}

void DataManagerDb::parseExamProjectJsonDoc(const QJsonDocument &doc)
{
    if (doc.isEmpty()) return;
    QJsonObject obj = doc.object();
    qDebug() << __func__ << __LINE__ << doc;
    QJsonArray array = obj["data"].toArray();
    for (int i = 0; i < array.size(); i++) {
        QJsonObject oobj = array[i].toObject();
        ExamProject localExamProject;
        localExamProject.name = oobj["name"].toString();
        localExamProject.type = oobj["type"].toString();
        localExamProject.unit = oobj["unit"].toString();
        localExamProject.value = oobj["value"].toString();
        qDebug() << __func__ << __LINE__ << i << localExamProject.name;
        qDebug() << __func__ << __LINE__ << i << localExamProject.type;
        qDebug() << __func__ << __LINE__ << i << localExamProject.unit;
        qDebug() << __func__ << __LINE__ << i << localExamProject.value;

        QSqlError error = addExamproject(localExamProject.name, localExamProject.type, localExamProject.unit, localExamProject.value);
        qDebug() << __func__ << __LINE__ << i << error.text();
        //        m_examProjects.insert(localExamProject.name, localExamProject);
        // write to database examprojects table
        if (localExamProject.name == m_curExamName) {
            m_curExamInfo.name = m_curExamName;
            m_curExamInfo.unit = localExamProject.unit;
            m_curExamInfo.type = localExamProject.type;
            m_curExamInfo.value = localExamProject.value;
            m_curExamInfo.valid = true;
        }
    }
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
