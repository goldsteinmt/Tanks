#pragma once
#include "TanksObject.h"

ref class Tanks: public TanksObject{
private:
<<<<<<< HEAD
	
=======
	int num_mines;

>>>>>>> origin/master
public:
	Tanks(int, int);

	void move(int key);
	int pocket();
	void grabMine();
	void dropMine();

};
