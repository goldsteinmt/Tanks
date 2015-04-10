#pragma once
#include "TanksObject.h"

ref class Tanks: public TanksObject{
private:
	int num_mines, num_bullets;


public:
	Tanks(int, int);

	void move(int key);
	int pocket();
	int get_num_bullets();
	void dropMine();

};
