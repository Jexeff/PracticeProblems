#pragma once

class Tetris {
public:
	Tetris(int w);

	//ACCESSORS 
	int get_width() const; //Obtains tetris board width
	int get_max_height() const; //Obtains tertris board max height
	int get_lowest_height();
	int highest_height(int location, int piece_width, int piece_height);
	int count_squares();
	int remove_full_rows();
	void add_piece(char s, int r, int l); //Adds a piece to the gameboard
	void allocate_new_array(char*& n, int new_size); //allocates new array for data that includes the old array
	void print() const;
	void destroy();

	int* get_height_loc() { return heights; } //Obtains pointer refering to height array location
	char** get_data_loc() { return data; } // Obtains pointer refering to pointer of data array location


private:
	//Pointer Locations
	int* heights;
	char** data;

	//Variables
	int width;
};