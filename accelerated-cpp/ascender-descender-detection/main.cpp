#include <iostream>
#include <vector>
#include <string>
#include "strmanip.h"
#include "detect.h"

using std::cout; using std::cin; using std::endl;
using std::string; using std::getline;
using std::vector;

int main()
{
	vector<string> words;
	string buf;
	while (getline(cin, buf)) {
		vector<string> splitWords = split(buf);
		words.insert(words.end(), splitWords.begin(), splitWords.end());
	}

	// Process words
	for (string word : words) {
		if (containsAscendersOrDescenders(word))
			cout << word << " - TRUE" << endl;
		else
			cout << word << " - FALSE" << endl;
	}
	return 0;
}
