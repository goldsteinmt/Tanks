#pragma once

#include <vector>
#include <windows.h>
#include <tchar.h>

#include "ReadFile.h"
//#include "CollisionDetect.h"

#include "Walls.h"
#include "Tanks.h"
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
		int WORLD_WIDTH, WORLD_HEIGHT;

		Graphics ^g, ^gBuff;
		Bitmap ^buffer;

		Bitmap ^floorBitmap = gcnew Bitmap("Images/floor.png");
		Bitmap ^wallBitmap = gcnew Bitmap("Images/wall.png");
		Bitmap ^tankBitmap = gcnew Bitmap("Images/tank.png");
		Bitmap ^tankGunBitmap = gcnew Bitmap("Images/tank_gun.png");
		Bitmap ^mineBitmap = gcnew Bitmap("Images/mine.png");
		Bitmap ^bulletBitmap = gcnew Bitmap("Images/bullet.png");
		Bitmap ^pointerBitmap = gcnew Bitmap("Images/pointer.png");

		

		array<Walls^, 1>^ walls;
		array<Tanks^, 1>^ enemyTanks;

		Tanks ^player_1;

	private: System::Windows::Forms::Panel^  worldPanel;



			 /// <summary>
			 /// Required designer variable.
			 /// </summary>
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->worldPanel = (gcnew System::Windows::Forms::Panel());
				 this->SuspendLayout();
				 // 
				 // worldPanel
				 // 
				 this->worldPanel->Location = System::Drawing::Point(12, 12);
				 this->worldPanel->Name = L"worldPanel";
				 this->worldPanel->Size = System::Drawing::Size(520, 520);
				 this->worldPanel->TabIndex = 0;
				 this->worldPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
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
				 this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
				 this->ResumeLayout(false);

			 }
#pragma endregion

			 std::vector<Bullets^>^ bullets;
			 std::vector<Mines^>^ mines;

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 //initCustomCursor();
				 WORLD_WIDTH = worldPanel->Width;
				 WORLD_HEIGHT = worldPanel->Height;

				 bullets = gcnew std::vector<Bullets^>();
				 mines = gcnew std::vector<Mines^>();

				 bullets->reserve(1);
				 mines->reserve(1);
				 
				 buffer = gcnew Bitmap(WORLD_WIDTH, WORLD_HEIGHT, Imaging::PixelFormat::Format32bppArgb);
				 gBuff = Graphics::FromImage(buffer);
				 g = worldPanel->CreateGraphics();
	}
			 
	private: System::Void initCustomCursor(){
				 //TODO
	}

	private: System::Void drawWorld(){
				 drawFloor();
				 drawWalls();
				 //drawMines();
				 //drawBullets();
				 drawTanks();

				 g->DrawImage(buffer, 0, 0);

				 //Bitmap.RotateFlip needs RotateFlip Object -- Rotating Tank Cannon

	}

	private: System::Void drawFloor(){
				 for (int x = 0; x < WORLD_WIDTH; x += floorBitmap->Width){
					 for (int y = 0; y < WORLD_HEIGHT; y += floorBitmap->Height){
						 gBuff->DrawImage(floorBitmap, x, y);
					 }
				 }
	}

	private: System::Void drawWalls(){
				 for (int l = 0; l < walls->Length; l++){
					 gBuff->DrawImage(wallBitmap, walls[l]->get_x(), walls[l]->get_x());
				 }
	}

	private: System::Void drawTanks(){
				 for (int l = 0; l < enemyTanks->Length; l++){
					 gBuff->DrawImage(tankBitmap, enemyTanks[l]->get_x(), enemyTanks[l]->get_x());
				 }
	}
			 /*
	private: System::Void drawBullets(){
	for (int l = 0; l < bullets->size; l++){
	gBuff->DrawImage(bulletBitmap, bullets->at(l)->get_x(), bullets->at(l)->get_y());
	}
	}

	private: System::Void drawMines(){
	for (int l = 0; l < mines->size; l++){
	gBuff->DrawImage(mineBitmap, mines->at(l)->get_x(), mines->at(l)->get_y());
	}
	}*/

	private: System::Void drawTankGun(){
				 //not sure exactly how to rotate this yet

				 gBuff->DrawImage(tankGunBitmap, player_1->get_x(), player_1->get_y());
	}

	private: System::Void drawCursor(int x, int y){
				 gBuff->DrawImage(pointerBitmap, x, y);
	}

	private: System::Void clearBuffer(){
				 gBuff->FillRectangle(gcnew SolidBrush(Color::White), 0, 0, WORLD_WIDTH, WORLD_HEIGHT);
	}

			 /*
				Mouse move event handler for cursor and tankGun updates
				*/
	private: System::Void MyForm_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				// clearBuffer();
				// drawCursor(e->X, e->Y);
				// g->DrawImage(buffer, 0, 0);
	}
	};
};
