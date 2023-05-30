#include "detect.h"
#include <list>
#include <string>

using std::list; using std::string;

bool containsAscenders(const string& s)
{
	return false;
}

bool containsDescenders(const string& s)
{
	return false;
}

bool containsAscendersOrDescenders(const string& s)
{
	return containsAscenders(s) || containsDescenders(s);
}
