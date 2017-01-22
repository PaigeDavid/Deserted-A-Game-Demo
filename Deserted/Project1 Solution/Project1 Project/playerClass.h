//FILE : playerClass.h
//PROG : Paige Peck
//PURP : Subclass for the ship sprite
//Inherits from class spriteClass

#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

//This class inherits from the Sprite class, so it has access
//to all the variables and methods there.
class Player : public Sprite
{
private:
	//int weaponFireDelay;	//Only the player needs this
	int gattlingFireDelay;
	int laserFireDelay;
	int railFireDelay;
	int missileFireDelay;
	bool proximityCanFire, beamIsShooting, bulletKill;
	//SEW SYSTEM
	int buttonATime, buttonSTime, buttonDTime, 
		buttonZTime, buttonXTime, buttonCTime, buttonDelay;

public:
	Player();
	~Player();
	void resetPlayer();
	void limitSprite();
	bool initShip(char *);
	void handleKeyboard();
	//WEAPONS
	void gattlingGun();
	void laserShot();
	void gaussShot();
	void railShot();
	void missileShot();
	void beamShot();
	void proximityShot();
	void switchWeapons();
	bool getGatling()				{return gatling;}
	bool getLaser()					{return laser;}
	bool getGauss()					{return gauss;}
	int getGaussCharge()			{return gaussCharge;}
	bool getRail()					{return rail;}
	bool getMissile()				{return missile;}
	int getMissileReload()			{return missileReload;}
	bool getBeam()					{return beam;}
	bool getProximity()				{return proximity;}
	int getProximityAmount()		{return proximityAmount;}
	int getProximityDelay()			{return proximityFireDelay;}
	bool getBulletKill()			{return bulletKill;}
	void setBulletKill(bool setBK)	{bulletKill = setBK;}
	int getBeamScaleX()				{return beamScaleX;}
	int getBeamCenterX()			{return beamCenterX;}
	void setBeamScaleX(int);
	void setBeamCenterX(int beamX)	{beamCenterX = beamX;}
	void beamBuildUp();
	bool getBeamIsShooting()		{return beamIsShooting;}
	//SHIELD ABILITY
	void setAllKeysFalse();

};

//Constructor.  Most initialization of variables will be done in
//resetPlayer, so game can be reset at any time.
Player::Player()
{
	beamScaleX = 1;
	beamCenterX = 5 * beamScaleX;
	x = 50;
	y = 200;
	velX = 0.0;
	velY = 0.0;
	faceAngle = 0;

	//Weapon delays
	weaponFireDelay = 0;
	gattlingFireDelay = 16;
	laserFireDelay = 12;
	gaussFireDelay = 14;
	gaussTimeDelay = 0;
	gaussCharge = 0;
	railFireDelay = 15;
	railCharge = 0;
	missileReload = 5;
	missileFireDelay = 30;
	proximityAmount = 0;
	proximityMax = MAX_PROXIMITY;
	proximityFireDelay = 90;
	proximityCanFire = false;

	gatling = false;
	laser = false;
	gauss = false;
	rail = false;
	missile = false;
	beam = true;
	bulletKill = false;

	proximity = false;

	//SEW SYSTEM
	reservePower = 0.0;
	buttonDelay = SEW_BUTTON_DELAY;

	//Engine ability
	enginePower = .3;			//For testing purposes, must be .6 or higher to activate ability
	engineAbility = false;
	engineAbilityCanUse = true;
	frameCount = 0;
	frameDelay = 3;
	curFrame = 0;
	maxFrame = 20;
	engineCooldownDelay = 0;
	engineAbilityPower = 100;
	engineAbilityOver = true;
	abilityRecharge = 0;

	widthFrame0 = 78;
	heightFrame0 = 43;
	widthFrame1 = 89;
	heightFrame1 = 47;
	widthFrame2 = 97;
	heightFrame2 = 51; 
	widthFrame3 = 105;
	heightFrame3 = 56; 
	widthFrame4 = 113;
	heightFrame4 = 60;

	//SHIELD ABILITY
	shieldPower = .3;			//For testing purposes, must be .6 or higher to activate ability
	shieldAbility = false;
	shieldAbilityOver = true;
	empTime = 0;
	empDelay = 90;

	//WEAPON ABILITY
	weaponPower = .3;			//For testing purposes, must be .6 or higher to activate ability
	weaponAbility = false;
	weaponAbilityOver = true;
	overchargeTime = OVER_CHARGE_DELAY;
	overchargeDelay = 0;
}//END Constructor

