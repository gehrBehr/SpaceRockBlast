/*********************************************************************
 * File: game.cpp
 author: Adam Gehring
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include "flyingObject.h"
#include <vector>
#include "point.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;
#define SCREEN_BORDER 5
#define CLOSE_ENOUGH 15

/***************************************
* GAME CONSTRUCTOR
* Set up the initial conditions of the game
***************************************/
Game::Game(Point tl, Point br)
{
	gameStart = false;
	hardMode = false;
	rockAmount = 5;
	lives = 3;

	if (gameStart)
	{
		for (int i = 0; i < rockAmount; i++)
		{
			
			rock.push_back(new BigRock);

		}
		score = 0;
		
	}

}

/****************************************
* GAME DESTRUCTOR
****************************************/
Game :: ~Game()
{
	
	

}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames. pass in the rock and the ship
 * and check if it's less than rock.radius() we know there has been a 
 * colision. 
 **********************************************************/
float Game :: getClosestDistance(FlyingObject &obj1, FlyingObject &obj2)
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/***************************************
* GAME :: HANDLE INPUT
* accept input from the user
***************************************/
void Game::handleInput(const Interface & ui)
{

	// Change the direction of the ship
	if (ui.isLeft())
	{
		ship.rotateLeft();
	}

	if (ui.isDown() && ship.isAlive())
	{
		ship.doAbarrelRoll();
		ship.invincibleTimer(3);
		//std::cerr << "IS invincible: " << ship.isInvincible();

	}
	if (ui.isUp())
	{
		ship.moveForward();
		ship.thrust = true;
	}
	else
		ship.thrust = false;

	if (ui.isRight())
	{
		ship.rotateRight();
	}

	if (ui.isV())
	{
		gameStart = true;
	}
	if (ui.isX() && (lives >= 0))
	{
		ship.invincibleTimer(18);
		ship.secondChance();
		lives--;
		
	}
	if (ui.isHardMode())
	{
		rockAmount = 21;
		hardMode = true;
	
	}
	// Check for "Spacebar"
	if (ui.isSpace() && ship.isAlive() && (ship.coolDown <= 0))
	{
		
		Bullet newBullet;
		newBullet.fire(ship.getPoint(), ship.getDirection(), ship.getVelocity());

		bullets.push_back(newBullet);
		ship.ShotsFired();


	}
}
/***************************************
* GAME :: ADVANCE
* advance the game one unit of time
* if the game has not started it will
* output the controls on the screen
***************************************/
void Game::advance()
{
	if (!gameStart)
	{
		Point help(-170, 150);
		drawText(help, "NEW GAME  Controls: Press \"v\" To begin. ");
		Point help2(-170, 130);
		drawText(help2, "Use the arrow keys to move. Press Space to Fire.");
		Point help3(-170, 110);
		drawText(help3, "Press X to use a life.");
		Point help4(-170, 80);
		drawText(help4, "Special: Press H for Hard MODE,");
		Point help5(-170, 60);	
		drawText(help5, "Press Down To DO A BARREL ROLL!");


	}
	else if (gameStart)
	{
		advanceBullets();
		advanceRock();
		advanceShip();

		handleCollisions();
		cleanUp();
	}
}

/*********************************************
* GAME :: DRAW
* Draw everything on the screen
*********************************************/
void Game::draw(const Interface & ui)
{
	if (ship.isAlive() && lives >= 0)
	{
		ship.draw();

	}
	if (ship.isInvincible())
	{
		drawCircle(ship.getPoint(), 10);
	}
	//checks for amount of lives that the ship has n stuff.
	if (lives > 0)
	{
		Point liveCounter(-180, 170);
		drawToughBird(liveCounter, 10, (lives));
	}
	else if( lives < 0)
	{
		Point onScreen(-30,0);
		drawText(onScreen, "GAME OVER");
		onScreen.setX(-88);
		onScreen.setY(-20);
		drawText(onScreen, "HIGH SCORE: 14358283303");
		onScreen.setY(-40);
		drawText(onScreen, "Your Score:");
		onScreen.setX(28);
		drawNumber(onScreen, score);

	}

	//if the game has entered HardMode
	if (hardMode)
	{
		Point onScreen(64, 190);
		drawText(onScreen, "HARD MODE Activated.");
	}
	

	list <Rock*> ::iterator it;

	for (it = rock.begin(); it != rock.end(); it++)
	{
		(*it)->draw();
	}
	if (rock.size() < rockAmount)
	{

		BigRock* temp = new BigRock;
		temp->draw();
		rock.push_back(temp);
	}
	
	// draw the bullets, if they are alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}

	// Put the score on the screen
	Point scoreLocation(-195, 195);
	drawNumber(scoreLocation, score);


}

/****************************************************
* Checks to see if the objects are within the bounds
* of the screen.
*****************************************************/
bool Game::isOnScreen(const Point & point)
{
	return true;
}

