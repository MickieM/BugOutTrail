//FILE : Sprite.cpp

//PROG : Mickie Maxey

//PURP : Sprite class

#include "Sprite.h"

Sprite::Sprite()
{
	x = 0;
	y = 0;
	velX = 0;
	dirX = 0;
	speed = 0;
	boundX = 0;
	

	maxFrame = 0;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;
	animationDirection = 0;

	image = NULL;

	alive = true;
	collidable = true;
}

void Sprite::destroy()
{
	
}

void Sprite::init(float x, float y, float velX, int dirX, int boundX)
{
	Sprite::x = x;
	Sprite::y = y;
	Sprite::velX = velX;
	Sprite::dirX = dirX;
	Sprite::boundX = boundX;
}

void Sprite::update()
{
	x += velX * dirX;
}

void Sprite::render()
{}

bool Sprite::checkCollisions(Sprite *otherObject)
{
	float oX = otherObject->getX();
	float oY = otherObject->getY();

	int obX = otherObject->getBoundX();

	if( x + boundX > oX - obX && x - boundX < oX + obX)
		return true;
	else
		return false;
}

void Sprite::collided(int objectID)
{}

bool Sprite::Collidable()
{
	return alive && collidable;
}

