#pragma once
#include "TanksObject.h"

ref class Bullets: public TanksObject{

private:
	int xdiff, ydiff;

public:
	Bullets(int, int);

	void fire(int,int);
	void travel(int, int);

};