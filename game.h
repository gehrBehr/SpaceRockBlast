/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <iterator>
using namespace std;

#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "ship.h"
#include "flyingObject.h"
#include "bullet.h"
#include "rocks.h"
#include <list>


/******************************************
 *Asteroids Game
 * Sir, the possibility of successfully 
 * navigating an asteroid field is 
 * approximately three thousand, seven 
 * hundred and twenty to one!
 ****************************************/


#define CLOSE_ENOUGH 15


 /*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{

public:

float getClosestDistance(FlyingObject &obj1, FlyingObject &obj2);

	/*********************************************
* Constructor
* Initializes the game
*********************************************/
	Game(Point tl, Point br);
	~Game();



	/*********************************************
* Function: handleInput
* Description: Takes actions according to whatever
*  keys the user has pressed.
*********************************************/
	void handleInput(const Interface & ui);

/*********************************************
* Function: advance
* Description: Move everything forward one
*  step in time.
*********************************************/
	void advance();

/*********************************************
 Function: draw
* Description: draws everything for the game.
*********************************************/
	void draw(const Interface & ui);

	/**************************************************
	* gets the closest distance
	*************************************************/
//	float getClosestDistance( FlyingObject & obj1, FlyingObject & obj2);

private:
	// The coordinates of the screen
	Point topLeft;
	Point bottomRight;

	//Rack 'em up
	int score;

	//3 sounds good...
	int lives;

	//how many rocks up in here?
	int rockAmount;

	//The party don't start till I walk in
	bool gameStart;

	//display hard mode at the top
	bool hardMode;

	//Fastest thing in the galaxy
	Ship ship;
	
	std :: vector <Bullet> bullets;

	//the list of Asteroids
	std :: list <Rock*> rock;

	/*************************************************
	* Private methods to help with the game logic.
	*************************************************/
	bool isOnScreen(const Point & point);
	void advanceBullets();
	void advanceRock();
	void advanceShip();

	void handleCollisions();
	void cleanUp();
};

#endif /* GAME_H */
