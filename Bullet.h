//FILE : Bullet.h

//PROG : Mickie Maxey

//PURP : Bullet Sprite header file

#pragma once

#include "Sprite.h"

class Bullet : public Sprite
{
private:
	
public:
	Bullet(float x, float y, int dirX);

	void destroy();

	void update();
	void render();

	void collided(int objectID);

	
};