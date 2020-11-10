#pragma once
#include <iomanip>

//____________________________________ NODE CLASS ________________________________________
template <class T>
class Node {
public:
	Node() : up(NULL), down(NULL), left(NULL), right(NULL) {}
	Node(const T& v) : value(v), up(NULL), down(NULL), left(NULL), right(NULL) {}

	T value;
	Node<T>* up;
	Node<T>* down;
	Node<T>* left;
	Node<T>* right;
};

template <class T> class Grid;

//_________________________________ GRID ITERATOR CLASS __________________________________
template <class T>
class GridIterator {

public:
	friend class Grid<T>;
	//void setSpiralTrue() { spiral = true; }
	GridIterator(Node<T>* p = NULL) : ptr(p) {};

	T& operator* () { return ptr->value; }

	GridIterator<T>& left() {
		ptr = ptr->left;
		return *this;
	}

	GridIterator<T>& right() {

		ptr = ptr->right;
		return *this;
	}

	GridIterator<T>& up() {
		ptr = ptr->up;
		return *this;
	}

	GridIterator<T>& down() {
		ptr = ptr->down;
		return *this;
	}
	GridIterator<T>& operator++(int) {
		if (spiral = false) {
			if (going_right == true && ptr->right != NULL) {
				ptr = ptr->right;
				return *this;
			}
			else if (going_right == true && ptr->right == NULL) {
				going_right = false;
				ptr = ptr->down;
				return *this;
			}
			else if (going_right == false && ptr->left != NULL) {
				ptr = ptr->left;
				return *this;
			}
			else {
				going_right = true;
				ptr = ptr->down;
				return *this;
			}
		}/*
		else {
			if (direction == "top") {
				top--;
				grid_size--;
				if (top == 1) { direction = "right"; }
				ptr = ptr->right;
				return *this;
			}
			else if (direction == "right") {
				size_right--;
				grid_size--;
				if (size_right == 1) { direction = "bottom";	}
				ptr = ptr->down;
				return *this;
			}
			else if (direction == "bottom") {
				bottom--;
				grid_size--;
				if (bottom == 1) { direction = "left"; }
				ptr = ptr->left;
				return *this;
			}
			else if (grid_size == 0) {
				ptr = NULL;
				return *this;
			}
			else{
				size_left--;
				grid_size--;
				if (size_left == 1) {
					direction = "top";
					loop_count++;
					s_top = width - (loop_count * 2);
					s_right = height - (loop_count * 2);
					s_bottom = width - (loop_count * 2);
					s_left = (height - 1) - (loop_count * 2);
				}
				ptr = ptr->up;
				return *this;
			}
		}*/
	}

	GridIterator<T>& operator--(int) {
		if (going_left == true && ptr->left != NULL) {
			ptr = ptr->left;
			return *this;
		}
		else if (going_left == true && ptr->left == NULL) {
			going_left = false;
			ptr = ptr->up;
			return *this;
		}
		else if (going_left == false && ptr->right != NULL) {
			ptr = ptr->right;
			return *this;
		}
		else {
			going_left = true;
			ptr = ptr->up;
			return *this;
		}
	}
	bool operator!= (const GridIterator<T>& r) const { return ptr != r.ptr; }

private:
	
	Node<T>* ptr;
	//std::string direction = "top";
	bool going_right = true;
	bool going_left = true;
	bool spiral = false;
	/*int loop_count = 0;
	unsigned int width;
	unsigned int height;
	unsigned int grid_size;
	unsigned int top = width;
	unsigned int bottom = width;
	unsigned int size_left = height - 1;
	unsigned int size_right = height;
	unsigned int s_top;
	unsigned int s_right;
	unsigned int s_bottom;
	unsigned int s_left;*/
};

//____________________________________ GRID CLASS ________________________________________
template <class T>
class Grid {
public:

	//friend class GridIterator<T>;
	//Constructor
	Grid();
	Grid(int w, int h, T v = 0);
	//Grid(const Grid<T>& old) { copy_list(old); }
	~Grid() { destroy_grid(); }

