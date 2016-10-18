#include "ship.h"

// Put your ship methods here
/******************************************
* draw the ship in the center
*********************************************/
void Ship::draw()
{

	drawShip(point, direction, thrust);

}

/*******************************************************
* lets the game know if the ship can be killed
********************************************************/
bool Ship::isInvincible()
{
	return invincible;

}

/*************************************************
* Function: used to make the ship invincible
* the ship becomes invincible under two conditions:
* when it is doing a barrel roll, and when we just barely
* came back to life.
*************************************************/
void Ship::invincibleTimer(int fps)
{
	invincible += fps;

}

/**************************************
* subtracts from the rotation
***************************************/
void Ship::rotateLeft()
{
	direction += ROTATE_AMOUNT;
}

/*****************************************
*
****************************************/
void Ship::rotateRight()
{
	direction -= ROTATE_AMOUNT;
}

/**************************************************
* when the maximum number if bullets have been shot
* set the gun to reloading
************************************************/
bool Ship::maxBullets()
{
	if (bulletShot >= 12)
		return true;
	else
		return false;
}

/*****************************************
* Function: to move the ship in the direction
* it is facing we have the direction and 
* some lovely trig functions to give us the 
* correct angle.
*****************************************/
void Ship::moveForward()
{

	//std :: cout << "move!";
	float dx = THRUST_AMOUNT *(-sin(2* M_PI * (direction / 360.0)));
	float dy = THRUST_AMOUNT *(cos(2 * M_PI * (direction / 360.0)));
	
	speed.addToDx(dx);
	speed.addToDy(dy);


}

/****************************************
* does a complete 360 while shooting out a 
* sheild deflector for a moment.
*****************************************/
void Ship::doAbarrelRoll()
{
	direction -= 90;
	drawSacredBird(point, 10);
}

/************************************************
* Sets the ship back to it's start place with 
* limited invincibility
************************************************/
void Ship::secondChance()
{
	alive = true;
	point.setX(0);
	point.setY(0);
	speed.setDx(0);
	speed.setDy(0);
	direction = 0;
	invincible = 20;

		//std::cerr << "IS INVINCIBLE: " << invincible << "\n";
}

/******************************************
* increment that one more bullet has been fired
******************************************/
void Ship::ShotsFired()
{
	bulletShot++;
}

/*****************************************
* sets the bullets fired back to zero instead of
* putting more bullets in the gun.
*****************************************/
void Ship::reloadGun()
{
	bulletShot = 0;
}

/*********************************************
*
***********************************************/
int Ship::getDirection()
{
	return direction;
}

