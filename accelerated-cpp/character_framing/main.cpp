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

	// Concatenate each frame such that two frames fit horizontally.
	cout << "\n\nCONCATENATION: " << endl;
	// 1. Set up horizontal framing
	vector<vector<string>> hcatFrames;
	vector<vector<string>>::const_iterator frameIter = frames.begin();
	while (frameIter != frames.end()) {
		// Concat this frame and the next
		vector<string> left = (*frameIter);
		frameIter++;
		if (frameIter == frames.end()) {
			hcatFrames.push_back(left);
			break;
		}
		vector<string> right = (*frameIter);
		frameIter++;
		hcatFrames.push_back(hcat(left, right));
	}
	// 2. Set up vertical framing
	vector<vector<string>>::const_iterator hcatFrameIter = hcatFrames.begin();
	vector<string> concatFrames = (*hcatFrameIter);
	hcatFrameIter++;
	while (hcatFrameIter != hcatFrames.end()) {
		concatFrames = vcat(concatFrames, (*hcatFrameIter));
		hcatFrameIter++;
	}
	// Report
	cout << getFrameString(concatFrames) << endl;

	return 0;
}
