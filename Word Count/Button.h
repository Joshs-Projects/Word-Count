#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

class Button {
protected:
	int posX = 0;
	int posY = 0;

	int sizeX = 0;
	int sizeY = 0;

	int scaledSizeX = 0;
	int scaledSizeY = 0;

	const char* buttonPictureName;
	const char* clickedButtonPictureName;

	int SetPos(int ButtonLocationX, int ButtonLocationY) {
		posX = ButtonLocationX;
		posY = ButtonLocationY;

		return -1;
	}

	int SetSize(int ButtonSizeX, int ButtonSizeY, int ScaledSizeX, int ScaledSizeY) {
		sizeX = ButtonSizeX;
		sizeY = ButtonSizeY;

		scaledSizeX = ScaledSizeX;
		scaledSizeY = ScaledSizeY;
		
		return -1;
	}

	int SetButtonPicture(const char* NameOfButton, const char* ClickedButtonName) {
		buttonPictureName = NameOfButton;
		clickedButtonPictureName = ClickedButtonName;

		return -1;
	};

public:
	ALLEGRO_BITMAP* buttonPicture = NULL;
	ALLEGRO_BITMAP* clickedButtonPicture = NULL;

	Button() {	}

	Button(int ButtonLocationX, int ButtonLocationY, int ButtonSizeX, int ButtonSizeY, const char* NameOfButton, const char* ClickedButtonName, int ScaledSizeX, int ScaledSizeY) {
		SetPos(ButtonLocationX, ButtonLocationY);
		SetSize(ButtonSizeX, ButtonSizeY, ScaledSizeX, ScaledSizeY);
		SetButtonPicture(NameOfButton, ClickedButtonName);

		buttonPicture = al_load_bitmap(NameOfButton);
		clickedButtonPicture = al_load_bitmap(ClickedButtonName);

		
	}

	//Override this function with subclasses
	int WhenHit() {

		return 0;
	}

	int GiveYPos() {
		return posY;
	}

	int GiveXPos() {
		return posX;
	}

	int GiveYSize() {
		return sizeY;
	}

	int GiveXSize() {
		return sizeX;
	}

	int GiveScaledYSize() {
		return scaledSizeY;
	}

	int GiveScaledXSize() {
		return scaledSizeX;
	}

	bool IfHit(int MouseX, int MouseY) {
		if ((MouseX > posX) && (MouseX < (posX + scaledSizeX)) && (MouseY > posY) && (MouseY < posY + scaledSizeY)) {
			WhenHit();
		}
	}
};