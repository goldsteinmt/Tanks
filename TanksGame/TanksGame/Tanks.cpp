#include "Tanks.h"
Tanks::Tanks(){}
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
