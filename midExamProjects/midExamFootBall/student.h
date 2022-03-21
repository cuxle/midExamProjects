#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QMap>

enum StuColumn{
    StuStart = 1,
    StuIndex = StuStart,
    StuName,
    StuId,
    StuGender,
    StuSchool,
    StuExamItem,
    StuScore,
    Stu1stScore,
    Stu2stScore,
    Stu3stScore,
    StuExamTime,
    StuUploadStatus,
    StuErrorInfo,
    StuVideoPath,
    StuEnd = StuVideoPath
};


class Student : public QObject
{
public:
    explicit Student(QObject *parent = nullptr);
    QVariant data(StuColumn col);
    bool setData(StuColumn col, QVariant data);

private:
    QMap<int, QVariant> m_data;

};

#endif // STUDENT_H
