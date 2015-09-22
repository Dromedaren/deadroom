/*
 * level1.cc
 *
 *  Created on: 13 dec 2013
 *      Author: harvog
 */
#include "newlevel.h"
#include <string>
#include <sstream>
#include <cctype>

Newlevel::Newlevel(Game* gamePointer) : Level(gamePointer)
{
	if (levelcount == 1)
	{
		difficultysettings = { 10, 3, 2, 10, 6, 1, 1, 3, 10000 };
		levelBackground	= gamePointer->loadImage("assets/level1.png");
	}
	else if (levelcount == 2)
	{
		difficultysettings = { 20, 4, 2, 10, 6, 1, 2, 4, 20000 };
		levelBackground	= gamePointer->loadImage("assets/level2.png");
	}
	else if (levelcount == 3){
		difficultysettings = { 50, 4, 2, 15, 4, 2, 2, 5, 30000 };
		levelBackground	= gamePointer->loadImage("assets/level1.png");
	}

        else {
          difficultysettings = { 50, 4, 2, 15, 3, 2, 6, 2, 30000 };
          levelBackground = gamePointer->loadImage("assets/level1.png");
        }

	player = new Player(gamePointer, this, "Elias");
	zombies.push_back(new Zombie(gamePointer, this, "zombie", player));
	zombies.push_back(new Zombie(gamePointer, this, "zombie", player));
	zombies.push_back(new Zombie(gamePointer, this,"zombie", player));
	ui = new Ui(gamePointer, player);
}

Newlevel::~Newlevel()
{
	std::cout << "destroying level before creating new one" << std::endl;
	delete ui;
	delete player;
}
