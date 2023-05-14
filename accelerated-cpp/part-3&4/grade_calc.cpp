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

typedef vector<double>::size_type vec_sz;

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


int main()
{
    streamsize defaultPrecision = cout.precision();
    string studentName = "";
    double gradesMidterm = 0.0;
    double gradesFinal = 0.0;
    vector<double> gradesHomework;

    // Request student name
    cout << "Enter first name: ";
    cin >> studentName;

    cout << "Hello, " << studentName << endl;

    // Request grade data
    cout << "Enter midterm and final grades: ";
    cin >> gradesMidterm >> gradesFinal;

    // Request homework grades
    cout << "Enter homework grades: ";
    readDoublesIntoVector(cin, gradesHomework, false);
    if (gradesHomework.size() == 0) {
        cout << "Please enter your grades." << endl;
        return 1;
    }

    // Evaluate median and mean of homework grades
    vec_sz homeworkCount = gradesHomework.size();
    double gradesHomeworkMedian = getMedian(gradesHomework);
    double gradesHomeworkMean = getMean(gradesHomework);
    cout << "Homework Report: \n\tMedian Grade: "
         << setprecision(3)
         << gradesHomeworkMedian
         << "\n\tMean Grade: "
         << gradesHomeworkMean
         << setprecision(defaultPrecision)
         << endl;
    
    // Output result
    cout << "Final Grade: " 
         << setprecision(3)
         << getFinalGrade(gradesMidterm, gradesFinal, gradesHomework)
         << setprecision(defaultPrecision)
         << endl;

    return 0;
}