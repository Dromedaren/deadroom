/*
 * level.cc
 *
 *  Created on: 13 dec 2013
 *      Author: harvog
 */

#include "level.h"
int Level::levelcount = 0;

Level::Level(Game* gamePointer) : difficultysettings(), game(gamePointer),
								  zombieSpriteSheet(game->loadImage("assets/zombiesheet.png"))
{
	/**
	 * level constructor loads the game music, sets the initial volume and increases that static counter
	 * level count by one. It loads the zombie sprite sheet, and stores the game "engine" pointer internally.
	 */

	game_music = game->loadMusic("assets/confuze.mp3");
	++levelcount;
}
Level::~Level()
{
	/**
	 * level is resposible for freeing its surfaces and music.
	 */
	SDL_FreeSurface(zombieSpriteSheet);
	SDL_FreeSurface(levelBackground);
	Mix_FreeMusic(game_music);
}

void Level::blit()
{
	/**
	 * blit will draw the level, arrows, zombies and the user interface.
	 */
		game->applyImage(0, 0 ,levelBackground, game->screen);
		game->applyImage(player->getSpritePosition().x, player->getSpritePosition().y , player->getSprite(), game->screen, player->getSpriteSheetRect());

		/* If there are arrows then draw them */
		for (Arrow* arrow : player->getArrows())
		{
			game->applyImage(arrow->getSpritePosition().x, arrow->getSpritePosition().y, player->getArrowSprite(), game->screen, arrow->getSpriteSheetRect());
		}

		/* If there are zombies alive draw them */
		for (Sprite* zombie : zombies)
		{
			game->applyImage(zombie->getSpritePosition().x, zombie->getSpritePosition().y, zombieSpriteSheet, game->screen, zombie->getSpriteSheetRect());
		}

	game->applyImage(200, 15, ui->getSprite(), levelBackground, ui->getSpriteSheetRect());
	game->applyImage(35, 20, ui->getUIText(), levelBackground);
}

void Level::events()
{
	/**
	 * events goes through every object in the level and checks each objects
	 * own events. it handles spawning of zombies, updating health, etc.
	 */

	if (difficultysettings.zombiesTotal <= 0)
		{
		std::cout << "level :" << levelcount << std::endl;
			game->setGameState(game->COMPLETELEVEL);
		}

        /**
         * Checks that we havn't reached max amout of zombies spawned and spawns a wave of zombies every x seconds
         */
			if(difficultysettings.zombiesTotal > zombies.size())
			{
                          if (difficultysettings.waveSize + zombies.size() > difficultysettings.zombiesTotal)
				{
                                  difficultysettings.waveSize = difficultysettings.zombiesTotal - zombies.size();
				}
				else
				{
					if(SDL_GetTicks() % difficultysettings.waveCooldown > difficultysettings.waveCooldown-300 || zombies.size() == 0)
					{
						for (unsigned int i{0}; i < difficultysettings.waveSize; i++)
						{
							zombies.push_back(new Zombie(game, this, "zombie"+i, player));
						}
						difficultysettings.waveSize++;
					}
				}
			}

			/* If a zombie has 0 health, remove it from the game,
			 * this is an event that should be handeled before any type of
			 * collision detection
			*/
			for ( std::list<Zombie*>::iterator it = zombies.begin(); it != zombies.end();)
			{
				if((*it)->getHealth() < 1)
				{
					delete (*it);
					zombies.erase(it++);
					difficultysettings.zombiesTotal--;
				}
				else
				{
					++it;
				}
			}

			player->events();

			for (Zombie* zombie : zombies)
			{
				zombie->events();
			}
			ui->events();
}

void Level::update()
{
	/**
	 * update does the actual moving of all objects on screen
	 * it moves the player, arrows, zombies and everything else that is moving.
	 */

	player->move();

		if (player->getArrows().size() != 0)
		{
			for (Arrow* arrow : player->getArrows())
			{
			arrow->move();
			}
		}

		for (Zombie* zombie : zombies)
		{
			zombie->move();
		}
	}

void Level::collision_detection()
{
	/**
	 * every type of movable object has to stay inside the screen area so we call
	 * boundry collisions and each objects own collision detection functions to
	 * determine what action to take when objects collide with walls or other objects.
	 */

	player->boundries_collision();
	player->collision();

	for (Zombie* zombie : zombies)
	{
		zombie->boundries_collision();
		zombie->collision();
	}

        /**
         * Check the players arrows for any collisions with boundries or enemies
         */
		for ( std::list<Arrow*>::iterator it = player->getArrows().begin(); it != player->getArrows().end();)
		{
			if((*it)->boundries_collision())
			{
				delete (*it);
				player->getArrows().erase(it++);
			}
			else if ((*it)->collision())
			{
				delete(*it);
				player->getArrows().erase(it++);
			}
			else
			{
				++it;
			}
		}
	}

SDL_Surface* Level::getZombieSprite() const
{
	/**
	 * returns the zombie sprite
	 */

	return zombieSpriteSheet;
}

const std::list<Zombie*>& Level::getZombies() const
{
	/**
	 * returns a list of zombies that exist
	 * in-game.
	 */
	return zombies;
}