/***************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
***************************************/
void Game::advanceBullets()
{

	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{

		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();
			bullets[i].life--;

			if (bullets[i].life <= 0)
			{
				// the bullet has 40 frames
				bullets[i].kill();
			}

		}
	}
}

/**************************************************************************
* GAME::ADVANCE ROCK
*
* 1. If there are no rocks, create one with some probability
* 2. If there is a rock, and it's alive, advance it
* 3. Check if the rock has gone of the screen, and what side so that we can wrap it.
*************************************************************************************/
void Game::advanceRock()
{
	list <Rock*> :: iterator it;
	
	for ( it = rock.begin(); it != rock.end(); it++)
	{

		// we have a rock, make sure it's "alive"
		if ((*it)->isAlive())
		{
			// move it forward
			(*it)->advance();
		}
			// check if the rock has been hit
		else
		{
			(*it)->kill();
			
		}
		
	}
}

/**************************************************************************
* GAME::ADVANCE Ship
*
* move the ship if it's alive and is moving
*************************************************************************************/
void Game::advanceShip()
{
	if (ship.isInvincible())
	{
		ship.invincibleTimer(-1);
	}

	/*******************************************
	* runs a check so that the ship can't shoot
	* indefinately. About 20 frames cooldown.
	********************************************/
	if (ship.maxBullets())
	{
		ship.coolDown = 22;
		ship.reloadGun();

	}
	if (ship.coolDown != 0)
	{
		// Don't fire unless the cooldown period has expired
		ship.coolDown--;

		Point reload;
		reload.setX(0);
		reload.setY(180);
		drawText(reload, "RELOADING");

	}
	if (ship.isAlive())
	{
		// advance the ship
		ship.advance();
	}
	else if (!ship.isAlive() || lives < 0)
	{
		ship.kill();
	}
}

/*****************************************************
* Function: Handle Collisions
* reason: we need to be constantly checking
* for instances when the ship hits the fan. I mean,
* if the ship hits a rock or if the bullets hit rocks
******************************************************/
void Game::handleCollisions()
{
	list <Rock*> ::iterator R;

	for (R = rock.begin(); R != rock.end(); R++)
	{
		//if the ship hits the rock
		if (fabs(ship.getPoint().getX() - (*R)->getPoint().getX())
			< CLOSE_ENOUGH &&
			fabs(ship.getPoint().getY() - (*R)->getPoint().getY())
			< CLOSE_ENOUGH)
		{
			if (ship.isAlive()) //if it's alive and not invincible
			{
			
				if (ship.isInvincible() && (ship.getVelocity().getDx() != 0))
				{
					std::cerr << "Killed the rock but not the ship.\n";
					score += (*R)->breakApart(rock);
					(*R)->kill();
				}
				else if(ship.isInvincible() && ship.getVelocity().getDx() == 0)
				{
					std::cerr << "Just Used a life but got hit...\n";
					/*ship.kill();
					score += (*R)->breakApart(rock);
					(*R)->kill();*/
					break;
				}
				else
				{
					std::cerr << "Wasn't Rock-Proof...\n";
					ship.kill();
					score += (*R)->breakApart(rock);
					(*R)->kill();
				}
				
			}

		}
		for (int i = 0; i < bullets.size(); i++)
		{
			if (fabs(ship.getPoint().getX() - (*R)->getPoint().getX())
				< CLOSE_ENOUGH &&
				fabs(ship.getPoint().getY() - (*R)->getPoint().getY())
				< CLOSE_ENOUGH)
			{
				if (!ship.isInvincible())
				{
					std::cerr << "Killed When not moving\n";
					ship.kill();
					(*R)->kill();
				}
				
			}
			if (bullets[i].isAlive())
			{
				if (fabs(bullets[i].getPoint().getX() - (*R)->getPoint().getX())
					< CLOSE_ENOUGH &&
					fabs(bullets[i].getPoint().getY() - (*R)->getPoint().getY())
					< CLOSE_ENOUGH)
				{
					//we hit a rock 
					//kill the bullet and the rock
					bullets[i].kill();

					//increment the score
					score += (*R)->breakApart(rock);
					(*R)->kill();
					
				}
			}
			
		}
	
	}
	cleanUp();
	
}

/***********************************************
*
***********************************************/
void Game::cleanUp()
{
	vector<Bullet>::iterator bulletIt = bullets.begin();
	list<Rock*> ::iterator rockIt = rock.begin();

	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!bullet.isAlive())
		{
			
			// remove from list and advance
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
		}
	}

	//goes through and distroys all the rocks
	while (rockIt != rock.end())
	{
		Rock* prock = *rockIt;

		if (!prock->isAlive())
		{
			delete[] prock;
			// remove from list and advance
			rockIt = rock.erase(rockIt);
		}
		else
		{
			rockIt++; // advance
		}
	}
}
