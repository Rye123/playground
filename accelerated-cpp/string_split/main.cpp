#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::getline;
using std::cin;
using std::cout;
using std::endl;

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

int main()
{
	string s;
	while (getline(cin, s)) {
		vector<string> v = split(s, ' ');

		// Write each line's split words
		for (string word : v) {
			cout << word << endl;
		}
	}
	return 0;
}
