#include "velocity.h"

/**************************************************
* Defalut constructor sets the change in x and y to 0
* because when we start we aren't moving
***************************************************/
Velocity::Velocity()
{
	dx = 0.0;
	dy = 0.0;
}

/***************************************************
* the non defalut takes two perameters x and y
***************************************************/
Velocity::Velocity(float changeX, float changeY)
{
	dx = changeX;
	dy = changeY;
}

/************************************************
* these will continualy add to the x values
*******************************************/
void Velocity::addToDx(float dx)
{
	this->dx += dx;
}


/*************************************************
* these will continualy add to the y values
**************************************************/
void Velocity::addToDy(float dy)
{
	this->dy += dy;


}

/********************************************
* Non member functions can only get the x pos
* with this function
*********************************************/
float Velocity::getDx()
{
	return dx;
}

/********************************************
* Non member functions can only get the y pos
* with this function
*********************************************/
float Velocity::getDy()
{
	return dy;
}

/*******************************************
* gives the x value a new location
********************************************/
void Velocity::setDx(float changeX)
{
	dx = changeX;
}

/*******************************************
* gives the y value a new location
********************************************/
void Velocity::setDy(float changeY)
{
	dy = changeY;
}

/*******************************************************
* Overloads the operator to add velocities together.
********************************************************
Velocity Velocity::operator+=(const Velocity & rhs)
{
	setCents(rhs.getCents() + cents);
	setDollars(rhs.getDollars() + dollars);
	handleOverflow();


Velocity v();

	return m;
	*/