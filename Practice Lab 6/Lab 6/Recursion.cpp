#include "Recursion.h"
#include <iostream>

Recursion::Recursion() {
	x = 0;
	y = 0;
}

Recursion::Recursion(int x_coord, int y_coord) {
	x = x_coord;
	y = y_coord;
}

void Recursion::findRoutes(int x, int y) {
	if (x == 0 && y == 0) {
		total++;
		return;
	}
	else if (x == 0) {
		findRoutes(x, y - 1);
	}
	else if (y == 0) {
		findRoutes(x-1, y);
	}
	else {
		findRoutes(x - 1, y);
		findRoutes(x, y - 1);
	}
};

void Recursion::printTotal() {
	std::cout << "The total number of paths is " << total << std::endl;
}