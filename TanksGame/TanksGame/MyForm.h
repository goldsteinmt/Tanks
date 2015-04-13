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
			Cursor->Hide();
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

		int** commands;

		Graphics ^g, ^gBuff;
		Bitmap ^buffer;

		Bitmap ^floorBitmap = gcnew Bitmap("Images/floor.png");
		Bitmap ^wallBitmap = gcnew Bitmap("Images/wall.png");
		Bitmap ^tankBitmap = gcnew Bitmap("Images/tank.png");
		Bitmap ^tankGunBitmap = gcnew Bitmap("Images/tank_gun.png");
		Bitmap ^mineBitmap = gcnew Bitmap("Images/mine.png");
		Bitmap ^bulletBitmap = gcnew Bitmap("Images/bullet.png");
		Bitmap ^pointerBitmap = gcnew Bitmap("Images/pointer.png");

		array<Walls^, 1> ^array_of_walls;
		array<AITanks^, 1> ^array_of_enemyTanks;

		Tanks ^player_1;

	private: System::Windows::Forms::Panel^  worldPanel;
	private: System::Windows::Forms::Timer^  game_timer;
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
				 this->SuspendLayout();
				 // 
				 // worldPanel
				 // 
				 this->worldPanel->Location = System::Drawing::Point(12, 12);
				 this->worldPanel->Name = L"worldPanel";
				 this->worldPanel->Size = System::Drawing::Size(520, 520);
				 this->worldPanel->TabIndex = 0;
				 this->worldPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::worldPanel_Paint);
				 this->worldPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
				 // 
				 // game_timer
				 // 
				 this->game_timer->Tick += gcnew System::EventHandler(this, &MyForm::game_timer_Tick);
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(542, 540);
				 this->Controls->Add(this->worldPanel);
				 this->Name = L"MyForm";
				 this->Text = L"MyForm";
				 this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
				 this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
				 this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseClick);
				 this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
				 this->ResumeLayout(false);

			 }
#pragma endregion

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 //initCustomCursor();
				 WORLD_WIDTH = worldPanel->Width;
				 WORLD_HEIGHT = worldPanel->Height;
				 
				 buffer = gcnew Bitmap(WORLD_WIDTH, WORLD_HEIGHT, Imaging::PixelFormat::Format32bppArgb);
				 gBuff = Graphics::FromImage(buffer);
				 g = worldPanel->CreateGraphics();

				 /*
				 0 - wall
				 1 - player
				 2 - ai
				 */
				 ReadFile *file = new ReadFile();
				 commands = file->parseCommandFile();
				 
				 array_of_enemyTanks = gcnew array<AITanks^, 1>(file->getNumAITanks);
				 array_of_walls = gcnew array<Walls^, 1>(file->getNumWalls);

				 int num_commands = file->getNumCommands();
				 const int num_args = 3;

				 for (int a = 0; a < num_commands; a++){
						 if (commands[a][0] == 0){
							 array_of_walls[a] = gcnew Walls(commands[a][1], commands[a][2]);
						 }
						 else if (commands[a][0] == 1){
							 player_1 = gcnew Tanks(commands[a][1], commands[a][2]);
						 }
						 else if (commands[a][0] == 2){
							 array_of_enemyTanks[a] = gcnew AITanks();
						 }
				 }
	}
			 
	private: System::Void initCustomCursor(){
				 //TODO
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
					 gBuff->DrawImage(wallBitmap, array_of_walls[l]->get_x(), array_of_walls[l]->get_x());
				 }
	}

	private: System::Void drawTanks(){
				 for (int l = 0; l < array_of_enemyTanks->Length; l++){
					 gBuff->DrawImage(tankBitmap, array_of_enemyTanks[l]->get_x(), array_of_enemyTanks[l]->get_x());
				 }
	}
			 
	private: System::Void drawBullets(){
					for (int l = 0; l < array_of_enemyTanks->Length; l++){
						for (int b = 0; b < array_of_enemyTanks[l]->get_num_bullets(); b++){
							gBuff->DrawImage(bulletBitmap, array_of_enemyTanks[l]->get_bullets()[l]->get_x(), array_of_enemyTanks[l]->get_bullets()[l]->get_y());
						}
					}
	}

	private: System::Void drawMines(){
					for (int l = 0; l < array_of_enemyTanks->Length; l++){
						for (int b = 0; b < array_of_enemyTanks[l]->pocket(); b++){
							gBuff->DrawImage(bulletBitmap, array_of_enemyTanks[l]->get_mines()[l]->get_x(), array_of_enemyTanks[l]->get_mines()[l]->get_y());
						}
					}
	}
			 
	private: System::Void drawTankGun(){
				 //not sure exactly how to rotate this yet
				 //probably should get a bunch of images
				 gBuff->DrawImage(tankGunBitmap, player_1->get_x(), player_1->get_y());
	}

	private: System::Void clearBuffer(){
				 gBuff->FillRectangle(gcnew SolidBrush(Color::White), 0, 0, WORLD_WIDTH, WORLD_HEIGHT);
	}

	private: System::Void updatePlayerTankLocation(){
				 //TODO
	}

	private: System::Void MyForm_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				// aim gun
	}
	
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::W){
					 upDown = 1;
				 }
				 if (e->KeyCode == Keys::A){
					 leftRight = -1;
				 }
				 if (e->KeyCode == Keys::S){
					 upDown = -1;
				 }
				 if (e->KeyCode == Keys::D){
					 leftRight = 1;
				 }
	}

	private: System::Void MyForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 //temporary code
				 if (e->KeyCode == Keys::W){
					 upDown = 0;
				 }
				 if (e->KeyCode == Keys::A){
					 leftRight = 0;
				 }
				 if (e->KeyCode == Keys::S){
					 upDown = 0;
				 }
				 if (e->KeyCode == Keys::D){
					 leftRight = 0;
				 }
	}

	private: System::Void MyForm_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //shoot bullet
				 if (player_1->can_shoot()){
					 player_1->shoot(e->X, e->Y);
				 }
	}

	private: System::Void game_timer_Tick(System::Object^  sender, System::EventArgs^  e) {
				 
	}

	private: System::Void worldPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 drawFloor();
				 drawWalls();
				 drawMines();
				 drawBullets();
				 drawTanks();

				 g->DrawImage(buffer, 0, 0);
	}
};
};
