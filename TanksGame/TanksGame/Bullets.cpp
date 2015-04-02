#include "Bullets.h"
Bullets::Bullets(int newx, int newy){ x = newx; y = newy; }

int Bullets::get_x(){ return x; }

int Bullets::get_y(){ return y; }


void Bullets::fire(int destination_x, int destination_y){
	xdiff = destination_x - x;
	ydiff = destination_y - y;

	for (int i = xdiff * ydiff; i > 1; i--) {
		if ((xdiff % i == 0) && (ydiff % i == 0)) {
			xdiff /= i; ydiff /= i;
		}
	}
}

void Bullets::travel(int xdiff, int ydiff){
	x += xdiff;
	y += ydiff;
	}

