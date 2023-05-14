#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> // for std::sort
#include <stdexcept> // for domainerror

using std::cin;             using std::cout;
using std::endl;            using std::string;
using std::setprecision;    using std::streamsize;
using std::vector;          using std::sort;
using std::domain_error;    using std::istream;
using std::max;

typedef vector<double>::size_type vec_sz;

/**
 * Represents a student.
*/
struct StudentInfo {
    string name;
    double gradesMidterm, gradesFinal;
    vector<double> gradesHomework;
};

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

/**
 * Returns the median of a vector of values.
*/
double getMedian(vector<double> values) {
    vec_sz size = values.size();
    if (size == 0)
        throw new domain_error("Given values vector is empty.");
    sort(values.begin(), values.end());
    vec_sz midIdx = size / 2;
    return (size %2 == 0) ? (values[midIdx] + values[midIdx+1])/2
                                   : values[midIdx];
}

/**
 * Returns the mean of a vector of values.
*/
double getMean(vector<double> values) {
    vec_sz size = values.size();
    if (size == 0)
        throw new domain_error("Given values vector is empty.");
    double mean = 0;
    for (double value : values)
        mean += value;
    mean /= size;
    return mean;
}

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

bool compareNames(const StudentInfo& s1, const StudentInfo& s2) {
    return s1.name < s2.name;
}

int main()
{
    vector<StudentInfo> students;
    string::size_type maxlen = 0;

    // Process records, finding length of longest name
    StudentInfo record;
    while (readStudentInfo(cin, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    // Sort by names
    sort(students.begin(), students.end(), compareNames);

    // Report results
    for (StudentInfo record : students) {
        // Write padded student name
        cout << record.name << string(maxlen + 1 - record.name.size(), ' ');

        // Compute and write result.
        try {
            double grade = getFinalGrade(record);
            streamsize prec = cout.precision();
            cout << setprecision(3) << grade << setprecision(prec);
        } catch (domain_error e) {
            cout << e.what();
        }

        cout << endl;
    }

    return 0;
}