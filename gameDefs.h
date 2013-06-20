//FILE : GameDefs.h

//PROG : Mickie Maxey

//PURP : Globals

#pragma once

const int WIDTH = 800;
const int HEIGHT = 600;
const int FPS = 60;
#define BLACK al_map_rgb(0, 0, 0)
#define WHITE al_map_rgb(255, 255, 255)
enum ID{PLAYER, ENEMY, BULLET, BORDER, MISC, AMMOBOX, FOODBOX, KID};
enum STATE{TITLE, INSTRUCT, PLAYING, LOST, WON};

