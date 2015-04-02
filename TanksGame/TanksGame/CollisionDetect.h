#pragma once

#include "Bullets.h"
#include "Mines.h"
#include "Tanks.h"
#include "AITanks.h"
#include "Walls.h"

// AUTHOR: Matthew Goldstein

class CollisionDetect {
private:

public:
	//bool checkCollide(Bullets, Bullets); // Check if a bullet collides with another bullet
	bool checkCollide(Bullets, Walls); // Check if the bullet hit the wall
	bool checkCollide(Bullets, AITanks); // Check if the bullet hit an AI Tank
	bool checkCollide(Bullets, Tanks); // Check if the bullet hit the player tank
	bool checkCollide(Bullets, Mines); // Check if the bullet hit the mine
	bool checkCollide(AITanks, Tanks); // Check if the AI and the player hit each other
	bool checkCollide(AITanks, AITanks); // Check if two AI Tanks hit each other
	bool checkCollide(AITanks, Walls); // Check if the AI hits a wall
	bool checkCollide(AITanks, Mines); // Check if the AI ran over a mine
	bool checkCollide(Tanks, Mines); // Check if the player ran over a mine
	bool checkCollide(Tanks, Walls); // Check if the player crashed into the wall
};