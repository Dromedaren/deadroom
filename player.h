/*
 * player.h
 *
 *  Created on: Nov 24, 2013
 *      Author: Harald
 *				Elias
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "timer.h"

class Arrow;
class Player: public Sprite {
public:
	Player(Game* game, Level* level, std::string playername);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	~Player();

	void move();
	void takeDamage(int damage);
	void events();
	int getHealth();
    int attack();
	bool collision();
	SDL_Surface* getArrowSprite() const;

    std::list<Arrow*>& getArrows();


private:

    /* These variables make it easier to handle cooldowns
     * so that we cant spam arrows all over the screen
    */
	Uint32 cooldownStarttime{0};
	Uint32 arrowCooldownTime{1000}; // 1 second wait time between arrows
	Uint32 currentCooldownTime{SDL_GetTicks() - cooldownStarttime};

	std::list<Arrow*> arrows{};
	SDL_Surface* arrowSheet{game->loadImage("assets/arrowsheet.png")};

    Game* game;
    Level* level;

	int health{0};
	int damage{0};
	int speed{0};
	std::string facing{"DOWN"};
	std::string facing_for_arrow{"DOWN"};
};
#endif // PLAYER_H
