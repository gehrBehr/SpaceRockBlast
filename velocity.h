/***********************************************************************
* Header File:
*    Velocity : A class that caculates and applys velocity
* Author:
*    Adam Gehring
* Summary:
*    We need the speed of the objects
************************************************************************/
#ifndef VELOCITY_H
#define VELOCITY_H

#include "uiDraw.h"

/********************************************
* Velocity
* Got the need for speed
********************************************/
class Velocity
{

private:
	float dx;
	float dy;

public:
	//constructors
	Velocity();
	Velocity(float changeX, float changeY);

	//the functions to constantly change the speed
	void addToDx(float dx);
	void addToDy(float dy);
        
	//get the positions of x and y
	float getDx();
	float getDy();

	// set the positions
	void setDx(float changeX);
	void setDy(float changeY);

	Velocity operator += (const Velocity & rhs);

};


#endif
