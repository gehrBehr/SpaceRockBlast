#include "rocks.h"

/*******************************************************
* because we want the rocks to start in diffent locations
* it will put it at the top left right or bottom
*****************************************************/
int Rock :: boundries()
{
	int wall = random(1, 5);

	switch (wall)
	{
	case 1:
		edge.setX(-200);
		edge.setY(random(-200,200));
		return 1;
		break;
	case 2:
		edge.setX(random(-200, 200));
		edge.setY(200);
		return 1;
		break;
	case 3:
		edge.setX(200);
		edge.setY(random(-200, 200));
		return 1;
		break;
	case 4:
		edge.setX(random(-200, 200));
		edge.setY(-200);
		return 1;
		break;
	default:
		break;
		return 0;
	}
	
}

/*********************************************
* The defalut draw is blank by design
*********************************************/
void Rock::draw()
{
}

/************************************************
* starts the rocks moving somewheres
*************************************************/
void Rock::launchRocks()
{
	point = edge;
	//Point p(random(-200, 200), random(-200, 200));
	speed.setDx(BIG_ROCK_SPEED * (cos(M_PI * (angle / 360.0))));
	speed.setDy(BIG_ROCK_SPEED * (-sin(M_PI * (angle / 360.0))));
	

}


/*****************************************************
* GET_TYPE: lets the game file know what the rock's Identity
* is. Like a SSN, but different.
*******************************************************/
int Rock::getType()
{
	return 1;
}
/*******************************************
*DRAW: draws a big floating space rock.
********************************************/
void BigRock::draw()
{
	spin += 2;
	drawLargeAsteroid(point, spin);
}

/*************************************************
* Function:Break
* make new asteroids added on to the list.
* each rock needs it's own type of break apart.
* if the rock it big add two med and one small etc.
*************************************************/
int BigRock::breakApart(list<Rock*> & rocks)
{
	MediumRock* temp1 = new MediumRock(point,(Velocity(speed.getDx(),(speed.getDy()+1))));
	MediumRock* temp2 = new MediumRock(point, (Velocity(speed.getDx(), (speed.getDy() - 1))));
	SmallRock* numero1= new SmallRock(point, (Velocity((speed.getDx() + 1), speed.getDy())));

	rocks.push_back(temp1);
	rocks.push_back(temp2);
	rocks.push_back(numero1);
	kill();
	
	return 20;


}

/****************************************************
* Draws a Med rock
*****************************************************/
void MediumRock::draw()
{
	spin += 5;
	drawMediumAsteroid(point, spin);
}

/*************************************************
////get the rocks location or point
////Point rightHere = (*R).getPoint();
//////int type = (*R).getType();
////Velocity duhSpeed = (*R).getVelocity();
////createRock(rightHere, type, duhSpeed);
*************************************************/
int MediumRock::breakApart(list<Rock*> & rocks)
{

	SmallRock* numero1 = new SmallRock(point, (Velocity((speed.getDx() + 3), speed.getDy())));
	SmallRock* numero2 = new SmallRock(point, (Velocity((speed.getDx() - 3), speed.getDy())));

	rocks.push_back(numero2);
	rocks.push_back(numero1);
	kill();
	return 50;
}

/************************************************
* draw a small rock thingy
***************************************************/
void SmallRock::draw()
{
	spin += 10;
	drawSmallAsteroid(point, spin);
}

/*************************************************************
* when it breaks apart it just dies...
*************************************************************/
int SmallRock::breakApart(list<Rock*> & rocks)
{
	kill();
	return 100;
}
