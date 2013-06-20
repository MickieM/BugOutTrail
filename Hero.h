//FILE : Hero.h

//PROG : Mickie Maxey

//PURP : Hero Sprite header file

#pragma once

#include "Sprite.h"

class Hero:public Sprite
{
	private:
		int health;
		int ammo;
		int hunger;
		int animationRow;
		bool facingRight;
		int dirX;
		int kills;
		
	public:
		Hero();
		void destroy();

		void init(ALLEGRO_BITMAP *image = NULL);
		void update();
		void render();

		void moveLeft();
		void moveRight();

		int getHealth() {return health;}
		int getAmmo() {return ammo;}
		int getHunger() {return hunger;}
		int getBX() {return Sprite::boundX;}
		int getKills() {return kills;}
		bool getFacingRight() {return facingRight;}

		void addAmmo() {ammo=20;}
		void setAmmo() {ammo--;}
		void addKill() {kills++;}
		void setHunger() {hunger--;};
		void addFood() {hunger=25;}
		void collided(int objectID);
};