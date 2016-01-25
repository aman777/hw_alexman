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
	}
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
				if ( ((i-1) > floors) ) {
					output << "Error - floor " << i << "  does not exist" << endl;
				}
				else if (floorsizes[i-1] != 0) {
					output << "Error - floor " << i << " is not empty" << endl;			
				}
				else {
					floorsizes[i-1] = k;

					trojans[i-1] = new string*[k];
					possessions[i-1] = new int[k];

					for (int j = 0; j < k; j++) {
						possessions[i-1][j] = 0;
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

			else if ( ((i-1) > floors)) {
				output << "Error - invalid floor" << endl;
			}

			else if (floorsizes[i-1] == 0) {
				output << "Error - no one lives on that floor" << endl;
			}	

			else {
				delete[] trojans[i-1];
				trojans[i-1] = NULL;				
				floorsizes[i-1] = 0;
				delete[] possessions[i-1];
				possessions[i-1] = NULL;
			}
		}
		
		else if (curr == "OBTAIN") {
			int i, j, k;
			ss >> i >> j >> k;

			if ((!ss.eof()) || (ss.fail())) {
				output << "Error - incorrect command" << endl;
			}

			if (floorsizes[i-1] == 0) {
				output << "Error - nobody lives on that floor" << endl;
			}

			else if (possessions[i-1][j-1] == 0) {
				possessions[i-1][j-1] = k;
				trojans[i-1][j-1] = new string[k];

				for (int x = 0; x < k; x++) {
					string stuff;
					ss >> stuff;
					
					trojans[i-1][j-1][x] = stuff;
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
			if (possessions[i-1][j-1] != 0) {
				for (int k = 0; k < possessions[i-1][j-1]; k++) { //SEG FAULT IN THIS LOOP
					output << trojans[i-1][j-1][k] << endl; 
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


/*
	for (int i = 0; i < floors; i++) {
		delete[] possessions[i];
	}
	delete[] floorsizes;
	delete[] trojans[floors];
	delete[] trojans;
	delete[] possessions;
*/
	return 0;
}