#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPEED 1

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define M_PI 3.1459

#include "velocity.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include <list>
#include <cmath>
using namespace std;

/**********************************************************
* Class ROCK This is the defalut rock class that is a flying
* object. It sets the start point to somewhere on the screen.
**********************************************************/
class Rock : public FlyingObject
{
  protected:
   int radius;
   Point edge;
   int spin;
   float angle;

  public:
	  Rock()
	  {

		  //std::cerr << "Construct\n";
		  angle = random(0.0, 360.0);
		  boundries();
		  point = edge;
		 launchRocks();

	  }
	  /********************************************
	  * Function: chooses a random boundry for the
	  * rock to appear.
	  *******************************************/
	  int boundries();
	  virtual void draw();

	  virtual int getType() = 0;
	  void launchRocks();

	  
	  virtual int breakApart(list<Rock*> & rocks) = 0;



};

/***********************************************
 * BIG ROCK
 * I'm gonna get closer.
 * Closer!
 ************************************************/
class BigRock : public Rock
{
public:
	BigRock() {
	speed.setDx(BIG_ROCK_SPEED * (-cos(M_PI / 180.0 * angle)));
	speed.setDx(BIG_ROCK_SPEED * (sin(M_PI / 180.0 * angle))); //launchRocks();
	}
	void draw();

	//returns the type of rock
	int getType() { return 1; }
	virtual int breakApart(list<Rock*> & rocks);


};

/************************************
* Medium size two should be created
* when the big rock breaks
************************************/
class MediumRock : public  Rock
{

public:
	MediumRock() {}
	MediumRock(Point p, Velocity v) { speed = v; point = p; }

	void draw();

	int getType() { return 2; }
	virtual int breakApart(list<Rock*> & rocks);

};

/************************************
* Small size gets distroyed when hit
* creates two when the MED rock is broken
****************************************/
class SmallRock : public Rock
{
public:
	SmallRock(){}
	SmallRock(Point p, Velocity v) { speed = v; point = p; }

	void draw();
	int getType() { return 3; }
	virtual int breakApart(list<Rock*> & rocks);

};



#endif /* rocks_h */
