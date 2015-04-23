#include "Tanks.h"
#include "Mines.h"
#include "Bullets.h"

Tanks::Tanks(int setX, int setY){ x = setX; y = setY; num_bullets = 0; num_updates = 0; }

Tanks::Tanks(){} // Default constructor to prevent errors in other classes

void Tanks::move(int key){
	//for WASD keys
	//W is 1, D is 2, S is 3, A is 4

	switch (key){
	case 1:
		y--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y++;
		break;
	case 4:
		x--;
		break;
	}
}

int Tanks::pocket() {return num_mines;}

int Tanks::get_num_bullets() { return num_bullets; }

void Tanks::dropMine() { num_mines--; }

void Tanks::set_mines() {

	mines = gcnew array<Mines^, 1>(num_mines);
}

void Tanks::set_bullets() {

	bullets = gcnew array<Bullets^, 1>(5);
}

Bullets^ Tanks::get_bullet(int num){
	if (num < 5)
		return bullets[num];
}

Mines^ Tanks::get_mine(int num){
	if (num < 5)
		return mines[num];
}

void Tanks::launch()
{
	if (num_bullets < 5)
		num_bullets++;
}

void Tanks::update()
{
	num_updates++;
	for (int i = 0; i < 5; i++){
		if (bullets[i] != nullptr && num_updates % 25 == 0){
			bullets[i]->travel();
		}
	
}
