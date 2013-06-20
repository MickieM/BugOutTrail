//FILE : Bullet.cpp

//PROG : Mickie Maxey

//PURP : Bullet class

#include "Bullet.h"

Bullet::Bullet(float x, float y, int dirX)
{
	Sprite::init(x, y, 10, dirX, 0);

	setID(BULLET);
}

void Bullet::destroy()
{
	Sprite::destroy();
}

void Bullet::update()
{
	Sprite::update();

	if(x > WIDTH)
		collided(BORDER);
}

void Bullet::render()
{
	al_draw_filled_circle(x, y, 2, WHITE);
}

void Bullet::collided(int objectID)
{
	if(objectID == ENEMY || objectID == BORDER)
		setAlive(false);

}