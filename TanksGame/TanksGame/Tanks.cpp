#include "Tanks.h"

Tanks::Tanks(int setX, int setY){
	x = setX;
	y = setY;
	num_bullets = 0;
	num_updates = 0;
	num_mines = 0;
	width = 60;
	height = 60; 	
	bullets = gcnew array<Bullets^, 1>(maxb);
	mines = gcnew array<Mines^, 1>(maxm);
}

Tanks::Tanks(){} // Default constructor to prevent errors in other classes

void Tanks::move(int key, array<Walls^, 1>^ warray){
	//for WASD keys
	//W is 1, D is 2, S is 3, A is 4

	if (checkCollide(warray, key))
		speed = -4;
	else if (checkCollide(warray, key) == false)
		speed = 2;

	switch (key){
	case 1:
		y-= speed;
		break;
	case 2:
		x+=speed;
		break;
	case 3:
		y+=speed;
		break;
	case 4:
		x-=speed;
		break;
	}

}

int Tanks::pocket() {return num_mines;}

int Tanks::get_num_bullets() { return num_bullets; }

void Tanks::dropMine() { 
	if (num_mines < maxm)
	{
		mines[num_mines] = gcnew Mines(x, y);
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
		bullets[num_bullets] = gcnew Bullets(x, y, dx, dy);
		num_bullets++;
	}
}

void Tanks::update()
{
	num_updates++;

	if (num_updates % maxu == 0)
	for (int i = 0; i < num_bullets; i++){
			bullets[i]->travel();
	}

	for (int i = 0; i < maxb; i++){
		if (bullets[i] != nullptr){
			if (bullets[i]->isDead()){
				for (int j = i; j < (maxb - 1); j++){
					bullets[j] = bullets[j + 1];
				}
				bullets[(maxb - 1)] = nullptr;
				num_bullets--;
			}
		}
	}

	for (int i = 0; i < maxm; i++){
		if (mines[i] != nullptr){
			if (mines[i]->isDead()){
				for (int j = i; j < (maxm - 1); j++){
					mines[j] = mines[j + 1];
				}
				mines[(maxm - 1)] = nullptr;
				num_mines--;
			}
		}
	}
	
}

bool Tanks::checkCollide(array<Walls^, 1>^ warray, int direction){
	CollisionDetect col;
	direction--;//to convert to 0123 that collisiondetect uses
	for (int i = 0; i < warray->Length; i++){
		if (col.detectCollide(this, warray[i], direction))
			return true;
	}
	return false;
}

int Tanks::get_direction(){
	return direction;
}