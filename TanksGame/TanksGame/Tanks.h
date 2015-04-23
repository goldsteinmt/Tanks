#pragma once
#include "TanksObject.h"

ref class Tanks: public TanksObject{
protected:
	int num_mines, num_bullets, num_updates;
	array<Bullets^, 1> ^bullets;
	array<Mines^, 1> ^mines;

	
public:
	Tanks(); // Default constructor to prevent errors in other classes
	Tanks(int, int);
	void update();
	Bullets^ get_bullet(int); 
	Mines^ get_mine(int);

	void move(int key);
	int pocket();
	int get_num_bullets();
	void launch();
	void dropMine();
	void set_mines();
	void set_bullets();

};
