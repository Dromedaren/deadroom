/*
 * arrow.cc
 *
 *  Created on: Dec 5, 2013
 *      Author: eli
 */

#include "arrow.h"
#include "zombie.h"
#include "level.h"

Arrow::Arrow(Game* gamePointer, Player* player, Level* level, std::string facing_direction, SDL_Rect playerPosition)
			: Sprite(gamePointer, "arrow", player->getArrowSprite()),
			  player(player),
			  level(level),
			  facing(facing_direction)
{
	/**
	 * arrow constructor contains settings for the arrows speed, size,
	 * sprite sheet positions and which direction it is facing when fired.
	 */

	SPRITE_SIZE = 10;
	spriteSheetRect.w = 10;
	spriteSheetRect.h = 10;

	if ( facing == "LEFT")
	{
		spriteSheetRect.x = animations.at("leftArrowAnimation").first;
		spritePosition.x = playerPosition.x;
		spritePosition.y = playerPosition.y + 15; // half the height of player sprite
	}

	if ( facing == "RIGHT")
	{
		spriteSheetRect.x = animations.at("rightArrowAnimation").first;
		spritePosition.x = playerPosition.x + 25; // whole width of player sprite
		spritePosition.y = playerPosition.y + 15; // half the player sprite
	}

	if ( facing == "UP")
	{
		spriteSheetRect.x = animations.at("upArrowAnimation").first;
		spritePosition.x = playerPosition.x + 12; // half the player width
		spritePosition.y = playerPosition.y; // current player y position
	}

	if ( facing == "DOWN")
	{
		spriteSheetRect.x = animations.at("downArrowAnimation").first;
		spritePosition.x = playerPosition.x + 12; // half of player width
		spritePosition.y = playerPosition.y + 30; // whole height of player sprite
	}
	if ( facing == "STANDING")
	{
		spritePosition.x = playerPosition.x + 12; // half of player width
		spritePosition.y = playerPosition.y + 30; // whole height of player sprite
	}

}

void Arrow::move()
{
	/**
	 * move uses the arrows direction to calculate in which direction to move.
	 */

	if ( facing == "LEFT" ) {
			spritePosition.x = spritePosition.x + arrowSpeed * direction["LEFT"];
		}

	else if ( facing == "RIGHT" ) {
		spritePosition.x = spritePosition.x + arrowSpeed * direction["RIGHT"];
	}

	if ( facing == "UP") {
		spritePosition.y = spritePosition.y + arrowSpeed * direction["UP"];
	}

	else if ( facing == "DOWN" ) {
		spritePosition.y = spritePosition.y + arrowSpeed * direction["DOWN"];
	}
	else if ( facing == "STANDING") {
		spritePosition.y = spritePosition.y + arrowSpeed * direction["DOWN"];
	}
}

bool Arrow::collision()
{
	/**
	 * iterate through all zombies on the level and check
	 * if the arrow collided with any of them, if so then do
	 * dammage on these foes!
	 */

	for ( Zombie* zombie: level->getZombies())
	{

		if (
				(spritePosition.x > zombie->getSpritePosition().x && spritePosition.x < zombie->getSpritePosition().x + zombie->getSpriteSize()) ||
				(spritePosition.x + getSpriteSize() > zombie->getSpritePosition().x && spritePosition.x + getSpriteSize() < zombie->getSpritePosition().x + zombie->getSpriteSize())
				) {
		if (
				(spritePosition.y > zombie->getSpritePosition().y && spritePosition.y < zombie->getSpritePosition().y + zombie->getSpriteSize()) ||
				(spritePosition.y + getSpriteSize() > zombie->getSpritePosition().y && spritePosition.y + getSpriteSize() < zombie->getSpritePosition().y + zombie->getSpriteSize())
				) {


				// When an arrow collides, the zombie takes damage!
				zombie->takeDamage(player->attack());
			return true;
			}
		}
	}
	return false;
}
