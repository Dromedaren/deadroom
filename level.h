/*
 * level.h
 *
 *  Created on: 13 dec 2013
 *      Author: harvog
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "game.h"
#include "player.h"
#include "zombie.h"
#include "arrow.h"
#include "UI.h"

class Level
{
public:
	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
	virtual ~Level();

	void blit();
	void events();
	void update();
	void collision_detection();
	SDL_Surface* getZombieSprite() const;
	const std::list<Zombie*>& getZombies() const;

	static int levelcount;
	struct Difficulty
		{
			unsigned int zombiesTotal,
				waveSize,
				playerDamage;
			int playerHealth;
			unsigned int playerSpeed,
				zombieDamage,
				zombieHealth,
				zombieSpeed;
			Uint32 waveCooldown;
		};

	Difficulty difficultysettings;
protected:
	Level(Game* gamePointer);
	Game* game;
	Player* player{nullptr};
	Ui* ui{nullptr};
	SDL_Surface* zombieSpriteSheet{nullptr};
	std::list<Zombie*> zombies{};
	SDL_Surface* levelBackground{nullptr};
private:
	Uint32 startTime{SDL_GetTicks()};
	Mix_Music* game_music{nullptr};
};
#endif // LEVEL_H_
