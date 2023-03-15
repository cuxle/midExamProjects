#include "utils.h"

QString Utils::strFormat = "yyyy-MM-dd hh:mm:ss ddd";

Utils::Utils()
{


}

QString Utils::calculateFinalScoreForTime(const Student& student)
{
    int value = calculateFinalScoreBySmallerCount(student);
    if (value == -1) {
        return QString("犯规");
    } else {
        // change ms to s
        return QString::number(value/1000.0, 'f', 2);
    }
}

QString Utils::calculateFinalScoreForCount(const Student& student)
{
    int value = calculateFinalScoreByBiggerCount(student);
    if (value == -1) {
        return QString("犯规");
    } else {
        return QString::number(value);
    }
}

int Utils::calculateFinalScoreBySmallerCount(const Student& student)
{
    // 考试次数不同最终成绩算法不同
    if (student.examCount == 1) {
        if (student.midStopFirst) {
            return -1;
        } else {
            return student.firstScore;
        }
    } else if (student.examCount == 2) {
        // 1. 两次都犯规
        if (student.midStopFirst && student.midStopSecond) {
            return -1;
        }
        // 2. 一个犯规
        else if (!student.midStopFirst && student.midStopSecond) {
            return student.firstScore;
        } else if (student.midStopFirst && !student.midStopSecond) {
            return student.secondScore;
        }
        // 3. 没有犯规
        else if (!student.midStopFirst && !student.midStopSecond) {
            int score = student.firstScore <= student.secondScore ? student.firstScore : student.secondScore;
            return score;
        }
    } else if (student.examCount == 3) {
        // 1. 三次犯规
        if (student.midStopFirst && student.midStopSecond && student.midStopThird) {
            return -1;
        }
         // 2. 两次犯规
        else if (!student.midStopFirst && student.midStopSecond && student.midStopThird) {
            return student.firstScore;
        } else if (student.midStopFirst && !student.midStopSecond && student.midStopThird) {
            return student.secondScore;
        } else if (student.midStopFirst && student.midStopSecond && !student.midStopThird) {
            return student.thirdScore;
        }
        // 3. 一次犯规
        else if (student.midStopFirst && !student.midStopSecond && !student.midStopThird) {
            int score = student.secondScore <= student.thirdScore ? student.secondScore : student.thirdScore;
            return score;
        } else if (!student.midStopFirst && student.midStopSecond && !student.midStopThird) {
            int score = student.firstScore <= student.thirdScore ? student.firstScore : student.thirdScore;
            return score;

        } else if (!student.midStopFirst && !student.midStopSecond && student.midStopThird) {
            int score = student.secondScore <= student.firstScore ? student.secondScore : student.firstScore;
            return score;
        }
        // 4. 没有犯规
        else if (!student.midStopFirst && !student.midStopSecond && !student.midStopThird) {
            int score = student.firstScore <= student.secondScore ? student.firstScore : student.secondScore;
            score = score <= student.thirdScore ? score : student.thirdScore;
            return score;
        }
    }

    return -1;
}

int Utils::calculateFinalScoreByBiggerCount(const Student& student)
{
    // 考试次数不同最终成绩算法不同
    if (student.examCount == 1) {
        if (student.midStopFirst) {
            return -1;
        } else {
            return student.firstScore;
        }
    } else if (student.examCount == 2) {
        // 1. 两次都犯规
        if (student.midStopFirst && student.midStopSecond) {
            return -1;
        }
        // 2. 一个犯规
        else if (!student.midStopFirst && student.midStopSecond) {
            return student.firstScore;
        } else if (student.midStopFirst && !student.midStopSecond) {
            return student.secondScore;
        }
        // 3. 没有犯规
        else if (!student.midStopFirst && !student.midStopSecond) {
            int score = student.firstScore >= student.secondScore ? student.firstScore : student.secondScore;
            return score;
        }
    } else if (student.examCount == 3) {
        // 1. 三次犯规
        if (student.midStopFirst && student.midStopSecond && student.midStopThird) {
            return -1;
        }
         // 2. 两次犯规
        else if (!student.midStopFirst && student.midStopSecond && student.midStopThird) {
            return student.firstScore;
        } else if (student.midStopFirst && !student.midStopSecond && student.midStopThird) {
            return student.secondScore;
        } else if (student.midStopFirst && student.midStopSecond && !student.midStopThird) {
            return student.thirdScore;
        }
        // 3. 一次犯规
        else if (student.midStopFirst && !student.midStopSecond && !student.midStopThird) {
            int score = student.secondScore >= student.thirdScore ? student.secondScore : student.thirdScore;
            return score;
        } else if (!student.midStopFirst && student.midStopSecond && !student.midStopThird) {
            int score = student.firstScore >= student.thirdScore ? student.firstScore : student.thirdScore;
            return score;

        } else if (!student.midStopFirst && !student.midStopSecond && student.midStopThird) {
            int score = student.secondScore >= student.firstScore ? student.secondScore : student.firstScore;
            return score;
        }
        // 4. 没有犯规
        else if (!student.midStopFirst && !student.midStopSecond && !student.midStopThird) {
            int score = student.firstScore >= student.secondScore ? student.firstScore : student.secondScore;
            score = score >= student.thirdScore ? score : student.thirdScore;
            return score;
        }
    }

    return -1;
}

bool Utils::floatEqual(float a, float b)
{
    return fabs(a - b) <= std::numeric_limits<float>::epsilon();
}

