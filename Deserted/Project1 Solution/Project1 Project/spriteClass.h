//FILE : spriteClass.h
//PROG : Paige Peck
//PURP : Class for player sprite

#ifndef SPRITECLASS_H
#define SPRITECLASS_H

#include <cmath>

class Sprite
{
protected:								//Access specifier that allows inheritance
	float x, y;
	float oldX, oldY;
	int width, height;
	float velX, velY;
	int faceAngle;
	bool alive;
	ALLEGRO_BITMAP *image;
	//SEW SYSTEM
	float reservePower;
	//PLAYER - ENGINE ABILITY (ROLL)
	float enginePower;
	bool engineAbility, engineAbilityCanUse;
	int frameCount, curFrame, frameDelay, maxFrame;
	int widthFrame1, heightFrame1, widthFrame2, 
		heightFrame2, widthFrame3, heightFrame3, 
		widthFrame0, heightFrame0, widthFrame4, heightFrame4;
	int engineAbilityPower, engineCooldownDelay, coolDownTime, 
		coolDownDelay, abilityRecharge;
	bool engineAbilityOver;
	//PLAYER - SHIELD ABILITY (EMP)
	float shieldPower;
	bool shieldAbility, shieldAbilityCanUse, shieldAbilityOver;
	int shieldCoolDownTime, shieldCooldownDelay;
	int empTime, empDelay;
	//PLAYER - WEAPON ABILITY (OVERCHARGE)
	float weaponPower;
	bool weaponAbility, weaponAbilityCanUse, weaponAbilityOver;
	int weaponCoolDownTime, weaponCooldownDelay;
	int overchargeTime, overchargeDelay;
	//PLAYER - WEAPONS
	bool gatling, laser, gauss, rail, missile, beam;
	int gaussCharge, gaussFireDelay, gaussTimeDelay, railCharge, 
		missileReload, proximityMax, proximityFireDelay;
	int weaponFireDelay;						//Just for testing
	int beamScaleX, beamCenterX;

public:
	Sprite();
	~Sprite();
	void movePlayer();
	void draw(float, float, bool, int, int);
	void drawPlayer();
	void drawText();
	void updatePosition();
	void stopSprite();
	float calcAngleMoveX(int angle);
	float calcAngleMoveY(int angle);

	//Short methods implemented
	double getX()					{return x;}
	double getY()					{return y;}
	float getVelX()					{return velX;}
	int getWidth()					{return width;}
	int getHeight()					{return height;}
	bool getAlive()					{return alive;}
	int getFaceAngle()				{return faceAngle;}

	void setX(float xIn)			{x = xIn;}
	void setY(float yIn)			{y = yIn;}
	void setOldXY()					{oldX = x; oldY = y;}
	void setVelX(float vel)			{velX = vel;}
	void setVelY(float vel)			{velY = vel;}
	void setAlive(bool aliveIn)		{alive = aliveIn;}
	void setFaceAngle(int faceIn)	{faceAngle = faceIn;}
	//ENGINE ABILITY
	void handleEngineAbility();
	void engineCooldowns();
	bool getEngineAbility()						{return engineAbility;}
	float getEnginePower()						{return enginePower;}
	bool getEngineAbilityCanUse()				{return engineAbilityCanUse;}
	void setEngineAbility(bool ea)				{engineAbility = ea;}
	void setEngineAbilityCanUse(bool eaCanUse)	{engineAbilityCanUse = eaCanUse;}
	bool getEngineAbilityOver()					{return engineAbilityOver;}
	void setEngineAbilityOver(bool eOver)		{engineAbilityOver = eOver;}
	//SHIELD ABILITY
	void handleShieldAbility();
	bool getShieldAbility()						{return shieldAbility;}
	float getShieldPower()						{return shieldPower;}
	void setShieldAbility(bool sa)				{shieldAbility = sa;}
	void shieldAbilityCooldowns();
	bool getShieldAbilityCanUse()				{return shieldAbilityCanUse;}
	void setShieldAbilityCanUse(bool saCanUse)	{shieldAbilityCanUse = saCanUse;}
	void setShieldAbilityOver(bool sOver)		{shieldAbilityOver = sOver;}
	bool getShieldAbilityOver()					{return shieldAbilityOver;}
	//WEAPON ABILITY
	void handleWeaponAbility();
	bool getWeaponAbility()						{return weaponAbility;}
	float getWeaponPower()						{return weaponPower;}
	void setWeaponAbility(bool wa)				{weaponAbility = wa;}
	void weaponAbilityCooldowns();
	bool getWeaponAbilityCanUse()				{return weaponAbilityCanUse;}
	void setWeaponAbilityCanUse(bool waCanUse)	{weaponAbilityCanUse = waCanUse;}
	void setWeaponAbilityOver(bool wOver)		{weaponAbilityOver = wOver;}
	bool getWeaponAbilityOver()					{return weaponAbilityOver;}
};

