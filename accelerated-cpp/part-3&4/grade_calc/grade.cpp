#include <vector>
#include "studentInfo.h"
#include "stats.h"

using std::vector;

/**
 * Returns the final grade, where `gradesHomework` is the chosen average for the homework.
*/
double getFinalGrade(const double gradesMidterm, const double gradesFinal, const double gradesHomeworkAvg) {
    return 0.2 * gradesMidterm + 0.4 * gradesFinal + 0.4 * gradesHomeworkAvg;
}

/**
 * Returns the final grade, where `homeworkGrades` is a reference to a vector of grades.
*/
double getFinalGrade(const double gradesMidterm, const double gradesFinal, const vector<double>& homeworkGrades) {
    double average = getMedian(homeworkGrades);
    return getFinalGrade(gradesMidterm, gradesFinal, average);
}

/**
 * Returns the final grades, based off a `StudentInfo` object.
*/
double getFinalGrade(const StudentInfo& sinfo) {
    return getFinalGrade(sinfo.gradesMidterm, sinfo.gradesFinal, sinfo.gradesHomework);
}