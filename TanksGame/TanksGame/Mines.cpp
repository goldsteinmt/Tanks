#include "Mines.h"

Mines::Mines(int setX, int setY){ x = setX; y = setY; }

bool Mines::isDead(){
	return dead;
}

void Mines::die(){
	dead = true;
}