//main.cpp
//Paige Peck
//Side scrolling space shooter "Deserted"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
//#include <iostream>

//header files
#include "desertedDefs.h"
#include "spriteClass.h"
#include "playerClass.h"
#include "bulletClass.h"
#include "bulletstackmgt.h"

//prototypes
bool initializeAllegro();
void handleKeyDown(int);
void handleKeyUp(int);
void changeGameState(int &, int);

//Declare player here
//Player *player = NULL;
//ALLEGRO_BITMAP *temp;

int main() 
{          
	bool redrawRequired = true, success = true, quit = false;

	//Change to STARTUP state...one-time Allegro & game initializations happen there
	changeGameState(gameState, INIT);
	//std::cout << "player = " << player << "\n\n";

	//Set the game state so the opening menu will appear when the game loop starts up
	//Object variable values are reset to game start values if the game has been in progress
	changeGameState(gameState, PLAYING);

	al_clear_to_color(BLACK);
	al_flip_display();

	//Start up the timer.  Never do this until just before the game is to start!
	al_start_timer(timer);
	
	//Game Loop
	while (!quit)
	{
		ALLEGRO_EVENT evt;
		//Wait for one of the allegro-defined events
		al_wait_for_event(eventQueue, &evt);

		//An event was generated. Check for all possible event types
		switch (evt.type)
		{
			case ALLEGRO_EVENT_KEY_DOWN:
				handleKeyDown(evt.keyboard.keycode);
				break;

			case ALLEGRO_EVENT_KEY_UP:
				handleKeyUp(evt.keyboard.keycode);
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				quit = true;
				break;

			case ALLEGRO_EVENT_TIMER:

				redrawRequired = true;

				if (gameState == STARTUP)
				{
					if (keys[ENTER])
					{
						changeGameState(gameState, PLAYING);
					}
					else if (keys[ESCAPE])
					{
						quit = true;
						//changeGameState(gameState, GAMEOVER);
					}
				}
				else if (gameState == PLAYING)
				{
					//Move player
					if(player->getShieldAbilityOver())			//Make it so player can't use any controls during this cooldown
						player->handleKeyboard();
					//Move the ship
					player->updatePosition();
					//Limit movement of ship
					player->limitSprite();

					//Update all live bullets
					//Also, checks for any collisions and destroys asteroids
					updateSprites(bulletStack);
					//Check the entire stack of bullets for any dead ones
					bulletStack = cleanSprites (bulletStack, FALSE);

					//IF Escape key pressed in PLAYING state, go to GAMEOVER state
					if (keys[ESCAPE])
					{
						quit = true;
						//changeGameState(gameState, GAMEOVER);
					}
				}//END if PLAYING
				else if (gameState == PAUSED)
				{
					if (keys[PKEY])
					{
						changeGameState(gameState, PLAYING);
					}
					else if (keys[QKEY])
					{
						quit = true;
					}
					else if (keys[RKEY])
					{
						changeGameState(gameState, STARTUP);
					}
				}//END if PAUSED

				break;

		}//END switch evt.type

		//========================================================
		//Rerender the display.
		//========================================================
		if (redrawRequired && al_is_event_queue_empty(eventQueue))
		{
			redrawRequired = false;
		//===========================
			//Render the PLAYING state
			//===========================
			if (gameState == PLAYING)
			{
				al_clear_to_color(BLACK);

				//Draw all bullets
				drawBullets (bulletStack);

				//Draw the player
				player->drawPlayer();

				player->drawText();

			}
			//===========================
			//Render the STARTUP state
			//===========================
			else if (gameState == STARTUP)
			{

			}
			//===========================
			//Render the PAUSED state
			//===========================
			else if (gameState == PAUSED)
			{

			}

			al_flip_display();

		}//END render
	}//END GAME LOOP


	//Change state to GAMEOVER & delete all dynamically allocated memory
	changeGameState(gameState, GAMEOVER);

return 0;
}

