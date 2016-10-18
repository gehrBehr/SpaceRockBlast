#include "bullet.h"

/**********************************************
* The bullet destructor
***********************************************/
Bullet::~Bullet()
{
	kill();
	//delete;
}

/***************************************
* draw the bullet at the ship
****************************************/
void Bullet::draw()
{

	drawDot(point);
}


/***************************************
* shoot the bullets
****************************************/
void Bullet::fire(Point point, float angle, Velocity shipspeed)
{
	this->point = point;
	float dx = (BULLET_SPEED + shipspeed.getDx()) * (-sin(2 * M_PI * (angle / 360.0)));
	float dy = (BULLET_SPEED + shipspeed.getDy()) * (cos(2 * M_PI * (angle / 360.0)));
	speed.setDx(dx);
	speed.setDy(dy);

}

