#include "tetris.h"
#include "piece.h"
#include <ctype.h>
#include <stddef.h>
#include <iostream>
#include <list>

//class constructor
Tetris::Tetris(int w) {

	//intializes board width
	width = w;
	int rows = 0;
	int cols = w;

	//initializes array of board width w, for allocation of heights.
	heights = new int[w];
	for (int i = 0; i < w; i++) { 
		heights[i] = 0;
	}

	//initializes array of board width w, for allocation of data in 2d character array.
	data = new char*[cols];
	for (int i = 0; i < cols; i++) {
		data[i] = new char[rows];
		for (int j = 0; j < rows; j++) {
			data[i][j] = ' ';
		}
	}

}

//Returns board width size
int Tetris::get_width() const { return width; }

//Returns boards max height
int Tetris::get_max_height() const {

	//loops through the height array on the heap and returns the max height value stored in the array.
	int max_height = 0;
	for (int i = 0; i < get_width(); i++) {
		if (heights[i] > max_height) { max_height = heights[i]; }
	}
	return max_height;
}

//Allocates a new array with the contents of the old array and increases the size where appropriate
void Tetris::allocate_new_array(char*& n, int new_size) {


}

int Tetris::highest_height(int location, int piece_width, int piece_height) {

	int highest_height = 0;
	for (int i = location; i < location + piece_width; i++) {
		if (heights[i] > highest_height) { highest_height = heights[i]; }
	}
	return highest_height;
}

int Tetris::get_lowest_height() {
	int lowest_height = get_max_height();
	for (int i = 0; i < width; i++) {
		if (lowest_height > heights[i]) { lowest_height = heights[i]; }
	}
	return lowest_height;
}

void Tetris::add_piece(char letter, int rotation, int location) {

	Piece tetris_piece(letter);
	tetris_piece.Rotate(rotation);

	int piece_width = tetris_piece.get_piece_width();
	int piece_height = tetris_piece.get_piece_height();
	int highest_height = Tetris::highest_height(location, tetris_piece.get_piece_width(), tetris_piece.get_piece_height());
	int* lowest_block = tetris_piece.Lowest_Character();

	//create new array pointers that holds locations of new arrays equal to new highest required height
	char** new_columns = new char* [piece_width];
	for (int i = 0; i < piece_width; i++) {
		new_columns[i] = new char[highest_height + piece_height];
		for (int j = 0; j < highest_height + piece_height; j++) {
			new_columns[i][j] = ' ';
		}
	}

	int row_leftoff = 0;
	//fills the new array with the values from the prior array
	for (int i = location; i < (location + piece_width); i++) {
		int temp = 0;
		for (int j = 0; j < heights[i]; j++) {
			new_columns[i - location][j] = data[i][j];
			temp++;
		}
		if (temp > row_leftoff) { row_leftoff = temp; }
	}

	int column_spaces[4];// = { NULL, NULL, NULL, NULL};

	for (int i = location, x = 0; i < location + piece_width; i++) {
		int temp = 0;
		for (int j = row_leftoff; j > row_leftoff - piece_height; j--) { 
			if (new_columns[i - location][j - 1] == ' ' && row_leftoff != 0) {
				temp++;
			}
			else {
				column_spaces[x] = temp;
				break;
			}
		}
		column_spaces[x] = temp;
		x++;
	}

	int move_down = 0;
	for (int i = 0; i < piece_width; i++) {
		column_spaces[i] = column_spaces[i] + lowest_block[i];
		if (column_spaces[i] < piece_height) { move_down = column_spaces[i]; }
	}

	//fills the new array with the values from the new piece
	char** piece_array = tetris_piece.get_piece_array();
	for (int i = location, x = 0; i < (location + piece_width); i++) {
		int row_start = row_leftoff;
		for (int j = heights[i], y = 0; j < heights[i] + piece_height; j++) {
			if (piece_array[x][y] == ' ') {
				y++;
				row_start++;
			}
			else {
				new_columns[x][row_start - move_down] = piece_array[x][y];
				row_start++;
				y++;
			}
		}
		x++;
	}

	//removes the old array from memory
	for (int i = location; i < location + piece_width; i++) {
		//delete[] data[i];
		data[i] = new_columns[i - location];
	}

	//updates the heights for the height array
	int start_height = highest_height + piece_height;
	for (int i = location; i < location + piece_width; i++) {
		for (int j = start_height - 1; j >= 0; j--) {
			if (data[i][j] == 'S' || data[i][j] == 'Z' || data[i][j] == 'J' || data[i][j] == 'L' || data[i][j] == 'O' || data[i][j] == 'I' || data[i][j] == 'T') {
				heights[i] = j + 1;
				break;
			}
		}
	}

	char** temp_data = new char* [width];
		for (int i = 0; i < width; i++) {
			temp_data[i] = new char[heights[i]];
			for (int j = 0; j < heights[i]; j++) {
				temp_data[i][j] = data[i][j];
			}
			//delete[] data[i];
		}

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < heights[i]; j++) {
				data[i][j] = temp_data[i][j];
			}
		}

	
		tetris_piece.destroy();
		/*for (int i = 0; i < width; i++) {
			delete[] temp_data[i];
		}
		for (int i = 0; i < piece_width; i++) {
			delete[] new_columns[i];
		}
		delete[] new_columns;
		delete[] temp_data;
		*/
}