void handleKeyDown(int keyCode)
{
	switch(keyCode)
	{
		case ALLEGRO_KEY_ESCAPE:
			keys[ESCAPE] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = true;
			break;
		case ALLEGRO_KEY_UP:
			keys[UP] = true;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = true;
			break;
		case ALLEGRO_KEY_SPACE:
			keys[SPACE] = true;
			break;
		case ALLEGRO_KEY_ENTER:
		case ALLEGRO_KEY_PAD_ENTER:
			keys[ENTER] = true;
			break;
		case ALLEGRO_KEY_P:
			keys[PKEY] = true;
			break;
		case ALLEGRO_KEY_Q:
			keys[QKEY] = true;
			break;
		case ALLEGRO_KEY_R:
			keys[RKEY] = true;
			break;
		case ALLEGRO_KEY_LSHIFT:
			keys[LSHIFT] = true;
			break;
		case ALLEGRO_KEY_TAB:
			keys[TAB] = true;
			break;
		case ALLEGRO_KEY_A:
			keys[AKEY] = true;
			break;
		case ALLEGRO_KEY_S:
			keys[SKEY] = true;
			break;
		case ALLEGRO_KEY_D:
			keys[DKEY] = true;
			break;
		case ALLEGRO_KEY_Z:
			keys[ZKEY] = true;
			break;
		case ALLEGRO_KEY_X:
			keys[XKEY] = true;
			break;
		case ALLEGRO_KEY_C:
			keys[CKEY] = true;
			break;
	}

}//END handleKeyDown

void handleKeyUp(int keyCode)
{
	switch(keyCode)
	{
		case ALLEGRO_KEY_ESCAPE:
			keys[ESCAPE] = false;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = false;
			break;
		case ALLEGRO_KEY_UP:
			keys[UP] = false;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = false;
			break;
		case ALLEGRO_KEY_SPACE:
			keys[SPACE] = false;
			break;
		case ALLEGRO_KEY_ENTER:
		case ALLEGRO_KEY_PAD_ENTER:
			keys[ENTER] = false;
			break;
		case ALLEGRO_KEY_P:
			keys[PKEY] = false;
			break;
		case ALLEGRO_KEY_Q:
			keys[QKEY] = false;
			break;
		case ALLEGRO_KEY_R:
			keys[RKEY] = false;
			break;
		case ALLEGRO_KEY_LSHIFT:
			keys[LSHIFT] = false;
			break;
		case ALLEGRO_KEY_TAB:
			keys[TAB] = false;
			break;
		case ALLEGRO_KEY_A:
			keys[AKEY] = false;
			break;
		case ALLEGRO_KEY_S:
			keys[SKEY] = false;
			break;
		case ALLEGRO_KEY_D:
			keys[DKEY] = false;
			break;
		case ALLEGRO_KEY_Z:
			keys[ZKEY] = false;
			break;
		case ALLEGRO_KEY_X:
			keys[XKEY] = false;
			break;
		case ALLEGRO_KEY_C:
			keys[CKEY] = false;
			break;
	}
}//END handleKeyUp


