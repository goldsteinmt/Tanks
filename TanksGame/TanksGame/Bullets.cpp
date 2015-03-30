#include "Bullets.h"
Bullets::Bullets(int newx, int newy){ x = newx; y = newy; }

int Bullets::get_x(){ return x; }

int Bullets::get_y(){ return y; }


void Bullets::travel(int destination_x, int destination_y){
	int xdiff = destination_x - x;
	int ydiff = destination_y - y;

}