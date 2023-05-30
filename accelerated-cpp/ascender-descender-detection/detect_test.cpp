// Simple test file for detect.h

#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include "detect.h"

using std::string;
using std::cout; using std::endl;

bool test_containsAscenders()
{
	string s0 = "the";
	if (!containsAscenders(s0)) // t, h
		return false;
	string s1 = "eee";
	if (containsAscenders(s1)) // no ascenders
		return false;
	string s2 = "THE";
	if (!containsAscenders(s2)) // test upper case
		return false;
	string s3 = "EEE";
	if (containsAscenders(s3))
		return false;
	string s4 = "baaaaaa";
	if (!containsAscenders(s4))
		return false;
	string s5 = "ggggg";
	if (containsAscenders(s5))
		return false;
	return true;
}

bool test_containsDescenders()
{
	string s0 = "the";
	if (containsDescenders(s0))
		return false;
	string s1 = "EEE";
	if (containsDescenders(s1))
		return false;
	string s2 = "gg";
	if (!containsDescenders(s2))
		return false;
	string s3 = "aqwerty";
	if (!containsDescenders(s3))
		return false;
	return true;
}

bool test_containsAscendersOrDescenders()
{
	string s0 = "the";
	if (!containsAscendersOrDescenders(s0))
		return false;
	string s1 = "eee";
	if (containsAscendersOrDescenders(s1))
		return false;
	string s2 = "QUICK";
	if (!containsAscendersOrDescenders(s2))
		return false;
	return true;
}

int main()
{
	assert(test_containsAscenders() && "containsAscenders: TEST FAILED");
	cout << "containsAscenders: TEST PASSED" << endl;
	assert (test_containsDescenders() && "containsDescenders: TEST FAILED");
	cout << "containsDescenders: TEST PASSED" << endl;
	assert (test_containsAscendersOrDescenders() && "test_containsAscendersOrDescenders: TEST FAILED");
	cout << "test_containsAscendersOrDescenders: TEST PASSED" << endl;
	return 0;
}


