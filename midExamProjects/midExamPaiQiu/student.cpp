#include "student.h"

#include <QVariant>

Student::Student(QObject *parent)
    : QObject(parent)
{

}

QVariant Student::data(StuColumn col)
{
    if (col < StuStart || col > StuEnd) {
        return QVariant();
    }
    return m_data[col];
}

bool Student::setData(StuColumn col, QVariant data)
{
    if (col < StuStart || col > StuEnd) {
        return false;
    }
    m_data[static_cast<int>(col)] = data;
    return true;
}
