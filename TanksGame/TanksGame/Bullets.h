<<<<<<< HEAD
#include "TanksObject.h"

ref class Bullets: public TanksObject{
=======
#pragma once

ref class Bullets{
>>>>>>> origin/master
private:
	int xdiff, ydiff;

public:
	Bullets(int, int);

	void fire(int,int);
	void travel(int, int);

};