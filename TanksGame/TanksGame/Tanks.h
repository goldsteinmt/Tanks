#pragma once
#include "TanksObject.h"

ref class Tanks: public TanksObject{
private:
	int num_mines;

public:
	Tanks(int, int);

	void move(int key);
	int pocket();
	void grabMine();
	void dropMine();

};