	typedef GridIterator<T> iterator;
	iterator begin_upper_left() { return iterator(upper_left); }
	iterator begin_upper_right() { return iterator(upper_right); }
	iterator begin_lower_left() { return iterator(lower_left); }
	iterator begin_lower_right() { return iterator(lower_right); }
	iterator begin_snake() { return iterator(upper_left); }
	iterator end_snake() { return iterator(NULL); }
	//iterator begin_spiral() {
	//	iterator setSprial();
	//	return iterator(upper_left); }
	//iterator end_spiral() {	return iterator(NULL); }
	

	//Accessors/Modifiers
	unsigned int getSize() { return grid_size; }
	unsigned int getHeight() { return height; }
	unsigned int getWidth() { return width; }
	
	void setWidth(int x) { width = x; }
	void setHeight(int y) { height = y; }

	void join(Grid<T> &grid);
	void stack(Grid<T>& grid);
	void lift(iterator itr, Grid<T>& top_grid);
	void chop(iterator itr, Grid<T>& side_grid);
	void reset(T);

	void set(int w, int h, T v);
	T get(int w, int h);
	void clear() { destroy_grid(); }
	void destroy_grid();
	Node<T>* GetUpperLeft() { return upper_left; }
	Node<T>* GetLowerLeft() { return lower_left; }
	void print();


private:
	//Nodes
	Node<T>* upper_left;
	Node<T>* upper_right;
	Node<T>* lower_left;
	Node<T>* lower_right;

	unsigned int height;
	unsigned int width;
	unsigned int grid_size;
	T value;
};

template <class T> Grid<T>::Grid() {
	Node<T>* upper_left = NULL;
	Node<T>* upper_right = NULL;
	Node<T>* lower_left = NULL;
	Node<T>* lower_right = NULL;
	grid_size = 0;
	height = 0;
	width = 0;
	value = 0;
};

template <class T> Grid<T>::Grid(int w, int h, T v) {
	grid_size = (w * h);
	width = w;
	height = h;
	Node<T>* current;
	Node<T>* prev;
	Node<T>* above;
	current = new Node<T>(v);
	prev = current;
	above = current;

	//Build grid here.
	//First Line
	for (int i = 0; i < w; i++) {
		//Top Left Node
		if (i == 0) {
			upper_left = current;
			lower_left = current;
			prev = current;
		}
		//Top Right Node
		else if (i == (w - 1)) {
			current = new Node<T>(v);
			prev->right = current;
			current->left = prev;
			upper_right = current;
			lower_right = current;
		}
		//Middle Nodes
		else {
			current = new Node<T>(v);
			current->left = prev;
			prev->right = current;
			prev = current;
		}
	}

	if (h > 1) {
		//Set Above Node
		for (int j = 1; j < h; j++) {
			above = upper_left;
			int k = j;
			while (k != 1) {
				above = above->down;
				k--;
			}

			for (int i = 0; i < w; i++) {
				//Bottom Left Node
				if (j == (h - 1) && i == 0) {
					current = new Node<T>(v);
					above->down = current;
					current->up = above;
					prev = current;
					lower_left = current;
					lower_right = current;
				}
				//Bottom Right Node
				else if (j == (h - 1) && i == (w - 1)) {
					current = new Node<T>(v);
					above = above->right;
					above->down = current;
					current->up = above;
					prev->right = current;
					current->left = prev;
					prev = current;
					lower_right = current;
				}
				//Left Edge Node
				else if (i == 0) {
					current = new Node<T>(v);
					prev = current;
					above->down = current;
					current->up = above;
				}
				//Middle Node(s)
				else {
					current = new Node<T>(v);
					above = above->right;
					above->down = current;
					current->up = above;
					prev->right = current;
					current->left = prev;
					prev = current;
				}

			}
		}
	}
};

template <class T> void Grid<T>::set(int w, int h, T v) {
	Node<T>* curr = upper_left;
	Node<T>* temp = curr;

	for (int j = 0; j < height; j++) {
		if (j > 0) {
			curr = temp;
			curr = curr->down;
		}
		temp = curr;
		for (int i = 0; i < width; i++) {
			if (w == i && h == j) {
				curr->value = v;
				break;
			}
			curr = curr->right;
		}
	}

}

