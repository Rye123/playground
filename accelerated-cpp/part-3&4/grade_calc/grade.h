#ifndef GUARD_grade_h
#define GUARD_grade_h

#include <vector>
#include "studentInfo.h"

/**
 * Returns the final grade, where `gradesHomework` is the chosen average for the homework.
*/
double getFinalGrade(const double gradesMidterm, const double gradesFinal, const double gradesHomeworkAvg);

/**
 * Returns the final grade, where `homeworkGrades` is a reference to a vector of grades.
*/
double getFinalGrade(const double gradesMidterm, const double gradesFinal, const std::vector<double>& homeworkGrades);

/**
 * Returns the final grades, based off a `StudentInfo` object.
*/
double getFinalGrade(const StudentInfo& sinfo);

#endif