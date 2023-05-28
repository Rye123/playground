#include <iostream>
#include <string>
#include <vector>

#include "string_helper.h"
#include "framing.h"

using std::string; using std::vector;
using std::cin; using std::cout; using std::endl;
using std::istream;

/**
 * Read lines from a given `istream`.
*/
istream& readLines(istream& is, vector<string>& lines)
{
	// Ensure no failure state
	if (!is)
		return is;

	string s;
	while (getline(is, s))
		lines.push_back(s);
	is.clear();
	return is;
}

vector<vector<string>> getFrames(vector<string> rawLines) {
	string DIVIDER = "!===!===!"; // unique string to divide two sets of lines that should be framed separately.
	vector<vector<string>> ret;
	vector<string> lines;
	for (string line : rawLines) {
		if (line == DIVIDER) {
			if (lines.size() > 0) {
				ret.push_back(getFrame(lines));
				lines.clear();
			}
		} else {
			lines.push_back(line);
		}
	}
	if (lines.size() > 0)
		ret.push_back(getFrame(lines));
	return ret;
}

int main()
{
	vector<string> raw;
	readLines(cin, raw);
	vector<vector<string>> frames = getFrames(raw);
	
	for (vector<string> frame : frames) {
		cout << "FRAME: " << endl;
		cout << getFrameString(frame) << endl;
	}
	return 0;
}
