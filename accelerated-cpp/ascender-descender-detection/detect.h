#ifndef GUARD_detect_h
#define GUARD_detect_h

// detect.h
// Provides functions that detect for ascenders or descenders.

#include <string>
#include <list>

static const std::list<char>  ASCENDERS{ 'b', 'd', 'f', 'h', 'k', 'l', 't' };
static const std::list<char> DESCENDERS{ 'g', 'j', 'p', 'q', 'y' };

bool containsAscenders(const std::string&);
bool containsDescenders(const std::string&);
bool containsAscendersOrDescenders(const std::string&);

#endif
