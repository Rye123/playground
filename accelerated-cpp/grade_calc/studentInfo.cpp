#include <iostream>
#include <string>
#include <vector>
#include "studentInfo.h"

using std::istream; using std::vector;

/**
 * Reads doubles into a vector `values` until EOF or invalid character.
*/
istream& readDoublesIntoVector(istream& in, vector<double>& values, bool clear) {
    if (clear)
        values.clear();

    if (in) {
        double value;
        while (in >> value)
            values.push_back(value);

        in.clear(); // clear any existing error state
    }
    return in;
}

/**
 * Reads doubles into a vector `values` until EOF or invalid character. `values` is not cleared first by default.
*/
istream& readDoublesIntoVector(istream& in, vector<double>& values) {
    return readDoublesIntoVector(in, values, false);
}

/**
 * Processes a line from an input stream into StudentInfo `sinfo`.
*/
istream& readStudentInfo(istream& is, StudentInfo& sinfo) {
    // Read first three parts
    is >> sinfo.name >> sinfo.gradesMidterm >> sinfo.gradesFinal;

    // Read homework grades
    readDoublesIntoVector(is, sinfo.gradesHomework);

    return is;
}