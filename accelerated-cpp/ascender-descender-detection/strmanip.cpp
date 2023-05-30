#include "strmanip.h"
#include <string>
#include <vector>
#include <cctype>

using std::string; using std::vector;
using std::isspace;

/**
 * Returns if the given character is a space.
 * Code adapted from https://en.cppreference.com/w/cpp/string/byte/isspace
*/
bool isSpace(char c)
{
	return (isspace(static_cast<unsigned char>(c)) != 0);
}

vector<string> split(const string& s)
{
	vector<string> ret;
	string word = "";

	for (char c : s) {
		if (isSpace(c)) {
			if (word.size() > 0)
				ret.push_back(word);
			word = "";
		} else if (isalnum(c)) {
			word += c;
		} else {
			// ignore other characters
			continue;
		}
	}
	if (word.size() > 0)
		ret.push_back(word);
	return ret;
}
