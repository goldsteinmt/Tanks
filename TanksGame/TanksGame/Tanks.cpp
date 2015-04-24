#include "Tanks.h"

Tanks::Tanks(int setX, int setY){ x = setX; y = setY; num_bullets = 0; num_updates = 0; num_mines = 0; }

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
	//mines[maxm-] = nullptr;
	//num_mines++; 
	if (num_mines < maxm)
	{
		num_mines++;

	}
}

void Tanks::set_mines() {
	mines = gcnew array<Mines^, 1>(maxm);
}

void Tanks::set_bullets() {

	bullets = gcnew array<Bullets^, 1>(maxb);
}

Bullets^ Tanks::get_bullet(int num){
	if (num < maxb)
		return bullets[num];
}

Mines^ Tanks::get_mine(int num){
	if (num < maxm)
		return mines[num];
}

void Tanks::launch(int dx, int dy)
{
	if (num_bullets < maxb)
	{
		num_bullets++;

		for (int i = 0; i < maxb; i++){
			if (bullets[i] == nullptr)
			{
				bullets[i] = gcnew Bullets(x, y, dx, dy); i = maxb;
				//set i to maxb so it only fires one bullet and not all available
			}
		}
	}
}

void Tanks::update()
{
	num_updates++;

	if (num_updates % maxu == 0)
	for (int i = 0; i < maxb; i++){
		if (bullets[i] != nullptr)
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
	for (int i = 0; i < maxm; i++){
		if (mines[i]->isDead()){
			for (int j = i; j < (maxm - 1); j++){
				mines[j] = mines[j + 1];
			}
			mines[(maxm - 1)] = nullptr;
			num_mines--;
		}
	}
	
}
