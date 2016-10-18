#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#define M_PI 3.1459

#include "flyingObject.h"
#include "point.h"

/************************************
* CLASS: SHIP
* Spins and moves in the direction the 
* cone is facing.
* "DO A BARREL ROLL!" 
*************************************/
class Ship : public FlyingObject
{

protected:
	
	int direction;
	int bulletShot;
	int invincible;

public:
	Ship() { alive = true; point.setX(0); point.setY(0); thrust = false; direction = 0;
		invincible = false; bulletShot = 0; coolDown = 0; }

	//"tells" the game where the ship "is"
	Point getPoint() { return point; }

	//draws a couple of lines for a ship
	void draw();

	//can't touch this
	bool isInvincible();

	//changes the ship's invincibliity
	void invincibleTimer(int fps);


	//directional movements for the ship as controled by keys
	void rotateLeft();
	void rotateRight();
	void moveForward();

	//thanks Pepe...
	void doAbarrelRoll();

	//Bring me back to life!!
	void secondChance();

	//increments the #of bullets fired
	void ShotsFired();

	//kind of reverse: sets the bullets fired to zero
	void reloadGun();

	//gets the angle the ship is facing
	int getDirection();

	//cooldown timer
	int coolDown;

	//fire in the back
	int thrust;

	//lets us know if we are reloading
	bool maxBullets();
};

#endif /* ship_h */
