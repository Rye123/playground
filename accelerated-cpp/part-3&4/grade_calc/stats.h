#ifndef GUARD_stats_h
#define GUARD_stats_h

// stats.h
#include <vector>

/**
 * Returns the median of a `vector<double>`.
 * Raises a `domain_error` if the given values vector is empty.
*/
double getMedian(std::vector<double> values);


/**
 * Returns the mean of a `vector<double>`.
 * Raises a `domain_error` if the given values vector is empty.
*/
double getMean(std::vector<double> values);

#endif