//Constructor
Sprite::Sprite()
{
	coolDownTime = 0;
	coolDownDelay = 30;
	shieldCoolDownTime = 0;
	shieldCooldownDelay = 240;
	weaponCoolDownTime = 0;
	weaponCooldownDelay = 120;
}//END constructor

//Destructor
Sprite::~Sprite()
{
}//END destructor


//Update any sprite's position based on velx and vely
void Sprite::updatePosition()
{
	//Update x,y position
	x += velX;
	y += velY;

	if(enginePower >= .6)
		engineCooldowns();
	else if(shieldPower >= .6)
		shieldAbilityCooldowns();
	else if(weaponPower >= .6)
		weaponAbilityCooldowns();

}//END updatePosition

//shieldAbilityCooldowns
//Cooldown and recharges for shield ability
void Sprite::shieldAbilityCooldowns()
{
	if(getShieldAbility())
	{
		if(getShieldAbilityCanUse())
		{
			setShieldAbilityOver(false);
			handleShieldAbility();
		}
		else
		{
			if(++shieldCoolDownTime > shieldCooldownDelay)
			{
				shieldCoolDownTime = 0;
				setShieldAbility(false);
				setShieldAbilityCanUse(true);
			}
		}
	}
	
}//END shieldAbilityCooldowns

//weaponAbilityCooldowns
//Cooldown and recharges for weapon ability
void Sprite::weaponAbilityCooldowns()
{
	if(getWeaponAbility())
	{
		if(getWeaponAbilityCanUse())
		{
			setWeaponAbilityOver(false);
			handleWeaponAbility();
		}
		else
		{
			if(++weaponCoolDownTime > weaponCooldownDelay)
			{
				weaponCoolDownTime = 0;
				setWeaponAbility(false);
				setWeaponAbilityCanUse(true);
			}
		}
	}
}//END weaponAbilityCooldowns

//engineCooldowns
//Cooldown and recharge for engine ability
void Sprite::engineCooldowns()
{
	if(getEngineAbility())
	{
		if(getEngineAbilityCanUse())
		{
			setEngineAbilityOver(false);
			handleEngineAbility();
		}
		else
		{
			if(++coolDownTime > coolDownDelay)
			{
				coolDownTime = 0;
				setEngineAbility(false);
				setEngineAbilityCanUse(true);
			}
		}
	}
	if(engineAbilityPower <= 0)
	{
		//ENGINE OVERHEAT TIMER, set to 5 seconds
		engineAbilityPower = 0;
		if(++engineCooldownDelay > ENGINE_OVERCHARGE_DELAY)
		{
			engineCooldownDelay = 0;
			engineAbilityPower = 1;
			
		}
	}
	else if(engineAbilityPower < 100 && getEngineAbilityOver())
	{
		//ENGINE ABILITY RECHARGE
		if(++abilityRecharge > RECHARGE_DELAY)
		{
			abilityRecharge = 0;
			engineAbilityPower += 1;
		}
	}

}//END engineCooldowns

//Calculate X movement value based on direction angle.
//angle is the current angle of motion of the object,
//not necessarily the angle it is facing.
float Sprite::calcAngleMoveX(int angle)
{
    return (float) cos(angle * ALLEGRO_PI / 180);
}

//Calculate Y movement value based on direction angle
float Sprite::calcAngleMoveY(int angle)
{
	//shipMoveX -= Math.cos(Math.PI*heroGame.rotation/180)*thrustPower;
    return (float) sin(angle * ALLEGRO_PI / 180);
}

//draw
//Draws the sprite at the given x, y coordinates
void Sprite::draw(float bulletX, float bulletY, bool beamChoice, int scaleX, int centerX)
{
	if(!beamChoice)
	{
		al_draw_rotated_bitmap(image, width / 2, height / 2,
								x + width/2, 
								y + height/2,
								faceAngle * ALLEGRO_PI / 180, 0);
	}
	else
	{
		al_draw_scaled_rotated_bitmap(image, width / 2, height / 2,
							bulletX + centerX, 
							bulletY,
							scaleX, 1,
							faceAngle * ALLEGRO_PI / 180, 0);
	}

}//END draw

//drawPlayer
//Draws the player at the given x, y coordinates
//with the proper scaling for the engine ability
void Sprite::drawPlayer()
{
		if(curFrame == 0)
			al_draw_scaled_bitmap(image, 0, 0, width, height, x, y, widthFrame0, heightFrame0, 0);
		else if(curFrame == 1 || curFrame == 2 || curFrame == 20)
			al_draw_scaled_bitmap(image, 0, 0, width, height, x, y, widthFrame1, heightFrame1, 0);
		else if(curFrame == 3 || curFrame == 4 || curFrame == 19)
			al_draw_scaled_bitmap(image, 0, 0, width, height, x, y, widthFrame2, heightFrame2, 0);
		else if(curFrame == 5 || curFrame == 6 || curFrame == 18)
			al_draw_scaled_bitmap(image, 0, 0, width, height, x, y, widthFrame3, heightFrame3, 0);
		else
			al_draw_scaled_bitmap(image, 0, 0, width, height, x, y, widthFrame4, heightFrame4, 0);		
}//END drawPlayer

