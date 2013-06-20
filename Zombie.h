//FILE : Zombie.h

//PROG : Mickie Maxey

//PURP : Zombie Sprite header file


#pragma once

#include "Sprite.h"

class Zombie: public Sprite
{
private:

	void (*takeHealth)(void);
	int face;
	int health;
	void (*addKill)(void);
	

public:

	Zombie(float x, float y, int dirX, ALLEGRO_BITMAP *image, void (*addKill)(void));
	void destroy();
	void update();
	void render();
	void setHealth() {health--;}
	int getHealth() {return health;}
	void collided(int objectID);
};