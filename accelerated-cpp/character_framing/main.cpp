#include <iostream>
#include <string>
#include <vector>

#include "string_helper.h"

using std::string; using std::vector;
using std::cin; using std::cout; using std::endl;
using std::max;

string::size_type getMaxLen(vector<string> strings)
{
	string::size_type maxlen = 0;
	for (string s : strings)
		maxlen = max(maxlen, s.size());
	return maxlen;
}

string getFrame(vector<string> lines)
{
	int frameChar = '*';
	int frameWidth = getMaxLen(lines) + 4;

	// Add vertical borders
	for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
		int paddingWidth = frameWidth - (*it).size();
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
		newLine += leftPad + (*it) + rightPad;
		newLine += frameChar;
		(*it) = newLine; 
	}

	// Add horizontal borders
	string horBorder = string(frameWidth, frameChar);
	string ret = "";
	ret += horBorder + '\n';
	for (string line : lines)
		ret += line + '\n';
	ret += horBorder;
	return ret;
}

int main()
{
	vector<string> lines;	
	string s;
	while (getline(cin, s)) {
		lines.push_back(s);	
	}
	s = getFrame(lines);
	cout << s << endl;
	return 0;
}
