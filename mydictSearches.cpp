#include <iostream>
#include <vector>
#include "mydictSearches.h"

using namespace std;

void fullwordSearch(vector<string> dictV, int low, int high, string word) {

	int compCount = 0;

	// Binary search - since dictionaries are in alphabetical order, we can consider them sorted arrays, which is the condition for binary search
	while(low <= high) { // Runs until it can't divide the dictionary anymore
		compCount += 1;
	
		int mid = (low + high) / 2; // We start with the middle element
		
		if(dictV.at(mid) < word) {
			low = mid + 1; // Element is in the right (larger) subarray, ignore everything smaller than the middle
		}
		else if(dictV.at(mid) > word) {
			high = mid - 1; // Element is in the left (smaller) subarray, ignore everything larger than the middle
		}
		else {

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
				mid -= 1; // Move to the element just before the current one
				if(mid < 0) { break; } // The first of many boundary-checks; this needs to be checked every time mid is changed to make sure the search stops at the start/end of the dictionary
				
			}

			mid = originalMid + 1; // Return to the first finding plus one to avoid repeating it
			if(mid >= dictV.size()) { break; }

			while(dictV.at(mid).substr(0,length) == word) { // Then we find everything after
				foundCount += 1;
				outputCount += 1;
				if (outputCount <= maxOutput) {
					cout << dictV.at(mid) << endl;
				}
				mid += 1;
				if(mid >= dictV.size()) { break; } // When you iterate forward and go beyond the last index, stop
			}
			break; // Essential! Infinite loop otherwise

		}
	  }

	cout << "Comparisons performed until first match: " << compCount << endl;
	cout << "Found entries: " << foundCount << endl;

}

void wildcardSearch(vector<string> dictV, int low, int high, string word, int length, int qPos, int maxOutput) {

	int compCount = 0;
	int foundCount = 0;
	int outputCount = 0;

	while(low <= high) {
		compCount += 1;
		
		int mid = (low + high) / 2;
		
		if(dictV.at(mid).substr(0,qPos) < word.substr(0,qPos)) { // The first half of a wildcard search is just a prefix search until the ?
			low = mid + 1;
		}
		else if(dictV.at(mid).substr(0,qPos) > word.substr(0,qPos)) {
			high = mid - 1;
		}
		else {
			int originalMid = mid;

			// Just like we did during prefix search, we will go through every element that matches our word up to the ?
			while(dictV.at(mid).substr(0,qPos) == word.substr(0,qPos)) {
				compCount += 1; // Incrementing comparison count since we are asked for the time to return all the answers
				while(qPos >= dictV.at(mid).length()) {	// Skip over entries with length less than the ?'s position, else we get out-of-range errors at the next comparison			
					mid -= 1;
				}
				if(mid < 0) { break; } // When you iterate backward and go beyond the first index, stop

				int entryLength = dictV.at(mid).length(); // To avoid confusion with the input word's length

				if (dictV.at(mid).substr(qPos + 1,entryLength - qPos) == word.substr(qPos + 1,length - qPos)) { // But we only display those that also match the part AFTER the ?
					foundCount += 1;
					outputCount += 1;
					if (outputCount <= maxOutput) {
						cout << dictV.at(mid) << endl;
					}
				}
				mid -= 1;
				if(mid < 0) { break; }
			}
			
			mid = originalMid + 1;
			if(mid >= dictV.size()) { break; }

			while(dictV.at(mid).substr(0,qPos) == word.substr(0,qPos)) { // Ditto
				compCount += 1;
				while(qPos >= dictV.at(mid).length()) {					
					mid += 1;
				}
				if(mid >= dictV.size()) { break; }
				int entryLength = dictV.at(mid).length();

				if (dictV.at(mid).substr(qPos + 1,entryLength - qPos) == word.substr(qPos + 1,length - qPos)) {
					foundCount += 1;
					outputCount += 1;
					if (outputCount <= maxOutput) {
						cout << dictV.at(mid) << endl;
					}
				}
				mid += 1;
				if(mid >= dictV.size()) { break; }
			}
			break;

		}
	  }

	cout << "Comparisons performed to return every answer: " << compCount << endl;
	cout << "Found entries: " << foundCount << endl;

}