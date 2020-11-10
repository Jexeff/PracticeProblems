#include "piece.h"
#include <stddef.h>
#include <iostream>
#include <cmath>

Piece::Piece(char l) {
	
	int x = 0;
	int y = 0;
	letter = l;
	piece_array = new char* [4];
	lowest_block = new int[4];

	for (int i = 0; i < 4; i++) {
		lowest_block[i] = 0;
	}

	for (int i = 0; i < 4; i++) {
		piece_array[i] = new char[4];
		for (int j = 0; j < 4; j++) {
			piece_array[i][j] = ' ';
		}
	}

	if (l == 'I') {
		piece_array[0][0] = 'I';
		piece_array[0][1] = 'I';
		piece_array[0][2] = 'I';
		piece_array[0][3] = 'I';
	}
	else if (l == 'O') {
		piece_array[0][0] = 'O';
		piece_array[0][1] = 'O';
		piece_array[1][0] = 'O';
		piece_array[1][1] = 'O';
	}
	else if (l == 'T') {
		piece_array[1][0] = 'T';
		piece_array[0][1] = 'T';
		piece_array[1][1] = 'T';
		piece_array[2][1] = 'T';
	}
	else if (l == 'Z') {
		piece_array[0][1] = 'Z';
		piece_array[1][1] = 'Z';
		piece_array[1][0] = 'Z';
		piece_array[2][0] = 'Z';
	}
	else if (l == 'S') {
		piece_array[0][0] = 'S';
		piece_array[1][0] = 'S';
		piece_array[1][1] = 'S';
		piece_array[2][1] = 'S';
	}
	else if (l == 'L') {
		piece_array[0][0] = 'L';
		piece_array[0][1] = 'L';
		piece_array[0][2] = 'L';
		piece_array[1][0] = 'L';
	}
	else if (l == 'J') {
		piece_array[0][0] = 'J';
		piece_array[1][0] = 'J';
		piece_array[1][1] = 'J';
		piece_array[1][2] = 'J';
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece_array[i][j] == letter) {
				coordinates[x][y] = i;
				y++;
				coordinates[x][y] = j;
				x++;
				y = 0;
			}
		}
	}

};

int* Piece::Lowest_Character() {


	int piece_width = get_piece_width();
	int lowest_block_height = get_piece_height();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; i < 4; j++) {
			if (piece_array[i][j] != ' ') {
				lowest_block[i] = j;
				break;
			}
		}
	}

	return lowest_block;
}

void Piece::Rotate(int degrees) {

// Rotating matrix by 90 degree in Clockwise direction
	int r = round(degrees / 90);
	int n = 4;
	int x = 0;
	int y = 0;
	int max_y = 0;
	int max_x = 0;

	while (r > 0) {

		for (int i = 0; i < n / 2; i++)
		{
			for (int j = i; j < n - i - 1; j++)
			{
				// Swapping elements after each iteration in Clockwise direction
				int temp = piece_array[i][j];
				piece_array[i][j] = piece_array[n - 1 - j][i];
				piece_array[n - 1 - j][i] = piece_array[n - 1 - i][n - 1 - j];
				piece_array[n - 1 - i][n - 1 - j] = piece_array[j][n - 1 - i];
				piece_array[j][n - 1 - i] = temp;
			}
		}
		r--;
	}
	std::cout << std::endl;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece_array[i][j] == letter) {
				coordinates[x][y] = i;
				y++;
				coordinates[x][y] = j;
				x++;
				y = 0;
			}
		}
	}



	//slides left
	while (coordinates[0][0] != 0 && coordinates[1][0] != 0 && coordinates[2][0] != 0 && coordinates[3][0] != 0) {
		for (int i = 0; i < 4; i++) {
			coordinates[i][0] -= 1;
		}

	}

	//slides down
	while (coordinates[0][1] != 0 && coordinates[1][1] != 0 && coordinates[2][1] != 0 && coordinates[3][1] != 0) {
		for (int i = 0; i < 4; i++) {
			coordinates[i][1] -= 1;
		}

	}

	//resets matrix to null
	x = 0;
	y = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == coordinates[x][y] && j == coordinates[x][y + 1]) {
				piece_array[i][j] = letter;
				x++;
				y = 0;
			}
			else {
				piece_array[i][j] = ' ';
			}
		}
	}


};

// Prints the matrix
void Piece::Print_array() {
	for (int j = 3; j >= 0; j--) {
		for (int i = 0; i < 4; i++) {
			std::cout << piece_array[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// Prints the coordinates where letters are stored in the matrix
void Piece::Print_coordinates() {
	for (int i = 0; i < 4; i++) {
		std::cout << "(";
		for (int j = 0; j < 1; j++) {
			std::cout << coordinates[i][j] << "," << coordinates[i][j+1] << ")";
		}
		std::cout << std::endl;
	}
}

int Piece::get_piece_width() {

	int max_x = 0;

	for (int i = 0; i < 4; i++) {
		if (coordinates[i][0] > max_x) { max_x = coordinates[i][0]; }
	}

	return max_x + 1;
};

int Piece::get_piece_height() {

	int max_y = 0;

	for (int i = 0; i < 4; i++) {
		if (coordinates[i][1] > max_y) { max_y = coordinates[i][1]; }
	}

	return max_y + 1;
};

void Piece::destroy() {
	for (int i = 0; i < 4; i++) {
		delete[] piece_array[i];
	}
	delete[] lowest_block;
}



