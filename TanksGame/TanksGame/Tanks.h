#pragma once
#include "TanksObject.h"

ref class Tanks: public TanksObject{
private:

public:
	Tanks(int, int);

	void move(int key);

};
