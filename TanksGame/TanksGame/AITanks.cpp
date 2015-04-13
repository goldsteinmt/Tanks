#include "AITanks.h"

// AUTHOR: Matthew Goldstein

AITanks::AITanks(int newX, int newY, Tanks^ newPlayer){
	player = newPlayer;
	x = newX;
	y = newY;
	width = 0;  // TODO: change
	height = 0; // TODO: change


	bulletsShot = gcnew array<Bullets^, 1>(NUM_BULLETS_CAN_FIRE);
	minesPlaced = gcnew array<Mines^, 1>(NUM_MINES_CAN_PLACE);

}

array<Bullets^, 1>(NUM_BULLETS_CAN_FIRE) AITanks::getCurrentBullets(){
	return bulletsShot;
}

AITanks::getCurrentMines(){
	return minesPlaced;
}