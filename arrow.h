/*
 * arrow.h
 *
 *  Created on: Dec 5, 2013
 *      Author: eli
 */

#ifndef ARROW_H_
#define ARROW_H_

#include "player.h"

class Arrow: public Sprite {
public:
	Arrow(Game* gamePointer, Player* player , Level* level, std::string facing_direction, SDL_Rect playerPosition);
	Arrow(const Arrow&) = delete;
	Arrow& operator=(const Arrow&) = delete;
	void move();
	bool collision();
	void blit();
private:
	Player* player;
	Level* level;
	std::string facing;
	const unsigned int arrowSpeed{20};
};
#endif /* ARROW_H_ */
