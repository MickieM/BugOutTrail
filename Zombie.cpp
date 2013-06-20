//FILE : Zombie.cpp

//PROG : Mickie Maxey

//PURP : Zombie Sprite class

#include "Zombie.h"

Zombie::Zombie(float x, float y, int dirX, ALLEGRO_BITMAP *image, void (*addKill)(void))
{
	Sprite::init(x, 550, 1, dirX, 30);

	setID(ENEMY);

	maxFrame = 5;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 12;
	frameWidth = 68;
	frameHeight = 80;
	animationColumns = 5;
	health = 2;
	speed = 2;
	Zombie::image = image;
	Zombie::addKill = addKill;
	
}

void Zombie::destroy()
{
	Sprite::destroy();
}

void Zombie::update()
{
	Sprite::update();

	if(dirX == -1)
		x-=speed;
	else x+=speed;

	if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame == maxFrame)
				curFrame = 0;
			else
				curFrame++;
		}

	if(x + frameWidth < 0)
		collided(BORDER);
}

void Zombie::render()
{
	Sprite::render();

	int fx = (curFrame % animationColumns) * frameWidth;

	if(dirX == -1)
		
		al_draw_bitmap_region(image, fx, 0, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
	else
	
		al_draw_bitmap_region(image, fx, 0, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2,ALLEGRO_FLIP_HORIZONTAL);
	
}

void Zombie::collided(int objectID)
{
	
	if(objectID == BORDER)
	{
		setAlive(false);
	}

	if(objectID == BULLET)
	{
		if(health == 1)
		{
			setAlive(false);
			addKill();
		}
		else
			health--;
	}

	if(objectID == PLAYER)
		setAlive(false);
	
}