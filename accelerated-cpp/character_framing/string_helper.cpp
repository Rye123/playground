#include "string_helper.h"
#include <vector>
#include <string>

using std::vector; using std::string;

/**
 * Splits a `string` into a `vector` of `string`s, using a delimiter `delim`.
*/
vector<string> split(const string& s, char delim) {
	vector<string> ret;
	string curWord = "";
	for (char c : s) {
		if (c == delim) {
			if (curWord.size() != 0)
				ret.push_back(curWord);
			curWord = "";
		} else {
			curWord.push_back(c);
		}
	}
	if (curWord.size() != 0)
		ret.push_back(curWord);
	return ret;
}

/**
 * Joins a `vector` of `strings` into a single `string`, delimited by `delim`.
*/
string join(const vector<string>& strings, char delim) {
	string ret = "";
	for (vector<string>::const_iterator it = strings.begin(); it != strings.end(); ++it) {
		if (it == strings.end())
			ret += (*it);
		else
			ret += (*it) + delim;
	}
	return ret;
}
