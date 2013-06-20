//FILE : FoodBox.h

//PROG : Mickie Maxey

//PURP : FoodBox Sprite header file

#pragma once

#include "Sprite.h"

class FoodBox: public Sprite
{
private:
	
	void (*addFood)(void);

public:
	FoodBox(ALLEGRO_BITMAP *image, void (*addFood)(void));

	void destroy();
	void update();
	void render();
	void collided(int objectID);
};