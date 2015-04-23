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

void Tanks::dropMine() { 
	mines[num_mines] = nullptr;
	num_mines--; }

void Tanks::set_mines() {

	mines = gcnew array<Mines^, 1>(num_mines);
}

void Tanks::set_bullets() {

	bullets = gcnew array<Bullets^, 1>(maxb);
}

Bullets^ Tanks::get_bullet(int num){
	if (num < maxb)
		return bullets[num];
}

Mines^ Tanks::get_mine(int num){
	if (num < num_mines)
		return mines[num];
}

void Tanks::launch(int dx, int dy)
{
	if (num_bullets < maxb)
	{
		num_bullets++;

		for (int i = 0; i < maxb; i++){
			if (bullets[i] == nullptr)
				bullets[i] = gcnew Bullets(x,y,dx,dy);
		}
	}
}

void Tanks::update()
{
	num_updates++;
	for (int i = 0; i < maxb; i++){
		if (bullets[i] != nullptr && num_updates % maxu == 0)
			bullets[i]->travel();
	}

	for (int i = 0; i < maxb; i++){
		if (bullets[i]->isDead()){
			for (int j = i; j < (maxb-1); j++){
				bullets[j] = bullets[j + 1];
			}
			bullets[(maxb-1)] = nullptr;
			num_bullets--;
		}
	}
	
}