//Destructor
Player::~Player()
{
	//Delete the player's image bitmap
	al_destroy_bitmap(image);
}

//Initialize ship's image and its width & height members,
//as well as variables that depend on them
bool Player::initShip(char *filename)
{
	//Load the ship's image
	if (!(image = al_load_bitmap(filename))) return false;	//Image did not load

	//Set up the ship's width and height from the image
	width = al_get_bitmap_width(image);
	height = al_get_bitmap_height(image);

	return true;
}//END initShip

void Player::resetPlayer()
{
	//alive = true;
    x = SCREEN_WIDTH / 2; 
    y = SCREEN_HEIGHT / 2;
    velX = 0.0; 
    velY = 0.0;

	weaponFireDelay = FIRE_DELAY;

    //faceAngle = 0; 
    //moveAngle = 0;
	//Start fire delay variable at max, so firing
	//can commence right away with no delay
	
}//END resetPlayer

//Sense and process arrow (motion) keys
void Player::handleKeyboard()
{
	if (keys[LEFT])
	{
		//shipMoveX -= Math.cos(Math.PI*heroGame.rotation/180)*thrustPower;
		velX -= calcAngleMoveX(0) * ACCELERATION;
	}

	if (keys[RIGHT])
	{
		velX += calcAngleMoveX(0) * ACCELERATION;
	}

	if (keys[UP])		//Accelerate up
	{
		velY += calcAngleMoveY(-90) * ACCELERATION;
	}
	if(keys[DOWN])		//Accelerate down
	{
		velY -= calcAngleMoveY(-90) * ACCELERATION;
	}
	if(keys[TAB])
	{
		switchWeapons();
		keys[TAB] = false;
	}
	if(!(keys[AKEY]))
		buttonATime = SEW_BUTTON_DELAY;
	if(!(keys[SKEY]))
		buttonSTime = SEW_BUTTON_DELAY;
	if(!(keys[DKEY]))
		buttonDTime = SEW_BUTTON_DELAY;
	if(!(keys[ZKEY]))
		buttonZTime = SEW_BUTTON_DELAY;
	if(!(keys[XKEY]))
		buttonXTime = SEW_BUTTON_DELAY;
	if(!(keys[CKEY]))
		buttonCTime = SEW_BUTTON_DELAY;

	if(keys[AKEY])								 //SHIELDS
	{
		if(++buttonATime > buttonDelay)
		{
			buttonATime = 0;
			if(reservePower >= 0.01)
			{
				if(reservePower < 0.05)
				{
					shieldPower += .025;
					reservePower -= .025;
				}
				else
				{
					shieldPower += .05;
					reservePower -= .05;
				}
			}
			else if(weaponPower > 0.01 && enginePower > 0.01)
			{
				weaponPower -= .025;
				enginePower -= .025;
				shieldPower += .05;
			}
			else if(weaponPower > 0.01 && enginePower <= 0.01)
			{
				weaponPower -= .025;
				shieldPower += .025;
			}
			else if(enginePower > 0.01 && weaponPower <= 0.01)
			{
				enginePower -= .025;
				shieldPower += .025;
			}
		}
	}
	if(keys[ZKEY])
	{
		if(++buttonZTime > buttonDelay)
		{
			buttonZTime = 0;
			if(shieldPower > 0.01)
			{
				if(shieldPower < 0.05)
				{
					shieldPower -= .025;
					reservePower += .025;
				}
				else
				{
					shieldPower -= .05;
					reservePower += .05;
				}
			}
		}
	}
	if(keys[SKEY])							//ENGINES
	{
		if(++buttonSTime > buttonDelay)
		{
			buttonSTime = 0;
			if(reservePower >= 0.01)
			{
				if(reservePower < 0.05)
				{
					enginePower += .025;
					reservePower -= .025;
				}
				else
				{
					enginePower += .05;
					reservePower -= .05;
				}
			}
			else if(weaponPower > 0.01 && shieldPower > 0.01)
			{
				weaponPower -= .025;
				shieldPower -= .025;
				enginePower += .05;
			}
			else if(weaponPower > 0.01 && shieldPower <= 0.01)
			{
				weaponPower -= .025;
				enginePower += .025;
			}
			else if(shieldPower > 0.01 && weaponPower <= 0.01)
			{
				shieldPower -= .025;
				enginePower += .025;
			}
		}
	}
	if(keys[XKEY])
	{
		if(++buttonXTime > buttonDelay)
		{
			buttonXTime = 0;
			if(enginePower > 0.01)
			{
				if(enginePower < 0.05)
				{
					enginePower -= .025;
					reservePower += .025;
				}
				else
				{
					enginePower -= .05;
					reservePower += .05;
				}
			}
		}
	}
	if(keys[DKEY])								//WEAPONS
	{
		if(++buttonDTime > buttonDelay)
		{
			buttonDTime = 0;
			if(reservePower >= 0.01)
			{
				if(reservePower < 0.05)
				{
					weaponPower += .025;
					reservePower -= .025;
				}
				else
				{
					weaponPower += .05;
					reservePower -= .05;
				}
			}
			else if(enginePower > 0.01 && shieldPower > 0.01)
			{
				shieldPower -= .025;
				enginePower -= .025;
				weaponPower += .05;
			}
			else if(enginePower > 0.01 && shieldPower <= 0.01)
			{
				enginePower -= .025;
				weaponPower += .025;
			}
			else if(shieldPower > 0.01 && enginePower <= 0.01)
			{
				shieldPower -= .025;
				weaponPower += .025;
			}
		}
	}
	if(keys[CKEY])
	{
		if(++buttonCTime > buttonDelay)
		{
			buttonCTime = 0;
			if(weaponPower > 0.01)
			{
				if(weaponPower < 0.05)
				{
					weaponPower -= .025;
					reservePower += .025;
				}
				else
				{
					weaponPower -= .05;
					reservePower += .05;
				}
			}
		}
	}
	if(keys[LSHIFT])
	{
		//ENGINE ABILITY
		if(getEnginePower() > .599 && !getEngineAbility() && getEngineAbilityCanUse() && engineAbilityPower > 0)
		{
			engineAbilityPower -= 65;
			setEngineAbility(true);
			keys[SPACE] = false;
		}
		//SHIELD ABILITY
		if(getShieldPower() > .599)
		{
			setAllKeysFalse();
			setShieldAbility(true);
		}
		//WEAPON ABILITY
		if(getWeaponPower() > .599)
		{
			setWeaponAbility(true);
		}

		keys[LSHIFT] = false;
	}//END LSHIFT key

	//Keep velocity down to a reasonable speed
	if (velX > MAXVEL) velX = MAXVEL;
	if (velX < -MAXVEL) velX = -MAXVEL;
	if (velY > MAXVEL) velY = MAXVEL;
	if (velY < -MAXVEL) velY = -MAXVEL;

	//Space bar fires weapon
	if (keys[SPACE])
	{
		if(getEngineAbilityOver()) //Don't allow firing when using engine ability
		{
			if(gatling)
				gattlingGun();
			else if(laser)
				laserShot();
			else if(gauss)
				gaussShot();
			else if(rail)
				railShot();
			else if(missile)
				missileShot();
			else if(beam)
				beamShot();
			else if(proximity)
				proximityShot();
		}
	}//END if space key

	if(gatling && !keys[SPACE])
	{
		//Handles gattling gun cooldown
		if(++weaponFireDelay > gattlingFireDelay)
		{
			if(gattlingFireDelay <= 20)
			{
				weaponFireDelay = 0;
				gattlingFireDelay += 1;
			}
		}
	}
	else if(gauss && !keys[SPACE])
	{
		if(gaussCharge >= 1)
		{
			fireLaser();
			gaussCharge = 0;
			gaussTimeDelay = 0;
			weaponFireDelay = 0;
			keys[SPACE] = false;
		}
		else
			weaponFireDelay = 0;
	}
	else if(rail && !keys[SPACE])
	{
		if(railCharge == CHARGETIME)
		{
			fireLaser();
			railCharge = 0;
			weaponFireDelay = 0;
			keys[SPACE] = false;
		}
		else
		{
			railCharge = 0;
			weaponFireDelay = 0;
			keys[SPACE] = false;
		}
	}
	else if(missile && missileReload > 0)
	{
		if(++weaponFireDelay > missileFireDelay)
		{
			weaponFireDelay = 0;
			--missileReload;
		}
	}
	else if(beam && !keys[SPACE])
	{
		if(beamScaleX > 1)
		{
			beamScaleX--;
			beamCenterX = 5 * beamScaleX;
		}
		else
		{
			beamScaleX = 1;
			beamIsShooting = false;
		}
		
	}
	
	else if(proximity && proximityAmount < proximityMax && !proximityCanFire)
	{
		if(++weaponFireDelay >= proximityFireDelay)
		{
			proximityCanFire = true;
		}
	}
	
}//END handleKeyboard