//drawText
void Sprite::drawText()
{
	al_draw_textf(arialBold12, WHITE, 0, 0, 0, "Use arrows to move");
	al_draw_textf(arialBold12, WHITE, 0, 15, 0, "Space bar to shoot");
	al_draw_textf(arialBold12, WHITE, 0, 30, 0, "Tab to switch weapon");
	al_draw_textf(arialBold12, WHITE, 0, 45, 0, "Left Shift to use ability");
	al_draw_textf(arialBold12, WHITE, 0, 60, 0, "For SEW system, A, S, D ");
	al_draw_textf(arialBold12, WHITE, 0, 75, 0, "adds to weapon, engine, shield");
	al_draw_textf(arialBold12, WHITE, 0, 90, 0, "Z, X, C subtracts");
	if(getEnginePower() > .599)
	{
		al_draw_textf(arialBold12, WHITE, 200, 10, 0, "Current Frame: %d", (int)curFrame);
		al_draw_textf(arialBold12, WHITE, 200, 25, 0, "Engine Ability Power: %d", (int)engineAbilityPower);
		al_draw_textf(arialBold12, WHITE, 200, 40, 0, "Engine Cooldown: %d", (int)coolDownTime);
		if(getEngineAbility() && !getEngineAbilityCanUse())
			al_draw_textf(arialBold12, WHITE, 200, 55, 0, "Ability Delay");
		if(engineAbilityPower <= 0)
			al_draw_textf(arialBold12, WHITE, 200, 70, 0, "ENGINE OVERHEATED");
	}
	else if(getShieldPower() > .599)
	{
		al_draw_textf(arialBold12, WHITE, 200, 10, 0, "EMP BLAST SELECTED");
		al_draw_textf(arialBold12, WHITE, 200, 25, 0, "EMP Cooldown: %d", (int)shieldCoolDownTime);
		if(getShieldAbilityCanUse() && getShieldAbilityOver())
			al_draw_textf(arialBold12, WHITE, 200, 40, 0, "EMP READY!");


	}
	else if(getWeaponPower() > .599)
	{
		al_draw_textf(arialBold12, WHITE, 200, 10, 0, "OVERCHARGE SELECTED");
		al_draw_textf(arialBold12, WHITE, 200, 25, 0, "Overcharge Use Time: %d", (int)overchargeTime);
		al_draw_textf(arialBold12, WHITE, 200, 40, 0, "Overcharge Cooldown: %d", (int)weaponCoolDownTime);
		if(getWeaponAbilityCanUse() && getWeaponAbilityOver())
			al_draw_textf(arialBold12, WHITE, 200, 55, 0, "OVERCHARGE READY!");
	}
	al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 10, 0, "Current Gun");
	if(gatling)
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 25, 0, "GATLING GUN");
	else if(laser)
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 25, 0, "LASER GUN");
	else if(gauss)
	{
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 25, 0, "GAUSS GUN");
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 40, 0, "GAUSS CHARGE: %d", (int)gaussCharge);
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 55, 0, "GAUSS Time Delay: %d", (int)gaussTimeDelay);
		if(gaussCharge == CHARGETIME)
			al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 70, 0, "FULL CHARGE");
	}
	else if(rail)
	{
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 25, 0, "RAIL GUN");
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 40, 0, "RAIL CHARGE: %d", (int)railCharge);
		if(railCharge == CHARGETIME)
			al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 55, 0, "FULL CHARGE");
	}
	else if(missile)
	{
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 25, 0, "MISSILES");
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 40, 0, "Missile Reload Time: %d", (int)missileReload);
	}
	else if(beam)
	{
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 25, 0, "BEAM");
	}
	else if(proximity)
	{
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 25, 0, "PROXIMITY MINES");
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 40, 0, "Proximity Reload: %d", (int)weaponFireDelay);
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2, 55, 0, "Mines Out:   %d", (int)proximityAmount);
		al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH/2 + 80, 55, 0, "/ %d", (int)proximityMax);
	}
	
	al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH - 200, 10, 0, "|  Shield |");
	al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH - 130, 10, 0, " Engines |");
	al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH - 70, 10, 0, "Weapons  |");	
	al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH - 185, 25, 0, " %.3f", (float)shieldPower);
	al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH - 120, 25, 0, "%.3f", (float)enginePower);
	al_draw_textf(arialBold12, WHITE, SCREEN_WIDTH - 65, 25, 0, "%.3f", (float)weaponPower);
}//END drawText

#endif