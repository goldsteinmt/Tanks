#pragma once

ref class Bullets{
private:
	int x, y, xdiff, ydiff;

public:
	Bullets(int, int);

	void fire(int,int);
	void travel(int, int);
	int get_x();
	int get_y();

};