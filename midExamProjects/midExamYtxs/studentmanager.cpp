#include "studentmanager.h"
#include <QDebug>

StudentManager::StudentManager(QObject *parent)
    : QObject(parent),
      m_xlsx(new QXlsx::Document())
{
    initXlsxDcoment();
}

void StudentManager::initXlsxDcoment()
{
    // 2. init xlsx file
    // 2.1 init header
    /*
    StuID,
    StuName,
    StuNum,
    StuGender,
    StuSchool,
    StuExamItem,
    StuScore,
    Stu1stScore,
    Stu2stScore,
    Stu3stScore,
    StuExamTime,
    StuUploadStatus,
    StuErrorInfo
    */
    //
    int headRow = 1;
    for (int i = StuIndex; i <= StuVideoPath; i++) {
        m_xlsx->write(headRow, i, m_xlsxHeader.at(i));
    }

    qDebug() << __func__ << m_xlsx->saveAs("students.xlsx");

}
