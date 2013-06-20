//FILE : Sprite.h

//PROG : Mickie Maxey

//PURP : Sprite header file

#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "gameDefs.h"

class Sprite
{
private:
	int ID;
	bool alive;
	bool collidable;

protected:
	float x;
	float y;
	float velX;
	int dirX;
	int speed;
	int boundX;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP *image;

public:
	Sprite();
	void virtual destroy();
	void init(float x, float y, float velX, int dirX, int boundX);
	void virtual update();
	void virtual render();

	float getX() {return x;}
	void setX(float x) {Sprite::x = x;}

	float getY() {return y;}
	void setY(float y) {Sprite::y = y;}

	int getBoundX() {return boundX;}
	
	int getID() {return ID;}
	void setID(int ID) {Sprite::ID = ID;}

	bool getAlive() {return alive;}
	void setAlive(bool alive) {Sprite::alive = alive;}

	bool getCollidable() {return collidable;}
	void setCollidable(bool collidable) {Sprite::collidable = collidable;}

	bool checkCollisions(Sprite *otherObject);
	void virtual collided(int objectID);
	
	bool Collidable();
};