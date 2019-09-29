#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Binary search - O(logn)
void fullwordSearch(vector<string> dictV, int low, int high, string word) {

	int compCount = 0;

	while(low <= high) {
		compCount += 1;
	
		int mid=(low + high) / 2; // We start with the middle element
		
		if(dictV.at(mid) < word) {
			low = mid + 1; // Element is in the right (larger) subarray, ignore everything smaller than the median
		}
		else if(dictV.at(mid) > word) {
			high = mid - 1; // Element is in the left (smaller) subarray, ignore everything larger than the median
		}
		else {

		//string returnMsg = "Word found at index " + mid + "\n";
		cout << "Comparisons performed: " << compCount << endl;
		cout << "Word found!" << endl;
		return;
		}
	  }

  cout << "Comparisons performed: " << compCount << endl;
  cout << "Word not found!" << endl;

}

void prefixSearch(vector<string> dictV, int low, int high, string word, int length, int maxOutput) {

	int compCount = 0;
	int foundCount = 0;
	int outputCount = 0;

	while(low <= high) {
		compCount += 1;
		
		int mid = (low + high) / 2;
		
		if(dictV.at(mid).substr(0,length) < word) {
			low = mid + 1;
		}
		else if(dictV.at(mid).substr(0,length) > word) {
			high = mid - 1;
		}
		else {
			int originalMid = mid; // Store the first finding for two-way search

			// Since the dictionary is sorted, all words starting with the prefix are next to each other, we just need to figure out how many are there
			while(dictV.at(mid).substr(0,length) == word) { // First we find every match before the first finding
				foundCount += 1;
				outputCount += 1; // We increment outputCount before the check to make sure we don't get one extra output
				if (outputCount <= maxOutput) {
					cout << dictV.at(mid) << endl;
				}
				mid -= 1;
				
			}

			mid = originalMid + 1; // Return to the first finding plus one to avoid repeating it

			while(dictV.at(mid).substr(0,length) == word) { // Then we find everything after
				foundCount += 1;
				outputCount += 1;
				if (outputCount <= maxOutput) {
					cout << dictV.at(mid) << endl;
				}
				mid += 1;
			}
			break; // Essential!

		}
	  }

	cout << "Comparisons performed until first match: " << compCount << endl;
	cout << "Found entries: " << foundCount << endl;

}

string wildcardSearch(vector<string> dictV, int low, int high, string word, int length, string::size_type qPos, int maxOutput) {

	int compCount = 0;
	int foundCount = 0;
	int outputCount = 0;

	while(low <= high) {
		compCount += 1;
		
		int mid = (low + high) / 2; // We start with the middle element
		
		if(dictV.at(mid).substr(0,qPos) < word.substr(0,qPos)) { // The first half of a wildcard search is just a prefix search until the ?
			low = mid + 1;
		}
		else if(dictV.at(mid).substr(0,qPos) > word.substr(0,qPos)) {
			high = mid - 1;
		}
		else {
			int originalMid = mid; // Store the first finding for two-way search
			int entryLength = dictV.at(mid).length(); // To avoid confusion with the input word's length

			// Just like we did during prefix search, we will go through every element that matches our word up to the ?
			while(dictV.at(mid).substr(0,qPos) == word.substr(0,qPos)) {
				if (dictV.at(mid).substr(qPos + 1,entryLength - qPos) == word.substr(qPos + 1,length - qPos)) { // But we only display those that also match the part AFTER the ?
					foundCount += 1;
					outputCount += 1;
					if (outputCount <= maxOutput) {
						cout << dictV.at(mid) << endl;
					}
				}
				mid -= 1;
			}

			mid = originalMid + 1; // Return to the first finding plus one to avoid repeating it

			while(dictV.at(mid).substr(0,qPos) == word.substr(0,qPos)) { // Ditto
				if (dictV.at(mid).substr(qPos + 1,entryLength - qPos) == word.substr(qPos + 1,length - qPos)) {
					foundCount += 1;
					outputCount += 1;
					if (outputCount <= maxOutput) {
						cout << dictV.at(mid) << endl;
					}
				}
				mid += 1;
			}
			break; // Essential!

		}
	  }

	cout << "Comparisons performed: " << compCount << endl;
	cout << "Found entries: " << foundCount << endl;

}


int main(int argc, char* args[]) {

	string dictName;
	int maxOutput;

	for(int i = 0; i < argc; i++) {
		string str(args[i]);
		if (str == "-d") {
			cout << args[i+1] << endl;
			string dictNameStr(args[i+1]);
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