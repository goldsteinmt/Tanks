#pragma once

// AUTHOR: Matthew Goldstein
ref class TanksObject{
	/*
	 *	The purpose of the TanksObject class is to be a super
	 *		class for the Tanks Class, the AITanks Class, the
	 *		Bullets Class, the Mines Class, and the Walls Class
	 */
protected:
	int x = 0; // x value of location
	int y = 0; // y value of location
	int width = 0; // width of object
	int height = 0; // height of object
public:
	int get_x(); // return x position of the object
	int get_y(); // return y position of the object
	int get_width(); // return width of the object
	int get_height(); // return height of the object
};