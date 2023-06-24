#include "Student.h"

Student::Student()
    :isValid(false)
{
    scores.resize(3);
}


void Student::initTimeExam() {
    for (auto &item : scores) {
        item = int_max;
    }
}

void Student::initCountExam() {
    for (auto &item : scores) {
        item = int_min;
    }
}

// Overloaded assignment
Student& Student::operator= (const Student& fraction) {
    return *this;
}

QString Student::getFinalScoreByTime()
{
    int value = getFinalExamResultByTime();
    if (value == int_max) {
        return "犯规";
    } else {
        return QString::number(value/1000.0, 'f', 2);
    }
}

QString Student::getFinalScoreByCount()
{
    int value = getFinalExamResultByCount();
    if (value == int_min) {
       return "犯规";
    } else {
        return QString::number(value);
    }
}

int Student::getFinalExamResultByTime() {
    return *std::min_element(std::begin(scores), std::end(scores));
}

int Student::getFinalExamResultByCount() {
    return *std::max_element(std::begin(scores), std::end(scores));
}
