#include "mydictSearches.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* args[]) {

	string dictName;
	int maxOutput = 0;

	for(int i = 0; i < argc; i++) {
		string str(args[i]);
		if (str == "-d") {
			string dictNameStr(args[i+1]); // The parameter after -d is the dictionary name
			dictName = dictNameStr;
		}

		if (str == "-l") {
			string maxOutputStr(args[i+1]); // Hack, replace if possible!
			maxOutput = stoi(maxOutputStr);
		}
	}

	vector<string> dictV;

	ifstream fin(dictName);

	if (fin.is_open()) {
		string var;
		while(fin) {
			fin >> var;
			dictV.push_back(var); // Stores dictionary in vector
			if (fin.eof()) {
				break; // Prevents duplication of last line
			}
		}
	}

	fin.close();
	

	string word;

	while(true) {
		cout << "Enter a string: ";
		cin >> word;
		string::size_type qPos = word.find("?"); // Check if there is a question mark in the string (and where it is), for wildcard potential

		if (word == "quit" or word == "exit") {
			break;
		}
		else if (word.find("*") != string::npos) { // Prefix
			int length = word.length() - 1; // Ignore the *
			word = word.substr(0,length); // Also remove it from the string we pass to the function
			prefixSearch(dictV, 0, dictV.size() - 1, word, length, maxOutput);

		}
		else if (qPos != string::npos) { // Wildcard
			wildcardSearch(dictV, 0,  dictV.size() - 1, word, word.length(), qPos, maxOutput);
		}
		else { // Full word
			fullwordSearch(dictV, 0, dictV.size() - 1, word);
		}
	}

	return EXIT_SUCCESS;
}