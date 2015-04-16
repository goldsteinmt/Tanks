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
	const int BULLET_FIRE_RATE = 50; // number of frames between each bullet update
	const int MINE_PLACE_RATE = 150; // number of frames between each mine place
	const int MOVE_RATE = 25; // number of frames between each movement
	int num_current_bullets = 0; // number of bullets currently existing
	int num_mines_placed = 0; // number of mines tank has placed
	array<Bullets^, 1>^ bulletsShot; // holds current bullets
	array<Mines^, 1>^ minesPlaced; // holds mines that have been placed
	int numUpdates = 0; // number of updates 
public:
	AITanks(int, int, Tanks^); // constructor -- takes the player as an argument to decide when to shoot
	void move(); // function to decide whether or not to move ai tank and where to move it to
	void shoot(); // function to decide whether or not to shoot at the player and actually shoot
	Bullets^ getBullet(int); // returns the array of currently live bullets
	Mines^ getMine(int); // returns the array of currently placed mines
	void update(); // updates for every redraw
};