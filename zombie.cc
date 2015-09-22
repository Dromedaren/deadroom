/*
 * zombie.cc
 *
 *  Created on: 5 dec 2013
 *      Author: harvog
 */
#include "zombie.h"
#include "level.h"


Zombie::Zombie(Game* gamePointer, Level* level, std::string zombiename, Player* player)
								: Sprite(gamePointer, zombiename, level->getZombieSprite()),
								  player(player), level(level)
{
	/**
	 * the zombie constructor defaults the facing direction to down, sets the zombies health, damage and speed
	 * depending on which difficulty setting we are playing on.
	 * The constructor also randomizes the spawn location for the zombies and sets the initial animation frame in the sprite
	 * sheet.
	 */
    // Zombie specific stats and sprite information
    facing = "DOWN";
    health = level->difficultysettings.zombieHealth;
    damage = level->difficultysettings.zombieDamage;
	speed = level->difficultysettings.zombieSpeed;

	SPRITE_SIZE = 30;
	randomSpawn(); // spawn zombies on the random places it can spawn
	spriteSheetRect.x = 100;
	spriteSheetRect.y = 0;
	spriteSheetRect.w = 25;
	spriteSheetRect.h = 30;
}

void Zombie::move()
{
	/**
	 * the move function is based on the players movement so we can get some sense of artificial intelligence.
	 * However this function just finds the player in the x-axis and then walks towards the player in the y-axis,
	 * creating the effect of the zombies walking toward the player.
	 */
	if( spritePosition.x + 12 < player->getSpritePosition().x )
	{
		spritePosition.x = spritePosition.x + speed * direction["RIGHT"];
		facing = "RIGHT";
	}
	else if ( spritePosition.x > player->getSpritePosition().x + 12)
	{
		spritePosition.x = spritePosition.x + speed * direction["LEFT"];
		facing = "LEFT";
	}

	else if ( spritePosition.y <= player->getSpritePosition().y )
	{
		spritePosition.y = spritePosition.y + speed * direction["DOWN"];
		facing = "DOWN";
	}
	else if ( spritePosition.y >= player->getSpritePosition().y )
	{
		spritePosition.y = spritePosition.y + speed * direction["UP"];
		facing = "UP";
	}
}

int Zombie::attack(){
	/**
	 * when the zombies collide with the player, we take damage equal to the zombies damage.
	 */
    return damage;
}

void Zombie::events() {

	/**
	 * the zombie has its own system of movement but uses the same system for facing, and animations
	 */
	if ( facing == "LEFT" )
	{
		if (spriteSheetRect.x == animations.at("leftAnimation1").first)
		{
			spriteSheetRect.x = animations.at("leftAnimation2").first;
		}
		else
		{
			spriteSheetRect.x = animations.at("leftAnimation1").first;
		}
	}

	else if ( facing == "RIGHT" )
	{
			if (spriteSheetRect.x == animations.at("rightAnimation1").first)
			{
				spriteSheetRect.x = animations.at("rightAnimation2").first;
			}
			else
			{
				spriteSheetRect.x = animations.at("rightAnimation1").first;
			}
	}

	else if (facing == "UP" )
	{
		if (spriteSheetRect.x == animations.at("upAnimation1").first)
		{
			spriteSheetRect.x = animations.at("upAnimation2").first;
		}
		else
		{
		spriteSheetRect.x = animations.at("upAnimation1").first;
		}
	}

	else if (facing == "DOWN" )
	{
		if (spriteSheetRect.x == animations.at("downAnimation1").first)
		{
			spriteSheetRect.x = animations.at("downAnimation2").first;
		}
		else
        {
            spriteSheetRect.x = animations.at("downAnimation1").first;
		}
	}
}

int Zombie::getHealth() const
{
	/**
	 * return the health of a zombie.
	 */
	return health;
}

void Zombie::takeDamage(int damage)
{
	/**
	 * the zombie takes damage equal to the damage given.
	 */
    health -= damage;
}

bool Zombie::collision()
{
	/** We check every zombie if they collide with each other*/
	for ( Zombie* zombie: level->getZombies() )
	{
		if (
			(spritePosition.x > zombie->getSpritePosition().x && spritePosition.x < zombie->getSpritePosition().x + zombie->SPRITE_SIZE) ||
			(spritePosition.x + SPRITE_SIZE > zombie->getSpritePosition().x && spritePosition.x + SPRITE_SIZE < zombie->getSpritePosition().x + zombie->SPRITE_SIZE)
		)
		{
			if (
				(spritePosition.y > zombie->getSpritePosition().y && spritePosition.y < zombie->getSpritePosition().y + zombie->SPRITE_SIZE) ||
				(spritePosition.y + SPRITE_SIZE > zombie->getSpritePosition().y && getSpritePosition().y + SPRITE_SIZE < zombie->getSpritePosition().y + zombie->SPRITE_SIZE)
			)
			{

                return true;
            }
		}
	}
	return false;
}

void Zombie::randomSpawn()
{
	/**
	 * we have 4 different openings in the level that we can use to randomly select where we want to spawn
	 * the zombies. we use a random generator to choose a number between 1-4 , that number corresponds to
	 * coordinates on the level.
	 */
	std::uniform_int_distribution<int> random_zombie_spawn(1,4);
	int randomspawnvalue = random_zombie_spawn(game->random_generator);
	if (randomspawnvalue == 1)
	{
		spritePosition.x = randomEntryPoints.at("top").first;
		spritePosition.y = randomEntryPoints.at("top").second;
	}

	if (randomspawnvalue == 2)
	{
		spritePosition.x = randomEntryPoints.at("right").first;
		spritePosition.y = randomEntryPoints.at("right").second;
	}

	if (randomspawnvalue == 3)
	{
		spritePosition.x = randomEntryPoints.at("down").first;
		spritePosition.y = randomEntryPoints.at("down").second;
	}

	if (randomspawnvalue == 4)
	{
		spritePosition.x = randomEntryPoints.at("left").first;
		spritePosition.y = randomEntryPoints.at("left").second;
	}
}

