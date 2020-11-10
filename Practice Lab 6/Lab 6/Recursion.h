#pragma once
class Recursion
{
public:
	Recursion();
	Recursion(int x_coord, int y_coord);
	void findRoutes(int x,int y);
	void printTotal();

private:
	int x;
	int y;
	int total = 0;
};

