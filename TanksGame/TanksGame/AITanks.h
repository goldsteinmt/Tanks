#pragma once

#include "Tanks.h"

// AUTHOR: Matthew Goldstein

ref class AITanks: public Tanks{
private:
	Tanks^ player;

public:
	AITanks(int, int, Tanks^); // constructor -- takes the player as an argument to decide when to shoot
	void move();
};