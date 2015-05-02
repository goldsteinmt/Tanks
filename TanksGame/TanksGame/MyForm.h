#pragma once

#include <vector>

#include "ReadFile.h"
#include "CollisionDetect.h"

#include "Walls.h"
#include "Tanks.h"
#include "AITanks.h"
#include "Bullets.h"
#include "Mines.h"

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			//Cursor->Hide();
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		int WORLD_WIDTH, WORLD_HEIGHT, leftRight = 0, upDown = 0;
		bool upPressed = false, downPressed = false, rightPressed = false, leftPressed = false, mPaused = false;

		int** commands;

		ReadFile *file;

		Graphics ^g, ^gBuff;
		Bitmap ^buffer;

		Bitmap ^floorBitmap = gcnew Bitmap("Images/floor.png");
		Bitmap ^wallBitmap = gcnew Bitmap("Images/wall.png");
		Bitmap ^tankBitmap = gcnew Bitmap("Images/tank.png");
		Bitmap ^horizontalTankBitmap = gcnew Bitmap("Images/tank_horizontal.png");
		Bitmap ^enemyTankBitmap = gcnew Bitmap("Images/enemy_tank.png");
		Bitmap ^horizontalEnemyTankBitmap = gcnew Bitmap("Images/enemy_tank_horizontal.png");
		Bitmap ^tankGunBitmap = gcnew Bitmap("Images/tank_gun.png");
		Bitmap ^mineBitmap = gcnew Bitmap("Images/mine.png");
		Bitmap ^bulletBitmap = gcnew Bitmap("Images/bullet.png");
		Bitmap ^debugBulletBitmap = gcnew Bitmap("Images/debugBullet.png");
		Bitmap ^pointerBitmap = gcnew Bitmap("Images/pointer.png");
		Bitmap ^pausedBitmap = gcnew Bitmap("Images/paused.png");
		Bitmap ^rotatedTankGunBitmap = gcnew Bitmap(1, 1); //placeholder

		CollisionDetect *col;

		array<Walls^, 1> ^array_of_walls;
		array<AITanks^, 1> ^array_of_enemyTanks;

		Tanks ^player_1;

	private: System::Windows::Forms::Panel^  worldPanel;
	private: System::Windows::Forms::Timer^  game_timer;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;

			 /// <summary>
			 /// Required designer variable.
			 /// </summary>

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->worldPanel = (gcnew System::Windows::Forms::Panel());
				 this->game_timer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				 this->SuspendLayout();
				 // 
				 // worldPanel
				 // 
				 this->worldPanel->Location = System::Drawing::Point(12, 12);
				 this->worldPanel->Name = L"worldPanel";
				 this->worldPanel->Size = System::Drawing::Size(520, 520);
				 this->worldPanel->TabIndex = 0;
				 this->worldPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::worldPanel_Paint);
				 this->worldPanel->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseClick);
				 this->worldPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
				 // 
				 // game_timer
				 // 
				 this->game_timer->Interval = 20;
				 this->game_timer->Tick += gcnew System::EventHandler(this, &MyForm::game_timer_Tick);
				 // 
				 // timer1
				 // 
				 this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(542, 540);
				 this->Controls->Add(this->worldPanel);
				 this->Name = L"MyForm";
				 this->Text = L"Tanks @ 50fps";
				 this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
				 this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
				 this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseClick);
				 this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
				 this->ResumeLayout(false);

			 }
