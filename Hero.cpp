//FILE : Hero.cpp

//PROG : Mickie Maxey

//PURP : Hero class

#include "Hero.h"

Hero::Hero()
{}

void Hero::destroy()
{
	Sprite::destroy();
}

void Hero::init(ALLEGRO_BITMAP *image)
{

	Sprite::init(300, 550, 4, 0, 25);

	setID(PLAYER);
	setAlive(true);

	health = 10;
	ammo = 25;
	hunger = 25;
	kills = 0;
	facingRight = true;
	speed = 3; 
	dirX = 0;


	maxFrame = 5;
	curFrame = 0;
	frameWidth = 75;
	frameHeight = 70;
	frameDelay = 10;
	animationColumns = 6;
	animationDirection = 1;


	if(image != NULL)
		Hero::image = image;
}

void Hero::update()
{
	
	if(x < 0)
		x = 0;
	else if(x > WIDTH)
		x = WIDTH;

	if(y < 0)
		y = 0;
	else if(y > HEIGHT)
		y = HEIGHT;
}

void Hero::render()
{

	Sprite::render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = frameHeight;

	if(facingRight)
		al_draw_bitmap_region(image, fx, 0, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
	else
		al_draw_bitmap_region(image, fx, 0, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, ALLEGRO_FLIP_HORIZONTAL);
	
}

void Hero::moveRight()
{
	facingRight = true;
	if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame == maxFrame)
				curFrame = 0;
			else
				curFrame++;
		}
	
	x+= speed;
	
}

void Hero::moveLeft()
{
	facingRight = false;
	if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame == maxFrame)
				curFrame = 0;
			else
				curFrame++;
		}
	
	x-= speed;
}


void Hero::collided(int objectID)
{
	if(objectID == ENEMY)
		health-=1;
}