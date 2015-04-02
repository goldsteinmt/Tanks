#pragma once

#include "TanksObject.h"

ref class Walls : public TanksObject{
private:
	int x, y;

public:
	Walls(int, int);
};