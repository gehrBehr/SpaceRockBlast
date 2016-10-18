#include "FlyingObject.h"


/*******************************************
* This function is mainly used to set the
* location of the object
*********************************************/
Point FlyingObject::setPoint(Point point)
{
	this->point = point;

	return point;

}


/****************************************
* Mainly used to reset the Velocity
**************************************/
Velocity FlyingObject::setVelocity(Velocity)
{
	
	return Velocity();
}

/*************************************
* moves the object
****************************************/
void FlyingObject::advance()
{

	point.setX(point.getX() + speed.getDx());
	point.setY(point.getY() + speed.getDy());


	//add wraping here example
	if (point.getX() > 200)
	{
		point.setX(-point.getX());
	}
	else if (point.getX() < -200)
	{
		point.setX(-point.getX());
	}
	else if (point.getY() > 200)
	{
		point.setY(-point.getY());
	}
	else if (point.getY() < -200)
	{
		point.setY(-point.getY());
	}
}



