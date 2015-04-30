#pragma once

#include "Tanks.h"
#include "Mines.h"
#include "Bullets.h"
#include "Walls.h"
#include "CollisionDetect.h"

// AUTHOR: Matthew Goldstein

ref class AITanks: public Tanks{
private:
	Tanks^ player; // holder for player 1 so ai tank can shoot at it
	bool dead = false; // whether or not the tank is dead
	const int NUM_BULLETS_CAN_FIRE = 5; // number of bullets that can be fired at a time
	const int NUM_MINES_CAN_PLACE = 3; // number of mines that can be placed at a time
	const int BULLET_FIRE_RATE = 50; // number of frames between each bullet update
	const int MINE_PLACE_RATE = 150; // number of frames between each mine place
	const int BULLET_MOVE_RATE = 2; // number of frames between each movement
	const int TANK_MOVE_RATE = 3; // number of frames between each tank movement
	const int TANK_ROTATE_RATE = 225; // tank will rotate every this number of updates to simulate random movement
	const int MOVE_DISTANCE = 5; // number of pixels to move at each update
	int num_current_bullets = 0; // number of bullets currently existing
	int num_mines_placed = 0; // number of mines tank has placed
	array<Bullets^, 1>^ bulletsShot; // holds current bullets
	array<Mines^, 1>^ minesPlaced; // holds mines that have been placed
	int numUpdates = 0; // number of updates 
	int direction = 0; // (%4) 0 = north, 1 = east, 2 = south, 3 = west
	bool checkCollide(array<Walls^,1>^); // checks if ai tank collided with a wall.
public:
	AITanks(int, int, Tanks^); // constructor -- takes the player as an argument to decide when to shoot
	bool isDead(); // returns true if the tank is dead and false otherwise
	void die(); // kills the tank
	Bullets^ getBullet(int); // returns the array of currently live bullets
	Mines^ getMine(int); // returns the array of currently placed mines
	void update(array<Walls^, 1>^); // updates for every redraw
};