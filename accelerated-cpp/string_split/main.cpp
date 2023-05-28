#include <iostream>
#include <string>
#include <vector>
#include "split.h"

using std::vector;
using std::string;
using std::getline;
using std::cin;
using std::cout;
using std::endl;


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
