#pragma once
#include "TanksObject.h"

ref class Bullets: public TanksObject{

private:
	int xdiff, ydiff, num_update = 0;
	bool dead = false;

public:
	Bullets(int, int, int, int);

	void fire(int,int);
	void travel();
	bool isDead();
	void die();

};