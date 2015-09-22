/*
 *
 *  Created on: Nov 24, 2013
 *      Author: Harald
 *				Elias
 */

#include "level.h"
#include "arrow.h"

Player::Player(Game* gamePointer, Level* level, std::string playername)
    : Sprite(gamePointer, playername),
      game(gamePointer),
      level(level)

{
	/**
	 * the player constructor loads the player sprite sheet, sets the size of the
	 * sprite, positions on the level, where in the sprite sheet the animation starts.
	 * It also sets the player health, damage and moving speed.
	 */
    // Player specifik stats and sprite information
    spriteSheet = game->loadImage("assets/bowsheet.png");

    SPRITE_SIZE = spriteSheet->w / 8 + 5;
    spritePosition.x = game->getScreenWidth() / 2;
    spritePosition.y = game->getScreenHeight() / 2;
    spriteSheetRect.x = animations.at("downAnimation1").first;
    spriteSheetRect.y = 0;
    spriteSheetRect.w = spriteSheet->w / 8; // 25px
    spriteSheetRect.h = spriteSheet->h;

    speed = level->difficultysettings.playerSpeed;
    health = level->difficultysettings.playerHealth;
    damage = level->difficultysettings.playerDamage;
}

Player::~Player()
{
	/**
	 * player is resposible for freeing its surfaces.
	 */
    SDL_FreeSurface(spriteSheet);
    SDL_FreeSurface(arrowSheet);
    // clear both zombies and arrows when calling player destructor
    for (Zombie* zombie : level->getZombies())
    {
    	delete zombie;
    }
    for (Arrow* arrow : arrows)
    {
    	delete arrow;
    }
}

int Player::attack()
{
	/**
	 * attack deals damage equal to the players damage onto an enemy.
	 */
    return damage;
}
void Player::move()
{
    /** We use a system of direction with facing as our main way of telling the character how it should
     * move when we have pressed certain buttons
     */

    if ( facing == "LEFT" )
    {
        spritePosition.x = spritePosition.x + speed * direction["LEFT"];
    }

    else if ( facing == "RIGHT" )
    {
        spritePosition.x = spritePosition.x + speed * direction["RIGHT"];
    }

    if ( facing == "UP")
    {
        spritePosition.y = spritePosition.y + speed * direction["UP"];
    }

    else if ( facing == "DOWN" )
    {
        spritePosition.y = spritePosition.y + speed * direction["DOWN"];
    }

    else if ( facing == "STANDING")
    {
        spritePosition.x = spritePosition.x + speed * direction["STANDING"];
        spritePosition.y = spritePosition.y + speed * direction["STANDING"];
    }
}
bool Player::collision()
{
	/** We check every zombie if we have collided with it, if we did we take damage and we also "bounce" back when
	 * we take damage, to show the player an effect of being attacked.
	 */
    for ( Zombie* zombie: level->getZombies() )
    {
        if (
            (spritePosition.x > zombie->getSpritePosition().x && spritePosition.x < zombie->getSpritePosition().x + zombie->getSpriteSize()) ||
            (spritePosition.x + getSpriteSize() > zombie->getSpritePosition().x && spritePosition.x + getSpriteSize() < zombie->getSpritePosition().x + zombie->getSpriteSize())
        )
        {
            if (
                (spritePosition.y > zombie->getSpritePosition().y && spritePosition.y < zombie->getSpritePosition().y + zombie->getSpriteSize()) ||
                (spritePosition.y + getSpriteSize() > zombie->getSpritePosition().y && getSpritePosition().y + getSpriteSize() < zombie->getSpritePosition().y + zombie->getSpriteSize())
            )
            {
                takeDamage(zombie->attack());

                if ( facing == "LEFT" )
                {
                    spritePosition.x = spritePosition.x + speed * direction["RIGHT"] + 15;
                }

                else if ( facing == "RIGHT" )
                {
                    spritePosition.x = spritePosition.x + speed * direction["LEFT"] - 15;
                }

                if ( facing == "DOWN")
                {
                    spritePosition.y = spritePosition.y + speed * direction["DOWN"] + 15;
                }

                else if ( facing == "UP" )
                {
                    spritePosition.y = spritePosition.y + speed * direction["UP"] - 15;
                }

                /**This part is so that we can be attacked even if we are standing still, meaning
                 * that the zombies direction is the primary focus in order to calculate how we should
                 * interact
                 */
                else if ( facing == "STANDING")
                {
                    if ( zombie->getFacingDirection() == "LEFT" )
                    {
                        spritePosition.x = spritePosition.x + speed * direction["RIGHT"] + 15;
                    }

                    else if ( zombie->getFacingDirection() == "RIGHT" )
                    {
                        spritePosition.x = spritePosition.x + speed * direction["LEFT"] - 15;
                    }

                    if ( zombie->getFacingDirection() == "DOWN")
                    {
                        spritePosition.y = spritePosition.y + speed * direction["DOWN"] + 15;
                    }

                    else if ( zombie->getFacingDirection() == "UP" )
                    {
                        spritePosition.y = spritePosition.y + speed * direction["UP"] - 15;
                    }
                }
                // if we collided, return true
                return true;
            }
        }
    }
    //if we didnt colide with any zombies then return false
    return false;
}

