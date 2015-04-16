#pragma once
#include "TanksObject.h"

ref class Tanks: public TanksObject{
private:

	int num_mines, num_bullets;
	array<Tanks^, 1> ^bullets;
	array<Tanks^, 1> ^mines;
	
public:
	Tanks(int, int);
	

	void move(int key);
	int pocket();
	int get_num_bullets();
	void dropMine();
	void set_mines();
	void set_bullets();

};
