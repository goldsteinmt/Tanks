#pragma once

// AUTHOR: Matthew Goldstein
ref class TanksObject{
	/*
	 *	The purpose of the TanksObject class is to be a super
	 *		class for the Tanks Class, the AITanks Class, the
	 *		Bullets Class, the Mines Class, and the Walls Class
	 */
private:
	int x; // x value of location
	int y; // y value of location
	int width; // width of object
	int height; // height of object
public:
	int get_x();
};