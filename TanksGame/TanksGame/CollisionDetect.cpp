#include "CollisionDetect.h"

// AUTHOR: Matthew Goldstein

bool CollisionDetect::detectCollide(TanksObject ^obj1, TanksObject ^obj2){
	int obj1_x, obj1_y, obj1_w, obj1_h, obj2_x, obj2_y, obj2_w, obj2_h; // x, y, width and height of both objects
	obj1_x = obj1->get_x();
	obj1_y = obj1->get_y();
	obj1_w = obj1->get_width();
	obj1_h = obj1->get_height();
	obj2_x = obj2->get_x();
	obj2_y = obj2->get_y();
	obj2_w = obj2->get_width();
	obj2_h = obj2->get_height();

	// check x values
	if ((obj1_x >= obj2_x && obj1_x <= (obj2_x + obj2_w)) ||
		((obj1_x + obj1_w) >= obj2_x && (obj1_x + obj1_w) <= (obj2_x + obj2_w))){
		// check y values
		if ((obj1_y >= obj2_y && obj1_y <= (obj2_y + obj2_h)) ||
			((obj1_y + obj1_h) >= obj2_y && (obj1_y + obj1_h) <= (obj2_y + obj2_h))){
			return true; // the two objects collided
		}
	}

	return false; // the two objects didn't collide
}