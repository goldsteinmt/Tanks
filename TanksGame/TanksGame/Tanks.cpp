#include "Tanks.h"

Tanks::Tanks(int newx, int newy){x = newx; y = newy;}

int Tanks::get_x(){return x;}

int Tanks::get_y(){return y;}


void Tanks::move(int key){

	switch (key){
	case 1:
		y++;
		break;
	case 2:
		x++;
		break;
	case 3:
		y--;
		break;
	case 4:
		x--;
		break;
	}
}
