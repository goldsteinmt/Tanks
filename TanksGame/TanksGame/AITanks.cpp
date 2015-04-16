#include "AITanks.h"
#include "Bullets.h"

// AUTHOR: Matthew Goldstein

AITanks::AITanks(int newX, int newY, Tanks^ newPlayer){
	player = newPlayer;
	x = newX;
	y = newY;
	width = 60;  // TODO: change
	height = 60; // TODO: change


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
	if (numUpdates % 50 == 0){
		if (num_current_bullets < 5){
			bulletsShot[num_current_bullets] = gcnew Bullets(x, y, player->get_x(), player->get_y());
			num_bullets++;
		}
	}

}