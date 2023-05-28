#ifndef GUARD_framing_h
#define GUARD_framing_h

// framing.h
#include <string>
#include <vector>

std::string::size_type getMaxLen(const std::vector<std::string>&);
std::vector<std::string> getFrame(const std::vector<std::string>&);
std::string getFrameString(const std::vector<std::string>&);

#endif