void changeGameState(int &state, int newState)
{
	//Handle leaving the current state
	//At present, there are no actions to take when leaving any state
	//But this is here for future possibilities
	//switch (state)
	//{
	//	case INIT:		break;
	//	case STARTUP:	break;
	//	case PLAYING:	break;
	//	case PAUSED:	break;
	//	case GAMEOVER:	break;
	//}

	state = newState;

	//Handle entering the new state
	switch (state)
	{
		//INIT handles all the initializations at the very beginning
		//It is not possible to get back to this state
		case INIT:
			//Initialize allegro, etc
			if (!initializeAllegro()) exit(-1);

			srand((unsigned) time(NULL));

			//Set up laserfire sound WAV
			//laserfire declared globally in spacedefs.h
			//laserfire = al_load_sample("fire.wav");
			//if (!laserfire) exit(-5);

			//Load the Mappy background file
			//if (MapLoad("SpaceTileBackground.FMP", 1) != 0) exit(-3);

			//Compute the actual width/height in pixels of the loaded map
			//These are used later in scrolling the map
			//mapWidthInPixels = mapwidth * mapblockwidth;
			//mapHeightInPixels = mapheight * mapblockheight;

			//Set the back buffer as the drawing bitmap for the display
			al_set_target_bitmap(al_get_backbuffer(display));
			al_hide_mouse_cursor(display);
			al_set_window_title(display, "DESERTED");

			//Initialize the event queue
			eventQueue = al_create_event_queue();
			if (!eventQueue)
			{
				al_destroy_display(display);
				al_destroy_timer(timer);
				exit(-1);
			}

			//Register events as arriving from these sources:  display, timer, keyboard
			al_register_event_source(eventQueue, al_get_display_event_source(display));
			al_register_event_source(eventQueue, al_get_timer_event_source(timer));
			al_register_event_source(eventQueue, al_get_keyboard_event_source());

			//Initialize the ship
			player = new Player;
			//Load the ship's image, and initialize other members
			if (!player->initShip("player1.png")) exit(-2);

			//Set up the bullet images
			bulletsImageGatling = al_load_bitmap("gatling.png");
			if (!bulletsImageGatling) exit(-2);

			bulletsImageGauss = al_load_bitmap("gauss.png");
			if(!bulletsImageGauss) exit(-2);

			bulletsImageRail = al_load_bitmap("gauss.png");
			if(!bulletsImageRail) exit(-2);

			bulletsImageMissile = al_load_bitmap("gauss.png");
			if(!bulletsImageMissile) exit(-2);

			bulletsImageBeam = al_load_bitmap("beam.png");
			if(!bulletsImageBeam) exit(-2);

			bulletsImageProximity = al_load_bitmap("proximity.png");
			if(!bulletsImageProximity) exit(-2);

			bulletsImageLaser = al_load_bitmap("laser.bmp");
			if (!bulletsImageLaser) exit(-2);
			al_convert_mask_to_alpha(bulletsImageLaser, al_map_rgb(255, 0, 255));
			/***********************											//FIX ALL THIS, PLACE SOMEWHERE ELSE, TEMPORARY
			temp = al_load_bitmap("sew.png");
			if(!temp) exit(-2);
			for(int ct = 0; ct <= 34; ++ct)
			{
				sewImage[ct] = al_create_bitmap(20, 100);
				al_set_target_bitmap(sewImage[ct]);
				al_convert_mask_to_alpha(temp, al_map_rgb(255, 0, 255));
				al_draw_bitmap_region(temp, 0, 0, 20, 100, 0, 0, 0);
			}
			*/
			break;

		case STARTUP:
			player->resetPlayer();

			//Kill any and all bullets, in case game was in progress when change state was called
			bulletStack = cleanSprites (bulletStack, TRUE);	
			break;

		case PLAYING:	break;
		case PAUSED:	break;
		case GAMEOVER:	
			//Free up all the allocated memory for bullets
			bulletStack = cleanSprites (bulletStack, TRUE);
			delete player;
			al_destroy_bitmap(bulletsImageGatling);
			al_destroy_bitmap(bulletsImageLaser);
			al_destroy_bitmap(bulletsImageGauss);
			al_destroy_bitmap(bulletsImageRail);
			al_destroy_bitmap(bulletsImageMissile);
			al_destroy_bitmap(bulletsImageBeam);
			al_destroy_bitmap(bulletsImageProximity);
			//for (int ct = 0; ct < 34; ++ ct)
			//	al_destroy_bitmap(sewImage[ct]);
			//al_destroy_bitmap(temp);

			al_destroy_font(arialBold12);
			al_destroy_timer(timer);
			al_destroy_display(display);
			al_destroy_event_queue(eventQueue);
			break;
	}//END switch(state)
}//END changeGameState



//Take care of Allegro initialization tasks. Return false if any fail.
bool initializeAllegro()
{
	bool success = true;

	//Init basic environment
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR", "Allegro failed to initialize!", NULL, NULL, NULL);
		success = false;
	}

	//Initialize keyboard input
	if (!al_install_keyboard())
	{
		al_show_native_message_box(NULL, "ERROR", "Keyboard failed to initialize!", NULL, NULL, NULL);
		success = false;
	}

	//Initialize timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		al_show_native_message_box(NULL, "ERROR", "Timer failed to initialize!", NULL, NULL, NULL);
		success = false;
	}

	//Initialize display
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display)
	{
		al_show_native_message_box(NULL, "ERROR", "Display failed to initialize!", NULL, NULL, NULL);
		success = false;
	}

	//Install sound "equipment"!
	if (!al_install_audio()) return -5;
	if (!al_init_acodec_addon()) return -5;
	//Reserve one voice.  You need as many of these as you have
	//different sounds.
	if (!al_reserve_samples(1)) return -5;

	//Initialize the image mechanism
	if (!al_init_image_addon())
	{
		al_show_native_message_box(NULL, "ERROR", "Image addon failed to initialize!", NULL, NULL, NULL);
		success = false;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	//load the arial font
	arialBold12 = al_load_font("arialbd.ttf", 12, 0);
	if (!arialBold12) return -3;
	//arialBold24 = al_load_font("arialbd.ttf", 24, 0);
	//if (!arialBold24) return -3;

	return success;
}//END initializeAllegro