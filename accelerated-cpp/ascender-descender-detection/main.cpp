/**
 * main:
 * Program that scans a list of words in a text file, and
 * identifies the logest word with neither ascenders or
 * descenders.
*/

#include <iostream>
#include <vector>
#include <string>
#include "strmanip.h"
#include "detect.h"

using std::cout; using std::cin; using std::endl;
using std::string; using std::getline;
using std::vector;

bool DEBUG = true; // set to true to display the running longest word

int main()
{
	vector<string> words;
	string buf;
	while (getline(cin, buf)) {
		vector<string> splitWords = split(buf);
		words.insert(words.end(), splitWords.begin(), splitWords.end());
	}

	// Process words
	string longestWord = "";
	int longestLength = 0;
	for (string word : words) {
		if (!containsAscendersOrDescenders(word)) {
			if (word.size() <= longestLength)
				continue;
			longestWord = word;
			longestLength = word.size();
			if (DEBUG)
				cout << "Current longest: " << word << " (Length " << longestLength << ")" << endl;
		}
	}
	cout << "Longest word: " << longestWord << endl;
	return 0;
}
