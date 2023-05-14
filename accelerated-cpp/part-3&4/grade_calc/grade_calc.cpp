#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> // for std::sort
#include <stdexcept> // for domainerror
#include "stats.h"
#include "studentInfo.h"
#include "grade.h"

using std::cin;             using std::cout;
using std::endl;            using std::string;
using std::setprecision;    using std::streamsize;
using std::vector;          using std::sort;
using std::domain_error;    using std::max;

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