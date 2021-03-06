#include "CollisionDetect.h"

// AUTHOR: Joseph Chouinard

bool CollisionDetect::detectCollide(TanksObject ^obj1, TanksObject ^obj2){
	if (obj1 == nullptr || obj2 == nullptr){
		return false;
	}
	int obj1_x, obj1_y, obj1_w, obj1_h, obj2_x, obj2_y, obj2_w, obj2_h; // x, y, width and height of both objects
	obj1_x = obj1->get_x();
	obj1_y = obj1->get_y();
	obj1_w = obj1->get_width();
	obj1_h = obj1->get_height();
	obj2_x = obj2->get_x();
	obj2_y = obj2->get_y();
	obj2_w = obj2->get_width();
	obj2_h = obj2->get_height();

	// check values
	if ((obj1_x >= (obj2_x - obj1_w) && obj1_x <= (obj2_x + obj2_w)) && 
		((obj1_y >= (obj2_y - obj1_h)) && (obj1_y <= (obj2_y + obj2_h)))){
		return true;
	}

	return false; // the two objects didn't collide
}

bool CollisionDetect::detectCollide(TanksObject ^obj1, TanksObject ^obj2, int direction){
	if (obj1 == nullptr || obj2 == nullptr){
		return false;
	}
	int obj1_x, obj1_y, obj1_w, obj1_h, obj2_x, obj2_y, obj2_w, obj2_h; // x, y, width and height of both objects
	int dir = direction % 4;
	obj1_x = obj1->get_x();
	obj1_y = obj1->get_y();
	obj1_w = obj1->get_width();
	obj1_h = obj1->get_height();
	obj2_x = obj2->get_x();
	obj2_y = obj2->get_y();
	obj2_w = obj2->get_width();
	obj2_h = obj2->get_height();

	switch (dir){
	case 0: // moving up - new
		if ((obj1_x > (obj2_x - obj1_w) && obj1_x < (obj2_x + obj2_w)) && ((obj1_y >= obj2_y) && (obj1_y <= obj2_y + obj2_h)))
			return true;
		return false;
	case 1: // moving right - new
		if ((obj1_x + obj1_w >= obj2_x && obj1_x + obj1_w <= (obj2_x + obj2_w)) && ((obj1_y > obj2_y - obj1_h) && (obj1_y < obj2_y + obj2_h)))
			return true;
		return false;
	case 2: // moving down new
		if ((obj1_x >(obj2_x - obj1_w) && obj1_x < (obj2_x + obj2_w)) && ((obj1_y + obj1_h >= obj2_y) && (obj1_y + obj1_h <= obj2_y + obj2_h)))
			return true;
		return false;
	case 3: // moving left - new
		if ((obj1_x >= obj2_x && obj1_x <= (obj2_x + obj2_w)) && ((obj1_y > obj2_y - obj1_h) && (obj1_y < obj2_y + obj2_h)))
			return true;
		return false;
	default: // should never get here
		return true;
	}

	return false; // the two objects didn't collide
}