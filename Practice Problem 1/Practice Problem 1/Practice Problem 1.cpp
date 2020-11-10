// Database Homework 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <algorithm>

void print(std::vector<std::vector<char>> puzVec) {

	//Prints the PuzVec Vector of Vectors

	for (int i = 0; i < puzVec.size(); i++) {
		for (int j = 0; j < puzVec[i].size(); j++) {
			std::cout << puzVec[i][j];
		}
		std::cout << "\n";
	}

}

int main(int argc, char* argv[])
{

	std::ifstream Puzzle(argv[1]);
	std::ifstream linuxDictionary(argv[2]);
	std::string str;
	std::vector<std::string> lcd;
	std::vector<std::vector<char>> puzVec;
	std::string checkVec;
	std::vector<std::string> notWords;
	std::vector<std::string> horizontal;
	std::vector<std::string> vertical;
	std::vector<int> horX;
	std::vector<int> horY;
	std::vector<int> vertX;
	std::vector<int> vertY;
	
		

	if (!Puzzle.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}

	if (!linuxDictionary.good()) {
		std::cerr << "Can't open " << argv[2] << " to read.\n";
		exit(1);
	}


	while (!linuxDictionary.eof()) {

		getline(linuxDictionary, str);
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		lcd.push_back(str);
	}

	while (!Puzzle.eof()) {

		std::vector<char> temp;
		getline(Puzzle, str);

		for (int i = 0; i < str.length(); i++){
			temp.push_back(str[i]);
			
		}
		puzVec.push_back(temp);
	
	}

	//Checks Vector size.
	//std::cout << puzVec.size();
	
	// Checks Horizontal Words.
	for (int i = 0; i < puzVec.size(); i++) {
		for (int j = 0; j < puzVec[i].size(); j++) {
			if (puzVec[i][j] != '#') {
				checkVec.push_back(puzVec[i][j]);

				if (j == puzVec[i].size()-1 && checkVec.size() >= 2) {
					bool match = false;
					for (int k = 0; k < lcd.size(); k++) {
						if (checkVec == lcd[k]) {
							match = true;
							horizontal.push_back(checkVec);
							horX.push_back(i);
							horY.push_back(j-checkVec.size()+1);
							checkVec.clear();
							break;
						}
					}

					if (match != true) {
						notWords.push_back(checkVec);
					}

				}
			}
			else if (checkVec.size() >= 2 && (j == puzVec[i].size()-1 || puzVec[i][j + 1] == '#')) {
				bool match = false;
				for (int k = 0; k < lcd.size(); k++) {
					if (checkVec == lcd[k]) {
						match = true;
						horizontal.push_back(checkVec);
						horX.push_back(i);
						horY.push_back(j - checkVec.size()+1);
						checkVec.clear();
						break;
					}
				}

				if (match != true) {
					notWords.push_back(checkVec);
	
				}
			}
			else {
				checkVec.clear();
			}
		}
		checkVec.clear();
	}


// Checks Vertical Words.

	for (int i = 0; i < puzVec[0].size(); i++) {
		for (int j = 0; j < puzVec.size()-1; j++) {
			if (puzVec[j][i] != '#') {
				checkVec.push_back(puzVec[j][i]);
				
				if (j == puzVec.size()-2 && checkVec.size() >= 2) {
					bool match = false;
					for (int k = 0; k < lcd.size(); k++) {
						if (checkVec == lcd[k]) {
							vertical.push_back(checkVec);
							vertX.push_back(j - checkVec.size() + 1);
							vertY.push_back(i);
							match = true;
							checkVec.clear();
							break;
						}
					}

					if (match != true) {
						notWords.push_back(checkVec);
					}
				
				}
			}
			else if (checkVec.size() >= 2 && (j == puzVec.size()-2 || puzVec[j+1][i] == '#')) {
				bool match = false;
				for (int k = 0; k < lcd.size(); k++) {
					if (checkVec == lcd[k]) {
						vertical.push_back(checkVec);
						vertX.push_back(j - checkVec.size() + 1);
						vertY.push_back(i);
						match = true;
						checkVec.clear();
						break;
					}
				}

				if (match != true) {
					notWords.push_back(checkVec);

				}
			}
			else {
				checkVec.clear();
			}

		}
		checkVec.clear();
	}

	for (int i = 0; i < notWords.size(); i++) {
		std::cout << notWords[i] << " is not a word \n";
	}

	if (notWords.size() == 0) {
		std::cout << "This is a valid puzzle. \n";
	}

	else {
		std::cout << "This is not a valid puzzle. \n";
	}
	
	if (argc >= 3);
	{
		if ((std::string)argv[3] == "--print") {

			std::cout << "\n+";

			for (int i = 0; i < puzVec[0].size(); i++) {
					std::cout << "----+";
			}
			std::cout << "\n";

			for (int i = 0; i < puzVec.size()-1; i++) {
				for (int y = 1; y <= 2; y++){
					for (int j = 0; j < puzVec[i].size(); j++) {

						if (j == puzVec[0].size() - 1 && puzVec[i][j] != '#') {
							std::cout << "|    |\n";
						}
						else if (j == puzVec[0].size() - 1  && puzVec[i][j] == '#') {
							std::cout << "|####|\n";
						}
						else if (puzVec[i][j] != '#') {
							std::cout << "|    ";
						}
						else {
							std::cout << "|####";
						}
					}
					if (y == 2) {
						for (int x = 0; x < puzVec[0].size(); x++) {
							std::cout << "+----";
							if (x == puzVec[0].size()-1) {
								std::cout << "+\n";
							}
						}
					}
				
				}
			}
				
					
		}

		if ((std::string)argv[4] == "--print_coordinates") {
			for (int i = 0; i < horizontal.size(); i++) {
				std::cout << "(" << horX[i] << "," << horY[i] << ")" << " ACROSS " << horizontal[i] << "\n";
			}
			for (int i = 0; i < vertical.size(); i++) {
				std::cout << "(" << vertX[i] << "," << vertY[i] << ")" << " DOWN " << vertical[i] << "\n";
			}

		}
		else {
		}

	}

}

		

	


	/*for (int i = 0; i < puzVec.size(); i++) {
		for (int j = 0; j < puzVec[i].size(); j++) {
			if (puzVec[i][j] != '#' && i-1 >= 0 && j-1 >= 0) {
				tempChar = puzVec[i][j];
				str.push_back(tempChar);
			}
			else if (puzVec[i][j] == '#' && puzVec[i-1][j-1] != '#') {
				
				
				
				tempChar = puzVec[i][j];
				str.push_back(tempChar);
				checkVec.push_back(str);
				str.clear();`
				
			}
			else {
				j < puzVec[i].size();
				checkVec.push_back(str);
				str.clear();
				
			}
		}
	}

	for (int i = 0; i < puzVec.size(); i++) {
		std::cout << checkVec[i] << "\n";
	}*/
		
	

	/*for (int i = 0; i < puzVec.size(); i++) {
		for (int j = 0; j < puzVec[i].size(); j++) {
			tempChar.push_back(puzVec[i][j]);
				
		}
	}

	for (int i = 0; i < checkVec.size(); i++) {
		for (int j = 0; j < checkVec[i].size(); j++) {
			std::cout << checkVec[i][j];
		}
		std::cout << "\n";
	}

	*/


	
	
	
	

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
