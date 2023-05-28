#include <string>
#include <vector>
#include "string_helper.h"
#include "framing.h"

using std::vector; using std::string; using std::max;

string::size_type getMaxLen(const vector<string>& strings)
{
	string::size_type maxlen = 0;
	for (string s : strings)
		maxlen = max(maxlen, s.size());
	return maxlen;
}

/**
 * Returns a framed version of a vector of strings.
*/
vector<string> getFrame(const vector<string>& lines)
{
	vector<string> ret;
	int frameChar = '*';
	int frameWidth = getMaxLen(lines) + 4;
	string horBorder = string(frameWidth, frameChar);
	
	ret.push_back(horBorder); // top border
	for (string line : lines) {
		int paddingWidth = frameWidth - line.size();
		string leftPad; string rightPad;
		// Set padding such that line is centralised.
		int padLen = (paddingWidth / 2) - 1;
		leftPad = string(padLen, ' ');
		if (paddingWidth % 2 == 0)
			rightPad = string(padLen, ' ');
		else
			rightPad = string(padLen+1, ' ');

		// Centralise the line in the frame.
		string newLine = "";
		newLine += frameChar;
		newLine += leftPad + line + rightPad;
		newLine += frameChar;
		ret.push_back(newLine);
	}
	ret.push_back(horBorder); // bottom border
	return ret;
}

string getFrameString(const vector<string>& frame)
{
	return join(frame, '\n');
}
