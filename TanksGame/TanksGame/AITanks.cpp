#include "AITanks.h"


// AUTHOR: Matthew Goldstein

AITanks::AITanks(int newX, int newY, Tanks^ newPlayer){
	player = newPlayer;
	x = newX;
	y = newY;
	width = 50;
	height = 50;

	bulletsShot = gcnew array<Bullets^, 1>(NUM_BULLETS_CAN_FIRE);
	minesPlaced = gcnew array<Mines^, 1>(NUM_MINES_CAN_PLACE);

	for (int i = 0; i < NUM_BULLETS_CAN_FIRE; i++){
		bulletsShot[i] = nullptr;
	}
	for (int m = 0; m < NUM_MINES_CAN_PLACE; m++){
		minesPlaced[m] = nullptr;
	}
}

Bullets^ AITanks::getBullet(int index){
	if (index < NUM_BULLETS_CAN_FIRE)
		return bulletsShot[index];
}

Mines^ AITanks::getMine(int index){
	if (index < NUM_MINES_CAN_PLACE)
		return minesPlaced[index];
}

void AITanks::update(array<Walls^, 1>^ wallsArr){
	numUpdates++;

	if (numUpdates % BULLET_FIRE_RATE == 0){
		if (num_current_bullets < NUM_BULLETS_CAN_FIRE){
			bulletsShot[num_current_bullets] = gcnew Bullets(x + width/2, y +height/2, player->get_x() + (player->get_width() / 2), player->get_y() + (player->get_height() / 2));
			num_current_bullets++;
		}
	}

	if (numUpdates % MINE_PLACE_RATE == 0 && num_mines_placed < NUM_MINES_CAN_PLACE){
		minesPlaced[num_mines_placed] = gcnew Mines(x + (width / 2), y + height);
		num_mines_placed++;
	}

	if (checkCollide(wallsArr)){
		direction++;
	}
	if (numUpdates % TANK_ROTATE_RATE == 0){
		direction--;
	}
	

	if (numUpdates % TANK_MOVE_RATE == 0){
		if (direction % 4 == 0){
			y -= MOVE_DISTANCE;
		}
		else if (direction % 4 == 1){
			x += MOVE_DISTANCE;
		}
		else if (direction % 4 == 2){
			y += MOVE_DISTANCE;
		}
		else if (direction % 4 == 3){
			x -= MOVE_DISTANCE;
		}
	}

	for (int j = 0; j < NUM_BULLETS_CAN_FIRE; j++){
		if (bulletsShot[j] != nullptr){
			if (bulletsShot[j]->isDead()){
				for (int k = j; k < NUM_BULLETS_CAN_FIRE - 1; k++){
					bulletsShot[k] = bulletsShot[k + 1];
				}
				bulletsShot[NUM_BULLETS_CAN_FIRE - 1] = nullptr;
				num_current_bullets--;
			}
		}
	}

	for (int i = 0; i < NUM_BULLETS_CAN_FIRE; i++){
		if (bulletsShot[i] != nullptr && numUpdates % BULLET_MOVE_RATE == 0){
			bulletsShot[i]->travel();
		}
	}
}

bool AITanks::checkCollide(array<Walls^, 1>^ wallsArr){
	CollisionDetect col;
	for (int i = 0; i < wallsArr->Length; i++){
		if (col.detectCollide(this, wallsArr[i], direction))
			return true;
	}
	return false;
}

void AITanks::die(){
	dead = true;
}

bool AITanks::isDead(){
	return dead;
}

int AITanks::get_num_bullets(){
	return num_current_bullets;
}

int AITanks::getDirection(){
	return direction;
}