//handleEngineAbility
//Handles ship roll and invulnerability
void Sprite::handleEngineAbility()
{
	if(++frameCount > frameDelay)
	{
		frameCount = 0;
		if(++curFrame > maxFrame)
		{
			setEngineAbilityOver(true);
			curFrame = 0;
			setEngineAbilityCanUse(false);
		}
	}
}//END handleEngineAbility

//handleShieldAbility
//Handles EMP burst
void Sprite::handleShieldAbility()
{
	if(++empTime > empDelay)
	{
		empTime = 0;
		setShieldAbilityOver(true);
		setShieldAbilityCanUse(false);
	}
}//END handleShieldAbility

//handleWeaponAbility
//Handles adition damage per shot, 
//And makes weapon cooldowns faster
void Sprite::handleWeaponAbility()
{
	if(--overchargeTime < overchargeDelay)
	{
		overchargeTime = OVER_CHARGE_DELAY;
		setWeaponAbilityOver(true);
		setWeaponAbilityCanUse(false);
		proximityMax = MAX_PROXIMITY;
	}
	else
	{
		if(proximity && weaponFireDelay >= 89)
		{}
		else
			weaponFireDelay++;
		proximityMax = MAX_PROXIMITY + 2;
	}
}//END handleWeaponAbility

//setAllKeysFalse
//Sets each key to false,
//for the purpose of EMP blast shutting down everything for a short time
void Player::setAllKeysFalse()
{
	for(int i = 0; i < 12; ++i)
	{
		keys[i] = false;
	}
}//END setAllKeysFalse