#pragma endregion
			
			 //points where playe r_1 gun is facing
			 int gx = 0, gy = 0;

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) 
	{
				 //initializes graphics objects and buffer
				 InitWorldVariables();

				 //loads level data
				 LoadLevelFromFile();
	}

	private: System::Void startTimers(){
				//starts both timers
				game_timer->Start();
				timer1->Start();
	}

	private: System::Void stopTimers(){
				//starts both timers
				game_timer->Stop();
				timer1->Stop();
	}

	private: System::Void togglePause(){
				 if (mPaused = !mPaused){
					 stopTimers();
					 g->DrawImage(pausedBitmap, 40, 170);
				 }
				 else{
					 startTimers();
				 }
	}

	private: System::Void reset(){
				 upPressed = false;
				 downPressed = false;
				 leftPressed = false;
				 rightPressed = false;
				 LoadLevelFromFile();
	}

	private: System::Void InitWorldVariables(){
				 //Sets up the world dimention variables and the panel graphics
				 WORLD_WIDTH = worldPanel->Width;
				 WORLD_HEIGHT = worldPanel->Height;

				 buffer = gcnew Bitmap(WORLD_WIDTH, WORLD_HEIGHT, Imaging::PixelFormat::Format32bppArgb);
				 gBuff = Graphics::FromImage(buffer);
				 g = worldPanel->CreateGraphics();

				 col = new CollisionDetect();
	}

	private: System::Void LoadLevelFromFile(){
				 /*
				 0 - wall
				 1 - player
				 2 - ai
				 */

				 file = new ReadFile();
				 commands = file->parseCommandFile();

				 //gets array size information from file
				 array_of_enemyTanks = gcnew array<AITanks^, 1>(file->getNumAITanks());
				 array_of_walls = gcnew array<Walls^, 1>(file->getNumWalls());

				 int num_commands = file->getNumCommands();
				 int wallx = 0, etankx = 0;

				 for (int a = 0; a < num_commands; a++){
					 if (commands[a][0] == 0){
						 array_of_walls[wallx] = gcnew Walls(commands[a][1], commands[a][2], wallBitmap->Width, wallBitmap->Height);
						 wallx++;
					 }
					 else if (commands[a][0] == 1){
						 player_1 = gcnew Tanks(commands[a][1], commands[a][2]);
					 }
					 else if (commands[a][0] == 2){
						 array_of_enemyTanks[etankx] = gcnew AITanks(commands[a][1], commands[a][2], player_1);
						 etankx++;
					 }
				 }
				 startTimers();
	}

	private: System::Void initCustomCursor(){

	}

	private: System::Void drawFloor(){
				 for (int x = 0; x < WORLD_WIDTH; x += floorBitmap->Width){
					 for (int y = 0; y < WORLD_HEIGHT; y += floorBitmap->Height){
						 gBuff->DrawImage(floorBitmap, x, y);
					 }
				 }
	}

	private: System::Void drawWalls(){
				 for (int l = 0; l < array_of_walls->Length; l++){
					 gBuff->DrawImage(wallBitmap, array_of_walls[l]->get_x(), array_of_walls[l]->get_y());
				 }
	}

			 //if the tanks aren't dead - draw them
	private: System::Void drawTanks(){
				 for (int l = 0; l < array_of_enemyTanks->Length; l++){
					 if (!array_of_enemyTanks[l]->isDead()){
						 if (array_of_enemyTanks[l]->getDirection() % 2 == 0){
							 gBuff->DrawImage(enemyTankBitmap, array_of_enemyTanks[l]->get_x(), array_of_enemyTanks[l]->get_y());
						 }
						 else{
							 gBuff->DrawImage(horizontalEnemyTankBitmap, array_of_enemyTanks[l]->get_x(), array_of_enemyTanks[l]->get_y());
						 }
					 }
				 }

				 if (!player_1->isDead()){
					 if (player_1->get_direction()%2 == 0 )
						gBuff->DrawImage(tankBitmap, player_1->get_x(), player_1->get_y());
					 else{
						 gBuff->DrawImage(horizontalTankBitmap, player_1->get_x(), player_1->get_y());
					 }
				 }
	}

			 //if the bullets aren't dead and are not nullptr - draw them
	private: System::Void drawBullets(){
				 for (int l = 0; l < array_of_enemyTanks->Length; l++){
					 for (int b = 0; b < array_of_enemyTanks[l]->get_num_bullets(); b++){
						 if (array_of_enemyTanks[l]->getBullet(b) != nullptr){
							 if (!array_of_enemyTanks[l]->getBullet(b)->isDead())
								 gBuff->DrawImage(bulletBitmap, array_of_enemyTanks[l]->getBullet(l)->get_x(), array_of_enemyTanks[l]->getBullet(l)->get_y());
						 }
					 }
				 }

				 for (int b = 0; b < player_1->get_num_bullets(); b++){
					 if (player_1->get_bullet(b) != nullptr){
						 if (!player_1->get_bullet(b)->isDead())
							 gBuff->DrawImage(bulletBitmap, player_1->get_bullet(b)->get_x(), player_1->get_bullet(b)->get_y());
					 }
				 }
	}

	private: System::Void drawMines(){
				 for (int l = 0; l < array_of_enemyTanks->Length; l++){
					 for (int b = 0; b < array_of_enemyTanks[l]->pocket(); b++){
						 gBuff->DrawImage(mineBitmap, array_of_enemyTanks[l]->getMine(l)->get_x(), array_of_enemyTanks[l]->getMine(l)->get_y());
					 }
				 }
				 for (int q = 0; q < 3; q++){
					 if (player_1->get_mine(q) != nullptr)
						 gBuff->DrawImage(mineBitmap, player_1->get_mine(q)->get_x(), player_1->get_mine(q)->get_y());
				 }
	}

			 //if the player isn't dead - draw the gun
	private: System::Void drawTankGun(){
				 if (!player_1->isDead())
				 gBuff->DrawImage(rotatedTankGunBitmap, player_1->get_x() - ((rotatedTankGunBitmap->Width - tankBitmap->Width) / 2), player_1->get_y() - ((rotatedTankGunBitmap->Height - tankBitmap->Height) / 2));
	}

	private: System::Void clearBuffer(){
				 gBuff->FillRectangle(gcnew SolidBrush(Color::White), 0, 0, WORLD_WIDTH, WORLD_HEIGHT);
	}

	private: System::Boolean isPlayerCollided(){
				 for (int x = 0; x < array_of_enemyTanks->Length; x++){
					 if (col->detectCollide(player_1, array_of_enemyTanks[x], player_1->get_direction()))
						 return true;
				 }
				 return false;
	}

			 //moves player based on the key pressed
	private: System::Void updatePlayerTankLocation(){
				 if (upPressed && !isPlayerCollided())
				 {
					 player_1->move(1, array_of_walls);
				 }
				 else if (downPressed && !isPlayerCollided()){
					 player_1->move(3, array_of_walls);
				 }

				 if (leftPressed && !isPlayerCollided()){
					 player_1->move(4, array_of_walls);
				 }
				 else if (rightPressed && !isPlayerCollided()){
					 player_1->move(2, array_of_walls);
				 }

	}

			 //calls update on all tanks
	private: System::Void updateTanks(){
				 player_1->update();
				 for (int updaterIndex = 0; updaterIndex < array_of_enemyTanks->Length; updaterIndex++)
					 array_of_enemyTanks[updaterIndex]->update(array_of_walls);
	}

			 //checks if the bullets collided with anything and deletes them accordingly
	private: System::Void updateBullets(){
				 for (int d = 0; d < array_of_enemyTanks->Length; d++){
					 for (int w = 0; w < array_of_enemyTanks[d]->get_num_bullets(); w++){
						 for (int e = 0; e < array_of_walls->Length; e++){
							 if (col->detectCollide(array_of_enemyTanks[d]->getBullet(w), array_of_walls[e])){
								 array_of_enemyTanks[d]->getBullet(w)->die();
								 break;
							 }
							
						 }
					 }
				 }
				 for (int w = 0; w < player_1->get_num_bullets(); w++){
					 for (int e = 0; e < array_of_walls->Length; e++){
						 if (col->detectCollide(player_1->get_bullet(w), array_of_walls[e])){
							 player_1->get_bullet(w)->die();
							 break;
						 }
					 }
				 }

				 for (int a = 0; a < array_of_enemyTanks->Length; a++){
					 for (int v = 0; v < player_1->get_num_bullets(); v++){
						 if (col->detectCollide(player_1->get_bullet(v), array_of_enemyTanks[a])){
							 player_1->get_bullet(v)->die();
							 array_of_enemyTanks[a]->die();
							 
							 stopTimers();

							 MessageBox ^mb;
							 mb->Show(L"You Win!", L"Game Over");
						 }
					 }
				 }

				 for (int y = 0; y < array_of_enemyTanks->Length; y++){
					 for (int r = 0; r < array_of_enemyTanks[y]->get_num_bullets(); r++){
						 if (col->detectCollide(array_of_enemyTanks[y]->getBullet(r), player_1)){
							 array_of_enemyTanks[y]->getBullet(r)->die();
							 player_1->die();
							 
							 stopTimers();
							 
							 MessageBox ^mb; 
							 mb->Show(L"You Lose!", L"Game Over");
						 }
					 }
				 }

	}

	private: System::Void updateMines(){
				 for (int y = 0; y < array_of_enemyTanks->Length; y++){
					 for (int x = 0; x < array_of_enemyTanks[y]->get_num_mines(); x++){
						 if (col->detectCollide(player_1, array_of_enemyTanks[y]->getMine(x))){
							 player_1->die();
							 stopTimers();
							 MessageBox ^mb;
							 mb->Show(L"You Lose!", L"Game Over");
						 }
					 }
				 }
				 for (int y = 0; y < array_of_enemyTanks->Length; y++){
					 for (int p = 0; p < player_1->pocket(); p++)
						 if (col->detectCollide(array_of_enemyTanks[y], player_1->get_mine(p))){
							 array_of_enemyTanks[y]->die();
							 stopTimers();
							 MessageBox ^mb;
							 mb->Show(L"You Win!", L"Game Over");
						 }
					 
				 }
				 
	}

	private: System::Void drawWorld(){

				 drawFloor();
				 drawWalls();
				 drawMines();
				 drawBullets();
				 drawTanks();
				 drawTankGun();

				 g->DrawImage(buffer, Point(0, 0));
				 clearBuffer();

	}

			 //sets the gun point location
	private: System::Void MyForm_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

				 gx = e->X;
				 gy = e->Y;

	}

	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::W){
					 upDown = 1;
					 upPressed = true;
				 }
				 if (e->KeyCode == Keys::A){
					 leftRight = -1;
					 leftPressed = true;
				 }
				 if (e->KeyCode == Keys::S){
					 upDown = -1;
					 downPressed = true;
				 }
				 if (e->KeyCode == Keys::D){
					 leftRight = 1;
					 rightPressed = true;
				 }
				 if (e->KeyCode == Keys::R){
					 reset();
				 }
				 if (e->KeyCode == Keys::P){
					 togglePause();
				 }
				 if (e->KeyCode == Keys::Space){
					 player_1->dropMine();
				 }
	}

	private: System::Void MyForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::W){
					 upDown = 0;
					 upPressed = false;
				 }
				 if (e->KeyCode == Keys::A){
					 leftRight = 0;
					 leftPressed = false;
				 }
				 if (e->KeyCode == Keys::S){
					 upDown = 0;
					 downPressed = false;
				 }
				 if (e->KeyCode == Keys::D){
					 leftRight = 0;
					 rightPressed = false;
				 }
	}

	private: System::Void MyForm_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //shoot bullet
				 player_1->launch(e->X, e->Y);

	}

	private: System::Void game_timer_Tick(System::Object^  sender, System::EventArgs^  e) {
				 updatePlayerTankLocation();
				 updateTanks();
				 updateBullets();
				 updateMines();
				 drawWorld();
	}

	private: System::Void worldPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 drawWorld();
	}
	
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 float angle = Math::Atan2(gy - (player_1->get_y() + (tankBitmap->Height / 2)), gx - (player_1->get_x() + (tankBitmap->Width / 2)));
				 //Convert degrees to radians 
				 float radians = angle + (Math::PI / 2); // *(Math::PI / 180);

				 float cosine = (float)cos(radians);
				 float sine = (float)sin(radians);

				 float Point1x = (-tankGunBitmap->Height*sine);
				 float Point1y = (tankGunBitmap->Height*cosine);
				 float Point2x = (tankGunBitmap->Width*cosine - tankGunBitmap->Height*sine);
				 float Point2y = (tankGunBitmap->Height*cosine + tankGunBitmap->Width*sine);
				 float Point3x = (tankGunBitmap->Width*cosine);
				 float Point3y = (tankGunBitmap->Width*sine);

				 float minx = Math::Min(0, (int)Math::Min((int)Point1x, (int)Math::Min(Point2x, Point3x)));
				 float miny = Math::Min(0, (int)Math::Min((int)Point1y, (int)Math::Min(Point2y, Point3y)));
				 float maxx = Math::Max((int)Point1x, (int)Math::Max(Point2x, Point3x));
				 float maxy = Math::Max((int)Point1y, (int)Math::Max(Point2y, Point3y));

				 int dw = (int)ceil(fabs(maxx) - minx);
				 int dh = (int)ceil(fabs(maxy) - miny);

				 Bitmap ^DestBitmap = gcnew Bitmap(dw, dh, Imaging::PixelFormat::Format32bppArgb);

				 for (int x = 0; x < dw; x++)
				 {
					 for (int y = 0; y < dh; y++)
					 {
						 int SrcBitmapx = (int)((x + minx)*cosine + (y + miny)*sine);
						 int SrcBitmapy = (int)((y + miny)*cosine - (x + minx)*sine);
						 if (SrcBitmapx >= 0 && SrcBitmapx < tankGunBitmap->Width && SrcBitmapy >= 0 &&
							 SrcBitmapy < tankGunBitmap->Height)
						 {
							 DestBitmap->SetPixel(x, y, tankGunBitmap->GetPixel(SrcBitmapx, SrcBitmapy));
						 }
					 }
				 }
				 rotatedTankGunBitmap = DestBitmap;
	}
};
};