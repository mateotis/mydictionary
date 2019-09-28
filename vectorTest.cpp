#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

	string word = "explo?ion";
	string::size_type qFound = word.find("?");

	if (qFound != string::npos) {
		cout << qFound << endl;
		cout << word.substr(0, qFound) << endl;
		cout << word.substr(qFound,1) << endl;
		cout << word.substr(qFound + 1,word.length() - qFound - 1) << endl; // To make sure the ? is excluded
		//int length = word.length() - 1; // Ignore the *
		//word = word.substr(0,length); // Also remove it from the string we pass to the function
		//cout << prefixSearch(dictV, 0, dictV.size() - 1, word, length) << endl;

		}

	return EXIT_SUCCESS;

	int a = 5;
	int b = 10;

	a = b;

	b += 20;

	cout << a << endl << b << endl;

	b = a;

	cout << a << endl << b << endl;


	vector<int> myVector;

	for (int i = 0; i < 16; i++) {
		myVector.push_back(i);
	}

	cout << myVector.size() << endl;
	cout << myVector.capacity() << endl;

	cout << myVector.back() << endl;
	myVector.back() = 20;
	cout << myVector.back() << endl;

	for (int i = 0; i < 8; i++) {
		myVector.pop_back();
	}

	cout << myVector.size() << endl;
	cout << myVector.capacity() << endl;

}