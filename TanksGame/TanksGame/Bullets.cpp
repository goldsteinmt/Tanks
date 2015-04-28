#include "Bullets.h"
Bullets::Bullets(int setX, int setY, int destination_x, int destination_y)
{
	x = setX; y = setY;
	fire(destination_x, destination_y);
}


void Bullets::fire(int dx, int dy){
	int factor;
	xdiff = dx - x;
	ydiff = dy - y;
	if ((xdiff < 0 && ydiff < 0) || (xdiff>0 && ydiff>0))
		factor = 1;
	else factor = -1;

	for (int i = xdiff * ydiff*factor; i > 1; i--) {
		if ((xdiff % i == 0) && (ydiff % i == 0)) {
			xdiff /= i; ydiff /= i;
		}
	}
}

void Bullets::travel(){
	x += xdiff;
	y += ydiff;
}

bool Bullets::isDead(){
	return dead;
}


void Bullets::die(){
	dead = true;
}