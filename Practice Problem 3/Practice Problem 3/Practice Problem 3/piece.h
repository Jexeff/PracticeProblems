#pragma once

class Piece {
public:
	//CONSTRUCTOR
	Piece(char l);

	void Rotate(int degrees);
	void Print_array();
	void Print_coordinates();
	char** get_piece_array() { return piece_array; }
	int* Lowest_Character();
	int get_piece_width();
	int get_piece_height();
	void destroy();

private:
	char** piece_array;
	char letter;
	int* lowest_block;
	int coordinates[4][2];

};