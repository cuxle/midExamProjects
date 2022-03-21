#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <QObject>
#include <QMap>
#include "xlsxdocument.h"
#include "student.h"


class StudentManager : public QObject
{
    Q_OBJECT
public:
    explicit StudentManager(QObject *parent = nullptr);

signals:

public slots:
private:
    void initXlsxDcoment();
private:
     QXlsx::Document *m_xlsx = nullptr;
     const QString str = "你好中国";
     const QStringList m_xlsxHeader;

//     const QStringList m_xlsxHeader = {"", QStringLiteral("序号"), QStringLiteral("姓名"),  QStringLiteral("学号"), QStringLiteral("性别"), QStringLiteral("学校"), QStringLiteral("考试项目"),
//                                QStringLiteral("考试成绩"), QStringLiteral("第一次考试成绩"), QStringLiteral("第二次考试成绩"), QStringLiteral("第三次考试成绩"),
//                                QStringLiteral("考试时间"), QStringLiteral("上传状态"), QStringLiteral("错误信息"), QStringLiteral("视频路径")};
     QList<Student> m_students;

};

#endif // STUDENTMANAGER_H
