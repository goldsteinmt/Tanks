#pragma once
#include "TanksObject.h"
#include "Bullets.h"
#include "Mines.h"

ref class Tanks: public TanksObject{
protected:
	int num_mines, num_bullets, num_updates;
	int maxb = 5; //max bullets on screen
	int maxu = 25;//number of updates after which to draw bullets travelling
	int maxm = 3;//max mines to be placed
	array<Bullets^, 1> ^bullets;
	array<Mines^, 1> ^mines;

	
public:
	Tanks(); // Default constructor to prevent errors in other classes
	Tanks(int, int);

	void update();

	Bullets^ get_bullet(int); 
	Mines^ get_mine(int);

	void move(int key);
	int pocket();//returns number of mines on screen even though name insinuates the opposite
	int get_num_bullets();
	void launch(int, int); //fires bullet
	void dropMine();
	void set_mines();
	void set_bullets();

};
