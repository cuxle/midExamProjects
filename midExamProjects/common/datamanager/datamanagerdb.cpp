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
        id varchar(30),
        name varchar(10),
        gender integer,
        project varchar(10),
        firstScore integer,
        secondScore integer,
        thirdScore integer,
        midStopFirst integer,
        midStopSecond integer,
        midStopThird integer,
        examCount integer,
        examTime varchar(40),
        firstStartTime varchar(40),
        firstStopTime varchar(40),
        secondStartTime varchar(40),
        secondStopTime varchar(40),
        thirdStartTime varchar(40),
        thirdStopTime varchar(40),
        uploadStatus integer,
        isOnline integer,
        errorMsg varchar(40),
        onSiteVideo varchar(40)))");

const auto INSERT_SCORE_SQL = QLatin1String(R"(
        insert into scores(zkh, id, name, gender, project, firstScore, secondScore, thirdScore,
                           midStopFirst, midStopSecond, midStopThird, examCount, examTime,  firstStartTime,
        firstStopTime, secondStartTime, secondStopTime, thirdStartTime, thirdStopTime, uploadStatus, isOnline, errorMsg, onSiteVideo)
                           values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?))");

const auto IDS_SQL =  QLatin1String(R"(
        create table ids(id varchar(10) unique))");

const auto INSERT_IDS_SQL = QLatin1String(R"(
        insert into ids(id)
                    values(?))");

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

void DataManagerDb::addScorePrivate(QSqlQuery &q, const Student &student)
//void DataManagerDb::addScorePrivate(QSqlQuery &q,
//                                    const QString &zkh,
//                                    const QString &name,
//                                    int gender,
//                                    const QString &examProject,
//                                    int firstScore,
//                                    int secondScore,
//                                    int thirdScore,
//                                    bool midStopFist, bool midStopSecond, bool midStopThird,
//                                    const QString &examTime,
//                                    int uploadStatus,
//                                    bool isOnline,
//                                    const QString &errorMsg,
//                                    const QString &onSiteVide)
{
    q.addBindValue(student.zkh);
    q.addBindValue(student.id);
    q.addBindValue(student.name);
    q.addBindValue(student.gender);
    q.addBindValue(student.examProjectName);
    q.addBindValue(student.firstScore);
    q.addBindValue(student.secondScore);
    q.addBindValue(student.thirdScore);
    q.addBindValue(student.midStopFirst);
    q.addBindValue(student.midStopSecond);
    q.addBindValue(student.midStopThird);
    q.addBindValue(student.examCount);
    q.addBindValue(student.examTime);
    q.addBindValue(student.examStartFirstTime);
    q.addBindValue(student.examStopFirstTime);
    q.addBindValue(student.examStartSecondTime);
    q.addBindValue(student.examStopSecondTime);
    q.addBindValue(student.examStartThirdTime);
    q.addBindValue(student.examStopThirdTime);
    q.addBindValue(student.uploadStatus);
    q.addBindValue(student.isOnline);
    q.addBindValue(student.errorMsg);
    q.addBindValue(student.videoPath);
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
    } else {
        qDebug() << __func__ << __LINE__ << "failed to get project info from database";
    }
}

QSqlError DataManagerDb::addStudentsFromExecl(const QString &execlName)
{
    if (execlName.isEmpty()) return QSqlError();
    QXlsx::Document m_xlsx(execlName);

    qDebug() << __func__ << __LINE__ << execlName;

    QFile file(execlName);
    if (!file.exists()) {
        return QSqlError();
    }

    int m_rowsInXlsx = 2;
    while (true) {
        QVariant zkh = m_xlsx.read(m_rowsInXlsx, 1);
        if (zkh.isNull()) {
            break;
        }

        QVariant name = m_xlsx.read(m_rowsInXlsx, 2);
        QVariant gender = m_xlsx.read(m_rowsInXlsx, 3);
        QVariant zxdm = m_xlsx.read(m_rowsInXlsx, 4);
        QVariant zxmc = m_xlsx.read(m_rowsInXlsx, 5);
        QVariant id = m_xlsx.read(m_rowsInXlsx, 6);

        addStudent(zkh.toString(), name.toString(), gender.toInt(), zxdm.toString(), zxmc.toString(), id.toString());

        m_rowsInXlsx++;
    }
    return QSqlError();
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

QSqlError DataManagerDb::addScore(const Student &student)
//QSqlError DataManagerDb::addScore(const QString &zkh, const QString &name, int gender, const QString &examProject, int firstScore, int secondScore, int thirdScore,
//                                  bool midStopFist, bool midStopSecond, bool midStopThird,const QString &examTime, int uploadStatus, bool isOnline, const QString &errorMsg, const QString &onSiteVide)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_SCORE_SQL))
        return q.lastError();
    addScorePrivate(q, student);
    return QSqlError();
}