template <class T> T Grid<T>::get(int w, int h) {
	Node<T>* curr = upper_left;
	Node<T>* temp = curr;

	for (int j = 0; j < height; j++) {
		if (j > 0) {
			curr = temp;
			curr = curr->down;
		}
		temp = curr;
		for (int i = 0; i < width; i++) {
			if (w == i && h == j) {
				return curr->value;
			}
			curr = curr->right;
		}
	}
}

template <class T> void Grid<T>::join(Grid<T> &new_grid) {
	Node<T>* current_grid = upper_right;
	Node<T>* joining_grid = new_grid.GetUpperLeft();
	Node<T>* above_grid = joining_grid;
	for (int i = 0; i < height; i++) {
		//upper right node
		if (i == 0) {
			current_grid->right = joining_grid;
			joining_grid->left = current_grid;
			upper_right = new_grid.upper_right;
			current_grid = current_grid->down;
			joining_grid = joining_grid->down;
		}
		//bottom right node
		else if (i == height-1) {
			current_grid->right = joining_grid;
			joining_grid->left = current_grid;
			above_grid->down = joining_grid;
			joining_grid->up = above_grid;
			lower_right = new_grid.lower_right;
		}
		//middle node(s)
		else {
			current_grid->right = joining_grid;
			joining_grid->left = current_grid;
			above_grid->down = joining_grid;
			joining_grid->up = above_grid;

			//shift iterator down;
			current_grid = current_grid->down;
			above_grid = above_grid->down;
			joining_grid = joining_grid->down;
		}
	}
	//set newly conjoined grid width
	width += new_grid.getWidth();

	//Removing pointers to new grid and set height and width to 0;
	new_grid.upper_left = NULL;
	new_grid.upper_right = NULL;
	new_grid.lower_left = NULL;
	new_grid.lower_right = NULL;
	new_grid.setWidth(0);
	new_grid.setHeight(0);

}

template <class T> void Grid<T>::stack(Grid<T>& new_grid) {

	Node<T>* current_grid = upper_left;
	Node<T>* joining_grid = new_grid.GetLowerLeft();
	Node<T>* prev_grid = joining_grid;

	for (int i = 0; i < width; i++) {
		//upper left node
		if (i == 0) {
			current_grid->up = joining_grid;
			joining_grid->down = current_grid;
			upper_left = new_grid.upper_left;
			joining_grid = joining_grid->right;
			current_grid = current_grid->right;
		}
		//upper right node
		else if (i == width - 1) {
			current_grid->up = joining_grid;
			joining_grid->down = current_grid;
			joining_grid->left = prev_grid;
			prev_grid->right = joining_grid;
			upper_right = new_grid.upper_right;;
		}
		//middle node(s)
		else {
			current_grid->up = joining_grid;
			joining_grid->down = current_grid;
			joining_grid->left = prev_grid;
			prev_grid->right = joining_grid;

			joining_grid = joining_grid->right;
			prev_grid = prev_grid->right;
			current_grid = current_grid->right;
		}

	}
	//set newly conjoined grid width
	height += new_grid.getHeight();
	grid_size = height * width;

	//Removing pointers to new grid and set height and width to 0;
	new_grid.upper_left = NULL;
	new_grid.upper_right = NULL;
	new_grid.lower_left = NULL;
	new_grid.lower_right = NULL;
	new_grid.setWidth(0);
	new_grid.setHeight(0);
}

template <class T> void Grid<T>::reset(T input) {
	Node<T>* curr = upper_left;
	Node<T>* temp = curr;
	for (int i = 0; i < height; i++) {
		if (i > 0) {
			curr = temp;
			curr = curr->down;
		}
		temp = curr;
		for (int j = 0; j < width; j++) {
			curr->value = input;
			curr = curr->right;
		}
	}
};

template <class T> void Grid<T>::print() {
	Node<T>* curr = upper_left;
	Node<T>* temp = curr;
	for (int i = 0; i < height; i++) {
		if (i > 0) {
			curr = temp;
			curr = curr->down;
		}
		temp = curr;
		for (int j = 0; j < width; j++) {
			std::cout << std::setw(3);
			std::cout << curr->value << " ";
			if (curr->right == NULL) {
				std::cout << std::endl;
				break;
			}
			curr = curr->right;	
		}
	}
};

