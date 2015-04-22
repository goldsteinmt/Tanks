#include "AITanks.h"
#include "Bullets.h"

// AUTHOR: Matthew Goldstein

AITanks::AITanks(int newX, int newY, Tanks^ newPlayer){
	player = newPlayer;
	x = newX;
	y = newY;
	width = 60; 
	height = 60; 

	bulletsShot = gcnew array<Bullets^, 1>(NUM_BULLETS_CAN_FIRE);
	minesPlaced = gcnew array<Mines^, 1>(NUM_MINES_CAN_PLACE);

}

Bullets^ AITanks::getBullet(int index){
	if (index < NUM_BULLETS_CAN_FIRE)
		return bulletsShot[index];
}

Mines^ AITanks::getMine(int index){
	if (index < NUM_MINES_CAN_PLACE)
		return minesPlaced[index];
}

void AITanks::update(){
	numUpdates++;
	if (numUpdates % BULLET_FIRE_RATE == 0){
		if (num_current_bullets < NUM_BULLETS_CAN_FIRE){
			bulletsShot[num_current_bullets] = gcnew Bullets(x, y, player->get_x(), player->get_y());
			num_bullets++;
		}
	}

	if (numUpdates % MINE_PLACE_RATE == 0 && num_mines_placed < NUM_MINES_CAN_PLACE){
		minesPlaced[num_mines_placed] = gcnew Mines(x + (width / 2), y + height);
	}

	if (numUpdates % MOVE_RATE == 0){
		if (direction%4 == 0){
			y -= MOVE_DISTANCE;
		}
		else if (direction%4 == 1){
			x += MOVE_DISTANCE;
		}
		else if (direction % 4 == 2){
			y += MOVE_DISTANCE;
		}
		else if (direction % 4 == 3){
			x -= MOVE_DISTANCE;
		}
	}

	for (int i = 0; i < NUM_BULLETS_CAN_FIRE; i++){
		if (bulletsShot[i] != nullptr && numUpdates % MOVE_RATE == 0){
			bulletsShot[i]->travel();
		}
	}
}

void AITanks::move(){

}