QSqlError DataManagerDb::updateStudentScoreUploadStatus(const Student &student)
{
    QSqlQuery query;
    if (!student.examStartFirstTime.isEmpty()) {
        query.prepare("update scores set uploadStatus=? where examTime=?");
        query.addBindValue(QString::number(student.uploadStatus));
        query.addBindValue(student.examStartFirstTime);
    } else {
        query.prepare("update scores set uploadStatus=? where secondStartTime=?");
        query.addBindValue(QString::number(student.uploadStatus));
        query.addBindValue(student.examStartSecondTime);
    }
    query.exec();

    qDebug() << __func__ << __LINE__ << student.examStartFirstTime << student.uploadStatus << query.lastError().text();
    return query.lastError();
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
            break;
        }
    }
    return project;
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

//        qDebug() << __func__ << "name" << student.name;
//        qDebug() << __func__ << "gender" << student.gender;
//        qDebug() << __func__ << "zkh" << student.zkh;
//        qDebug() << __func__ << "zxdm" << student.zxdm;
//        qDebug() << __func__ << "zxmc" << student.zxmc;
//        qDebug() << __func__ << "id" << student.id;
    }
    return student;
}

QSqlError DataManagerDb::addIdCode(const QString &id)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_IDS_SQL))
        return q.lastError();
    q.addBindValue(id);
    q.exec();
    qDebug() << __func__ << __LINE__ << q.lastError().text();
    return QSqlError();
}

void DataManagerDb::updateIdCode(const QString &id, const QString &code)
{
    m_curIdCode.id = id;
    m_curIdCode.code = code;
    if (!m_idCodes.contains(m_curIdCode)) {
        m_idCodes.append(m_curIdCode);
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

void DataManagerDb::readUnUploadedStudents()
{
     // fill m_uploadStudentQueue with not uploaded students
    QSqlQuery query;
    QString qstr = QString("SELECT * FROM scores where uploadStatus = %1").arg(QString::number(0));
    query.prepare(qstr);
    query.exec();

    int idxExamCount = query.record().indexOf("examCount");

    int idxFirstScore = query.record().indexOf("firstScore");
    int idxFirstStartTime = query.record().indexOf("firstStartTime");
    int idxFirstStopTime = query.record().indexOf("firstStopTime");

    int idxSecondScore = query.record().indexOf("secondScore");
    int idxSecondStartTime = query.record().indexOf("secondStartTime");
    int idxSecondStopTime = query.record().indexOf("secondStopTime");

    int idxThirdScore = query.record().indexOf("thirdScore");
    int idxThirdStartTime = query.record().indexOf("thirdStartTime");
    int idxThirdStopTime = query.record().indexOf("thirdStopTime");

    int idxMidStopFirst = query.record().indexOf("midStopFirst");
    int idxMidStopSecond = query.record().indexOf("midStopSecond");
    int idxMidStopThird = query.record().indexOf("midStopThird");

    int idxId = query.record().indexOf("id");

    while (query.next()) {

        Student student;
        student.examCount = query.value(idxExamCount).toInt();
        student.firstScore = query.value(idxFirstScore).toInt();
        student.examStartFirstTime = query.value(idxFirstStartTime).toString();
        student.examStopFirstTime = query.value(idxFirstStopTime).toString();

        qDebug() << __func__ << __LINE__ << student.examStartFirstTime;

        student.secondScore = query.value(idxSecondScore).toInt();
        student.examStartSecondTime = query.value(idxSecondStartTime).toString();
        student.examStopSecondTime = query.value(idxSecondStopTime).toString();

        student.thirdScore = query.value(idxThirdScore).toInt();
        student.examStartThirdTime = query.value(idxThirdStartTime).toString();
        student.examStopThirdTime = query.value(idxThirdStopTime).toString();

        student.midStopFirst = query.value(idxMidStopFirst).toBool();
        student.midStopSecond = query.value(idxMidStopSecond).toBool();
        student.midStopThird = query.value(idxMidStopThird).toBool();

        student.id = query.value(idxId).toString();
        student.isValid = true;
        m_uploadStudentQueue.push_back(student);
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
