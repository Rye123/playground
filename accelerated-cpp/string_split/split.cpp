#include "split.h"
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
