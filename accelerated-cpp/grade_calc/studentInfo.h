#ifndef GUARD_studentinfo_h
#define GUARD_studentinfo_h

#include <string>
#include <vector>
#include <iostream>

/**
 * Represents a student.
*/
struct StudentInfo {
    std::string name;
    double gradesMidterm, gradesFinal;
    std::vector<double> gradesHomework;
};

/**
 * Processes a line from an input stream into StudentInfo `sinfo`.
*/
std::istream& readStudentInfo(std::istream& is, StudentInfo& sinfo);

#endif