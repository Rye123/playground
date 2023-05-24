#include <vector>
#include <algorithm> // for std::sort
#include <stdexcept> // for domain_error
#include "stats.h"

using std::vector;  using std::domain_error;

typedef vector<double>::size_type vec_sz;

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