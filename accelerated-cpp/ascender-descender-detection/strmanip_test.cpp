// strmanip_test: Tests functions in strmanip.h
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "strmanip.h"

using std::string; using std::vector;
using std::cout; using std::endl;

bool test_split()
{
	string s0 = "The quick brown fox";
	vector<string> w0{ "The", "quick", "brown", "fox" };
	if (!(split(s0) == w0))
		return false;

	string s1 = "The\nquick\nbrown\nfox";
	if (!(split(s1) == w0))
		return false;

	string s2 = "The";
	vector<string> w2{ "The" };
	if (!(split(s2) == w2))
		return false;

	string s3 = "   The   \n";
	if (!(split(s3) == w2))
		return false;

	string s4 = "\tThe\tquick brown\n fox";
	if (!(split(s4) == w0))
		return false;
	return true;
}

int main()
{
	assert(test_split() && "test_split: TEST FAILED");
	cout << "test_split: TEST PASSED" << endl;
	return 0;
}
