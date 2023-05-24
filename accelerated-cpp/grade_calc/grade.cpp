#include <vector>
#include <list>
#include "studentInfo.h"
#include "stats.h"

using std::vector;
using std::list;

double FAILURE_GRADE = 60;

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

/**
 * Predicate, to determine if a given student failed.
*/
bool gradesFailed(const StudentInfo& sinfo) {
	return getFinalGrade(sinfo) < FAILURE_GRADE;
}

/**
 * Extracts failed students from a given list, returning a new list of the failed students
*/
list<StudentInfo> extractFails(list<StudentInfo>& students) {
	list<StudentInfo> fails;
	list<StudentInfo>::iterator iter = students.begin();

	while (iter != students.end()) {
		if (gradesFailed(*iter)){
			fails.push_back(*iter);
			iter = students.erase(iter);
		} else {
			iter++;
		}
	}
	return fails;
}
