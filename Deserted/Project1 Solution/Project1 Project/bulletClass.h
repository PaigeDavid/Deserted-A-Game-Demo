//FILE : bulletClass.h
//PROG : Paige Peck, edit from Dave Jones
//PURP : Class for the ship's bullets
//Inherits from class Sprite

#ifndef BULLETCLASS_H
#define BULLETCLASS_H

class Bullet : public Sprite
{
protected:
	Bullet *next;
	int bulletX;

public:
	Bullet();
	~Bullet();
	Bullet *getNext()				{return next;}
	void setNext(Bullet *nextIn)	{next = nextIn;}
	void initializeBullet(Player *);
};

//Constructor
Bullet::Bullet()
{
	//Set up basic stuff only.  The method initializeBullet
	//does the key initializations
	image = NULL;
	next = NULL;
	alive = true;
	velX = 0.0; 
    velY = 0.0;
	faceAngle = 0;
}//END constructor

//Destructor
Bullet::~Bullet()
{
}//END destructor

void Bullet::initializeBullet(Player *thePlayer)
{
	//Set bullet's image to global bitmap
	if(thePlayer->getGatling())
	{
		image = bulletsImageGatling;
		faceAngle = 0;
		bulletSpeed = 10;
	}
	else if(thePlayer->getLaser())
	{
		image = bulletsImageLaser;
		faceAngle = -90;
		bulletSpeed = 15;
	}
	else if(thePlayer->getGauss())
	{
		image = bulletsImageGauss;
		faceAngle = 0;
		bulletSpeed = 7 + thePlayer->getGaussCharge();
	}
	else if(thePlayer->getRail())
	{
		image = bulletsImageRail;
		faceAngle = 0;
		bulletSpeed = 20;
	}
	else if(thePlayer->getMissile())
	{
		image = bulletsImageMissile;
		faceAngle = 0;
		bulletSpeed = MAXVEL + 1;
	}
	else if(thePlayer->getBeam())
	{
		image = bulletsImageBeam;
		faceAngle = 0;
		bulletSpeed = 0;
	}
	else if(thePlayer->getProximity())
	{
		image = bulletsImageProximity;
		faceAngle = 0;
		bulletSpeed = -1;
	}

	//Set the object dimensions to the dimensions
	//of the actual image
	width =	al_get_bitmap_width(image);
	height = al_get_bitmap_height(image);

	x = (thePlayer->getX() + 0.5 * thePlayer->getWidth() - 0.5 * width) + 3;
	y = (thePlayer->getY() + 0.5 * thePlayer->getHeight() - 0.5 * height) - 5;

	//Set the bullets velocity values
	velX = bulletSpeed * calcAngleMoveX(0);
	velY = bulletSpeed * calcAngleMoveY(0);

}//END initializeBullet

#endif BULLETCLASS_H