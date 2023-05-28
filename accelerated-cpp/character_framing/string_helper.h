#ifndef GUARD_string_helper_h
#define GUARD_string_helper_h

// string_helper.h
#include <string>
#include <vector>

std::vector<std::string> split(const std::string&, char delim);
std::string join(const std::vector<std::string>&, char delim);

#endif
