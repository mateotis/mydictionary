#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Linear search - O(n)
string findWordLinear(vector<string> dictV, string word) {

	int compCount = 0;

	for(int i = 0; i < dictV.size(); i++) {
		compCount += 1;
	if (dictV.at(i) == word) {
		cout << "Comparisons performed: " << compCount << endl;
		return "Word found!";
		}
	}

  cout << "Comparisons performed: " << compCount << endl;
  return "Word not found!";
}

// Binary search - O(logn)
string findWordBinary(vector<string> dictV, int low, int high, string word) {

	int compCount = 0;

	while(low <= high) {
		compCount += 1;
	
		int mid=(low + high) / 2; // Median
		
		if(dictV.at(mid) < word) {
			low = mid + 1; // Element is in the right (larger) subarray, ignore everything smaller than the median
		}
		else if(dictV.at(mid) > word) {
			high = mid - 1; // Element is in the left (smaller) subarray, ignore everything larger than the median
		}
		else {

		//string returnMsg = "Word found at index " + mid + "\n";
		cout << "Comparisons performed: " << compCount << endl;
		return "Word found!";
		}
	  }

  cout << "Comparisons performed: " << compCount << endl;
  return "Word not found!";

}

string prefixSearch(vector<string> dictV, int low, int high, string word, int length) {

	int compCount = 0;

	while(low <= high) {
		compCount += 1;
		
		int mid = (low + high) / 2; // Median
		
		if(dictV.at(mid).substr(0,length) < word) {
			low = mid + 1; // Element is in the right (larger) subarray, ignore everything smaller than the median
		}
		else if(dictV.at(mid).substr(0,length) > word) {
			high = mid - 1; // Element is in the left (smaller) subarray, ignore everything larger than the median
		}
		else {
			int originalMid = mid; // Store the first finding for two-way search

			// Since the dictionary is sorted, all words starting with the prefix are next to each other, we just need to figure out how many are there
			while(dictV.at(mid).substr(0,length) == word) { // First we find every match before the first finding
				cout << dictV.at(mid) << endl;
				mid -= 1;
			}

			mid = originalMid + 1; // Return to the first finding plus one to avoid repeating it

			while(dictV.at(mid).substr(0,length) == word) { // Then we find everything after
				cout << dictV.at(mid) << endl;
				mid += 1;
			}
			break; // Essential!

		}
	  }

	cout << "Comparisons performed: " << compCount << endl;
	return "Word(s) found!";

}


int main() {

	vector<string> dictV;

	ifstream fin("Dictionary2.txt");

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
		if (word == "quit" or word == "exit") {
			break;
		}
		//cout << findWordLinear(dictV, word) << endl;

		//cout << findWordBinary(dictV, 0, dictV.size() - 1, word) << endl;

		int length = word.length();

		cout << prefixSearch(dictV, 0, dictV.size() - 1, word, length) << endl;

	}

/*  for(int i = 0; i < dictV.size(); i++) {
	cout << dictV.at(i) << endl;
  }*/

	return EXIT_SUCCESS;
}