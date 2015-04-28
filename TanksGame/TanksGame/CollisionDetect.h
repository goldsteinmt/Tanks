#pragma once

#include "TanksObject.h"

// AUTHOR: Matthew Goldstein

class CollisionDetect {
public:
	bool detectCollide(TanksObject^, TanksObject^); // Check if the two TanksObjects collide
	bool detectCollide(TanksObject^, TanksObject^, int); // same as above with direction
};