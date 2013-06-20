//FILE : Kid.cpp

//PROG : Mickie Maxey

//PURP : Kid Sprite class

#include "Kid.h"

Kid::Kid()
{}

void Kid::init (ALLEGRO_BITMAP *image)
{
	Sprite::init(WIDTH/2, 555, 0, 0, 20);

	setID(KID);
	setAlive(true);
	maxFrame = 6;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 12;
	frameWidth = 40;
	frameHeight = 60;
	animationColumns = 6;

	if(image != NULL)
		Kid::image = image;
	
}

void Kid::destroy()
{
	Sprite::destroy();
}

void Kid::update()
{
	Sprite::update();

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

void Kid::render()
{
	Sprite::render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = frameHeight;

		al_draw_bitmap_region(image, fx, 0, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
	
}

void Kid::collided(int objectID)
{

	if(objectID == ENEMY)
	{
		setAlive(false);
		dead = true;
	}
	
}