//gattlingGun
//Handles gattling gun shot delays and firing
void Player::gattlingGun()
{
	//Limit the firing rate
	if (++weaponFireDelay > gattlingFireDelay)
	{
		weaponFireDelay = 0;
		if(gattlingFireDelay >= 3)
			gattlingFireDelay -= 1;
		//Play the fire wave sound
		//al_play_sample (laserfire, gain, pan, pitch, ALLEGRO_PLAYMODE_ONCE, 0);
		fireLaser();
	}
}//END gattlingGun

//laserShot
//Handles laser shot delayes and firing
void Player::laserShot()
{
	if(++weaponFireDelay > laserFireDelay)
	{
		weaponFireDelay = 0;
		fireLaser();
	}
}//END laserShot

//gaussShot
//Handles gauss shot, where player needs to hold 
//space bar to let the shot charge, then on release and 
//full charge, it shoots, if charge was not enough, bullet speed will be slow
//some time after full charge, gauss shot will release
void Player::gaussShot()
{
	if(++weaponFireDelay > gaussFireDelay && gaussCharge < CHARGETIME)
	{
		weaponFireDelay = 0;
		++gaussCharge;
	}
	if(gaussCharge == CHARGETIME && ++gaussTimeDelay > GAUSSTIMEDELAY)
	{
		fireLaser();
		gaussTimeDelay = 0;
		gaussCharge = 0;
		keys[SPACE] = false;
	}
}//END gaussShot

