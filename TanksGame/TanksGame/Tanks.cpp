#include "Tanks.h"
#include "Mines.h"

Tanks::Tanks(int setX, int setY){x = setX; y = setY;}


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

	mines = gcnew array<Tanks^, 1>(num_mines);

	//for (int i = 0; i < num_mines; i++)
	//	mines[i] = gcnew Mines(i);
}

void Tanks::set_bullets() {

	bullets = gcnew array<Tanks^, 1>(num_bullets);
}

