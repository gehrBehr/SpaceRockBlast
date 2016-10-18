#pragma once
/***********************************************************************
* Header File :
*FLYING OBJECT : A class that is anything that flies around
* Author :
*Adam Gehring
* Summary :
* everything that flies will be derived from this
************************************************************************/
#ifndef FLYING_Object
#define FLYING_Object

#include "uiDraw.h"
#include "velocity.h"
#include "point.h"
#include <iostream>

/********************************************
* UFO
* anything that flies. currently unidentified
********************************************/
class FlyingObject
{

protected:
	Velocity speed;
	Point point;
	bool alive;

public:
	//kill it when its hit
	void kill() { alive = false; }

	//Staying alive! ha ah ah ah
	bool isAlive() { return alive; }

	//getters and setters for location
	Point getPoint() { return point; }
	Point setPoint(Point point);

	//getters and setters for speed
	Velocity getVelocity() { return speed; }
	Velocity setVelocity(Velocity);

	//moves and shakes
	void advance();



};


#endif
