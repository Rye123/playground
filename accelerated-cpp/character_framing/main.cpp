#include <iostream>
#include <string>
#include <vector>

#include "string_helper.h"
#include "framing.h"

using std::string; using std::vector;
using std::cin; using std::cout; using std::endl;

int main()
{
	vector<string> lines;	
	string s;
	while (getline(cin, s)) {
		lines.push_back(s);	
	}
	vector<string> framed = getFrame(lines);
	s = getFrameString(framed);
	cout << s << endl;
	return 0;
}
