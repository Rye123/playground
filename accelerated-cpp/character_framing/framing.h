#ifndef GUARD_framing_h
#define GUARD_framing_h

// framing.h
#include <string>
#include <vector>

std::string::size_type getMaxLen(std::vector<std::string>);
std::string getFrame(std::vector<std::string>);

#endif
