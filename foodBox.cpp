//FILE :FoodBox.cpp

//PROG : Mickie Maxey

//PURP : FoodBox class

#include "FoodBox.h"

FoodBox::FoodBox(ALLEGRO_BITMAP *image, void (*addFood)(void))
{
	Sprite::init(600, 550, 0, 0, 15);

	setID(FOODBOX);

	FoodBox::image = image;
	
	FoodBox::addFood = addFood;
}

void FoodBox::destroy()
{
	Sprite::destroy();
}

void FoodBox::render()
{
	al_draw_bitmap(image, 600, 550, 0);
}

void FoodBox::update()
{
	Sprite::update();
}


void FoodBox::collided(int objectID)
{
	if(objectID == PLAYER)
	{
		addFood();
		setAlive(false);
	}
}
