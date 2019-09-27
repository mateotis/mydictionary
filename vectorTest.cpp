#include <iostream>
#include <vector>

using namespace std;

int main() {

	int a = 5;
	int b = 10;

	a = b;

	b += 20;

	cout << a << endl << b << endl;

	b = a;

	cout << a << endl << b << endl;

	return EXIT_SUCCESS;

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