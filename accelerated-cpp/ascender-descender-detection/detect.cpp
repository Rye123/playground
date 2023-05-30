#include "detect.h"
#include <list>
#include <string>
#include <cctype>

using std::list; using std::string;

bool isInList(const char& c, list<char> ls)
{
	for (char lsc : ls) {
		if (lsc == c)
			return true;
	}
	return false;
}

bool containsAscenders(const string& s)
{
	for (char c : s) {
		c = tolower(c);
		if (isInList(c, ASCENDERS))
			return true;
	}
	return false;
}

bool containsDescenders(const string& s)
{
	for (char c : s) {
		c = tolower(c);
		if (isInList(c, DESCENDERS))
			return true;
	}
	return false;
}

bool containsAscendersOrDescenders(const string& s)
{
	return containsAscenders(s) || containsDescenders(s);
}
