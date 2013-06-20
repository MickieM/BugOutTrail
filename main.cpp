//FILE : main.cpp

//PROG : Mickie Maxey

//PURP : Main game control

#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Sprite.h"
#include "gameDefs.h"
#include "Hero.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Background.h"
#include "AmmoBox.h"
#include "FoodBox.h"
#include "Kid.h"

bool keys[] = {false, false, false};
enum KEYS{LEFT, RIGHT, SPACE};

//globals
Hero *player1;
Kid *kid1;

std::list<Sprite *> objects;
std::list<Sprite *>::iterator iter;
std::list<Sprite *>::iterator iter2;

Background *titleScreen;
Background *lostScreen;
Background *wonScreen;
Background *instructScreen;
ALLEGRO_SAMPLE_INSTANCE *songInstance;

//PROTOTYPES

void changeState(int &state, int newState);
void __cdecl addAmmo();
void __cdecl addKill();
void __cdecl addFood();

int main(int argc, char **argv)
{
	//MAIN VARIABLES
	bool done = false;
	bool render = false;
	int hungerDec = 0;

	//PROJECT VARIABLES
	player1 = new Hero();
	kid1 = new Kid();

	int state = -1;

	ALLEGRO_BITMAP *heroImage = NULL;
	ALLEGRO_BITMAP *zombieImage = NULL;
	ALLEGRO_BITMAP *kidImage = NULL;
	ALLEGRO_BITMAP *bgImage1 = NULL;
	ALLEGRO_BITMAP *bgImage2 = NULL;
	ALLEGRO_BITMAP *bgImage3 = NULL;
	ALLEGRO_BITMAP *titleImage = NULL;
	ALLEGRO_BITMAP *instructImage = NULL;
	ALLEGRO_BITMAP *lostImage = NULL;
	ALLEGRO_BITMAP *wonImage = NULL;
	ALLEGRO_BITMAP *ammoImage = NULL;
	ALLEGRO_BITMAP *foodImage = NULL;
    ALLEGRO_SAMPLE *shot = NULL;
	ALLEGRO_SAMPLE *song = NULL;
	ALLEGRO_SAMPLE *fanfare = NULL;


	//ALLEGRO VARIABLES
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18, *font24;
		
	//ALLEGRO INIT FUNCTIONS

	if(!al_init())									
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			

	if(!display)										
		return -1;


	//ADDON INSTALL
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	
	//PROJECT INIT
	font18 = al_load_font("abtechia.ttf", 18, 0);
	font24 = al_load_font("abtechia.ttf", 24, 0);
	al_reserve_samples(15);

	//SPRITES
	bgImage1 = al_load_bitmap("City background.jpg");
	bgImage2 = al_load_bitmap("suburbiaBG.png");
	bgImage3 = al_load_bitmap("c_h__menus__forest_scrolling_by_cinth_degree-d46clap.png");

	Background *bg = new Background(bgImage1, 1);
	objects.push_back(bg);

	heroImage = al_load_bitmap("runningHero.bmp");
	al_convert_mask_to_alpha(heroImage, al_map_rgb(255, 0, 255));
	player1->init(heroImage);
	objects.push_back(player1);

	zombieImage = al_load_bitmap("zombieSheet1.bmp");
	al_convert_mask_to_alpha(zombieImage, WHITE);

	kidImage = al_load_bitmap("kidImage.bmp");
	al_convert_mask_to_alpha(kidImage, WHITE);
	kid1->init(kidImage);
	objects.push_back(kid1);

	ammoImage = al_load_bitmap("ammoBox.bmp");
	al_convert_mask_to_alpha(ammoImage, al_map_rgb(255, 255, 255));

	foodImage = al_load_bitmap("foodBox.bmp");
	al_convert_mask_to_alpha(ammoImage, al_map_rgb(255, 255, 255));

	//SCREENS
	titleImage = al_load_bitmap("loadScreen.bmp");
	lostImage = al_load_bitmap("gameOver.png");
	wonImage = al_load_bitmap("winScreen.png");
	instructImage = al_load_bitmap("instructScreen.png");

	titleScreen = new Background(titleImage, 0);
	instructScreen = new Background(instructImage, 0);
	lostScreen = new Background(lostImage, 0);
	wonScreen = new Background(wonImage, 0);


	//SOUNDS
	shot = al_load_sample("fiveseven1_copy2.wav");
	song = al_load_sample("QuickSilver.wav");
	fanfare = al_load_sample("88066^FANFARE.wav");
	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	changeState(state, TITLE);

	srand(time(NULL));

	//TIMER INIT AND STARTUP
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	
	//MAIN GAME LOOP
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		hungerDec++;

		if(hungerDec%50 == 0)
			player1->setHunger();

		//INPUT
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				if(state == LOST)
				{
					changeState(state, INSTRUCT);
					
				}
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;

				if(state == TITLE)
					changeState(state, INSTRUCT);

				else if(state == INSTRUCT)
				{
					changeState(state, PLAYING);
				}

				//spawn bullets
				else if(state == PLAYING && player1->getAmmo() > 0)
				{
					if(player1->getFacingRight() == true)
					{
						Bullet *bullet = new Bullet(player1->getX() + 20, player1->getY(), 1);
						objects.push_back(bullet);
						al_play_sample(shot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						player1->setAmmo();
					}
					else 
					{
						Bullet *bullet = new Bullet(player1->getX() + 20, player1->getY(), -1);
						objects.push_back(bullet);
						al_play_sample(shot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						player1->setAmmo();
					}
					
					//spawn ammo boxes
					if(player1->getAmmo() < 5)
					{
						AmmoBox *ammoBox = new AmmoBox(ammoImage, &addAmmo);
						objects.push_back (ammoBox);	
					}
					
				}
				break;
			}//END SWITCH
		}//END KEY DOWN

		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;

			}//END SWITCH
		}//END KEY UP

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
	
			if(state == PLAYING)
			{

				if(keys[RIGHT])
					player1->moveRight();
				else if(keys[LEFT])
					player1->moveLeft();

				//spawn food boxes
				if(player1->getHunger() < 5)
				{
					FoodBox *foodBox = new FoodBox(foodImage, &addFood);
					objects.push_back(foodBox);	
				}

				//spawn zombies
				if(rand() % 100 == 0)
				{
					Zombie *zombie = new Zombie(WIDTH, 300, -1, zombieImage, &addKill);
					objects.push_back(zombie);
				}

				if(rand() % 150 == 0)
				{
					Zombie *zombie = new Zombie(10, 300, 1, zombieImage, &addKill);
					objects.push_back(zombie);
				}

				
				//update
				for(iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->update();
			
				//collisions
				for(iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if(!(*iter)->Collidable() ) continue;

					for(iter2 = iter; iter2 != objects.end(); ++iter2)
					{
						if( !(*iter2)->Collidable() ) continue;
						if( (*iter)->getID() == (*iter2)->getID()) continue;

						if( (*iter)->checkCollisions( (*iter2)))
						{
							(*iter)->collided( (*iter2)->getID());
							(*iter2)->collided( (*iter)->getID());
						}//ENDIF
					}//ENDFOR2
				}//ENDFOR1

				//handle things that kill you
				if(player1->getHealth() == 0 || player1->getHunger() == 0)
					changeState(state, LOST);
				if(kid1->getDead() == true)
					changeState(state, LOST);

				//clear dead
				for(iter = objects.begin(); iter != objects.end();)
				{
					if(!(*iter)->getAlive())
					{
						delete (*iter);
						iter = objects.erase(iter);
					}
					else
						iter++;
				}

				//change levels
				if(player1->getKills() > 10)
				{
					bg->setImage(bgImage2);
				}
				if(player1->getKills() > 20)
				{
					bg->setImage(bgImage3);
				}
				if(player1->getKills() > 30)
				{
					al_play_sample(fanfare, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					changeState(state, WON);
				}

			}//END PLAYING IF

		}//END TIMER EVENT

		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			
			//BEGIN RENDER
			if(state == TITLE)
			{
				titleScreen->render();
			}
			else if(state == INSTRUCT)
			{
				instructScreen->render();
			}
			else if (state == PLAYING)
			{
				for(iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->render();

				//Text statements
				al_draw_textf(font18, WHITE, 0, 10, 0, "Press Esc to quit...");
				al_draw_textf(font18, WHITE, 0, 26, 0, "Health: %i", player1->getHealth());
				al_draw_textf(font18, WHITE, 0, 42, 0, "Hunger: %i", player1->getHunger());
				al_draw_textf(font18, WHITE, 0, 58, 0, "Ammo: %i", player1->getAmmo());
				al_draw_textf(font18, WHITE, 0, 74, 0, "Kills: %i", player1->getKills());

				if(player1->getAmmo() == 0)
				{
					al_draw_textf(font24, WHITE, (WIDTH/2)-90, (HEIGHT/2), 0, "OUT OF AMMO!!");
				}
				if(player1->getHunger() <= 10)
				{
					al_draw_textf(font24, WHITE, (WIDTH/2)-80, (HEIGHT/2) + 30, 0, "LOW FOOD!!!");
				}

				if(player1->getKills() > 10 && player1->getKills() < 20)
				{	
					al_draw_textf(font24, WHITE, (WIDTH/2)-70, 20, 0, "LEVEL 2!!");
				}

				if(player1->getKills() > 20)
				{	
					al_draw_textf(font24, WHITE, (WIDTH/2)-70, 20, 0, "LEVEL 3!!");
				}
			}
			else if(state == LOST)
			{
				lostScreen->render();

				if(player1->getHealth() <= 0)
				{
					al_draw_textf(font24, WHITE, 204, 50, 0, "RAN OUT OF HEALTH!!");	
					if(player1->getHunger() <= 1)
						player1->addFood();
				}
				if(player1->getHunger() <= 0)
					al_draw_textf(font24, WHITE, 205, 50, 0, "STARVED TO DEATH!!");
				if(player1->getHealth() > 0 && player1->getHunger() > 0)
					al_draw_textf(font24, WHITE, 138, 50, 0, "DAUGHTER EATEN BY ZOMBIES!!");
			}
			else if(state == WON)
			{
				wonScreen->render ();	
			}

			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}//END RENDER

	}//END GAME LOOP

	//==============================================
	//DESTROY PROJECT OBJECTS
	//==============================================
	for(iter = objects.begin(); iter != objects.end();)
	{
		(*iter)->destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}

	//SCREENS==================================
	titleScreen->destroy();
	instructScreen->destroy ();
	lostScreen->destroy();
	wonScreen->destroy();
	delete titleScreen;
	delete instructScreen;
	delete lostScreen;
	delete wonScreen;

	//IMAGES=====================================
	al_destroy_bitmap(zombieImage);
	al_destroy_bitmap(heroImage);
	al_destroy_bitmap(kidImage);
	al_destroy_bitmap(bgImage1);
	al_destroy_bitmap(bgImage2);
	al_destroy_bitmap(bgImage3);
	al_destroy_bitmap(titleImage);
	al_destroy_bitmap(instructImage);
	al_destroy_bitmap(lostImage);
	al_destroy_bitmap(wonImage);
	al_destroy_bitmap(ammoImage);
	al_destroy_bitmap(foodImage);

	//SOUNDS======================================
	al_destroy_sample(shot);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
	al_destroy_sample(fanfare);
	
	//SHELL OBJECTS=================================
	al_destroy_font(font18);
	al_destroy_font(font24);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
 
	return 0;


}//END MAIN

void __cdecl addAmmo()
{
	player1->addAmmo();
}//END addAmmo

void __cdecl addKill()
{
	player1->addKill();
}//END addAmmo

void __cdecl addFood()
{
	player1->addFood();
}//END addAmmo

void changeState(int &state, int newState)
{
	
	if(state == PLAYING)
	{
		for(iter = objects.begin(); iter != objects.end(); ++iter)
		{
			if( (*iter)->getID() != PLAYER && (*iter)->getID() != MISC)
				(*iter)->setAlive(false);			
		}

		al_stop_sample_instance(songInstance);
	}

	state = newState;

	if(state == PLAYING)
	{
		player1->init();
		al_play_sample_instance(songInstance);
	}

}//END changeState