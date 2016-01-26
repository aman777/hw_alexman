#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	ifstream infile (argv[1]);
	int numLetters;

	infile >> numLetters;
	string* words = new string[numLetters];

	for (int i = 0; i < numLetters; i++) {
		infile >> words[i];
	}

	for (int i = numLetters -1; i >= 0; i--) {
		cout << words[i] << endl;
	}

	delete[] words;
	infile.close();

	return 0;
}