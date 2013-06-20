//FILE : Background.cpp

//PROG : Mickie Maxey

//PURP : Background class

#include "Background.h"

Background::Background(ALLEGRO_BITMAP *image, float velX)
{
	Sprite::init(0, 0, velX, -1, 0);

	setID(MISC);
	setCollidable(false);

	Background::image = image;
	frameWidth = al_get_bitmap_width(image);

}

void Background::destroy()
{
	Sprite::destroy();
}

void Background::update()
{
	Sprite::update();
	if(x + frameWidth <= 0)
		x = 0;
}

void Background::render()
{
	Sprite::render();

	al_draw_bitmap(image, x, y, 0);

	if(x + frameWidth < WIDTH)
		al_draw_bitmap(image, x + frameWidth, y, 0);
}

void Background::setImage(ALLEGRO_BITMAP *image)
{
	Background::image = image;
	frameWidth = al_get_bitmap_width(image);
}