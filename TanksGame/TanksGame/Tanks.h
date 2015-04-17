#pragma once
#include "TanksObject.h"

ref class Tanks: public TanksObject{
protected:
	int num_mines, num_bullets, num_updates;
	array<Tanks^, 1> ^bullets;
	array<Tanks^, 1> ^mines;
	
public:
	Tanks(int, int);
	void update();
	//check if collided and check if dead-bullets
	//check if mines have been stepped on
	//make num bullets ++ when fired every 25 updates (to fire call travel)

	void move(int key);
	int pocket();
	int get_num_bullets();
	void dropMine();
	void set_mines();
	void set_bullets();

};
