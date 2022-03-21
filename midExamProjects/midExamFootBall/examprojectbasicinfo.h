#ifndef EXAMPROJECTBASICINFO_H
#define EXAMPROJECTBASICINFO_H

#include <QObject>

class ExamProjectBasicInfo : public QObject
{
    Q_OBJECT
public:
    explicit ExamProjectBasicInfo(QObject *parent = nullptr);

signals:
private:
    QString m_examName;
    QString m_examId;
    QString m_deviceNumber;
    QString m_unit;
};

#endif // EXAMPROJECTBASICINFO_H
