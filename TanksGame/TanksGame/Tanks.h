#pragma once

ref class Tanks{
private:
	int x, y;

public:
	Tanks(int, int);

	void move(int key);
	int get_x();
	int get_y();

};