//railShot
//Handles rail shot, where player needs to hold
//space bar to let the shot charge, then on full charge
//and release of space bar, shot is fired. MUST HAVE FULL CHARGE TO SHOOT
void Player::railShot()
{
	if(++weaponFireDelay > railFireDelay && railCharge < CHARGETIME)
	{
		weaponFireDelay = 0;
		++railCharge;
	}
}//END railShot

//missileShot
//Handles missile shot
//Missile is slow, and slow recharge, but powerful
void Player::missileShot()
{
	if(missileReload == 0)
	{
		missileReload = 5;
		fireLaser();
		keys[SPACE] = false;
	}
}//END missileShot

//beamShot
//Handles beam firing 
//Constant light beam that fires quickly enough
//for it to look like a steady stream of light
void Player::beamShot()
{
	if(beamIsShooting)
	{	
		beamBuildUp();
	}
	else
	{
		setBeamScaleX(1);
		fireLaser();
		beamIsShooting = true;
	}
	

}//END beamShot4

//beamBuildUp
//Beam scales to larger image after space bar held for certain amount of time
void Player::beamBuildUp()
{
	if(beamScaleX < 45)
	{
		beamScaleX++;
		beamCenterX = 5 * beamScaleX;
	}
	else
	{
		beamScaleX = 45;
	}
}//END beamBuildUp

void Player::setBeamScaleX(int scaleX)
{
	beamScaleX = scaleX; 
	beamCenterX = 5 * beamScaleX;
}

//proximityShot
//Handles proximity drops
//Only small amount allowed on screen, 
//moving in a set reverse pace
void Player::proximityShot()
{
	if(proximityCanFire)
	{
		proximityAmount++;
		weaponFireDelay = 0;
		fireLaser();
		proximityCanFire = false;
		keys[SPACE] = false;
	}
}//END proximityShot

//switchWeapons
//Checks to see which weapon is currently selected,
//then switches to the other weapon
void Player::switchWeapons()
{
	if(gatling)
	{
		gattlingFireDelay = 20;
		//laser = true;
		gatling = false;
		beam = true;
	}
	else if(missile)
	{
		gatling = true;
		//laser = false;
		missile = false;
	}
	else if(beam)
	{
		if(!beamIsShooting)
		{
			bulletKill = true;
			gatling = true;
			beam = false;
		}
	}
}//END switchWeapons

//limitSprite
//Limits sprite from moving beyond the barriers set
void Player::limitSprite()
{
	//Stop player from moving beyond screen size and "invisible wall"
	//And reset player velocity when hitting a "wall"
	if ((x > (SCREEN_WIDTH - width))) 
	{
		x = SCREEN_WIDTH-width;
		velX = 0;
	}
	if ((x < 0)) 
	{
		x = 0;
		velX = 0;
	}
	if ((y > SCREEN_HEIGHT-height)) 
	{
		y = SCREEN_HEIGHT-height;
		velY = 0;
	}
	if ((y < 0)) 
	{
		y = 0;
		velY = 0;
	}

}//END LimitSprite

#endif