int Tetris::remove_full_rows() {

	int row_to_remove[4] = { 0, 0, 0, 0 };
	int counter = 0;
	int score = 0;
	bool is_row_full = true;
	bool rows_removed = false;

	//Determines which rows need to be removed if any
	for (int j = 0; j < get_lowest_height(); j++) {
		for (int i = 0; i < width; i++) {
			if (data[i][j] == ' ') { is_row_full = false; }
		}
		if (is_row_full == true) {
			row_to_remove[counter] = j;
			rows_removed = true;
			counter++;
		}
		is_row_full = true;
		
	}

	if (rows_removed == true) {

		//Creates new 2D array for rows to stay
		char** new_data = new char* [width];
		for (int i = 0; i < width; i++) {
			new_data[i] = new char[heights[i]];
		}

		//for (int i = 0; i < 4; i++) { std::cout << row_to_remove[i] << std::endl; }

		int counter_end = counter;
		for (int i = 0; i < width; i++) {
			delete[] new_data[i];
		}
		delete[] new_data;
		score += counter;

		//initializes new temp_data array of appropraite size
		char** temp_data = new char* [width];
		for (int i = 0; i < width; i++) {
			if (heights[i] == 0) { temp_data[i] = new char[heights[i]]; }
			else { temp_data[i] = new char[(heights[i] - counter_end)]; }
		}

		//adds new_data to temp_data and removes blank rows
		for (int i = 0; i < width; i++) {
			counter = 0;
			for (int j = 0; j < (heights[i]); j++) {
				int x = j+counter;
				while (x == row_to_remove[counter] && j < heights[i]) {
					counter++;
					x++;
				}
				temp_data[i][j] = data[i][j + counter];
			}
		}

		//points data at new temp_data
		for (int i = 0; i < width; i++) {
			data[i] = temp_data[i];
		}

		delete[] temp_data;

		//changes heights array to have new heights based on removed rows
		for (int i = 0; i < width; i++) {
			bool is_column_empty = true;
			int column_height = 0;
			for (int j = 0; j <= heights[i] - counter_end; j++) {
				if (data[i][j] == 'O' || data[i][j] == 'I' || data[i][j] == 'S' || data[i][j] == 'Z' || data[i][j] == 'J' || data[i][j] == 'L' || data[i][j] == 'T') {
					column_height = j + 1;
					is_column_empty = false;
				}
			}
			if (is_column_empty == true) { heights[i] = 0; }
			else { heights[i] = column_height; }
		}

	}
	return score;

}


int Tetris::count_squares() {
	int squares_total = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < heights[i]; j++) {
			if (data[i][j] != ' ') { squares_total += 1; }
		}
	}
	return squares_total;
}

void Tetris::destroy() {
	for (int i = 0; i < width; i++) {
			delete[] data[i];
	} 
	delete[] data;
	delete[] heights;
}