template <class T> void Grid<T>::destroy_grid() {
	if (grid_size != 0) {
		iterator temp = upper_left;
		iterator scrap = upper_left;

		while (temp != NULL) {
			scrap = temp;
			temp++;
			delete scrap.ptr;
			scrap.ptr = NULL;
			grid_size--;
		}
	}
	if (grid_size == 0) {
		height = 0;
		width = 0;
	}
}

template <class T> void Grid<T>::lift(iterator itr, Grid<T>& top_grid) {

	int row_height = 0;
	int row_counter = 0;
	top_grid.height = -1;

	iterator scrap_grid_itr = itr;
	iterator grid_itr = scrap_grid_itr;
	iterator height_itr = itr;

	while (height_itr.ptr != NULL) {
		height_itr.up();
		top_grid.height++;
	}

	//ADD CONDITIONAL TO PREVENT EDGE CASE
	grid_itr.right(); 
	while (scrap_grid_itr.ptr != NULL) {
		grid_itr.left();
		scrap_grid_itr.left();
	}
	//set new grid width & height;
	top_grid.width = width;
	top_grid.grid_size = top_grid.height * top_grid.width;


	//set upper left and right node of new grid
	top_grid.upper_left = upper_left;
	top_grid.upper_right = upper_right;
	
	//set upper left of old grid
	upper_left = grid_itr.ptr;
	
	//set lower left of new grid
	grid_itr.up();
	top_grid.lower_left = grid_itr.ptr;

	//move iterator to right side
	for (int i = 1; i < width; i++) {
		grid_itr.right();
	}

	//set lower right node of new grid
	top_grid.lower_right = grid_itr.ptr;

	//move iterator down
	grid_itr.down();

	//set upper right of old grid
	upper_right = grid_itr.ptr;

	Node<T>* curr = top_grid.lower_left;
	for (int i = 0; i < width; i++) {
		curr->down = NULL;
		curr = curr->right;
	}

	curr = upper_left;
	for (int i = 0; i < width; i++) {
		curr->up = NULL;
		curr = curr->right;
	}

	//set new height
	height = height - top_grid.height;

	//set new size
	grid_size = height * width;
}

template <class T> void Grid<T>::chop(iterator itr, Grid<T>& side_grid) {

	int row_height = 0;
	int row_counter = 0;
	side_grid.width = 0;
	side_grid.height = height;

	iterator scrap_grid_itr = itr;
	iterator grid_itr = scrap_grid_itr;
	iterator width_itr = itr;

	//determine width of new grid
	while (width_itr.ptr != NULL) {
		width_itr.right();
		side_grid.width++;
	}

	//ADD CONDITIONAL TO PREVENT EDGE CASE
	//move iterator to starting position
	grid_itr.down();
	while (scrap_grid_itr.ptr != NULL) {
		grid_itr.up();
		scrap_grid_itr.up();
	}

	//ADD CONDITIONAL TO PREVENT EDGE CASE
	//set upper left gird
	side_grid.upper_left = grid_itr.ptr;

	//move iterator to new upper right node
	for (int i = 0; i < side_grid.width-1; i++) {
		grid_itr.right();
	}
	
	//set upper right node
	side_grid.upper_right = grid_itr.ptr;

	//move iterator down to new bottom right node
	for (int i = 0; i < side_grid.height - 1; i++) {
		grid_itr.down();
	}
	side_grid.lower_right = grid_itr.ptr;

	//move iterator left to new bottom left node
	for (int i = 0; i < side_grid.width - 1; i++) {
		grid_itr.left();
	}
	side_grid.lower_left = grid_itr.ptr;

	//move iterator left to old grid new bottom right node
	grid_itr.left();
	lower_right = grid_itr.ptr;

	//move iterator up to old grid new top right node
	for (int i = 0; i < side_grid.height - 1; i++) {
		grid_itr.up();
	}
	upper_right = grid_itr.ptr;

	Node<T>* curr = side_grid.upper_left;
	for (int i = 0; i < height; i++) {
		curr->left = NULL;
		curr = curr->down;
	}

	curr = upper_right;
	for (int i = 0; i < height; i++) {
		curr->right = NULL;
		curr = curr->down;
	}

	//set new width
	width = width - side_grid.width;

	//set new size
	grid_size = height * width;
}

