//FILE : bulletstackmgt.h
//PROG : Paige Peck, edit from Dave Jones
//PURP : Functions to manage the stack of bullets
//Since each bullet is part of a stack, the management
//of the stack needs to be separate from the class

#ifndef BULLETSTACKMGT_H
#define BULLETSTACKMGT_H

#include <cmath>

//Declare the bullet stack as global, because it needs to be
//identifiable by the following functions, which are sometimes
//called by objects.  This is a pointer to the top of the stack
//of laser bullets.  The pointer is to the top of the stack, and
//then each bullet in the linked list points to the next one.
Bullet *bulletStack = NULL;

//Declare the player as global:  the stack functions need to
//know about the ship for positioning a new bullet
Player *player = NULL;

//Create a new bullet and initialize it
//The top of the stack is passed in, and this new object
//becomes the new top of the stack.
Bullet *createBullet(Bullet *parent)
{
	Bullet *tmp = new Bullet;

	//Set its next pointer to the one passed in
	tmp->setNext(parent);
 
	//Set up important members
	tmp->initializeBullet (player);

	return tmp;
}//END createBullet

//Weapon fired. Create the laser bullet
void fireLaser()
{
	bulletStack = createBullet (bulletStack);
}

//Update a sprite's X, Y coordinates
//Currently applies to only bullets
void updateSprite(Bullet *thisBullet)
{
	//Memorize previous positions in case it's needed
	thisBullet->setOldXY();

	//Update current X & Y
	thisBullet->updatePosition();

	//Now, need to check to see if bullet has flown off screen if its not a beam
	//If so, set alive to false
	//DOESN'T NEED Y CHECK, BUT JUST FOR TESTING
	if(!player->getBeam())
	{
		if ((thisBullet->getX() < 0) || (thisBullet->getY() < 0) ||
			(thisBullet->getX() > SCREEN_WIDTH) || (thisBullet->getY() > SCREEN_HEIGHT))
		{
			thisBullet->setAlive(false);
			if(proximity)
			{
				--proximityAmount;
			}
		}
	}
	else
	{
		if(!keys[SPACE] && !player->getBeamIsShooting())
		{
			thisBullet->setAlive(false);
		}
		if(player->getBulletKill())
		{
			thisBullet->setAlive(false);
			player->setBulletKill(false);
		}
	}
}//END updateSprite

//Update the stack of bullets passed in
void updateSprites(Bullet *thisBullet)
{
	//int ct;

	//Loop through the stack and update all bullets.
	//This terminates when it reaches the bottom of the stack,
	//since the thisBullet pointer is then NULL.
	while (thisBullet)
	{
		//Updates this sprite's coordinates & check for going offscreen
		updateSprite(thisBullet);


		//COLLISION CHECK


		//Go to next sprite in the stack
		thisBullet = thisBullet->getNext();
	}
}//END updateSprites

//Check the entire stack to clear out any "deadwood".
//Parameters:	thisSprite - the top of the stack currently
//				all - if FALSE, then just clean out certain sprites
//					  if TRUE, then clean out the entire stack
//Returns the top of stack, in case it has changed.
Bullet *cleanSprites (Bullet *thisSprite, bool all)
{
	Bullet *tmp;
	Bullet *top;

	top = thisSprite;
	tmp = NULL;

	//Loop through all the sprites
	while (thisSprite)
	{
		if (!(thisSprite->getAlive()) || all)	//If the Sprite is dead, 
		{										//or we are killing all Sprites
			if (tmp)
			{
				tmp->setNext(thisSprite->getNext());
				delete thisSprite;
				thisSprite = tmp->getNext();
			}
			else
			{
				top = thisSprite->getNext();
				delete thisSprite;
				thisSprite = top;
			}
		}
		else
		{
			tmp = thisSprite;
			thisSprite = thisSprite->getNext();
		}
	} //END WHILE
	return top;
}//END cleanSprites

//Draw all images for the sprite stack passed in
void drawBullets(Bullet *thisSprite)
{
	while (thisSprite)
	{
		thisSprite->draw(player->getX() + player->getWidth()/2 + 5, player->getY() + player->getHeight()/2 - 5, 
			player->getBeam(), player->getBeamScaleX(), player->getBeamCenterX());
		thisSprite = thisSprite->getNext();
	}
}//END drawSprites

//Collision detector based on 80% reduction in bounding box
//Returns TRUE if collision, FALSE if not
//bool spriteCollide (Sprite *sprite1, Sprite *sprite2)
//{	

//}//END spriteCollide


#endif