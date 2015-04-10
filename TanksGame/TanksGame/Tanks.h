#pragma once
#include "TanksObject.h"

ref class Tanks: public TanksObject{
private:
<<<<<<< HEAD
	int num_mines, num_bullets;


=======
	
	int num_mines;
>>>>>>> origin/master
public:
	Tanks();
	Tanks(int, int);

	void move(int key);
	int pocket();
	int get_num_bullets();
	void dropMine();

};
