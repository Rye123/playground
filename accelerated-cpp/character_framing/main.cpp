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

istream& readFrame(istream& is, vector<string>& frame)
{
	// Ensure no failure state
	if (!is)
		return is;

	vector<string> lines;
	readLines(is, lines);
	frame = getFrame(lines);
	is.clear();
	return is;
}

int main()
{
	vector<string> framed;
	readFrame(cin, framed);
	string s = getFrameString(framed);
	cout << s << endl;

	return 0;
}
