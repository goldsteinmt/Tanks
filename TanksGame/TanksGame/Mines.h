#pragma once
#include "TanksObject.h"

ref class Mines: public TanksObject{
private:
	bool dead = false;

public:
	Mines(int, int);
	bool isDead();
	void die();
};