void Player::events()
{
	/**
	 * this function handles our keypresses for moving, and also makes sure that we cant fire
	 * how many arrows we want, it limits our shooting speed to the allowed time interval.
	 */
    currentCooldownTime = SDL_GetTicks() - cooldownStarttime;

    /* if we, the player have more then 0 hp then we are allowed to play*/
    if (health > 0)
    {
        if ( game->getKeystates()[SDLK_a] )
        {
            if (spriteSheetRect.x == animations.at("leftAnimation1").first)
            {
                spriteSheetRect.x = animations.at("leftAnimation2").first;
            }
            else
            {
                spriteSheetRect.x = animations.at("leftAnimation1").first;
            }
            facing_for_arrow = "LEFT";
            facing = "LEFT";
        }

        else if ( game->getKeystates()[SDLK_d] )
        {
            if (spriteSheetRect.x == animations.at("rightAnimation1").first)
            {
                spriteSheetRect.x = animations.at("rightAnimation2").first;
            }
            else
            {
                spriteSheetRect.x = animations.at("rightAnimation1").first;
            }
            facing_for_arrow = "RIGHT";

            facing = "RIGHT";
        }

        else if ( game->getKeystates()[SDLK_w] )
        {
            if (spriteSheetRect.x == animations.at("upAnimation1").first)
            {
                spriteSheetRect.x = animations.at("upAnimation2").first;
            }
            else
            {
                spriteSheetRect.x = animations.at("upAnimation1").first;
            }
            facing_for_arrow = "UP";
            facing = "UP";
        }

        else if (game->getKeystates()[SDLK_s])
        {
            if (spriteSheetRect.x == animations.at("downAnimation1").first)
            {
                spriteSheetRect.x = animations.at("downAnimation2").first;
            }
            else
            {
                spriteSheetRect.x = animations.at("downAnimation1").first;
            }
            facing_for_arrow = "DOWN";
            facing = "DOWN";
        }

        /** If we press space then we shoot an arrow*/
        else if (game->getKeystates()[SDLK_SPACE])
        {
            if (currentCooldownTime > arrowCooldownTime)
            {
                arrows.push_back(new Arrow(game, this, level, facing_for_arrow, spritePosition));
                cooldownStarttime = SDL_GetTicks();
            }
            facing = "STANDING";
        }
        else
        {
            facing = "STANDING";
        }
    }

    /** if we have 0 hp, then we lost the game*/
    else
    {
        game->setGameState(game->GAMEOVER);
    }
}
std::list<Arrow*>& Player::getArrows()
{
	/**
	 * returns a list holding all of the arrows
	 */
    return arrows;
}

void Player::takeDamage(int damage)
{
	/**
	 * if we get hit we take damage equal to the damage taken.
	 */
    health -= damage;
}

int Player::getHealth()
{
	/**
	 * returns the players health.
	 */
    return health;
}

SDL_Surface* Player::getArrowSprite() const
{
	/**
	 * returns the surface holding the arrow sprite sheet.
	 */
	return arrowSheet;
}
