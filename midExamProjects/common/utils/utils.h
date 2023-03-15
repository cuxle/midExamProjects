#ifndef UTILS_H
#define UTILS_H
#include <QObject>
#include <QString>
#include "Student.h"

class Utils
{
public:
    Utils();
    static QString strFormat;
    static QString calculateFinalScoreForTime(const Student& student);
    static QString calculateFinalScoreForCount(const Student& student);
    static int calculateFinalScoreByBiggerCount(const Student& student);
    static int calculateFinalScoreBySmallerCount(const Student& student);
    static bool floatEqual(float a, float b);
};

#endif // UTILS_H
