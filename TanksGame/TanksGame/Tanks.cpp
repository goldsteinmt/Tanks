#include "Tanks.h"

Tanks::Tanks(int newx, int newy){x = newx; y = newy;}


void Tanks::move(int key){
	//for WASD keys
	//W is 1, D is 2, S is 3, A is 4

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
