/*
 * sprite.h
 *
 *  Created on: Nov 30, 2013
 *      Author: bleh
 */

#ifndef SPRITE_H_
#define SPRITE_H_
#include "game.h"

using animationTable = std::map<std::string, std::pair<int, int>>;

class Sprite {
public:
	virtual ~Sprite();
	virtual void events();
	virtual void move();
	virtual bool boundries_collision();
	virtual bool collision() = 0;
    std::string getFacingDirection() const;
    SDL_Rect& getSpritePosition();
    SDL_Rect* getSpriteSheetRect();
    SDL_Surface* getSprite() const;
    int getSpriteSize() const;

protected:
	Sprite(Game* game, std::string name, SDL_Surface* spriteImage = nullptr);
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
    Game* game;

	std::map<std::string, int> direction{};
	std::string spriteName{};
	std::string facing{};
	SDL_Rect spritePosition;
	SDL_Rect spriteSheetRect;

	animationTable const animations =
		{
					{"upAnimation1", std::make_pair(0, 0)},
				    {"upAnimation2", std::make_pair(25, 0)},
				    {"rightAnimation1", std::make_pair(50, 0)},
					{"rightAnimation2", std::make_pair(75, 0)},
					{"downAnimation1", std::make_pair(100, 0)},
					{"downAnimation2", std::make_pair(125, 0)},
					{"leftAnimation1", std::make_pair(150, 0)},
					{"leftAnimation2", std::make_pair(175, 0)},
					{"upArrowAnimation", std::make_pair(0, 0)},
					{"rightArrowAnimation", std::make_pair(10, 0)},
					{"downArrowAnimation", std::make_pair(20, 0)},
					{"leftArrowAnimation", std::make_pair(30, 0)},
					{"lowHealthAnimation", std::make_pair(0, 0)},
					{"mediumHealthAnimation", std::make_pair(56, 0)},
					{"almostfullHealthAnimation", std::make_pair(112, 0)},
					{"fullHealthAnimation", std::make_pair(168, 0)}
	    };
	SDL_Surface* spriteSheet;
	int SPRITE_SIZE{0};
};
#endif //SPRITE_H
