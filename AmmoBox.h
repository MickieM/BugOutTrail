//FILE : AmmoBox.h

//PROG : Mickie Maxey

//PURP : AmmoBox Sprite header file

#pragma once

#include "Sprite.h"

class AmmoBox: public Sprite
{
private:
	
	void (*addAmmo)(void);

public:
	AmmoBox(ALLEGRO_BITMAP *image, void (*addAmmo)(void));
	
	void destroy();
	void update();
	void render();

	void collided(int objectID);
};