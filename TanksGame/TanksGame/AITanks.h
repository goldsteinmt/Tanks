#pragma once

#include "Tanks.h"
#include "Mines.h"
#include "Bullets.h"

// AUTHOR: Matthew Goldstein

ref class AITanks: public Tanks{
private:
	Tanks^ player; // holder for player 1 so ai tank can shoot at it
	const int NUM_BULLETS_CAN_FIRE = 5; // number of bullets that can be fired at a time
	const int NUM_MINES_CAN_PLACE = 3; // number of mines that can be placed at a time
	array<Bullets^, 1>^ bulletsShot; // holds current bullets
	array<Mines^, 1>^ minesPlaced; // holds mines that have been placed
public:
	AITanks(int, int, Tanks^); // constructor -- takes the player as an argument to decide when to shoot
	void move(); // function to decide whether or not to move ai tank and where to move it to
	void shoot(); // function to decide whether or not to shoot at the player and actually shoot
	array<Bullets^,1>^ getCurrentBullets(); // returns the array of currently live bullets
	array<Mines^, 1>^ getCurrentMines(); // returns the array of currently placed mines
};