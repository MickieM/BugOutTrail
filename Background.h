//FILE : Background.h

//PROG : Mickie Maxey

//PURP : Background header file

#pragma once

#include "Sprite.h"

class Background : public Sprite
{
private:

public:
	Background(ALLEGRO_BITMAP *image, float velX);
	void destroy();

	void update();
	void render();

	void setImage(ALLEGRO_BITMAP *image);

};