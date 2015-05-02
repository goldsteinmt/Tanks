#include "Bullets.h"
Bullets::Bullets(int setX, int setY, int destination_x, int destination_y)
{
	width = 8;
	height = 8;
	x = setX; y = setY;
	fire(x, y, destination_x, destination_y);
}

void Bullets::fire(int tx, int ty, int mx, int my){
	int dx = mx - tx;
	int dy = my - ty;
	if (dx != 0){
		float angle = System::Math::Atan2(dy, dx);
		xdiff = STEP_RADIUS * System::Math::Cos(angle);
		ydiff = STEP_RADIUS * System::Math::Sin(angle);
	}
	else if (my > ty){
		xdiff = 0;
		ydiff = STEP_RADIUS;
	}
	else{
		xdiff = 0;
		ydiff = -STEP_RADIUS;
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