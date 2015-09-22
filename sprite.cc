/*
 * sprite.cc
 *
 *  Created on: Nov 30, 2013
 *      Author: bleh
 */
#include "arrow.h"
#include "sprite.h"

Sprite::Sprite(Game* game, std::string spritename, SDL_Surface* spriteImage)
              : game(game),
                spriteName(spritename),
                spritePosition(),
                spriteSheetRect(),
				spriteSheet(spriteImage)

{
	/**
	 * the sprite constructor sets all nessecary pointers internally, gets the sprite name
	 * creates a map holding the directions that a sprite can move, including its corresponding value
	 * that is later used to calculate and update sprite positions.
	 */
	direction["UP"] = -1;
	direction["DOWN"] = 1;
	direction["LEFT"] = -1;
	direction["RIGHT"] = 1;
	direction["STANDING"] = 0;
}

Sprite::~Sprite(){}
void Sprite::events(){}
void Sprite::move(){}
bool Sprite::boundries_collision()
{
	/**
	 * this is a virtual function handling the boundry collisions for all types of sprites.
	 */
	//if the sprite goes to far to the left or right
	if( spritePosition.x < 40)
	{
		spritePosition.x = 40;
		return true;
	}

	else if ( (spritePosition.x + SPRITE_SIZE) > game->screen->w - 40 )
	{
		spritePosition.x = game->screen->w - 40 - SPRITE_SIZE;
		return true;
	}

	// if the sprite goes too far up or down
	if( spritePosition.y < 40 )
	{
		spritePosition.y = 40;
		return true;
	}

	else if ( spritePosition.y + SPRITE_SIZE > game->screen->h - 40)
	{
		spritePosition.y = game->screen->h - 40 - SPRITE_SIZE;
		return true;
	}
	return false;
}

std::string Sprite::getFacingDirection() const
{
	/**
	 * returns the direction a sprite is currently facing.
	 */
    return facing;
}

SDL_Rect& Sprite::getSpritePosition()
{
	/**
	 * returns a sprites current position on the level.
	 */
	return spritePosition;
}

SDL_Rect* Sprite::getSpriteSheetRect()
{
	/**
	 * returns where in the sprite sheet the current animation is at.
	 */
	return &spriteSheetRect;
}

int Sprite::getSpriteSize() const
{
	/**
	 * returns the size of the sprite.
	 */
	return SPRITE_SIZE;
}

SDL_Surface* Sprite::getSprite() const
{
	/**
	 * returns the surface that holds the sprite.
	 */
	return spriteSheet;
}
