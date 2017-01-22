//desertedDefs.h
//Paige Peck
//Defines constants for "Deserted"

#ifndef CAPTIVEDEFS_H
#define CAPTIVEDEFS_H

void fireLaser();

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 640
#define FPS 60
#define ACCELERATION 0.1f
#define MAXVEL 5
//#define BULLETSPEED 10		//Speed of bullet in one dimension, was 7
#define FIRE_DELAY 10		//Delay allowing the weapon to be fired
#define ENGINE_OVERCHARGE_DELAY 200
#define RECHARGE_DELAY 8
#define GAUSSTIMEDELAY 60
#define CHARGETIME 10		//Used for both rail and gauss, for how long it takes to charge fully
#define OVER_CHARGE_DELAY 240
#define MAX_PROXIMITY 3
#define SEW_BUTTON_DELAY 10

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0,0,0)

//Define keys array here since the class needs access
enum {UP, DOWN, LEFT, RIGHT, SPACE, ESCAPE, ENTER, 
	PKEY, QKEY, RKEY, LSHIFT, TAB, AKEY, SKEY, DKEY, ZKEY, XKEY, CKEY};
bool keys[] = {false, false, false, false, false, false, 
	false, false, false, false, false, false, false, false, false, false, false, false};

//Global bitmap pointers so they can be used anywhere
ALLEGRO_BITMAP *bulletsImageGatling;
ALLEGRO_BITMAP *bulletsImageLaser;
ALLEGRO_BITMAP *bulletsImageGauss;
ALLEGRO_BITMAP *bulletsImageRail;
ALLEGRO_BITMAP *bulletsImageMissile;
ALLEGRO_BITMAP *bulletsImageBeam;
ALLEGRO_BITMAP *bulletsImageProximity;
//ALLEGRO_BITMAP *sewImage[35];

int bulletSpeed, proximityAmount;
bool proximity;
//float sewFrame[35];

//Define state-management constants & variable
enum GAMESTATE {INIT, STARTUP, PLAYING, PAUSED, GAMEOVER};
int gameState = -1;
enum SHIPSTATE {NORMAL, HIT, DEATH};
int shipState = -1;

//Essential Allegro pointers
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *arialBold12;

#endif
//Error codes for initialization
//-1:  allegro basic did not init
//-2:  images were not all loaded
//-3:  Mappy load error
//-4:  font errors
//-5:  sound errors