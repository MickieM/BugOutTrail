//FILE :AmmoBox.cpp

//PROG : Mickie Maxey

//PURP : AmmoBox class

#include "AmmoBox.h"

AmmoBox::AmmoBox(ALLEGRO_BITMAP *image, void (*addAmmo)(void))
{
	Sprite::init(120, 550, 0, 0, 15);

	setID(AMMOBOX);

	AmmoBox::image = image;
	
	AmmoBox::addAmmo = addAmmo;
}

void AmmoBox::destroy()
{
	Sprite::destroy();
}

void AmmoBox::render()
{
	al_draw_bitmap(image, 120, 550, 0);
}

void AmmoBox::update()
{
	Sprite::update();
}

void AmmoBox::collided(int objectID)
{
	if(objectID == PLAYER)
	{
		addAmmo();
		setAlive(false);
	}
	
}
