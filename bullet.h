/***********************************************************************
* Header File :
*BULLET : A class that creates a bullet
* Author :
*Adam Gehring
* Summary :
*We need the bullets to fire from the ship at a specific velocity
so this class will make that happen
************************************************************************/
#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 10.0
#define M_PI 3.1459
#define MAXBULLETS 12

#include "uiDraw.h"
#include "velocity.h"
#include "point.h"
#include "FlyingObject.h"
#include <cmath> // used for sin, cos, and M_PI



/********************************************
* Bullet
* shot from the "ship" going nowhere fast.
* sometimes hits an asteroid 
********************************************/
class Bullet : public FlyingObject
{

public:
	//constructor
	Bullet() { alive = true; life = 40; bulletsUsed = 0; }

	~Bullet();
	//Bullet(Velocity v) { speed += v; }

	// just draw it already
	virtual void draw();

	
	
	//so that the bullet will only go for 40 frames
	int life;

	int bulletsUsed;


	//ready, aim...
	void fire(Point point, float angle, Velocity shipspeed);
	

};


#endif
