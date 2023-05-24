#ifndef GUARD_grade_h
#define GUARD_grade_h

#include <vector>
#include <list>
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

/**
 * Extracts failed students from a given list of students, returning the failed students as a new list.
*/
std::list<StudentInfo> extractFails(std::list<StudentInfo>& students);

#endif
