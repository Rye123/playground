#ifndef GUARD_strmanip_h
#define GUARD_strmanip_h

// strmanip.h: Defines functions for string manipulation

#include <string>
#include <vector>

/**
 * Splits a given string by the whitespaces. Only alphanumeric characters will be considered part of the word.
*/
std::vector<std::string> split(const std::string&);

#endif
