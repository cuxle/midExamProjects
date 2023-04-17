#ifndef UTILS_H
#define UTILS_H
#include <QObject>
#include <QString>
#include "Student.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>


class Utils
{
public:
    Utils();
    static QString strFormat;
    static int stopVideoDelay; // 10stmp;
    static QString calculateFinalScoreForTime(const Student& student);
    static QString calculateFinalScoreForCount(const Student& student);
    static int calculateFinalScoreByBiggerCount(const Student& student);
    static int calculateFinalScoreBySmallerCount(const Student& student);
    static bool floatEqual(float a, float b);
    static void formatImages(cv::Mat &mat);
};

#endif // UTILS_H
