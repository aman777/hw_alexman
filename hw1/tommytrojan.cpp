#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3){
    	cerr << "Please provide an input and output file." << endl;
    	return 1;
  	}
  	ifstream input(argv[1]);
  	ofstream output(argv[2]);

  	int floors;
  	int *floorsizes;
  	string ***trojans;
  	string curr;

  	input >> floors;
  	trojans = new string**[floors];

  //you will need to keep track of how many people are on each floor.
  	floorsizes = new int[floors];
  	int** possessions = new int*[floors];

  	for (int i = 0; i < floors; i++) {
		floorsizes[i] = 0;
		trojans[i] = NULL;
		possessions[i] = NULL;
	}
	getline(input, curr);
	while(getline(input, curr)) {
		stringstream ss;
		ss << curr;
		ss >> curr;
		if (curr == "MOVEIN") {
			int i,k;  
			ss >> i;
			ss >> k;
			if ((!ss.eof()) || (ss.fail())) {
				output << "Error - incorrect command" << endl;
			}
			else {
				if ( ((i) > floors) ) {
					output << "Error - floor " << i << "  does not exist" << endl;
				}
				else if (floorsizes[i] != 0) {
					output << "Error - floor " << i << " is not empty" << endl;			
				}
				else {
					floorsizes[i] = k;

					trojans[i] = new string*[k];
					possessions[i] = new int[k];

					for (int j = 0; j < k; j++) {
						possessions[i][j] = 0;
						trojans[i][j] = NULL;
					}
				}
			}
		}

		else if (curr == "MOVEOUT") {
			int i;
			ss >> i;
			if ((!ss.eof()) || (ss.fail())) {
				output << "Error - incorrect command" << endl;
			}

			else if ((i > floors)) {
				output << "Error - invalid floor" << endl;
			}

			else if (floorsizes[i] == 0) {
				output << "Error - no one lives on that floor" << endl;
			}	

			else {
				for (int x = 0; x < floorsizes[i]; x++) {
					delete [] trojans[i][x];
				}
				delete[] trojans[i];
				trojans[i] = NULL;
				floorsizes[i] = 0;
				if (possessions[i] != NULL) {
					delete[] possessions[i];
					possessions[i] = NULL;
				}
			}
		}
		
		else if (curr == "OBTAIN") {
			int i, j, k;
			ss >> i >> j >> k;

			if (ss.fail()) {
				output << "Error - incorrect command" << endl;
			}

			else if (floorsizes[i] == 0) {
				output << "Error - nobody lives on that floor" << endl;
			}

			else if (possessions[i][j] == 0) { //CORE DUMP HERE

				possessions[i][j] = k;
				trojans[i][j] = new string[k];

				for (int x = 0; x < k; x++) {
					// string stuff;
					// ss >> stuff;
					
					// trojans[i][j][x] = stuff;
					ss >> trojans[i][j][x];
				}

			}
			else 
				output << "Error - student already has possessions" << endl;
		}
		
		else if (curr == "OUTPUT") {
			int i, j;
			ss >> i >> j;

			if ((!ss.eof()) || (ss.fail())) {
				output << "Error - incorrect command" << endl;
			}
			if (possessions[i][j] != 0) {
				for (int k = 0; k < possessions[i][j]; k++) { //SEG FAULT IN THIS LOOP
					output << trojans[i][j][k] << endl; 
				} 				
			}

			else if (floorsizes[i] == 0) {
				output << "Error - no student 'i' on that floor" << endl;
			}

			else {  
				output << "Error - student has no possessions" << endl;	
			}
			
		}
		
		else {
			output << "Error - incorrect command" << endl;
		}
	}

//MAKE CHECKS FOR EACH THING
//MAKE SURE THAT NO ONE HAS AN ITEM

	for (int i = 0; i < floors; i++) {
		for (int j = 0; j < floorsizes[i]; j++) {
				delete[] trojans[i][j];
		}
		delete[] trojans[i];
		delete[] possessions[i];
	}
	delete[] trojans;
	delete[] possessions;
	delete[] floorsizes;

	return 0;
}