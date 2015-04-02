#include "Bullets.h"
Bullets::Bullets(int setX, int setY){ x = setX; y = setY; }


void Bullets::fire(int destination_x, int destination_y){
	int factor;
	xdiff = destination_x - x;
	ydiff = destination_y - y;
	if ((xdiff < 0 && ydiff<0) || (xdiff>0 && ydiff>0))
		factor = 1;
	else factor = -1;

	for (int i = xdiff * ydiff*factor; i > 1; i--) {
		if ((xdiff % i == 0) && (ydiff % i == 0)) {
			xdiff /= i; ydiff /= i;
		}
	}
}

void Bullets::travel(int xdiff, int ydiff){
	x += xdiff;
	y += ydiff;
	}

