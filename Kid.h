//FILE : Kid.h

//PROG : Mickie Maxey

//PURP : Kid Sprite header file


#pragma once

#include "Sprite.h"

class Kid: public Sprite
{
private:
	bool dead;
public:
	Kid();
	void destroy();
	void init(ALLEGRO_BITMAP *image = NULL);
	void update();
	void render();
	void collided(int objectID);
	bool getDead(){return dead;}
};