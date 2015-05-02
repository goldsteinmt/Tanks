#include "Mines.h"

Mines::Mines(int setX, int setY){ 
	x = setX; 
	y = setY; 
	width = 30;
	height = 30;
}

bool Mines::isDead(){
	return dead;
}

void Mines::die(){
	dead = true;
}